#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define AUTOCOMPLETED "autocompleted.txt"

char ErrorBracket;
char CorrectBracket;

struct STACK {
    char bracket;
    struct STACK *next;
};
struct STACK *top = NULL;

int isStackEmpty() {
    return top==NULL;
}

void push(char data) {
    struct STACK *nn;
    nn = (struct STACK*)malloc(sizeof(struct STACK));
    nn->bracket = data;
    if (top == NULL) {
        nn->next = NULL;
    } else {
        nn->next = top;
    }
    top = nn;
}

void pop() {
    struct STACK *temp;
    temp = top;
    if (top->next == NULL) {
        top = NULL;
    } else {
        top = top->next;
    }
    free(temp);
}

void popAll() {
    while (top != NULL) {
        pop();
    }
}

char stacktop() {
    return top->bracket;
}

void getCorrectBracket() {
    switch (stacktop()) {
        case '[':
            CorrectBracket = ']';
            break;
        case '(':
            CorrectBracket = ')';
            break;
        case '{':
            CorrectBracket = '}';
            break;
    }
}

void autocomplete(char *filename) {
    char CH;
    FILE *fp = fopen(filename, "r");
    FILE *ac = fopen(AUTOCOMPLETED,"w");
    while ((CH = fgetc(fp)) != EOF) { 
        fputc(CH, ac);
    }
    while (!isStackEmpty()) {
        getCorrectBracket();
        fputc(CorrectBracket,ac);
        pop();
    }
    fclose(fp);
    fclose(ac);
}

int main() {
    char filename[100];
    while (1) {
        int pos = 0;
        int line = 1;
        char CH;
        int flag = 1;
        printf("Enter the input file (type 'EXIT' to exit the program): ");
        fgets(filename,sizeof(filename),stdin);
        filename[strcspn(filename, "\n")] = '\0';
        if (strcmp(filename, "EXIT") == 0) {
            printf("\nThank you for using the program!\n");
            return 0;
        }
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Could not open file.\n");
            continue;
        }
        while ((CH = fgetc(fp)) != EOF) { 
            pos++;
            if (CH == '\n') {
                line++;
                pos = 0;
            }
    
            switch (CH) {
                case '{': case '(': case '[':
                    push(CH);
                    break;
                
                case '}':
                    if (isStackEmpty() || stacktop() != '{') {
                        flag = 0;
                    } else {
                        pop();
                    }
                    break;
                
                case ')':
                    if (isStackEmpty() || stacktop() != '(') {
                        flag = 0;
                    } else {
                        pop();
                    }
                    break;
                
                case ']':
                    if (isStackEmpty() || stacktop() != '[') {
                        flag = 0;
                    } else {
                        pop();
                    }                
                break;
            }
            if (!flag) {
                ErrorBracket = CH;
                break;
            }
        }
        fclose(fp);

        if (flag && isStackEmpty()) {
            printf("\nBalanced brackets.\n\n");
        } else if (flag && !isStackEmpty()) {
            pos++;
            getCorrectBracket();
            printf("\nUnexpected end of input.\nExpected a '%c' for '%c'\nLine %d, position %d.\nAutocompleted input at %s\n\n", CorrectBracket, stacktop(), line, pos,AUTOCOMPLETED);
            autocomplete(filename);
        } else {
            printf("\nUnexpected '%c'\nLine %d, position %d.\n\n", ErrorBracket, line, pos);
            popAll();
        }
    }
    return 0;
}
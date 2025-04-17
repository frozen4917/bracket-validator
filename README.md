# bracket-validator
C program to check if an input file has balanced brackets or not.

## Features
- Implemented using Stack (using Linked List)
- Accepts files as inputs
- Autocompletes incomplete file inputs
- Detects line and position of error

## Bracket Validations
The program checks for opening brackets `(`, `{`, `[` and pushes them into the stack. On encountering a closing bracket `)`, `}`, `]`, it makes sure that the stack is not empty, and the top of the stack has the correct opening bracket. It pops the opening bracket if the condition is satisfied.

Program returns **Balanced Brackets** if the stack is empty and no mismatched brackets were detected.

## Example Inputs
### info1.txt
```js
{
  "info": [
    {
      "name": "Alice",
      "scores": (98, 87, [45, 78])
    },
    {
      "name": "Bob",
      "scores": (76, 90, [33, 54])
    }
  ],
  "extra": {
    "tags": ["fast", { "level": (3, [1, 2]) }],
    "active": (true, false)
  }
}
```
This input has all correct brackets and thus returns **`Balanced Brackets`**.

### info2.txt
```js
{
  "info": [
    {
      "name": "Alice",
      "scores": (98, 87, [45, 78])
    },
    {
      "name": "Bob",
      "scores": (76, 90, [33, 54])
    }
  ],
  "extra": {
    "tags": ["fast", { "level": (3, [1, 2]) }],
    "active": (true, false)
```
This input ends unexpectedly. The program encounters no error mismatched brackets, but ends with the stack still having elements. 
This input is then autocompleted by the program in another file.

### info3.txt
```js
{
  "info": [
    {
      "name": "Alice",
      "scores": (98, 87, [45, 78])
    },
    {
      "name": "Bob",
      "scores": (76, 90, [33, 54])
    }
  ],
  "extra": {
    "tags": ["fast", { "level": (3, [1, 2)) }],
    "active": (true, false)
  }
}
```
This input has a mismatched brackets. The program detects the error and ends execution.

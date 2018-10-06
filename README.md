# sudokuSolver
A simple C++ program to solve sudoku puzzles

## Input format

The the grid in input file should be like this:

```
0 8 5 3 1 9 0 0 0
0 0 0 0 5 2 6 0 0
4 0 3 0 0 0 9 0 0
0 0 9 0 0 0 8 0 0
0 0 0 0 2 7 0 0 0
0 3 4 1 0 8 0 0 0
8 0 6 0 0 4 0 3 0
0 0 0 2 0 0 0 0 8
0 9 0 8 3 5 7 0 0
```

In which zeroes are unknown positions.

## Usage

To execute the solver, you must use the command './run' in the directory.
You can either pass a path to an input file or execute as it is and type the input yourself.

Example:
```
./run samples/inputs/hard_input1 (is going to execute with input file 'hard_input1')
./run (is going to execute without an input file, so you need to type one yourself)
```

Remark: This program is meant to execute using inputs from 'easy' to 'hard', execute using an input with difficulty
higher than that at your own risk (just kidding, for now the program may never stop executing if you do so)
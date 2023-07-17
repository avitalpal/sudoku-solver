# Sudoku Solver
This is a C++ program that solves Sudoku puzzles using a backtracking algorithm. It takes a Sudoku grid as input from a file named yourGrid.txt and prints the solved Sudoku grid to the console.

## How to Use
Clone or download the repository to your local machine.
Make sure you have a valid Sudoku grid in the yourGrid.txt file. The grid should be 9x9, with empty cells represented by 0 and filled cells with numbers between 1 and 9.
Compile the program using a C++ compiler (e.g., g++).
Run the compiled executable.

## Features
Validates the input Sudoku grid for correctness and format before solving.
Checks for the minimum number of givens required to ensure a unique solution.
Provides an option to review the rules of Sudoku before solving the puzzle.

## Algorithm
The Sudoku puzzle is solved using a recursive backtracking algorithm. The algorithm searches for an empty cell, tries all possible numbers from 1 to 9, and backtracks if a number doesn't lead to a valid solution. It continues this process until a solution is found or all possibilities have been exhausted.

### Disclaimer
This program assumes that the input file yourGrid.txt contains a valid Sudoku grid with exactly 9 rows and 9 columns. It also assumes that the input grid adheres to the rules of Sudoku, where each row, column, and 3x3 box contains distinct integers from 1 to 9.

Feel free to use, modify, and distribute this Sudoku Solver :)

### Happy Sudoku solving!

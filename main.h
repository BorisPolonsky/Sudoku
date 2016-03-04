#include <stdio.h>
#include "Sudoku.h"

/*
Brief
This is a program to search one of the possible solutionsto Sudoku Puzzle. 
Method: Directly Calculating/Brute Force
The time cost depends on the number and the form of Solutions. 

Any suggestion will be welcomed. 
By Boris Polonsky

2015-5-26, Beijing
*/

/*Disclaimer*/
/*
This program is not responsible for any information it has provided. 
*/

/*Revision History*/
/*
2015-6-21, Beijing
Changed function STATUS USER_SetSudoku(TypeDefSudoku*) in "Sudoku.h", after which user may choose how to initialize a Sudoku Puzzle. 
Added a simple timer in function void main(). 


2015-7-13, Beijing
Removed:
#define STATUS unsigned int
#define BOOL unsigned int

Commented all echoes in BOOL SudokuSearchSolution(TypeDefSudoku Problem,TypeDefSudoku* Solution)

Added:
typedef unsigned int STATUS;
typedef unsigned char BOOL;
*/

/*Known Bugs*/
/*
The program doesn't work correctly if the user gives a non-numeric input. 
*/
#ifndef __Sudoku_H
#define __Sudoku_H
#include <stdio.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE !FALSE
typedef struct ElemTypeSudoku
{
	unsigned int Data[9][9];
	unsigned int Table[9][9];
}TypeDefSudoku;

typedef unsigned int STATUS;
typedef unsigned char BOOL;

STATUS InitSudoku(TypeDefSudoku*);
STATUS USER_SetSudoku(TypeDefSudoku*);
STATUS SetSudoku(TypeDefSudoku*,unsigned int,unsigned int,unsigned int);
STATUS SudokuTableUpdate(TypeDefSudoku*,unsigned int,unsigned int,unsigned int);
BOOL SearchRow(TypeDefSudoku,unsigned int,unsigned int);
BOOL SearchColumn(TypeDefSudoku,unsigned int,unsigned int);
BOOL SearchBlock(TypeDefSudoku,unsigned int,unsigned int,unsigned int);
BOOL SudokuSearchSolution(TypeDefSudoku,TypeDefSudoku*);
BOOL SudokuConfirmedSolutionSearchComplete(TypedefSudoku);
BOOL SudokuFull(TypeDefSudoku);
BOOL SudokuValid(TypeDefSudoku);
void PrintSudoku(TypeDefSudoku);
void PrintSudokuTable(TypeDefSudoku);
#endif
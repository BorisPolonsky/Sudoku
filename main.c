#include "main.h"

void main()
{
	TypeDefSudoku Sudoku,Solution;
	clock_t t_begin, t_end;
	InitSudoku(&Sudoku);
	InitSudoku(&Solution);
	USER_SetSudoku(&Sudoku);
	system("cls");
	printf("Puzzle: \n");
	PrintSudoku(Sudoku);
	system("pause");
	t_begin = clock();
	if(SudokuSearchSolution(Sudoku,&Solution)==TRUE)
	{
		printf("Solution exists. \n\n");
		printf("Puzzle: \n");
		PrintSudoku(Sudoku);
		printf("Solution: \n");
		PrintSudoku(Solution);
	}
	else
		printf("No Solution Found. \n");
	t_end=clock();
	printf("Time elapsed: %ld ms. \n",t_end-t_begin);
	system("pause");
}
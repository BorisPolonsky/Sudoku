exec_name = SudokuSolver
SudokuSolver: main.o Sudoku.o
	gcc main.o Sudoku.o -o $(exec_name)
main.o: main.c main.h
	gcc -c main.c
Sudoku.o: Sudoku.c Sudoku.h
	gcc -c Sudoku.c 

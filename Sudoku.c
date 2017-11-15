#include "Sudoku.h"

STATUS InitSudoku(TypeDefSudoku *Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			Sudoku->Data[i][j]=0;
			Sudoku->Table[i][j]=9;
		}
	}
	return(OK);
}

STATUS USER_SetSudoku(TypeDefSudoku *Sudoku)
{
	unsigned i, NUM, row, column, num;
	BOOL InputValidFlag;
	while (1)
	{
		printf("In which way you want to initialize the Sudoku Puzzle? \n\n");
		printf("Option 1: \nEnter all element one by one in consequent order. A zero represents a void. \n\n");
		printf("Option 2: \nEnter the total number of given elements in Sudoku, \n");
		printf("then fill the slot(s) one by one by entering row number, column number, and the element in the certain slot. ");
		printf("For option 1, please enter 1, otherwise please enter 2. \n");
		scanf("%d", &NUM);
		if (NUM == 2)
		{
			system("clear");
			while (1)
			{
				printf("Please enter the total number of element(s) to be initialized. \n");
				scanf("%d", &NUM);
				if (NUM >= 0 && NUM <= 81)
					break;
				else
					printf("Invalid input. \n");
			}
			for (i = 0; i < NUM; i++)
			{
				while (1)
				{
					printf("Element Number %d of %d:\n", i + 1, NUM);
					printf("Enter row number(1-9). \n");
					scanf("%d", &row);
					printf("Enter column number(1-9). \n");
					scanf("%d", &column);
					printf("Enter Number to be put in this slot. \n");
					scanf("%d", &num);
					system("clear");
					if (SetSudoku(Sudoku, row, column, num) == ERROR)
					{
						printf("Invalid data. This input will not be taken into account. \n");
						PrintSudoku(*Sudoku);
					}
					else
					{
						PrintSudoku(*Sudoku);
						break;
					}
				}
			}
			break;
		}
		else if (NUM == 1)
		{
			system("clear");
			for (row = 1; row <= 9; row++)
			{
				while (1)
				{
					printf("Enter numbers to be put into slots in row %d. \n", row);
					printf("A '0' represents a void in corresponding slot. \n");
					printf("Example: \n1 2 0 0 0 0 0 3 4\n");
					InputValidFlag = TRUE;
					for (column = 1; column <= 9; column++)
					{
						scanf("%d", &NUM);
						if (NUM != 0 && Sudoku->Data[row - 1][column - 1] == 0)
						{
							if (SetSudoku(Sudoku, row, column, NUM) == FALSE)
								InputValidFlag = FALSE;
						}
					}
					system("clear");
					if (InputValidFlag == TRUE)
						break;
					else
					{
						printf("Invalid data dectected. Some inputs will not be taken into account. \n");
						PrintSudoku(*Sudoku);
						printf("Please enter again, enter 0 for slot(s) already occupied. \n");
					}
				}
				PrintSudoku(*Sudoku);
			}
			break;
		}
		else
		{
			system("clear");
			printf("Invalid Input. \n\n");
		}
	}
		return(OK);
}

STATUS SetSudoku(TypeDefSudoku* Sudoku,unsigned int row,unsigned int column,unsigned int num)
{
	if(row>=1&&row<=9&&column>=1&&column<=9&&num>=1&&num<=9)
	{
		if(Sudoku->Data[row-1][column-1]==0&&SearchRow(*Sudoku,row,num)==FALSE&&SearchColumn(*Sudoku,column,num)==FALSE&&SearchBlock(*Sudoku,row,column,num)==FALSE)
		{
			Sudoku->Data[row-1][column-1]=num;
			SudokuTableUpdate(Sudoku,row,column,num);
			return(OK);
		}
		else
			return(ERROR);
	}
	else
		return(ERROR);
	

}
STATUS SudokuTableUpdate(TypeDefSudoku *Sudoku,unsigned int row,unsigned int column,unsigned int num)
{
	unsigned int i,j;
	//row update
	for(j=0;j<9;j++) 
	{
		if((j<((column-1)/3)*3)||(j>((column-1)/3)*3+2))
		{
			if((SearchColumn(*Sudoku,j+1,num)==FALSE)&&(SearchBlock(*Sudoku,row,j+1,num)==FALSE)&&(Sudoku->Table[row-1][j]!=0))
				Sudoku->Table[row-1][j]--;
		}
	}
	//column update
	for(i=0;i<9;i++)
	{
		if((i<((row-1)/3)*3)||(i>((row-1)/3)*3+2))
		{
			if((SearchRow(*Sudoku,i+1,num)==FALSE)&&(SearchBlock(*Sudoku,i+1,column,num)==FALSE)&&(Sudoku->Table[i][column-1]!=0))
			Sudoku->Table[i][column-1]--;
		}
	}
	//block update
	for(i=((row-1)/3)*3;i<((row-1)/3)*3+3;i++)
	{
		for(j=((column-1)/3)*3;j<((column-1)/3)*3+3;j++)
		{
			if(Sudoku->Table[i][j]!=0)
			{
				if(i+1==row&&SearchColumn(*Sudoku,j+1,num)==FALSE)
					Sudoku->Table[i][j]--;
				if(j+1==column&&SearchRow(*Sudoku,i+1,num)==FALSE)
					Sudoku->Table[i][j]--;
				if(i+1!=row&&j+1!=column&&SearchRow(*Sudoku,i+1,num)==FALSE&&SearchColumn(*Sudoku,j+1,num)==FALSE)
					Sudoku->Table[i][j]--;
			}
				
		}
	}
	Sudoku->Table[row-1][column-1]=0;
	return(OK);
}

BOOL SearchRow(TypeDefSudoku Sudoku,unsigned int row,unsigned int num)
{
	unsigned int i;
	for(i=0;i<9;i++)
	{
		if(Sudoku.Data[row-1][i]==num)
			return(TRUE);
	}
	return(FALSE);
}

BOOL SearchColumn(TypeDefSudoku Sudoku,unsigned int column,unsigned int num)
{
	unsigned int i;
	for(i=0;i<9;i++)
	{
		if(Sudoku.Data[i][column-1]==num)
			return(TRUE);
	}
	return(FALSE);
}

BOOL SearchBlock(TypeDefSudoku Sudoku,unsigned int row,unsigned int column,unsigned int num)
{
	unsigned int i,j;
	for(i=((row-1)/3)*3;i<((row-1)/3)*3+3;i++)
	{
		for(j=((column-1)/3)*3;j<((column-1)/3)*3+3;j++)
		{
			if(Sudoku.Data[i][j]==num)
				return(TRUE);
		}
	}
	return(FALSE);
}

BOOL SudokuSearchSolution(TypeDefSudoku Problem,TypeDefSudoku* Solution)
{
	unsigned int i,j,k;
	TypeDefSudoku TestSolution;
	if(SudokuValid(Problem)==FALSE)
	{
		return(FALSE);
	}
	else
	{
		if(SudokuFull(Problem)==TRUE)
		{
			*Solution=Problem;
			return(TRUE);
		}
		else
		{
			for(i=0;i<9;i++)
			{
				for(j=0;j<9;j++)
				{
					if(Problem.Table[i][j]!=0)
						break;
				}
				if(j==9)
					j--;
				if(Problem.Table[i][j]!=0)
					break;
			}
			for(k=1;k<=9;k++)
			{
				TestSolution=Problem;
				if(SearchRow(Problem,i+1,k)==FALSE&&SearchColumn(Problem,j+1,k)==FALSE&&SearchBlock(Problem,i+1,j+1,k)==FALSE)
				{
					SetSudoku(&TestSolution,i+1,j+1,k);
					//printf("Testing Solution: \n");
					//PrintSudoku(TestSolution);
					if(SudokuSearchSolution(TestSolution,&TestSolution)==TRUE)
					{
						*Solution=TestSolution;
						return(TRUE);
					}
				}
			}
			//printf("Invalid Solution Trajectory Found: \n");
			//PrintSudoku(Problem);
			return(FALSE);
		}
	}
}

BOOL SudokuConfirmedSolutionSearchComplete(TypeDefSudoku Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(Sudoku.Table[i][j]==1)
				return(FALSE);
		}
	}
	return(TRUE);
}

BOOL SudokuFull(TypeDefSudoku Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
		if(Sudoku.Data[i][j]==0)
			return(FALSE);
		}
	}
	return(TRUE);
}

BOOL SudokuValid(TypeDefSudoku Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(Sudoku.Data[i][j]==0&&Sudoku.Table[i][j]==0)
				return(FALSE);
		}
	}
	return(TRUE);
}

void PrintSudoku(TypeDefSudoku Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(Sudoku.Data[i][j]!=0)
				printf("%2d",Sudoku.Data[i][j]);
			else
				printf("  ");
			if(j==2||j==5)
				printf("|");
		}
		printf("\n");
		if(i==2||i==5)
			printf("--------------------\n");
	}
}

void PrintSudokuTable(TypeDefSudoku Sudoku)
{
	unsigned int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%2d",Sudoku.Table[i][j]);
			if(j==2||j==5)
				printf("|");
		}
		printf("\n");
		if(i==2||i==5)
			printf("--------------------\n");
	}
}

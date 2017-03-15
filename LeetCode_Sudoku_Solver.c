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

STATUS InitSudoku(struct ElemTypeSudoku*);
STATUS SetSudoku(struct ElemTypeSudoku*,unsigned int,unsigned int,unsigned int);
STATUS SudokuTableUpdate(struct ElemTypeSudoku*,unsigned int,unsigned int,unsigned int);
BOOL SearchRow(struct ElemTypeSudoku,unsigned int,unsigned int);
BOOL SearchColumn(struct ElemTypeSudoku,unsigned int,unsigned int);
BOOL SearchBlock(struct ElemTypeSudoku,unsigned int,unsigned int,unsigned int);
BOOL SudokuSearchSolution(struct ElemTypeSudoku,TypeDefSudoku*);
BOOL SudokuConfirmedSolutionSearchComplete(struct ElemTypeSudoku);
BOOL SudokuFull(struct ElemTypeSudoku);
BOOL SudokuValid(struct ElemTypeSudoku);



STATUS InitSudoku(struct ElemTypeSudoku *Sudoku)
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

STATUS SetSudoku(TypeDefSudoku* Sudoku,unsigned int row,unsigned int column,unsigned int num)
{
	if(row>=1&&row<=9&&column>=1&&column<=9&&num>=1&&num<=9)
	{
		if(Sudoku->Data[row-1][column-1]==0&&SearchRow(*Sudoku,row,num)==FALSE&&SearchColumn(*Sudoku,column,num)

==FALSE&&SearchBlock(*Sudoku,row,column,num)==FALSE)
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
				if(i+1!=row&&j+1!=column&&SearchRow(*Sudoku,i+1,num)==FALSE&&SearchColumn(*Sudoku,j+1,num)

==FALSE)
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
				if(SearchRow(Problem,i+1,k)==FALSE&&SearchColumn(Problem,j+1,k)==FALSE&&SearchBlock

(Problem,i+1,j+1,k)==FALSE)
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

TypeDefSudoku inputAdapter(char** board)
{
    int i=0,j=0;
    TypeDefSudoku Sudoku;
    InitSudoku(&Sudoku);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(board[i][j]!='.')
                SetSudoku(&Sudoku,i+1,j+1,board[i][j]-'0');
        }
    }
    return(Sudoku);
}

void outputAdapter(TypeDefSudoku Sudoku,char** board)
{
    int i=0,j=0;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(Sudoku.Data[i][j]!=0)
                board[i][j]='0'+Sudoku.Data[i][j];
            else
                board[i][j]='.';
        }
    }
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) 
{
    TypeDefSudoku Sudoku=inputAdapter(board);
    SudokuSearchSolution(Sudoku,&Sudoku);
    outputAdapter(Sudoku,board);
}
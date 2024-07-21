#include<stdio.h>

#define EMPTY ' '
#define X 'X'
#define O 'O'

int bestMove[2]={-1, -1};

char board[5][5]={ {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
		   {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
	 	   {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
		   {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
		   {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY} };

int max(int a, int b)
{
	return (a>b)?a:b;
}

int min(int a, int b)
{
	return (a<b)?a:b;
}


void printBoard()
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("%c | ", board[i][j]);
		}
		printf("\n--------------------\n");
	}
}

char Winner(char b[5][5])
{
	for (int i=0; i<5; i++)
	{
		if ( board[i][1]!=EMPTY && board[i][1]==board[i][2] && board[i][2]==board[i][3] && (board[i][1]==board[i][0] || board[i][1]==board[i][4]))
			return board[i][1];

		else if(board[1][i]!=EMPTY&&board[1][i]==board[2][i] && board[2][i]==board[3][i] && (board[1][i]==board[0][i] || board[1][i]==board[4][i]))
			return board[1][i];
	}

	if (board[1][1]!=EMPTY && board[1][1]==board[2][2] && board[2][2]==board [3][3] && (board[0][0]==board[1][1] || board[4][4]==board[1][1]))
	       return board[1][1];
	else if (board[2][2]!=EMPTY && board[2][2]==board[1][3] && board[2][2]==board[3][1] && (board[0][4]==board[2][2] || board[4][0]==board[2][2]))
		return board[2][2];
	
	return EMPTY;
}	

int checkIfEmpty(char b[5][5])
{
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (board[i][j]==EMPTY)
				return 1;
		}
	}

	return 0;
}

int evaluate(char b[5][5])
{
	char c=Winner(b);
	switch (c)
	{
		case X: return 1;
		case O: return -1;
		default: return 0;
	}
}

int minimax(char b[5][5], int depth, int maximizingPlayer, int alpha, int beta)
{
	if(Winner(b)!=EMPTY || depth==0)
		return evaluate(b);

	if(maximizingPlayer)
	{
		int best = -10000;
		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				if(b[i][j]==EMPTY)
				{
					b[i][j]=X;
					int val=minimax(b, depth-1, 0, alpha, beta);
					b[i][j]=EMPTY;
					best=max(best, val);
					alpha=max(alpha, val);
					if(beta<=alpha)
						break;
				}
			}
		}
		return best;
	}

	else
	{
		int best = 10000;
		 for(int i=0; i<5; i++)
                {
                        for(int j=0; j<5; j++)
                        {
                                if(b[i][j]==EMPTY)
                                {
                                        b[i][j]=O;
                                        int val=minimax(b, depth-1, 1, alpha, beta);
                                        b[i][j]=EMPTY;
                                        best=min(best, val);
                                        alpha=min(beta, val);
                                        if(beta<=alpha)
                                                break;
                                }
                        }

                }
		 return best;
        }
}

void FindBestMove(char b[5][5])
{
	int best=-10000;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(b[i][j]==EMPTY)
			{
				b[i][j]=X;
				int moveScore=minimax(b, 5, 0, -10000, 10000);
				b[i][j]=EMPTY;

				if(moveScore>best)
				{
					best=moveScore;
					bestMove[0]=i;
					bestMove[1]=j;
				}
			}
		}
	}

	//return bestMove;
}




int main()
{
	char winner;
	while(1)
	{
		printBoard();
		winner=Winner(board);

		if(winner!=EMPTY)
		{
			printf("Winner is: %c\n", winner);
			break;
		}

		if(!checkIfEmpty(board))
		{
			printf("The game is a draw!\n");
			break;
		}

		int row, col;
		printf("Enter row(1-5) and column (1-5) of your move: ");
		scanf("%d %d", &row, &col);
		while(board[row-1][col-1]!=EMPTY)
		{
			printf("Invalid move, Try again.\nEnter row(1-5) and column (1-5) of your move: ");
			scanf("%d %d", &row, &col);
		}

		board[row-1][col-1]=O;
		
		printBoard();
		
		winner=Winner(board);

                if(winner!=EMPTY)
                {
                        printf("Winner is: %c\n", winner);
                        break;
                }

                if(!checkIfEmpty(board))
                {
                        printf("The game is a draw!\n");
                        break;
                }

		FindBestMove(board);
		printf("Computer's Turn, Move at %d %d\n\n", bestMove[0]+1, bestMove[1]+1);
                board[bestMove[0]][bestMove[1]]=X;
		
	}
	return 0;
}

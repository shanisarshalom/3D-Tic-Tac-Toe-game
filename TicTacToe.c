
#include <stdio.h>
#define FOUR 4
#define THREE 3
#define TWO 2
#define ONE 1
#define SIX 6

//functions
void clearInputBuffer();
int checkWinRow(char gameBoard[][FOUR][FOUR]);
void initMatrix(char gameBoard[][FOUR][FOUR]);
int checkWinCol(char gameBoard[][FOUR][FOUR]);
int checkWinSlant(char gameBoard[][FOUR][FOUR]);
void printGameBoard(char gameBoard[][FOUR][FOUR]);
int checkIfValid(int c);

void main()
{
	char choice = 0;
	char gameBoard[FOUR][FOUR][FOUR];
	int x , y, z;
	char input = '0';
	int counter = 0, inValid = 0, countTurns = 0;
	//print to start gmae, return the loop until the user press 'n'
	do
	{
		//counter == 0 at the first time in loop, and get ++ in the switch case
		if (counter == 0 && inValid == 0)
		{
			printf("Would you like to start? (y/n)\n");
		}
		if (counter > 0 || inValid == 1)
		{
			printf("Would you like to continue? (y/n)\n");
		}
		choice = getchar();
		switch (choice)
		{
		//case of play the game
		case 'y':
			printf("Please enter your game sequence.\n");
			//call a function to initialization the matrix with '*'
			initMatrix(gameBoard);
			{
				//initialize the variables
				inValid = 0;
				counter = 0;
				countTurns = 0;
		//loop to get the game sequence from users, check if valid, check win
		//continue to get game sequence until get '\n'
		while (input != '\n')
				{
			        scanf("%d", &x);
					//call a function to check the char from user
					if (!checkIfValid(x))
					{
						printf("Input incorrect.\n");
						//value of inValid change in order to indicate not to print the gameBoard
						inValid = 1;
						break;
					}
					//get the tab
					input = getchar();
					scanf("%d", &y);
					//call a function to check the char from user
					if (!checkIfValid(y))
					{
						printf("Input incorrect.\n");
						//value of inValid change in order to indicate not to print the gameBoard
						inValid = 1;
						break;
					}
					//get the tab
					input = getchar();
					scanf("%d", &z);
					//call a function to check the char from user
					if (!checkIfValid(z))
					{
						printf("Input incorrect.\n");
						//value of inValid change in order to indicate not to print the gameBoard
						inValid = 1;
						break;
					}
					if (gameBoard[x][y][z] != '*')
					{
						printf("Input incorrect.\n");
						//value of inValid change in order to indicate not to print the gameBoard
						inValid = 1;
						break;
					}
					//get at least seven turns and then start to check wins
					countTurns++;
					//counter indicate if dual or odd, dual = 'X', odd = 'O'
					if ((counter++ % TWO) == 0)
					{
						//place 'X' in the matrix
						gameBoard[x][y][z] = 'X';
						//call funcions to check all options to win
						if (countTurns > SIX)
						{
							if (checkWinRow(gameBoard) || checkWinCol(gameBoard) || 
								checkWinSlant(gameBoard))
							{
								printf("X is the winner.\n");
								break;
							}
						}
					}
					else
					{
						//place 'O' in the matrix
						gameBoard[x][y][z] = 'O';
						//call funcions to check all options to win
						if (countTurns > SIX)
						{
							if (checkWinRow(gameBoard) || checkWinCol(gameBoard) ||
								checkWinSlant(gameBoard))
							{
								printf("O is the winner.\n");
								break;
							}
						}
					}
					//check that gameBoard is full
					if (countTurns > 63)
					{
						//if all options to win false its tie
						if ((!checkWinRow(gameBoard)) && (!checkWinCol(gameBoard)) &&
							(!checkWinSlant(gameBoard)) && (inValid == 0))
						{
							printf("Tie.\n");
							break;
						}
					}
					//get the tab
					input = getchar();
				}
		//if all the inputes are valid print gameBoard
		if (inValid == 0)
		{
			printGameBoard(gameBoard);
		}
			}
		//call a function to clear the buffer if there is win/tie/invalid input
		clearInputBuffer();
		break;
		//case to exit the gmae
		case 'n': printf("YEET");
			//call a function to clear the buffer to print the menu again
			clearInputBuffer();
			break;
		}
	} while (choice != 'n');
}

/************************************************************************
* function name: checkIfValid *
* The Input: int "x" / "y" / "z" *
* The output: if the input from user is valid *
* The Function operation: check if the input is valid (bitween 0 to 3) *
*************************************************************************/
int checkIfValid(int c)
{
	if (c < 0 || c > THREE)
	{
		return 0;
	}
	return 1;
}

/************************************************************************
* function name: checkWinRow *
* The Input: char - the matrix with the values of players *
* The output: if there is row of one player in 2d/3d *
* The Function operation: check if there is row of one player in 2d/3d *
*************************************************************************/
int checkWinRow(char gameBoard[][FOUR][FOUR])
{
	for (int i = 0; i < FOUR; i++)
	{
		for (int j = 0; j < FOUR; j++)
		{
			if (gameBoard[i][j][0] != '*')
			{
				// check 2d
				if (gameBoard[i][j][0] == gameBoard[i][j][ONE] && gameBoard[i][j][0] ==
					gameBoard[i][j][TWO] && gameBoard[i][j][0] == gameBoard[i][j][THREE])
				{
					return 1;
				}
			}
		}
		// check up to down 3d row-slant
		if (gameBoard[0][i][0] != '*' && gameBoard[0][i][0] == gameBoard[ONE][i][ONE]
			&& gameBoard[0][i][0] == gameBoard[TWO][i][TWO] && gameBoard[0][i][0]
			== gameBoard[THREE][i][THREE])
		{
			return 1;
		}
		// check down to up 3d row-slant
		if (gameBoard[0][i][THREE] != '*' && gameBoard[0][i][THREE] ==
			gameBoard[ONE][i][TWO] && gameBoard[0][i][THREE] == gameBoard[TWO][i][ONE]
			&& gameBoard[0][i][THREE] == gameBoard[THREE][i][0])
		{
			return 1;
		}
	}
	return 0;
}

/************************************************************************
* function name: checkWinCol *
* The Input: char - the matrix with the values of players *
* The output: if there is column of one player in 2d/3d *
* The Function operation: check if there is column of one player in 2d/3d *
*************************************************************************/
int checkWinCol(char gameBoard[][FOUR][FOUR])
{
	for (int i = 0; i < FOUR; i++)
	{
		for (int k = 0; k < FOUR; k++)
		{
			// check 2d col
			if (gameBoard[i][0][k] != '*' && gameBoard[i][0][k] == gameBoard[i][ONE][k] &&
				gameBoard[i][0][k] == gameBoard[i][TWO][k] && gameBoard[i][0][k]
				== gameBoard[i][THREE][k])
			{
				return 1;
			}
			// check 3d col
			if (gameBoard[0][i][k] != '*' && gameBoard[0][i][k] == gameBoard[ONE][i][k] &&
				gameBoard[0][i][k] == gameBoard[TWO][i][k] && gameBoard[0][i][k]
				== gameBoard[THREE][i][k])
			{
				return 1;
			}
		}
	}
	return 0;
}

/************************************************************************
* function name: checkWinSlant *
* The Input: char - the matrix with the values of players *
* The output: if there is slant of one player in 2d/3d *
* The Function operation: check if there is slant of one player in 2d/3d *
*************************************************************************/
int checkWinSlant(char gameBoard[][FOUR][FOUR])
{
	for (int i = 0; i < FOUR; i++)
	{
		// check 2d slant up to down
		if (gameBoard[i][0][0] != '*' && gameBoard[i][0][0] == gameBoard[i][ONE][ONE]
			&& gameBoard[i][0][0] == gameBoard[i][TWO][TWO] && gameBoard[i][0][0] 
			== gameBoard[i][THREE][THREE])
		{
			return 1;
		}
		// check 2d slant down to up
		if (gameBoard[i][0][THREE] != '*' && gameBoard[i][0][THREE] == 
			gameBoard[i][ONE][TWO] && gameBoard[i][0][THREE] == gameBoard[i][TWO][ONE]
			&& gameBoard[i][0][THREE] == gameBoard[i][THREE][0])
		{
			return 1;
		}
	}
	// check 3d left to right up to down
	if (gameBoard[0][0][0] != '*' && gameBoard[0][0][0] ==gameBoard[ONE][ONE][ONE]
		&& gameBoard[0][0][0] == gameBoard[TWO][TWO][TWO] && gameBoard[0][0][0] 
		== gameBoard[THREE][THREE][THREE])
	{
		return 1;
	}
	// check 3d right to left down to up
	if (gameBoard[0][0][THREE] != '*' && gameBoard[0][0][THREE] == 
		gameBoard[ONE][ONE][TWO] && gameBoard[0][0][THREE] ==gameBoard[TWO][TWO][ONE]
		&& gameBoard[0][0][THREE] == gameBoard[THREE][THREE][0])
	{
		return 1;
	}
	// check 3d left to right down to up in rows
	if (gameBoard[0][THREE][0] != '*' && gameBoard[0][THREE][0] == 
		gameBoard[ONE][TWO][ONE] && gameBoard[0][THREE][0] ==gameBoard[TWO][ONE][TWO]
		&& gameBoard[0][THREE][0] == gameBoard[THREE][0][THREE])
	{
		return 1;
	}
	// check 3d left to right down to up
	if (gameBoard[THREE][0][0] != '*' && gameBoard[THREE][0][0] == 
		gameBoard[TWO][ONE][ONE] && gameBoard[THREE][0][0] ==gameBoard[ONE][TWO][TWO]
		&& gameBoard[THREE][0][0] == gameBoard[0][THREE][THREE])
	{
		return 1;
	}
	return 0;
}

/************************************************************************
* function name: initMatrix *
* The Input: char - matrix *
* The output: - *
* The Function operation: initialization the matrix with '*' *
*************************************************************************/
void initMatrix(char gameBoard[][FOUR][FOUR])
{
for (int i = 0; i < FOUR; i++)
{
	for (int j = 0; j < FOUR; j++)
	{
		for (int k = 0; k < FOUR; k++)
			gameBoard[i][j][k] = '*';
	}
}
}

/************************************************************************
* function name: printGameBoard *
* The Input: char - the matrix with the values of players *
* The output: - *
* The Function operation: print the matrix with the values of players *
*************************************************************************/
void printGameBoard(char gameBoard[][FOUR][FOUR])
{
	for (int i = 0; i < FOUR; i++)
	{
		for (int j = 0; j < FOUR; j++)
		{
			for (int k = 0; k < FOUR; k++)
			{
				printf("(%d %d %d) ", i, j, k);
			}
			for (int k = 0; k < FOUR; k++)
			{
				printf("%c ", gameBoard[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

/************************************************************************
* function name: clearInputBuffer *
* The Input: - *
* The output: - *
* The Function operation: clear the buffer if needed *
*************************************************************************/
void clearInputBuffer()
{
	char c;
	do
	{
		c = getchar();
	} while (c != '\n');
}
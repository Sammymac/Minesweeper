
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLUSH fflush(stdin)

void difficulty( void );
void beginner( void );
void intermediate( void );
void expert( void );
void minefield_generator( void );
void print_minefield( void );
void guess( void );
void boom( void );
void print_final_minefield( void );
void win( void );
void play_again( void );
void game_over( void );

int x, y;
int M, N;
float diff;
int total_mines = 0;
int mines = 0;
int minefield[30][30];										//This 2-D array contains all of the mines, numbers and blank spaces
int blank_minefield[30][30];								//This contains the minefield full of '|-|' characters
int final_minefield[30][30];

int main()
{
	printf("\t\tWelcome to Minesweeper\n");
	difficulty();
	return 0;
}

void difficulty( void )										//Function for choosing the difficulty level
{
	diff = 0;
	while( (diff != 1) && (diff != 2) && (diff != 3))		
	{
		printf("\t\tChoose a difficulty level(1-3):");	
		scanf("%f", &diff);
		FLUSH;
		if( (diff != 1) && (diff != 2) && (diff != 3))
		{
			printf("\t\tPlease enter either 1, 2 or 3\n");
		}
	}	

	if( diff == 1 )											//If, else if and else statements that each go to the respective difficulty
	{
		beginner();
	}
	else if( diff == 2 )
	{
		intermediate();
	}
	else if( diff == 3 )
	{
		expert();
	}
}

void beginner( void )										//Gives the minefield the 'beginner' grid and mines
{
	M = 9;
	N = 9;
	total_mines = 10;
	minefield_generator();
	guess();
}

void intermediate( void )									//Gives the minefield the 'intermediate' grid and mines
{
	M = 16;
	N = 16;
	total_mines = 40;
	minefield_generator();
	guess();
}

void expert( void )											//Gives the minefield the 'expert' grid size and mines
{
	M = 16;
	N = 30;
	total_mines = 99;
	minefield_generator();
	guess();
}

void minefield_generator( void )							//Function that generates the minefield
{
	int i = 0, j = 0;
	
	srand( time( NULL ) );									//Starts the random no. generator
	
	while( j < N )											//Nested loop for making the blank minefield and final minefield
	{
		while( i < M)
		{
			minefield[i][j] = '-';
			blank_minefield[i][j] = minefield[i][j];		
			final_minefield[i][j] = minefield[i][j];		
			i++;
		}
		i = 0;
		j++;
	}
	mines = 0;
	while( mines < total_mines )							//Randomly generates the mines into the minefield
	{
		i = rand()%(M);
		j = rand()%(N);
		if( minefield[i][j] != '*')							//If statement that checks if there is a mine already there and doesn't place a mine if there is
		{
			minefield[i][j] = '*';
			final_minefield[i][j] = minefield[i][j];
			mines++;
		}
	}
	i = 0;
	j = 0;
	
	while( j < N )											//While loop that generates the numbers for any adjacent mines
	{
		while( i < M)
		{
			if( minefield[i][j] != '*')
			{
				minefield[i][j] = 0;
			}	
			if((minefield[i-1][j-1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i-1][j] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i][j-1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i-1][j+1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i+1][j-1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i+1][j] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i][j+1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if((minefield[i+1][j+1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			i++;
		}
		i = 0;
		j++;
	}
	i = 0;
	j = 0;
}

void print_minefield(void)									// This function prints the minefield
{
	int i = 0, j = 0, z = 0;
	while( z < M )											// This while loop prints out the line of co-ordinates along the x axis of the minefield
	{
		if( z == 0 )
		{
			printf("\t");
		}
		printf("|%d|\t", z);
		z++;
	}
	printf("\n\n");
	
	while( j < N )											// Loop that prints out each character in the minefield							
	{	
		printf("|%d|\t", j);
		while( i < M)
		{
			if( blank_minefield[i][j] == '-')
			{
				printf("|%c|\t", blank_minefield[i][j]);
				
			}
			else if( minefield[i][j] == 0 )					// This changes any spaces with values of zero to the character 'B'
			{
				blank_minefield[i][j] = 'B';				
				printf("|%c|\t", blank_minefield[i][j]);
			}
			else
			{
				printf("|%d|\t", blank_minefield[i][j]);
				
			}
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
}


void guess( void )
{
	int q = 0, i=0, j=0, match=0;
	print_minefield();
	while( j < N )											// While loop for testing whether or not the user has cleared the minefield
	{
		while( i < M )
		{
			if(minefield[i][j] == blank_minefield[i][j])
			{
				match++;
			}
			i++;
		}
		i = 0;
		j++;
	}
	if( match == (( M * N ) - total_mines))					// If the user has cleared the minefield, the win() function is run
	{
		win();
	}
	printf("\nEnter the x value, then a space, then the y value:");
	scanf("%d %d", &x, &y);									// Reading in the co-ordinates for the guess
	FLUSH;
	if( (x >= M) || (x < 0) || (y < 0) || (y >= N) )
	{
		printf("\nPlease enter a value inside the grid\n");
		guess();
	}
	if( minefield[x][y] == '*' )							// Runs the boom() function if the user selects a mine
	{
		boom();
	}
	if( blank_minefield[x][y] != '-' )
	{
		printf("\nPlease enter a value that has not already been entered\n");
		guess();
	}
	
	else												// Checks if the adjacent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
	{
		blank_minefield[x][y] = minefield[x][y];
		if( minefield[x][y] == 0 )
		{
			if( minefield[x-1][y-1] == 0 )
			{
				blank_minefield[x-1][y] = minefield[x-1][y];
			}
			if( minefield[x-1][y] == 0 )
			{
				blank_minefield[x-1][y] = minefield[x-1][y];
			}
			if( minefield[x][y-1] == 0 )
			{
				blank_minefield[x][y-1] = minefield[x][y-1];
			}
			if( minefield[x-1][y+1] == 0 )
			{
				blank_minefield[x-1][y+1] = minefield[x-1][y+1];
			}
			if( minefield[x+1][y-1] == 0 )
			{
				blank_minefield[x+1][y-1] = minefield[x+1][y-1];
			}
			if( minefield[x+1][y] == 0 )
			{
				blank_minefield[x+1][y] = minefield[x+1][y];
			}
			if( minefield[x][y+1] == 0 )
			{
				blank_minefield[x][y+1] = minefield[x][y+1];
			}
			if( minefield[x+1][y+1] == 0 )
			{
				blank_minefield[x+1][y+1] = minefield[x+1][y+1];
			}
		}
		guess();
	}
}

void boom( void )										// Runs the print_final_minefield function, then the play_again function					
{
	print_final_minefield();
	printf("\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
	play_again();
}

void print_final_minefield( void )						// Prints the minefield, showing where all of the mines are placed
{
	int i = 0, j = 0, z = 0;
	while( z < M )
	{
		if( z == 0 )
		{
			printf("\t");
		}
		printf("|%d|\t", z);
		z++;
	}
	printf("\n\n");
	
	while( j < N )
	{	
		printf("|%d|\t", j);
		while( i < M)
		{
			printf("|%c|\t", final_minefield[i][j]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
}

void win( void )										// Runs the play_again function
{
	printf("\n\n\n\t\t\tYOU WIN!!!!!\n\n\n");
	play_again();
}

void play_again( void )									// Gives the user the option to play again
{
	char option[2];
	printf("\n\t\tWould you like to play again(Y/N)?:");
	scanf("%c", &option[0]);
	FLUSH;
	if((option[0] == 'Y') || (option[0] == 'y'))		// Restarts the program from after the welcome message
	{
		difficulty();
	}
	else if( (option[0] == 'N') || (option[0] == 'n'))
	{
		game_over();
	}
	else
	{
		printf("Please enter either Y or N");
		play_again();
	}
}

void game_over( void )									// Ends the program
{
	printf("\n\n\t\tGame Over");
	exit(1);
}

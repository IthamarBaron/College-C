#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define HIGHT 20
#define WIDTH 20
#define ALIVE 'H'
#define DEAD ' '
typedef enum {TRUE,FALSE} bool;


void PrintGen(char mat[HIGHT][WIDTH], int gen )
{
	printf("Generation [%d]\n", gen);
	for (size_t i = 0; i < WIDTH; i++)
	{
		printf("_");
	}
	puts("");
	for (int i = 0; i < HIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%c", mat[i][j]);
		}
		if (i<HIGHT-2)
			printf("\n");

	}
	for (size_t i = 0; i < WIDTH; i++)
	{
		printf("-");
	}
}


int CountAliveNeighbours(char mat[HIGHT][WIDTH], int i, int j ,int x[],int y[])
{
	int counter = 0;
	//count neigbhours
	for (int k = 0; k < 8; k++)
	{
		if (mat[i+(x[k])][j+(y[k])] == ALIVE)
		{
			counter++;
		}
	}

	return counter;
}

void NextGen(char mat[HIGHT][WIDTH], int x[], int y[])
{
	char PrevMat[HIGHT][WIDTH] = { 0 };
	//copy mat
	for (int i = 0; i < HIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			PrevMat[i][j] = mat[i][j];
		}
	}
	//create new generation
	for (int i = 0; i < HIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (CountAliveNeighbours(PrevMat, i, j, x, y) != 2)//Unchanged if has 2 neighbours
			{
				if (PrevMat[i][j] == ALIVE)
				{
					if (CountAliveNeighbours(PrevMat, i, j, x, y) <= 1) //Dies if has less then 1 neighbour
						mat[i][j] = DEAD;
					else if (CountAliveNeighbours(PrevMat, i, j, x, y) >= 4)// Dies if has more then 4 neighbours
						mat[i][j] = DEAD;
				}
				else
				{
					if (CountAliveNeighbours(PrevMat, i, j, x, y) == 3) //Born if has 3 neighbours
						mat[i][j] = ALIVE;
				}
			}
		}
	}

}

int main()
{
	int vecI[] = { -1,-1,-1,0,0,1,1,1 };
	int vecJ[] = { -1,0,1,-1,1,-1,0,1 };

	char matrix[HIGHT][WIDTH] = {
	   {DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, ALIVE, ALIVE, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,ALIVE},
	   {DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, ALIVE, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {ALIVE, ALIVE, DEAD, DEAD, ALIVE, DEAD, ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, ALIVE, ALIVE, ALIVE, DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD},
	   {DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD}
	};

	for (size_t i = 0; i < 500; i++)
	{
		NextGen(matrix,vecI,vecJ);
		for (int j = 0; j < 80000000; j++)
		{
		}
		system("cls");
		PrintGen(matrix, i);


	}
}



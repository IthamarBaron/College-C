//Ithamar Baron
#pragma warning(disable : 4996)
#include <stdio.h>
#include <ctype.h>

#define N 15

void DisplayCelsiusToFahrenheit()
{
	printf("Celsius | Fahrenheit\n=======================\n");

	for (int tempC = -274; tempC < 102; tempC += 11)
	{
		int tempF = tempC * 9.0 / 5.0 + 32;
		printf("%3d%c\t|\t%3d%c \n", tempC, 248, tempF, 248);
	}
	printf("=======================\n");
}

void FillMagicSquare(int mat[N][N])
{
	int i = 0, j = N / 2;
	int counter = 1;
	int middle = N / 2;
	mat[i][middle] = counter++;
	//could have been done with %N but well.. 
	while (counter != (N * N + 1))
	{
		if (i == 0 && j < N)
		{
			if (j == N - 1)
				i++;
			else
			{
				i = N - 1;
				j++;
			}

		}
		else if (j == N - 1 && i != 0)
		{
			j = 0;
			i--;

		}
		else if ((i > 0 && j < N) && (mat[i - 1][j + 1] != 0))
		{

			if (j == N)
				i = 0;
			else
				i++;
		}
		else
		{
			j++;
			i--;
		}

		if (i < N && j < N)
			mat[i][j] = counter++;
		else
		{
			printf("SOMETHING WENT WRONG!");
			return;
		}

	}
}

void PrintSeriess()
{
	int index = 0;
	int counter[6] = { 0 };
	int num;
	int currentLength = 0;
	for (int i = 0; i < 12; i++)
	{
		scanf("%1d", &num);
		if (num == 1)
			currentLength++;
		else
		{
			if (currentLength > 0)
			{
				counter[currentLength - 1]++;
				currentLength = 0;
			}
		}
	}

	if (currentLength > 0)
		counter[currentLength - 1]++;

	for (int i = 0; i < 6; i++)
	{
		if (counter[i] > 0)
			printf("%d series of %d ones\n", counter[i], i + 1);
	}

}

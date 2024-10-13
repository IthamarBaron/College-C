//Ithamar Baron 13/10/24
#pragma warning(disable : 4996)
#include <stdio.h>

typedef char string[255];

int power(int d, int n)
{	
	if (n == 0)
		return 1;
	if (n ==1)
		return d;
	return power(d, --n) * d;
}

void replaceSpaces(char* str) 
{
    if (*str == '\0')
        return;
    if (*str == ' ')
        *str = '*';
    replaceSpaces(str + 1);
}

//finds first appearens from the right
int findIndex(int arr[], int size, int num)
{
	if (size <= 0)
		return -1;
	if (arr[--size] == num)
		return size;
	return(findIndex(arr, size, num));
}

void sortArr(int arr[], int size)
{
	if (size <=0)
		return;
	for (int i = 0; i < size-1; i++)
	{
		if (arr[i] > arr[i+1])
		{
			int temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
		}
	}
	sortArr(arr, --size);
}

void printPascalTriangle(int index, int n)
{
	if (index == n)
		return;

	int digit = 1; 
	for (int i = 0; i <= index; i++) 
	{
		printf("%d ", digit);
		digit = digit * (index - i) / (i + 1); 
	}

	puts("");
	printPascalTriangle(++index, n);
}

int betterPower(int A, int B)
{
	if (B == 0)
		return 1; 

	int half = betterPower(A, B / 2); 
	if (B % 2 == 0)
		return half * half; 
	else
		return A * half * half;

}

int maxDigit(num)
{
	if (num == 0)
		return 0;

	int currentDigit = num % 10;
	int currenentMax = maxDigit(num / 10);
	if (currentDigit > currenentMax)
		return currentDigit;
	return currenentMax;
}

/*
[i-1,j-1] [i-1,j] [i-1,j+1]
 [i,j-1]   [i,j]   [i,j+1]
[i+1,j-1] [i+1,j] [i+1,j+1]
*/
//note, this destroy the original mat...
int getStainFrom(int mat[7][7], int index1, int index2) {
	if (index1 < 0 || index1 >= 7 || index2 < 0 || index2 >= 7)
		return 0; 
	if (mat[index1][index2] == 0)
		return 0;

	// mark visited cells
	mat[index1][index2] = 0;

	int stainSize = 1;

	stainSize += getStainFrom(mat, index1 - 1, index2 - 1);
	stainSize += getStainFrom(mat, index1 - 1, index2);
	stainSize += getStainFrom(mat, index1 - 1, index2 + 1);
	stainSize += getStainFrom(mat, index1, index2 - 1);
	stainSize += getStainFrom(mat, index1, index2 + 1);
	stainSize += getStainFrom(mat, index1 + 1, index2 - 1);
	stainSize += getStainFrom(mat, index1 + 1, index2);
	stainSize += getStainFrom(mat, index1 + 1, index2 + 1);

	return stainSize;
}


int main()
{
	int mat[7][7] = {
		{ 1, 1, 1, 0, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 1, 0 },
		{ 0, 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	int a = getStainFrom(mat, 3, 3, 0);
	printf("Result %d", a);

	return 0;
}
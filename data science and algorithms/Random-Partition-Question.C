#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef enum { FALSE = 0, TRUE = 1 } Boolean;


void Partition(int arr[], int length, int target, int** arrLeft, int** arrRight) // RunTime Complexity is O(N)
{
	int countLeft = 0; int countRight = 0;
	for (int i = 0; i < length; i++)
	{
		if (arr[i] <= target)
			countLeft++;
		else
			countRight++;
	}

	*arrLeft = (int*)malloc(countLeft-- * sizeof(int));
	*arrRight = (int*)malloc(countRight-- * sizeof(int));

	if (arrLeft == NULL || arrRight == NULL)
	{
		puts("NULL ALLOCATION!");
		return;
	}

	for (int i = length-1; i >=0; i--)
	{
		if (arr[i] <= target)
			*(*arrLeft+ countLeft--) = arr[i];
		else
			*(*arrRight + countRight--) = arr[i];
	}


void PrintArr(int arr[], int N)
{
	for (size_t i = 0; i < N; i++)
		printf("[%d]", arr[i]);
	puts("");
}
int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int* arrLeft = NULL;
	int* arrRight = NULL;

	Partition(arr, 10, 6, &arrLeft, &arrRight);
	PrintArr(arrLeft,6);
	PrintArr(arrRight,4);



	return 0;
}

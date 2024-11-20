#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------------------------------------
//   פונקציה מקבלת כפרמטרים את מערכי מצביעים ומחזירה את סכום  איברי "המטריצה
//----------------------------------------------------------------------------------------
int fun1(const int** pLeft, const int** pRight)
{
	int** pright = pRight;
	int sum = 0;
	for (int** leftPtr = pLeft; *leftPtr != NULL; leftPtr++)
	{
		for (int* leftPtrArr = *(leftPtr); leftPtrArr <= *pright; leftPtrArr++)
		{
			sum += *(leftPtrArr);
		}
		*(pright++);
	}
	return sum;
}
//----------------------------------------------------------------------------------------
//   פונקציה מקבלת כפרמטר את אחד ממערכי המספרים. היא תקבל את כתובת
//   ההתחלה וכתובת הסוף ותחזיר את כתובת האיבר המקסימלי שלו בצורה רקורסיבית
//-------------------------------------------------------------------------------------
int* fun2(const int* Start, const int* End)
{
	if (Start >= End)
		return Start;
	int* itemPtr = fun2(Start + 1, End);
	return *Start > *itemPtr ? Start : itemPtr;
}
//----------------------------------------------------------------------------------------
//  פונקציה מקבלת כפרמטרים את שני מערכי מצביעים  
//    :  LEFT, RIGHT.
//   הפונקציה תמצא ותשמור את כתובותיהם של מספרים המקסימליים בכל   
//   אחד ממערכי המספרים בתוך 
//       אותו תקצה דינמית MAX
//-------------------------------------------------------------------------------------
int** fun3(const int** pLeft, const int** pRight)
{
	int** pright = pRight;
	int count = 0;
	int** leftPtr = pLeft;
	while (*leftPtr!=NULL)
	{
		count++;
		leftPtr++;
		printf("count %d\n", count);
	}
	int** newPtrArray = (int**)malloc(count*sizeof(int*));
	if (newPtrArray = NULL)
		return NULL;
	int** pos = newPtrArray;
	printf("New array allocation went well");
	for (leftPtr = pLeft; *leftPtr != NULL; leftPtr++)
	{
		int* maxPtr = fun2(*leftPtr, *pright);
		*pos = maxPtr;
		printf("IM ALIVE 1\n");
		*(pright++);
		printf("IM ALIVE 2\n");
		pos++;
		printf("IM ALIVE 3\n");
	}
}

//----------------------------------------------------------------------------------------
int main()
{
	// מערכים חד מימדיים
	int ar1[] = { 5, 2, 0, 12, 25, 4 };
	int ar2[] = { 7, 13, 2, 1 };
	int ar3[] = { 8, -1, 5, 9, 3 };
	int ar4[] = { 2 };
	int ar5[] = { 1, 4, 3, 2, 7, 23 };
	//  LEFT ו- RIGHT שני מערכי למצביעים מערכים חד מימדיים
	int* Left[] = { ar1, ar2, ar3, ar4, ar5, NULL };
	int* Right[] = { ar1 + sizeof(ar1) / sizeof(int) - 1,
						 ar2 + sizeof(ar2) / sizeof(int) - 1,
						 ar3 + sizeof(ar3) / sizeof(int) - 1,
					 ar4 + sizeof(ar4) / sizeof(int) - 1,
						 ar5 + sizeof(ar5) / sizeof(int) - 1,
						 NULL };

	//  ממצביע למספרים המקסימליים בכל אחד מערכים חד מימדיים
	int** Max, ** startMax;
	int sumOfMax = 0;        //   סכום של מספרים המקסימליים בכל אחד מערכים חד מימדיים

	printf("Sum = %d \n", fun1(Left,Right));
	Max = fun3((const int**)Left, (const int**)Right);
	//  חישוב סכום של מספרים המקסימליים בכל אחד מערכים חד מימדיים 
	for (startMax = Max; Max < startMax + sizeof(Left) / sizeof(int*) - 1; Max++)
		sumOfMax += **Max;
	printf("Sum of max values = %d \n", sumOfMax);

}
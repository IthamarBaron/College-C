//Ithamar Baron 5/12/24
#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define ROWS 10
#define COLS 10
typedef enum { FALSE = 0, TRUE = 1 } Boolean;
typedef int TYPE_ITEM;
typedef struct sparesMat

{
	int row, col;
	TYPE_ITEM info;
	struct sparesMat* nextRow;
	struct sparesMat* nextCol;

}sparesMatNode, * sMatPtr;

// Function to initialize the sparse matrix
sMatPtr Init(int row, int col, TYPE_ITEM x)
{
	sMatPtr mat = (sMatPtr)malloc(sizeof(sparesMatNode));
	if (mat == NULL)
	{
		printf("Allocation failed\n");
		return NULL;
	}
	mat->col = col;
	mat->row = row;
	mat->info = x;
	mat->nextRow = mat;
	mat->nextCol = mat;
	return mat;
}

// Function to check if the matrix is empty
Boolean IsEmpty(sparesMatNode* mat)
{
	return mat->nextCol == mat || mat->nextRow == mat ? TRUE : FALSE;
}

void printRowsAndColsCount(sparesMatNode* mat) {
	int rowCount = 0;
	int colCount = 0;
	sMatPtr headCol = mat;
	sMatPtr headRow = mat;
	while (headCol->nextCol != mat)
	{
		colCount++;
		headCol = headCol->nextCol;
	}
	while (headRow->nextRow != mat)
	{
		rowCount++;
		headRow = headRow->nextRow;
	}


	printf("Number of rows: %d\n", rowCount);
	printf("Number of columns: %d\n", colCount);
}

// Function to insert a value into the matrix at a given position
//TAKES ROW ANC COL FROM 0 0 TO  N M. ajusts to fit format in the image!
void InsertToMatrix(sparesMatNode* mat, int row, int col, TYPE_ITEM x)
{
	row++; col++;

	sMatPtr rowHead = mat;
	while (rowHead->nextRow != mat && rowHead->nextRow->row < row)
	{
		rowHead = rowHead->nextRow;
	}
	if (rowHead->nextRow == mat || rowHead->nextRow->row > row)
	{
		sMatPtr newRow = Init(row, 0, -1);
		newRow->nextRow = rowHead->nextRow;
		rowHead->nextRow = newRow;
	}
	sMatPtr targetRow = rowHead->nextRow;

	sMatPtr colHead = mat;
	while (colHead->nextCol != mat && colHead->nextCol->col < col)
	{
		colHead = colHead->nextCol;
	}
	if (colHead->nextCol == mat || colHead->nextCol->col > col)
	{
		sMatPtr newCol = Init(0, col, -1);
		newCol->nextCol = colHead->nextCol;
		colHead->nextCol = newCol;
	}
	sMatPtr targetCol = colHead->nextCol;

	sMatPtr newNode = Init(row, col, x);

	sMatPtr rowPtr = targetRow;
	while (rowPtr->nextCol != targetRow && rowPtr->nextCol->col < col)
	{
		rowPtr = rowPtr->nextCol;
	}
	newNode->nextCol = rowPtr->nextCol;
	rowPtr->nextCol = newNode;

	sMatPtr colPtr = targetCol;
	while (colPtr->nextRow != targetCol && colPtr->nextRow->row < row)
	{
		colPtr = colPtr->nextRow;
	}
	newNode->nextRow = colPtr->nextRow;
	colPtr->nextRow = newNode;
}

void InsertAfter(sMatPtr rowBefore, sMatPtr colBefore, TYPE_ITEM X)
{
	sMatPtr newNode = Init(rowBefore->row, colBefore->col, X);

	sMatPtr nextAfterRows = rowBefore->nextCol;
	if (nextAfterRows->col != 0)
		nextAfterRows = nextAfterRows->nextCol;

	rowBefore->nextCol = newNode;
	newNode->nextCol = nextAfterRows;

	sMatPtr nextAfterCols = colBefore->nextRow;
	if (nextAfterCols->row != 0)
		nextAfterCols = nextAfterCols->nextCol;

	colBefore->nextRow = newNode;
	newNode->nextRow = nextAfterCols;

}

TYPE_ITEM DeleteAfter(sMatPtr rowBefore, sMatPtr colBefore)
{
	if (rowBefore != NULL && colBefore != NULL)
	{
		rowBefore->nextCol = rowBefore->nextCol->nextCol;
		sMatPtr* toRemove = colBefore->nextRow;
		colBefore->nextRow = colBefore->nextRow->nextRow;
		TYPE_ITEM value = (*toRemove)->info;
		free(*toRemove);
		return value;
	}
	return FALSE;//0 - values in spares matrix will never be 0 
}

sMatPtr FindAbove(sMatPtr mat, int row, int col)
{
	if (IsEmpty(mat))
		return NULL;
	sMatPtr headRows = mat;
	for (size_t i = 0; i < col; i++)
		headRows= headRows->nextCol;
	sMatPtr headColl = headRows;
	if (headRows->nextRow == headRows)
		return headRows;
	while (headColl->nextRow != headColl && headColl->nextRow->row < row )
		headColl = headColl->nextRow;
	return headColl;

}

sMatPtr FindBefore(sMatPtr mat, int row, int col)
{
	if (IsEmpty(mat))
		return NULL;

	sMatPtr headCols = mat;
	for (size_t i = 0; i < row; i++)
		headCols = headCols->nextRow;

	sMatPtr headRow = headCols;
	if (headCols->nextCol == headCols)
		return headCols;

	while (headRow->nextCol != headRow && headRow->nextCol->col < col)
		headRow = headRow->nextCol;

	return headRow;
}

void printSparesMatrix(sparesMatNode* mat) {
	sparesMatNode* row = mat->nextRow;

	while (row != mat) {
		sparesMatNode* col = row->nextCol;

		while (col != row) {
			printf("Value at (%d, %d): %d\n", col->row - 1, col->col - 1, col->info);
			col = col->nextCol;
		}

		row = row->nextRow;
	}
}

TYPE_ITEM RetrieveSparesMatrix(sMatPtr mat, int row, int col) {
	sMatPtr currentRow = mat->nextRow;
	while (currentRow != mat && currentRow->row < row + 1) {
		currentRow = currentRow->nextRow;
	}
	if (currentRow->row != row + 1) {
		return -1; 
	}
	sMatPtr currentCol = currentRow->nextCol;
	while (currentCol != currentRow && currentCol->col < col + 1) {
		currentCol = currentCol->nextCol;
	}
	if (currentCol->col != col + 1) {
		return -1; 
	}
	return currentCol->info;
}

// Function to multiply a row by a scalar value
void MultiplyRow(sMatPtr mat, int row, int scalar) {
	sMatPtr currentRow = mat->nextRow;
	while (currentRow != mat && currentRow->row < row + 1) {
		currentRow = currentRow->nextRow;
	}
	if (currentRow->row != row + 1) {
		return; 
	}
	sMatPtr currentCol = currentRow->nextCol;
	while (currentCol != currentRow) {
		currentCol->info *= scalar;
		currentCol = currentCol->nextCol;
	}
}

int main()
{
	sparesMatNode* matrix = Init(0, 0, -1);
	InsertToMatrix(matrix, 2, 0, -2);
	InsertToMatrix(matrix, 1, 1, 2);
	InsertToMatrix(matrix, 1, 3, 3);
	InsertToMatrix(matrix, 2, 1, 4);
	InsertToMatrix(matrix, 3, 2, -1);
	InsertToMatrix(matrix, 3, 3, 8);

	printSparesMatrix(matrix);

	int row, col;
	printf("Enter row and column to retrieve value: ");
	scanf("%d %d", &row, &col);
	TYPE_ITEM value = RetrieveSparesMatrix(matrix, row, col);
	if (value == -1)
		printf("Value at (%d, %d) does not exist.\n", row, col);
	else
		printf("Value at (%d, %d): %d\n", row, col, value);

	int scalar;
	printf("Enter row and a num to multiply: ");
	scanf("%d %d", &row, &scalar);
	MultiplyRow(matrix, row, scalar);

	printSparesMatrix(matrix);

	return 0;
}

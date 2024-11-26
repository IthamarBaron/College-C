#pragma once

typedef int matrix_type;
typedef struct matrix_type 
{
	int** mat;
	int rows;
	int cols;

}matrix, *matrixPtr;

matrixPtr InnitMatrix(int rows, int cols);
void FillMatrix(matrixPtr m, matrix_type filler);
void PrintMatrix(matrixPtr m);
void InputMatrix(matrixPtr m);
void FreeMatrix(matrixPtr m);
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include "DMatrix.h"

matrixPtr InnitMatrix(int rows, int cols)
{
	matrixPtr DMat = (matrixPtr)malloc(sizeof(matrix)); //struct allocation
	if (DMat== NULL)return NULL;
	DMat->cols = cols;
	DMat->rows = rows;
	DMat->mat = (int**)malloc(rows * sizeof(matrix_type*));//rows allocation
	if (DMat->mat == NULL)return NULL;
	DMat->mat[0] = (int*)malloc((cols * rows) * sizeof(matrix_type));//items allocation
	for (size_t i = 1; i <= cols-1; i++)
		DMat->mat[i] = DMat->mat[i - 1] + cols;
	return DMat;
}

/// <summary>
///method to fill a matrix made for me and is unrelated to the question 
/// </summary>
/// <param name="m">matrix to fill</param>
/// <param name="filler">item to fill with. [-1] for assending mat (0 - legth-1)/param>
void FillMatrix(matrixPtr m, matrix_type filler)
{
	int length = (m->rows) * (m->cols);
	for (size_t i = 0; i < length; i++)
		m->mat[0][i] = filler == -1 ? i :filler;
}
void PrintMatrix(matrixPtr m)
{
	printf("======Matrix Info======\n");
	printf("\tRows %d\n", m->rows);
	printf("\tCols %d\n", m->cols);
	printf("\tLength %d\n", m->cols*m->rows);
	printf("=========Matrix=========\n");

	for (size_t i = 0; i < m->rows; i++)
	{
		for (size_t j = 0; j < m->cols; j++)
			printf("[%d] ", m->mat[i][j]);
		printf("\n");
	}
}

void InputMatrix(matrixPtr m)
{

	matrix_type temp;
	int length = (m->rows) * (m->cols);
	printf("Fill [%d by %d] matrix!\n",(m->rows) , (m->cols));
	for (size_t i = 0; i < length; i++)
	{
		printf("\nInput item. (%d out of %d remaining): ", length - i, length);
		scanf("%d", &temp);
		m->mat[0][i] = temp;
	}

}

void FreeMatrix(matrixPtr m)
{
	free(m->mat[0]);
	free(m);
}

int main()
{
	matrixPtr matrix = InnitMatrix(3, 3);
	InputMatrix(matrix);
	PrintMatrix(matrix);

	return 0;
}
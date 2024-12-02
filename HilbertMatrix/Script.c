#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include "DMatrix.h"


void HilbertMat(matrixPtr Dmat)
{
	int rows = Dmat->rows;
	int cols = Dmat->cols;
	for (int i = 1; i < rows+1; i++)
	{
		for (int j = 1; j < cols+1; j++)
		{
			Dmat->mat[i-1][j-1] = (float)(1.0f / (float)(i + j - 1));
		}
	}
}
matrixPtr MulMats(const matrixPtr A,const matrixPtr B)
{
    if (A->cols != B->rows)
        return NULL;
    matrixPtr result = InnitMatrix(A->rows, B->cols);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->cols; j++)
        {
            result->mat[i][j] = 0;
            for (int k = 0; k < A->cols; k++)
                result->mat[i][j] += A->mat[i][k] * B->mat[k][j];
        }
    }

    return result;
}


int main(int argc, char* argv[])
{
    if (argc-1 < 4) //2 for each matrix (-1) for program name
    {
        printf("Invalid Params!\n");
        return -1;
    }

	matrixPtr matrix = InnitMatrix(atoi(argv[1]), atoi(argv[2]));
    HilbertMat(matrix);
    matrixPtr matrix2 = InnitMatrix(atoi(argv[3]), atoi(argv[4]));
	HilbertMat(matrix2);
    matrixPtr matrix3 = MulMats(matrix, matrix2);
	PrintMatrix(matrix3);

	return 0;
}
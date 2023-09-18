#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** make2dArray(int rows, int cols);

int main(void)
{
	int** ipp;
	int i, j, rows, cols;

	printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
	scanf("%d %d", &rows, &cols);
	ipp = make2dArray(rows, cols);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("ipp[%d][%d] =%2d ", i, j, ipp[i][j]);
		printf("\n");
	}


	return 0;

}

int** make2dArray(int rows, int cols)
{
	int** out;
	srand(time(NULL));

	out = (int**)malloc(sizeof(int*) * rows);

	for (int i = 0; i < rows; i++)
		out[i] = (int*)malloc(sizeof(int) * cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			out[i][j] = rand() % 100;

	return out;
}
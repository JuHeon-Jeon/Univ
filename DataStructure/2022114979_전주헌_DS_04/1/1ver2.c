#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int row;
	int col;
	int val;
} sparceMatrix;

int main(void)
{
	int matrix[20][20];
	sparceMatrix* sM;
	int input, row, col, val, index = 1;
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			matrix[i][j] = 0;

	printf("원소의 개수를 쓰시오 .. ");
	scanf("%d", &input);

	sM = (sparceMatrix*)malloc(sizeof(sparceMatrix) * (input + 1));
	sM[0].row = 20;
	sM[0].col = 20;
	sM[0].val = input;

	for (int i = 0; i < input;)//making Matrix
	{
		if (val = rand() % 100)
		{
			row = rand() % 20;
			col = rand() % 20;
			if (!matrix[row][col])
				matrix[row][col] = val;
			i++;
		}
	}

	printf("Random generated Matrix(20, 20)\n");
	for (int i = 0; i < 20; i++)//print Matrix & make sparceMatrix
	{
		for (int j = 0; j < 20; j++)
		{
			printf("%5d", matrix[i][j]);
			if (matrix[i][j])
			{
				sM[index].row = i;
				sM[index].col = j;
				sM[index].val = matrix[i][j];
				index++;
				if (index > input + 1)
				{
					printf("index error!\n");
					exit(stderr);
				}
			}
		}
		printf("\n");
	}

	printf("sparce matrix\n");
	for (int i = 0; i <= input; i++)
		printf("%5d, %5d %5d\n", sM[i].row, sM[i].col, sM[i].val);

	return 0;
}
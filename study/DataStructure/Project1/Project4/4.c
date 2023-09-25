#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sumAry_f1(int ary[][3], int row, int col);
int sumAry_f2(int(*ary)[3], int row, int col);
int sumAry_f3(int ary[2][3], int row, int col);


int main(void)
{
	int ary[][3] = { {1, 2, 3}, {4, 5, 6} };
	int row = 2, col = 3;

	printf("sumAry_f1() %d\n", sumAry_f1(ary, row, col));
	printf("sumAry_f2() %d\n", sumAry_f2(ary, row, col));
	printf("sumAry_f3() %d\n", sumAry_f3(ary, row, col));


	return 0;
}

int sumAry_f1(int ary[][3], int row, int col)
{
	int out = 0;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			out += ary[i][j];

	return out;
}
int sumAry_f2(int(*ary)[3], int row, int col)
{
	int out = 0;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			out += *(*(ary + i) + j);

	return out;
}
int sumAry_f3(int ary[2][3], int row, int col)
{
	int out = 0;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			out += ary[i][j];

	return out;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int ary1[] = { 8, 2, 8 };
	int* pAry = ary1;

	printf("ary1를 이용한 출력\n");
	for (int i = 0; i < 3; i++)
		printf("%d ", ary1[i]);
	printf("\n\n");

	printf("pAry를 이용한 출력\n");
	for (int i = 0; i < 3; i++)
		printf("%d ", *(pAry + i));
	printf("\n\n\n\n");

	int* pAry2[2];

	int ary2[][3] = { {4, 2, 3}, {5, 2, 3} };
	pAry2[0] = ary2;
	pAry2[1] = ary2[1];


	printf("ary2를 이용한 출력\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%d ", ary2[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("pAry2를 이용한 출력\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%d ", *(pAry2[i] + j));
		printf("\n");
	}
	printf("\n\n\n\n");

	int ary3[][2][3] = { { {1, 2, 3} , {4, 5, 6} } , { {7, 8, 9}, {10, 11, 12} } };
	pAry = ary3;

	printf("ary3를 이용한 출력\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 3; k++)
				printf("%d ", ary3[i][j][k]);
			printf("\n");
		}
		printf("\n\n");
	}
	printf("\n");

	printf("pAry를 이용한 출력\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 3; k++)
				printf("%d ", *(pAry + i * 2 * 3 + j * 3 + k));
			printf("\n");
		}
		printf("\n\n");
	}






	return 0;
}
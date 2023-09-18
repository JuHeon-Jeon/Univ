#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* make1dArray(int num);

int main(void)
{
	int* ipp;
	int i, num;

	printf("일차원 배열의 수를 입력하세요: ");
	scanf("%d", &num);


	ipp = make1dArray(num);
	for (i = 0; i < num; i++)
	{
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");
	}

	return 0;
}

int* make1dArray(int num)
{
	int* out;
	srand(time(NULL));

	out = (int*)malloc(sizeof(int) * num);

	for (int i = 0; i < num; i++)
		*(out + i) = rand() % 100;

	return out;
}
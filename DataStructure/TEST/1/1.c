#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int biggest(int* array);

int main(void)
{
	int max = 0;
	int array[5];

	printf("숫자를 입력하세요 : ");
	for (int i = 0; i < 5; i++)
		scanf("%d", &array[i]);

	max = biggest(array);

	printf("\n가장 큰 수는 : %d", max);

	return 0;
}

int biggest(int* array)
{
	int tmp = *array;

	for (int i = 0; i < 5; i++)
	{
		if (tmp < *array)
			tmp = *array;
		array++;
	}

	return tmp;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	int size, tmp, index, flag = 0;
	int* arr;

	for (int i = 0; i < 2; i++)
	{
		srand((unsigned int)time(NULL));
		printf("일차원 배열의 수를 입력하세요: ");
		scanf("%d", &size);
		arr = (int*)malloc(sizeof(int) * size);
		
		for (int j = 0; j < size; j++)
		{
			int tmp = rand();
			arr[j] = tmp % 100;
			printf("(%p)%-10d", arr[j], arr[j]);
		}
		
		printf("\n정렬결과\n");

		//array alignment
		index = size;
		do {
			index++;

			if (index >= size)
			{
				index = 0;
				flag = 0;
				for (int j = 1; j < size; j++)
				{
					//check if array is aligned
					if (arr[j - 1] > arr[j])
						flag = 1;
				}
			}
			else
			{
				if (index)
				{
					//aligning array
					if (arr[index - 1] > arr[index])
					{
						tmp = arr[index];
						arr[index] = arr[index - 1];
						arr[index - 1] = tmp;
					}
				}
				else
				{
					printf("index is below 0");
					exit(1);
				}

			}

		} while (flag);

		//print array
		for (int j = 0; j < size; j++)
			printf("%-10d", arr[j]);
		printf("\n");




		/*
		for (int j = 0; j < size; j++)
		{
			tmp = arr[0];
			index = 0;
			for (int k = 0; k < size; k++)
			{
				if (tmp > arr[k])
				{
					arr[index] = arr[k];
					index = k;
					arr[k] = tmp;
					tmp = arr[index];
				}
			}
		}
		*/
	}
}
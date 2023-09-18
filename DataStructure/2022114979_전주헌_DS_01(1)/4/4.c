#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>


void seleSort(int* arr, int size);
int binSrch(int* arr, int target, int left, int right);
int determine(int arr, int target);

int main(void)
{
	int input, random, arr[100], srchIn, srchOut;
	srand((unsigned int)time(NULL));

	printf("Enter the number of numbers to generate: ");
	scanf("%d", &input);

	if (input >= 100)
	{
		printf("You must type less than 100!");
		exit(1);
	}

	for (int i = 0; i < input; i++)
	{
		random = rand();
		arr[i] = random;
		printf("%-10d", arr[i]);
	}

	seleSort(arr, input);


	printf("\n\nSorted array:\n");
	for (int i = 0; i < input; i++)
		printf("%-10d", arr[i]);
	printf("\n");

	printf("Enter the number to search: ");
	scanf("%d", &srchIn);

	srchOut = binSrch(arr, srchIn, 0, input - 1);

	if (srchOut >= 0)
		printf("The search number is present in list[%d]\n", srchOut);
	else
		printf("%d is not present in array\n", srchIn);

	return 0;
}

void seleSort(int* arr, int size)
{
	int flag = 1, tmp, min, index;

	for (int i = 0; i < size; i++)
	{
		min = arr[i];
		index = i;
		//find min
		for (int j = i; j < size; j++)
		{
			if (min > arr[j])
			{
				index = j;
				min = arr[j];
			}
		}
		//swap min if min is found
		if (index > i)
		{
			arr[index] = arr[i];
			arr[i] = min;
		}
	}
}

int binSrch(int* arr, int target, int left, int right)
{
	int mid = left + ((right - left) / 2);

	printf("call binsearch_recur, left=%d, right=%d\n", left, right);

	if (mid > 0)
	{
		switch (determine(arr[mid], target))
		{
		case 1:
			binSrch(arr, target, mid + 1, right);
			break;
		case 0:
			return mid;
		case -1:
			binSrch(arr, target, left, mid - 1);
			break;
		}
	}
	else if (mid == 0)
	{
		if (!determine(arr[right], target))
			return right;
		else
			return -1;
	}
	else
		return -1;
}

int determine(int arr, int target)
{
	//target bigger -> 1 target smaller -> -1 target match -> 0
	if (arr < target)
		return 1;
	else if (arr > target)
		return -1;
	else
		return 0;
}
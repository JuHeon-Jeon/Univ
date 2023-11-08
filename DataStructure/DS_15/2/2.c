#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 500


int* treeIndex;

void makeWinner(int arr[], int max);
void inorder(int max, int arr[]);
int sort(int arr[], int max);

int main(void)
{
	int seed, k, num;
	int fail = 1;
	int* arr = NULL;
	int* result = NULL;

	//print
	printf("<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>\n\n");
	printf("the number of keys ( 4, 8, 16, or 32 as a power of 2) >> ");
	do
	{
		scanf("%d", &k);
		if (!(k % 2))
			fail = 0;
	} while (fail);
	printf("value of seed >> ");
	scanf("%d", &seed);
	srand(seed);
	//initalization
	arr = (int*)malloc(sizeof(int) * k);
	result = (int*)malloc(sizeof(int) * k);

	treeIndex = (int*)malloc(sizeof(int) * (2 * k));
	//get random num into arr
	for (int i = 0; i < k; i++)
	{
		num = rand() % MAX_NUM + 1;
		printf("%5d", num);
		arr[i] = num;
	}
	//initialize min-winner tree
	printf("\n\ninitialization of min-winner tree\n");
	makeWinner(arr, k);
	//inorder traversal
	printf("\ninorder traversal for min-winner tree\n");
	inorder(k, arr);
	printf("\n");
	//find 2 winners
	for (int i = 0; i < 2; i++)
		result[i] = sort(arr, k);
	//inorder traversal
	printf("Winner Tree inoder traversal after find 2 winners...\n");
	inorder(k, arr);
	//sort
	printf("\n\nsorting with min-winner tree...\n");
	for (int i = 2; i < k; i++)
		result[i] = sort(arr, k);
	//print
	printf("\nsorted result\n");
	for (int i = 0; i < k; i++)
		printf("%5d", result[i]);
	printf("\n");

	return 0;
}
void makeWinner(int arr[], int max)
{
	int indexMax = max * 2 - 1;
	int index;

	for (int i = 0; i < max; i++)
	{
		index = indexMax - (max - 1) + i;
		treeIndex[index] = i;
	}

	int count = max;

	while (count > 1)
	{
		indexMax = indexMax - count;
		count = count / 2;
		index = indexMax - count + 1;
		for (int i = 0; i < count; i++)
		{
			if (arr[treeIndex[index * 2]] > arr[treeIndex[index * 2 + 1]])
				treeIndex[index] = treeIndex[index * 2 + 1];
			else
				treeIndex[index] = treeIndex[index * 2];

			index++;
		}
	}
}
void inorder(int max, int arr[])
{
	int indexMax = max * 2 - 1;
	int stack[MAX_NUM];
	int top = -1;
	int index = 1;
	int arrIndex;

	for (;;)
	{
		for (; index <= indexMax; index = index * 2)
			stack[++top] = index;
		index = stack[top--];
		if (index < 0)
			break;
		arrIndex = treeIndex[index];
		printf("%5d", arr[arrIndex]);
		index = index * 2 + 1;
	}
}
int sort(int arr[], int max)
{
	int rtnIndex = treeIndex[1];
	int rtn = arr[rtnIndex];
	int indexMax = max * 2 - 1;
	int indexLast = indexMax - max + 1;
	int index = indexLast + rtnIndex;

	arr[treeIndex[index]] = 9999;
	index /= 2;

	while (index)
	{
		if (arr[treeIndex[index * 2]] > arr[treeIndex[index * 2 + 1]])
			treeIndex[index] = treeIndex[index * 2 + 1];
		else
			treeIndex[index] = treeIndex[index * 2];

		index /= 2;
	}

	return rtn;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 500


int* treeIndex;

void makeWinner(int arr[], int max);
void inorder(int max);

int main(void)
{
	int seed, k, num;
	int fail = 1;
	int* arr = NULL;

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
	inorder(k);
	printf("\n");
	//find 2 winners

	//inorder traversal
	printf("Winner Tree inoder traversal after find 2 winners...\n");
	inorder(k);




	return 0;
}
void makeWinner(int arr[], int max)
{
	int indexMax = max * 2 - 1;
	int index = -1;

	for (int i = 0; i < max; i++)
	{
		index = indexMax - (max - 1) + i;
		treeIndex[index] = arr[i];
	}

	int count = max;
	//need fix
	while (count)
	{
		indexMax = indexMax - count;
		count = count / 2;
		index = indexMax - count;
		for (int i = 0; i < count; i++)
		{
			if (treeIndex[index * 2] > treeIndex[index * 2 + 1])
				treeIndex[index] = treeIndex[index * 2 + 1];
			else
				treeIndex[index] = treeIndex[index * 2];

			index++;
		}
	}
}
void inorder(int max)
{
	int indexMax = max * 2 - 1;
	int stack[MAX_NUM];
	int top = -1;
	int index = 1;

	for (;;)
	{
		for (; index <= indexMax; index = index * 2)
			stack[++top] = index;
		index = stack[top--];
		if (index < 0)
			break;
		printf("%5d", treeIndex[index]);
		index = index * 2 + 1;
	}


}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



void makeWinner(int tree[16], int run[8][11]);
int sort(int tree[16], int run[8][11], int runIndex[8]);



int main(void)
{
	FILE* fp = NULL;
	int run[8][11];
	int sorted[80];
	int input;
	int tree[16];
	int runIndex[8] = { 0 };

	//read run from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	printf("<<<<<<<<run data>>>>>>>>\n\n");
	
	for (int i = 0; i < 8; i++)
	{
		printf("%d-th run:\n", i + 1);
		for (int j = 0; j < 10; j++)
		{
			fscanf(fp, "%d", &input);
			printf("%5d", input);
			run[i][j] = input;
		}
		run[i][10] = 9999;
		printf("\n");
	}

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//make min-winner tree
	makeWinner(tree, run);
	//levelorder
	printf("\nLevel-order traversal for initial min-winner tree\n");
	for (int i = 1; i < 16; i++)
		printf("%4d", run[tree[i]][0]);
	printf("\n");
	//sort
	printf("\nsorting with min-winner tree...\n");
	for (int i = 0; i < 80; i++)
		sorted[i] = sort(tree, run, runIndex);
	//print
	printf("\nsorted result\n");
	input = 0;
	for (int i = 0; i < 80; i++)
	{
		input = (input + 1) % 8;
		printf("%3d ", sorted[i]);
		if (!input)
			printf("\n");
	}

	return 0;
}
void makeWinner(int tree[16], int run[8][11])
{
	int index = 8;
	
	for (int i = 0; i < 8; i++)
		tree[i + index] = i;
	
	index /= 2;

	while (index)
	{
		for (int i = 0; i < index; i++)
		{
			if (run[tree[(index + i) * 2]][0] > run[tree[(index + i) * 2 + 1]][0])
				tree[index + i] = tree[(index + i) * 2 + 1];
			else
				tree[index + i] = tree[(index + i) * 2];
		}

		index /= 2;
	}
}
int sort(int tree[16], int run[8][11], int runIndex[8])
{
	int rtnIndex = tree[1];
	int rtn = run[rtnIndex][runIndex[rtnIndex]];
	int start = 8;
	int index = (start + rtnIndex) / 2;

	runIndex[rtnIndex]++;

	while (index)
	{
		if (run[tree[index * 2]][runIndex[tree[index * 2]]] > run[tree[index * 2 + 1]][runIndex[tree[index * 2 + 1]]])
			tree[index] = tree[index * 2 + 1];
		else
			tree[index] = tree[index * 2];

		index /= 2;
	}

	return rtn;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNum[8];
int rndnum = 1;
int size = 0;
int comparison;


int ht[8];

int h(int key);
void insert(int item);
int search(int item);

int main(void)
{
	FILE* fp = NULL;

	int input;
	int ary[8];
	for (int i = 0; i < 8; i++)
		ary[i] = -1;

	//read input from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	printf("key sequence from file :");
	while (!feof(fp))
	{
		input = -1;
		fscanf(fp, "%d", &input);
		if (input != -1)
		{
			printf("%5d", input);
			ary[size++] = input;
		}
	}
	printf("\n");

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//initialize randNum
	printf("input seed >> ");
	scanf("%d", &input);
	srand(input);
	printf("\n\n");

	for (int i = 1; i < 8; i++)
	{
		randNum[i] = rand() % 7 + 1;

		for (int j = 1; j < i; j++)
			if (randNum[i] == randNum[j])
				i--;
	}
	for (int i = 1; i < 8; i++)
		printf("randNum[%d] : %d\n", i, randNum[i]);

	
	printf("\n");
	//insert table
	for (int i = 0; i < size; i++)
		insert(ary[i]);
	//print table
	printf("%13s\n", "key");
	for (int i = 0; i < 8; i++)
	{
		printf("ht[%2d] :", i);
		if (ht[i])
			printf("%5d", ht[i]);
		printf("\n");
	}
	printf("\n");
	//search
	int comp;
	while (1)
	{
		printf("input 0 to quit\n");
		printf("key to search >> ");
		scanf("%d", &input);

		if (!input)
			break;

		comp = search(input);

		if (comp)
			printf("key : %d, the number of comparisions : %d\n\n", input, comp);
		else
			printf("it doesn't exist!\n\n");
	}

	return 0;
}
int h(int key)
{
	int rtn = key % 8;
	return rtn;
}
void insert(int item)
{
	int k = h(item);

	if (ht[k])
	{
		for (int i = 1; i < 8; i++)
		{
			k = (h(item) + randNum[i]) % 8;
			if (!ht[k])
				break;
		}

		if (k == h(item))
		{
			printf("cannot insert, table is full\n");
			exit(stderr);
		}
	}

	ht[k] = item;
}
int search(int item)
{
	int key = h(item);
	rndnum = 1;
	comparison = 0;

	while (1)
	{
		comparison++;

		if (ht[key] == item)
			break;
		if (rndnum > 7)
			return 0;

		key = (h(item) + randNum[rndnum]) % 8;
		
		rndnum++;
	}

	return comparison;
}
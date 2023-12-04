#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int ht[11];
char itemTable[11][10];


int stringToInt(char* key);
int h(int k);
void insert(int key, char* item);
int search(char* item);

int main(void)
{
	FILE* fp = NULL;
	int key;
	char item[10];

	//initialize table
	for (int i = 0; i < 11; i++)
	{
		ht[i] = 0;
		for (int j = 0; j < 10; j++)
			itemTable[i][j] = NULL;
	}

	//get input
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	printf("input strings : ");

	while (!feof(fp))
	{
		fscanf(fp, "%s", &item);
		key = stringToInt(item);
		insert(key, item);
		printf("%s ", item);
	}
	printf("\n\n");

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//print table
	printf("%18s%10s\n", "item", "key");
	for (int i = 0; i < 11; i++)
	{
		printf("ht[%2d] :", i);
		if (ht[i])
			printf("%10s%10d", itemTable[i], ht[i]);
		printf("\n");
	}
	printf("\n");

	//search
	printf("string to search >>");
	scanf("%s", &item);

	int comparison = search(item);

	if (comparison)
		printf("item : %s, key : %d, the number of comparisions : %d\n", item, stringToInt(item), comparison);
	else
		printf("it doesn't exist!\n");

	return 0;
}
int stringToInt(char* key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}
int h(int k)
{
	int rtn;
	rtn = k % 11;
	return rtn;
}
void insert(int key, char* item)
{
	int k = h(key);

	while (ht[k])
	{
		k = k + 1 % 11;

		if (k == h(key))
		{
			printf("cannot insert ht is full!\n");
			exit(stderr);
		}
	}

	ht[k] = key;
	strcpy(itemTable[k], item);
}
int search(char* item)
{
	int comparison = 0;
	int key = stringToInt(item);
	int k = h(key);

	while (1)
	{
		comparison++;
		if (ht[k] == key)
			break;
		k = (k + 1) % 11;
		if (k == h(key))
			return 0;
	}

	return comparison;

}
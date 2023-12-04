#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET 11

typedef struct element* elementLink;
typedef struct element
{
	char item[10];
	int key;
	elementLink link;
} element;

elementLink ht[BUCKET];

int comparison;

int stringToInt(char* key);
void insert(int key, char* item);
int search(char* item);
int h(int key);




int main(void)
{
	FILE* fp = NULL;
	char item[10];
	int key;
	elementLink ptr = NULL;

	for (int i = 0; i < BUCKET; i++)
		ht[i] = NULL;

	//get input and insert
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
	//print hashtable
	printf("%14s%5s\n", "item", "key");
	for (int i = 0; i < BUCKET; i++)
	{
		printf("ht[%2d] : ", i);
		ptr = ht[i];
		while (ptr)
		{
			printf("(%s %d) ", ptr->item, ptr->key);
			ptr = ptr->link;
		}
		printf("\n");
	}
	//search
	int comp;
	while (1)
	{
		printf("input 0 to quit\n");
		printf("key to search >> ");
		scanf("%s", &item);

		if (!strcmp("quit", item))
			break;

		comp = search(item);

		if (comp)
			printf("item: %s, key : %d, the number of comparisions : %d\n\n", item, stringToInt(item), comp);
		else
			printf("it doesn't exist!\n\n");
	}


	return 0;
}
int stringToInt(char* key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}
void insert(int key, char* item)
{
	int k = h(key);

	elementLink ptr = NULL;
	elementLink tmp = NULL;
	tmp = (elementLink)malloc(sizeof(element));
	strcpy(tmp->item, item);
	tmp->key = key;
	tmp->link = NULL;

	ptr = ht[k];

	if (ptr)
	{
		for (ptr; ptr->link; ptr = ptr->link);

		ptr->link = tmp;
	}
	else
		ht[k] = tmp;
}
int search(char* item)
{
	int key = stringToInt(item);
	int k = h(key);
	comparison = 0;

	elementLink ptr = ht[k];

	while (ptr)
	{
		comparison++;
		
		if (ptr->key == key)
			return comparison;

		ptr = ptr->link;
	}

	return 0;
}
int h(int key)
{
	int rtn = key % BUCKET;
	return rtn;
}
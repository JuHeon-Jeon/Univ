#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
	int data;
	struct listNode* link;
} listNode;

listNode* first = NULL;

void listAdd(listNode** first, listNode* x, int data);
void listDelete(listNode** first, listNode* trail, listNode* x);
listNode* listCompare(listNode* first, int data);
void listPrint(listNode* first);
void listDelOdd(listNode** first);
void deleteList(listNode** first);

int main(void)
{
	FILE* fp = NULL;
	int input;
	listNode* target = NULL;

	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}
	//read file & sort
	while (!feof(fp))
	{
		//get data
		fscanf(fp, "%d", &input);
		//compare data to list, get position
		target = listCompare(first, input);
		//insert to target
		listAdd(&first, target, input);
	}
	//close file
	if (fclose(fp) == EOF)
	{
		printf("error closing \"input.txt\"\n");
		exit(stderr);
	}
	//print list
	listPrint(first);
	//delete odd
	listDelOdd(&first);
	//print list
	printf("\nAfter deleting nodes with odd value\n\n");
	listPrint(first);
	//delete list
	deleteList(&first);


	return 0;
}
//add list after x
void listAdd(listNode** first, listNode* x, int data)
{
	//make list
	listNode* tmp;
	tmp = (listNode*)malloc(sizeof(listNode));
	tmp->data = data;

	//link
	if (*first)
	{
		if (x)
		{
			tmp->link = x->link;
			x->link = tmp;
		}
		else
		{
			tmp->link = *first;
			*first = tmp;
		}
	}
	else
	{
		tmp->link = NULL;
		*first = tmp;
	}
}
//delete list x, trail is one before x
void listDelete(listNode** first, listNode* trail, listNode* x)
{
	if (*first)
	{
		if (trail)
			trail->link = x->link;
		else
			*first = (*first)->link;
	}
	else
	{
		printf("error listDelete : no item in list\n");
		exit(stderr);
	}

	free(x);
}
//return equal or one bit smaller position
listNode* listCompare(listNode* first, int data)
{
	listNode* out = first;
	listNode* before = NULL;

	if (out)
		//compare current link to data
		while (out)
		{
			//data <= link
			//insert here
			if (data <= out->data)
				break;
			//data > link
			//next link
			else
			{
				before = out;
				out = out->link;
			}
		}

	return before;
}
void listPrint(listNode* first)
{
	listNode* now = first;
	int index = 1;

	if (now)
	{
		printf("The ordered list contains:\n");
		while (now)
		{
			printf("(%p,%7d,%p)", now, now->data, now->link);
			if (!index)
				printf("\n");

			index = (index + 1) % 3;
			now = now->link;
		}
	}
	else
		printf("empty list!\n");
}
void listDelOdd(listNode** first)
{
	listNode* ptr = *first;
	listNode* trail = NULL;

	while (ptr)
	{
		if (ptr->data % 2)
		{
			listDelete(first, trail, ptr);
			if (trail)
				ptr = trail->link;
			else
				ptr = *first;
		}
		else
		{
			trail = ptr;
			ptr = ptr->link;
		}
	}
}
void deleteList(listNode** first)
{
	listNode* ptr = *first;
	listNode* trail = NULL;

	while (ptr)
	{
		trail = ptr;
		ptr = ptr->link;

		free(trail);
	}
}
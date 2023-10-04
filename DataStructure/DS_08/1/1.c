#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void listAdd(listPointer* first, listPointer x, int data);
void listDelete(listPointer* first, listPointer trail, listPointer x);
listPointer listCompare(listPointer first, int data);
void listPrint(listPointer first);
void listDelOdd(listPointer* first);
void deleteList(listPointer* first);

int main(void)
{
	FILE* fp = NULL;
	int input;
	listPointer target;

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
	printf("\nAfter deleting nodes with odd value\n");
	listPrint(first);
	//delete list
	deleteList(&first);


	return 0;
}
//add list after x
void listAdd(listPointer* first, listPointer x, int data)
{
	//make list
	listPointer tmp;
	tmp = (listPointer)malloc(sizeof(listNode));
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
void listDelete(listPointer* first, listPointer trail, listPointer x)
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
listPointer listCompare(listPointer first, int data)
{
	listPointer out = first;
	listPointer before = NULL;

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
void listPrint(listPointer first)
{
	listPointer now = first;
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
void listDelOdd(listPointer* first)
{
	listPointer ptr = *first;
	listPointer trail = NULL;

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
void deleteList(listPointer* first)
{
	listPointer ptr = *first;
	listPointer trail = NULL;

	while (ptr)
	{
		trail = ptr;
		ptr = ptr->link;

		free(trail);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void push(int num);
void pop(listPointer* trail, listPointer* target);
void print(void);
void delOddNode(void);

int main(void)
{
	FILE* fp = NULL;
	int num;
	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open \"input.txt\"\n");
		exit(stderr);
	}
	//read file
	while (!feof(fp))
	{
		num = -1;
		fscanf(fp, "%d", &num);

		if (num != -1)
			push(num);
	}
	//close file
	if (fclose(fp))
	{
		printf("cannot close\"input.txt\"\n");
		exit(stderr);
	}
	//print list
	printf("The Circularly Linked List contains:\n");
	print();
	//delete nodes
	delOddNode();
	//printlist
	printf("\n\nAfter deleting nodes with odd value\n");
	printf("\nThe Circularly Linked List contains:\n");
	print();

	return 0;
}
void push(int num)
{
	listPointer temp = NULL;
	temp = (listPointer)malloc(sizeof(listNode));

	temp->data = num;
	temp->link = NULL;

	if (!first)
	{
		first = temp;
		first->link = first;
	}
	else
	{
		listPointer ptr = first;
		//need fix
		for (; ptr->link != first; ptr = ptr->link);

		temp->link = ptr->link;
		ptr->link = temp;
	}
}
void pop(listPointer* trail, listPointer* target)
{
	if (*trail)
	{
		(*trail)->link = (*target)->link;
		free(*target);
		*target = (*trail)->link;
	}
	else
	{
		(*trail) = *target;
		*target = (*target)->link;
		free(*trail);
		*trail = NULL;
	}
}
void print(void)
{
	listPointer ptr = first;
	int index = 0;
	for (; ptr->link != first; ptr = ptr->link)
	{
		printf("(%p,%8d,%10p )", ptr, ptr->data, ptr->link);
		index = (index + 1) % 3;
		if (!index)
			printf("\n");
	}

	printf("(%p,%8d,%10p )", ptr, ptr->data, ptr->link);
	index = (index + 1) % 3;
	if (!index)
		printf("\n");
}
void delOddNode(void)
{
	listPointer ptr = first;
	listPointer trail = NULL;

	while (ptr->link != first)
	{
		if (ptr->data % 2)
			pop(&trail, &ptr);
		else
		{
			trail = ptr;
			ptr = ptr->link;
		}
	}

	if (ptr->data % 2)
		pop(&trail, &ptr);
	else
	{
		trail = ptr;
		ptr = ptr->link;
	}

}
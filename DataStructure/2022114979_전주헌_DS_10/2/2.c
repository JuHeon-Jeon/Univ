#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;

nodePointer header = NULL;

void printF(void);
void printR(void);
void pushNode(int data);
void popNode(nodePointer* target);
void delNode(void);

int main(void)
{
	FILE* fp = NULL;
	int input;
	//initialize header
	header = (nodePointer)malloc(sizeof(node));
	header->llink = header;
	header->rlink = header;
	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("failed to open \"input.txt\"\n");
		exit(stderr);
	}
	//read file
	while (!feof(fp))
	{
		input = -1;

		fscanf(fp, "%d", &input);
		pushNode(input);
	}
	//close file
	if (fclose(fp) == EOF)
	{
		printf("failed to close \"input.txt\"\n");
		exit(stderr);
	}
	//print node
	printf("After creating a doubly linked circular list with a head node :\n");
	printf("forward\n");
	printF();
	printf("\nbackward\n");
	printR();
	//delete <= 50
	nodePointer ptr = header->rlink;

	while (ptr != header)
	{
		if (ptr->data <= 50)
			popNode(&ptr);
		else
			ptr = ptr->rlink;
	}
	//print node
	printf("\nAfter deleting numbers less than and equal to 50 :\n");
	printf("forward\n");
	printF();
	printf("\nbackward\n");
	printR();
	//delete node
	delNode();

	return 0;
}
void printF(void)
{
	nodePointer ptr = header->rlink;
	int index = 0;

	while (ptr != header)
	{
		printf("(%p %5d %p)   ", ptr->llink, ptr->data, ptr->rlink);
		ptr = ptr->rlink;

		index = (index + 1) % 4;
		if (!index)
			printf("\n");
	}
}
void printR(void)
{
	nodePointer ptr = header->llink;
	int index = 0;

	while (ptr != header)
	{
		printf("(%p %5d %p)   ", ptr->llink, ptr->data, ptr->rlink);
		ptr = ptr->llink;

		index = (index + 1) % 4;
		if (!index)
			printf("\n");
	}
}
void pushNode(int data)
{
	nodePointer newnode;
	newnode = (nodePointer)malloc(sizeof(node));
	
	newnode->data = data;
	newnode->rlink = header;
	newnode->llink = header->llink;
	header->llink->rlink = newnode;
	header->llink = newnode;
}
void popNode(nodePointer* target)
{
	nodePointer del = *target;
	if (del == header)
	{
		printf("cannot delete header!\n");
		exit(stderr);
	}
	*target = (*target)->rlink;

	del->llink->rlink = del->rlink;
	del->rlink->llink = del->llink;

	free(del);
}
void delNode(void)
{
	nodePointer ptr = header->rlink;

	while (ptr != header)
	{
		popNode(&ptr);
	}

	free(header);
}

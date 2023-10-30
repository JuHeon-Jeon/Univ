#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer lchild;
	char value;
	treePointer rchild;
} treeNode;

typedef struct treeQueue* queuePointer;
typedef struct treeQueue {
	treePointer value;
	queuePointer link;
} treeQueue;

treePointer stack[MAX_SIZE] = { NULL };
int top = -1;

queuePointer queue = NULL;

void push(treePointer ptr);
treePointer pop(void);
void inorderPrint(treePointer ptr);
void inorderStack(treePointer ptr);
void addq(treePointer* ptr);
treePointer deleteq(void);
void preorder(treePointer ptr);
void postorder(treePointer ptr);


int main(void)
{
	FILE* fp = NULL;
	char input;
	treePointer root = NULL;
	//print
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : ");

	//read file and make tree
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file\n");
		exit(stderr);
	}

	while (!feof(fp))
	{
		//read char
		input = 0;
		fscanf(fp, "%c", &input);
		if (input)
		{
			printf("%c", input);
			//make tree
			treePointer temp = NULL;
			temp = (treePointer)malloc(sizeof(treeNode));
			temp->value = input;

			if (input == '+' || input == '-' || input == '*' || input == '/' || input == '%')
			{
				temp->rchild = pop();
				temp->lchild = pop();
				push(temp);
				root = temp;
			}
			else
			{
				temp->lchild = NULL;
				temp->rchild = NULL;
				push(temp);
			}
		}
	}


	if (fclose(fp))
	{
		printf("cannot close file\n");
		exit(stderr);
	}
	//print
	printf("\ncreating its binary tree\n\n");

	//preorder
	printf("iterative preorder traversal    : ");
	preorder(root);
	//postorder
	printf("\n");
	printf("iterative postorder traversal   : ");
	postorder(root);

	return 0;
}
void push(treePointer ptr)
{
	if (top + 1 < MAX_SIZE)
		stack[++top] = ptr;
	else
	{
		printf("\n\n\ncannot push : stack is full!\n");
		exit(stderr);
	}
}
treePointer pop(void)
{
	if (top > -1)
		return stack[top--];
	else
		return NULL;
}
void inorderPrint(treePointer ptr)
{
	top = -1;
	for (;;)
	{
		for (; ptr; ptr = ptr->lchild)
			push(ptr);
		ptr = pop();
		if (!ptr)
			break;
		printf("%c ", ptr->value);
		ptr = ptr->rchild;
	}
}
void inorderStack(treePointer ptr)
{
	top = -1;
	for (;;)
	{
		for (; ptr; ptr = ptr->lchild)
		{
			push(ptr);
			printf("%c ", ptr->value);
		}
		ptr = pop();
		if (!ptr)
			break;
		ptr = ptr->rchild;
	}
}
void addq(treePointer* ptr)
{
	queuePointer target = NULL;
	target = (queuePointer)malloc(sizeof(treeQueue));
	target->value = *ptr;
	target->link = NULL;

	if (queue)
	{
		queuePointer temp = queue;
		for (; temp->link; temp = temp->link);
		temp->link = target;
	}
	else
		queue = target;
}
treePointer deleteq(void)
{
	if (queue)
	{
		queuePointer temp = queue;
		queue = queue->link;
		return temp->value;
	}
	else
		return NULL;
}
void preorder(treePointer ptr)
{
	top = -1;
	for (;;)
	{
		for (; ptr; ptr = ptr->lchild)
		{
			printf("%c", ptr->value);
			push(ptr);
		}
		
		ptr = pop();
		if (!ptr)
			break;
		
		ptr = ptr->rchild;
	}
}
void postorder(treePointer ptr)
{
	//need fix

	treePointer temp = NULL;
	top = -1;


	for (;;)
	{
		for (; ptr; ptr = ptr->lchild)
			if (ptr->value != 0)
				push(ptr);
		ptr = pop();
		if (!ptr)
			break;

		temp = ptr;
		ptr = ptr->rchild;

		if (!ptr || ptr->value == 0)
		{
			ptr = temp;
			printf("%c", ptr->value);
			ptr->value = 0;
		}
		else
			push(temp);

	}
}
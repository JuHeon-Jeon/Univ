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

void push(treePointer ptr);
treePointer pop(void);
void inorder(treePointer ptr);
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

	//infix
	printf("inorder traversal     : ");
	inorder(root);
	printf("\n");
	//prefix
	printf("preorder traversal    : ");
	preorder(root);
	printf("\n");
	//postfix
	printf("postorder traversal   : ");
	postorder(root);
	printf("\n");

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
	{
		printf("\n\n\ncannot pop : stack is empty!\n");
		exit(stderr);
	}
}
void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->lchild);
		printf("%c", ptr->value);
		inorder(ptr->rchild);
	}
}
void preorder(treePointer ptr)
{
	if (ptr)
	{
		printf("%c", ptr->value);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void postorder(treePointer ptr)
{
	if (ptr)
	{
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%c", ptr->value);
	}
}
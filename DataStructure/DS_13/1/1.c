#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 100

typedef enum { not, and, or, other } logical;
typedef enum { operand, operator } oper;

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer lchild;
	logical data;
	short int value;
	char alphabet;
	treePointer rchild;
} treeNode;

typedef struct set {
	char first;
	char second;
	char third;
} set;

treePointer stack[MAX_SIZE];
int top = -1;

treePointer container[MAX_SIZE];
int contTOP = -1;
treePointer makeTree(char input);
oper determine1(char input);
logical determine2(char input);
void push(treePointer *node);
treePointer pop(void);
void satisfiability(treePointer node, int first, int second, int third);
void setvalue(treePointer* node, set alphabets, logical first, logical second, logical third);
void pushContainer(treePointer* node);
void postorderEval(treePointer* node);



int main(void)
{
	FILE* fp = NULL;
	char input;
	treePointer root = NULL;
	set alphabets;
	alphabets.first = NULL;
	alphabets.second = NULL;
	alphabets.third = NULL;

	//print
	printf("input string(postfix)     : ");

	//read from file and make tree
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot read file\n");
		exit(stderr);
	}

	while (!feof(fp))
	{
		input = 0;
		fscanf(fp, "%c", &input);
		if (input)
		{
			printf("%c", input);
			root = makeTree(input);
			
			if (alphabets.first == NULL)
				alphabets.first = input;
			else if (alphabets.second == NULL && alphabets.first != input)
				alphabets.second = input;
			else if (alphabets.third == NULL && alphabets.first != input && alphabets.second != input)
				alphabets.third = input;
		}
	}

	if (!fclose(fp))
	{
		printf("cannot close file\n");
		exit(stderr);
	}
	//print
	printf("\n");
	printf("find true condition\n");
	//calculate satisfiability and print
	//0 0 0
	setvalue(&root, alphabets, false, false, false);
	//0 0 1
	setvalue(&root, alphabets, false, false, true);
	//0 1 0
	setvalue(&root, alphabets, false, true, false);
	//0 1 1
	setvalue(&root, alphabets, false, true, true);
	//1 0 0
	setvalue(&root, alphabets, true, false, false);
	//1 0 1
	setvalue(&root, alphabets, true, false, true);
	//1 1 0
	setvalue(&root, alphabets, true, true, false);
	//1 1 1
	setvalue(&root, alphabets, true, true, true);



	return 0;
}
treePointer makeTree(char input)
{
	treePointer temp = NULL;
	temp = (treePointer)malloc(sizeof(treeNode));
	temp->lchild = NULL;
	temp->rchild = NULL;
	temp->value = NULL;
	temp->data = other;
	temp->alphabet = NULL;

	if (determine1(input) == operand)
		temp->alphabet = input;
	else
		temp->data = determine2(input);

	if (temp->alphabet)
	{
		push(&temp);
		pushContainer(&temp);
	}
	else
	{
		if (temp->data == not)
		{
			temp->rchild = pop();
			push(&temp);
		}
		else
		{
			temp->rchild = pop();
			temp->lchild = pop();
			push(&temp);
		}
	}
		

}
logical determine2(char input)
{
	if (input == '&')
		return and ;
	else if (input == '|')
		return or ;
	else if (input == '~')
		return not ;
	else
	{
		printf("error determine!\n");
		exit(stderr);
	}
}
oper determine1(char input)
{
	if (input >= 'a' && input <= 'z')
		return operand ;
	else
		return operator ;
}
void push(treePointer* node)
{
	if (top + 1 < MAX_SIZE)
		stack[++top] = *node;
	else
	{
		printf("cannot push stack is full\n");
		exit(stderr);
	}
}
treePointer pop(void)
{
	if (top > -1)
		return stack[top--];
	else
	{
		printf("cannot pop stack is empty\n");
		exit(stderr);
	}
}
void satisfiability(treePointer node, int first, int second, int third)
{
	postorderEval(&node);

}
void setvalue(treePointer* node, set alphabets, logical first, logical second, logical third)
{

}
void pushContainer(treePointer* node)
{
	if (contTOP + 1 < MAX_SIZE)
		container[++contTOP] = *node;
	else
	{
		printf("cannot push containerA\n");
		exit(stderr);
	}
}
void postorderEval(treePointer* node)
{

}
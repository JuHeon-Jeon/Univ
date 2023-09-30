#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME_SIZE 80
#define ELEMENT_SIZE 10

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;
typedef struct {
	int bottom;
	int top;
} index;

enum { add, delete, sprint, quit, wrong };

element multiStack[ELEMENT_SIZE];
index* multiIndex;

void divideStack(int size);
int determine(char* token);
void push(int id, char* name);
void pop(int id);
void printStack(int id);
void quitProgram(int size);


int main(void)
{
	FILE* fp = NULL;
	int size = -1;
	char input[MAX_NAME_SIZE + 20] = { NULL };
	char* token;
	int tmpId;
	char* tmpName;

	//get stack size
	printf("How Many Stacks ? : ");
	scanf("%d", &size);

	//divide stack
	divideStack(size);
	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error : cannot open \"input.txt\"\n");
		exit(stderr);
	}
	//read file and execute command
	while (fgets(input, MAX_NAME_SIZE + 20, fp) != NULL)
	{
		//first strtok
		token = strtok(input, " \n");
		
		//read command
		switch (determine(token))
		{
		case add:
			tmpId = atoi(strtok(NULL, " \n"));
			tmpName = strtok(NULL, " \n");

			//if id is wrong, print error
			if (tmpId >= size || tmpId < 0)
			{
				printf("stack number error, try again\n");
				break;
			}
			if (tmpName)
				push(tmpId, tmpName);
			else
				printf("no name to push stack %d!!! command example) push 0 abc\n", tmpId);

			break;
		case delete:
			//if no id, print error
			tmpName = NULL;
			tmpName = strtok(NULL, " \n");

			if (tmpName)
				tmpId = atoi(tmpName);
			else
			{
				printf("no name to pop stack!!! command example) pop 0\n");
				break;
			}
			//if id is wrong, print error
			if (tmpId >= size || tmpId < 0)
				printf("stack number error, try again\n");
			//pop
			else
				pop(tmpId);
			break;
		case sprint:
			//if no id, print error
			tmpName = NULL;
			tmpName = strtok(NULL, " \n");
			
			if (tmpName)
				tmpId = atoi(tmpName);
			else
			{
				printf("no name to print stack!!! command example) sprint 0\n");
				break;
			}
			//print
			printStack(tmpId, size);

			break;
		case quit:
			quitProgram(size);

			exit(0);
		case wrong:
			printf("wrong command, try again!!\n");

			break;
		default:
			printf("error handling command\n");
			
			exit(stderr);
		}
	}
	
	//program end message
	quitProgram(size);

	//close file
	if (fclose(fp) == EOF)
	{
		printf("error : cannot close\"input.txt\"\n");
		exit(stderr);
	}
	//free index
	free(multiIndex);

	return 0;
}
void divideStack(int size)
{
	//initialize piece
	int piece = ELEMENT_SIZE / size;
	//if size is too big, return error
	//size + 1 to limit last stack's top
	if (piece)
		multiIndex = (index*)malloc(sizeof(index) * (size + 1));
	else
	{
		printf("too many stacks, please type less than 11\n");
		exit(stderr);
	}
	//first stack index
	multiIndex[0].bottom = 0;
	multiIndex[0].top = -1;
	//rest of stack index
	for (int i = 1; i < size; i++)
	{
		multiIndex[i].bottom = multiIndex[i - 1].bottom + piece;
		multiIndex[i].top = multiIndex[i].bottom - 1;
	}
	//limit last stack's top
	multiIndex[size].bottom = ELEMENT_SIZE;
}
int determine(char* token)
{
	if (!strcmp(token, "add"))
		return add;
	else if (!strcmp(token, "delete"))
		return delete;
	else if (!strcmp(token, "sprint"))
		return sprint;
	else if (!strcmp(token, "quit"))
		return quit;
	else
		return wrong;
}
void push(int id, char* name)
{
	int top = multiIndex[id].top;
	int limit = multiIndex[id + 1].bottom;

	if (top + 1 < limit)
	{
		//push
		strcat(multiStack[++top].name, name);
		multiIndex[id].top = top;
		//print
		printf("%s is Pushed in Stack No. %d\n", name, id);
	}
	else
		printf("stack %d is Full\n", id);
}
void pop(int id)
{
	int top = multiIndex[id].top;
	int limit = multiIndex[id].bottom;
	
	//print error message
	if (top <= limit - 1)
		printf("Stack %d is Empty\n", id);
	else
	{
		//print pop message
		printf("%s is popped from Stack No. %d\n", multiStack[top].name, id);
		//pop
		top--;
		multiIndex[id].top = top;
	}
}
void printStack(int id, int size)
{
	if (id >= size || id < 0)
	{
		printf("stack number error, try again\n");
		return;
	}

	int i = multiIndex[id].bottom;
	int top = multiIndex[id].top;

	printf("\n");
	for (top; top >= i; top--)
		printf("%s\n", multiStack[top].name);
	printf("\n");
}
void quitProgram(int size)
{
	printf("\nProgram end\n\n");

	for (int i = 0; i < size; i++)
	{
		printf("stack %d :", i);
		printStack(i, size);
	}
}
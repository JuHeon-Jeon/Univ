#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int sFront = 0, sRear = -1;

void push(int id, char* name);
void pop(void);
void sprint(void);
void quit(void);
void wrong(void);
int determine(char* Original);
void stackFull(void);
void stackEmpty(void);

int main(void)
{
	FILE* fp = NULL;
	char inputOriginal[1000], * inputToken = NULL;
	int inputId, size;
	int inputName[MAX_NAME_SIZE];

	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}

	while (fgets(inputOriginal, 1000, fp))
	{	
	switch (determine(inputOriginal))
	{
	case 1: //push
		inputToken = strtok(NULL, " ");
		inputId = atoi(inputToken);

		inputToken = strtok(NULL, " ");
		size = strlen(inputToken);
		if (inputToken[size - 1] == '\n')
			inputToken[size - 1] = '\0';
		strcpy(inputName, inputToken);
		
		push(inputId, inputName);

		break;
	case 2: //pop
		pop();

		break;
	case 3: //sprint
		sprint();

		break;
	case 4: //quit
		quit();
	case 5: //error
		wrong();

		break;
	}
	}

	fclose(fp);

	return 0;
}

void push(int id, char* name)
{
	stackFull();

	stack[++sRear].id = id;
	strcpy(stack[sRear].name, name);
}
void pop(void)
{
	stackEmpty();

	sRear--;
}
void sprint(void)
{
	printf("\n");
	for (int i = sRear; i >= sFront; i--)
		printf("%d %s\n", stack[i].id, stack[i].name);
	printf("\n");
}
void quit(void)
{
	printf("You have exited the Program\n");
	exit(0);
}
void wrong(void)
{
	printf("\nWrong command! try again!\n");
}
int determine(char* Original)
{
	char* token;
	int size;

	token = strtok(Original, " ");

	size = strlen(token);
	if (token[size - 1] == '\n')
		token[size - 1] = '\0';


	if (!strcmp(token, "push"))
		return 1;
	else if (!strcmp(token, "pop"))
		return 2;
	else if (!strcmp(token, "sprint"))
		return 3;
	else if (!strcmp(token, "quit"))
		return 4;
	else
		return 5;
}
void stackFull(void)
{
	if (sRear + 1 > MAX_STACK_SIZE - 1)
	{
		printf("stack is full, cannot add element\n");
		printf("current stack elements :\n");
		sprint();
		exit(0);
	}
}
void stackEmpty(void)
{
	if (sRear - 1 < sFront)
	{
		printf("stack is empty, cannot delete element");
		exit(0);
	}
}
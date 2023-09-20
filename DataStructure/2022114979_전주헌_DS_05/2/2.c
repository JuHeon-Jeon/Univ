//need more refinement
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int qFront = -1, qRear = -1;


void push(int id, char* name);
void pop(void);
void qprint(void);
void quit(void);
void wrong(void);
int qFull(void);
void qEmpty(void);
void dShift(void);
int determine(char* original);

int main(void)
{
	FILE* fp = NULL;
	char inputOriginal[100], * inputToken, inputName[100];
	int inputId;

	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}

	while (fgets(inputOriginal, 100, fp))
	{
		switch (determine(inputOriginal))
		{
		case 1: //add
			inputToken = strtok(NULL, " ");
			inputId = atoi(inputToken);

			inputToken = strtok(NULL, " ");
			int size = strlen(inputToken);

			if (inputToken[size - 1] == '\n')
				inputToken[size - 1] = '\0';

			strcpy(inputName, inputToken);

			push(inputId, inputName);

			break;
		case 2: //delete
			pop();

			break;
		case 3: //qprint
			qprint();

			break;
		case 4: //quit
			quit();
		case 5: //wrong
			wrong();

			break;
		}
	}


	fclose(fp);

	return 0;
}
void push(int id, char* name)
{
	if (!qFull())
	{
		queue[++qRear].id = id;
		strcpy(queue[qRear].name, name);
	}
}
void pop(void)
{
	qEmpty();
	
	qFront++;
	dShift();
}
void qprint(void)
{
	for (int i = qFront + 1; i <= qRear; i++)
		printf("%d %s\n", queue[i].id, queue[i].name);
	printf("\n");
}
void quit(void)
{
	printf("You have quited the program\n");
	exit(0);
}
void wrong(void)
{
	printf("Wrong command! try again!\n");
}
int qFull(void)
{
	if (qRear + 1 > MAX_QUEUE_SIZE - 1)
	{
		printf("Queue Full!\n");
		printf("element not added\n");

		return 1;
	}

	return 0;
}
void qEmpty(void)
{
	if (qFront == qRear - 1 || qRear == -1)
	{
		printf("Queue empty!\n");
		exit(stderr);
	}
}
void dShift(void)
{
	for (int i = qFront; i < qRear; i++)
	{
		queue[i].id = queue[i + 1].id;
		strcpy(queue[i].name, queue[i + 1].name);
	}
	printf("\nData Shift!\n");
}
int determine(char* original)
{
	char* token = strtok(original, " ");
	int size = strlen(token);

	if (token[size - 1] == '\n')
		token[size - 1] = '\0';

	if (!strcmp(token, "add"))
		return 1;
	else if (!strcmp(token, "delete"))
		return 2;
	else if (!strcmp(token, "qprint"))
		return 3;
	else if (!strcmp(token, "quit"))
		return 4;
	else
		return 5;
}

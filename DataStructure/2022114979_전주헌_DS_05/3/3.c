#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int rear = 0, front = 0;

void push(int id, char* name);
void pop(void);
void qprint(void);
void quit(void);
void wrong(void);
int determine(char* original);
int qFull(void);
void qEmpty(void);


int main(void)
{
	FILE* fp = NULL;
	char inputOriginal[100], * inputToken, inputName[100];
	int inputId;


	if (!(fp = fopen("input.txt", "r"))) //read file
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}

	while (fgets(inputOriginal, 100, fp)) //read command
	{
		switch (determine(inputOriginal)) //execute command
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

	

	fclose(fp);//close file

	return 0;
}

void push(int id, char* name)
{
	if (!qFull())
	{
		queue[rear].id = id;
		strcpy(queue[rear].name, name);

		rear = (rear + 1) % MAX_QUEUE_SIZE;
	}
}
void pop(void)
{
	qEmpty();

	front = (front + 1) % MAX_QUEUE_SIZE;
}
void qprint(void)
{
	if (front == rear)
		printf("\n");
	else
	{
		printf("\n");
		int i = front;
		while (!(i == rear))
		{
			printf("%d %s\n", queue[i].id, queue[i].name);
			i = (i + 1) % MAX_QUEUE_SIZE;
		}
	}
}
void quit(void)
{
	printf("You have quited the program\n");
	exit(0);
}
void wrong(void)
{
	printf("\nWrong command! try again!\n");
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
int qFull(void)
{
	if ((rear + 1) % MAX_QUEUE_SIZE == front && front != rear)
	{
		printf("queue is full, not added\n");
		return 1;
	}
	else
		return 0;
}
void qEmpty(void)
{
	if (front == rear)
	{
		printf("queue is empty\n");
		exit(stderr);
	}
}
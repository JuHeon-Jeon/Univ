#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element* queue;
int capacity = 2;
int front = 0, rear = 0;

void pop(void);
void qprint(void);
void quit(void);
void wrong(void);
int determine(char* original);
void push(int id, char* name);
int qFull(void);
void qEmpty(void);
void copy(element* a, element* b, element* c);


int main(void)
{
	FILE* fp = NULL;
	char inputOri[MAX_NAME_SIZE], * inputToken, inputName[MAX_NAME_SIZE];
	int inputId;
	
	queue = (element*)malloc(sizeof(element) * capacity); //initalize queue

	if (!(fp = fopen("input.txt", "r"))) //read file
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}

	while (fgets(inputOri, MAX_NAME_SIZE, fp)) //read command
	{
		switch (determine(inputOri))
		{
		case 1: //add
			inputToken = strtok(NULL, " "); //get id
			inputId = atoi(inputToken);

			inputToken = strtok(NULL, " "); //get name
			int size = strlen(inputToken);

			if (inputToken[size - 1] == '\n') //name refinement
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

	fclose(fp); //close file
	free(queue); //free queue

	return 0;
}
void pop(void)
{
	qEmpty();

	front = (front + 1) % capacity;
}
void qprint(void)
{
	if (front == rear)
		printf("\n");
	else
	{
		printf("\n");
		int i = (front + 1) % capacity;
		while (!(i == rear))
		{
			printf("%d %s\n", queue[i].id, queue[i].name);
			i = (i + 1) % capacity;
		}
		printf("%d %s\n", queue[i].id, queue[i].name);
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
void push(int id, char* name)
{
	if (qFull())
	{
		rear = (rear + 1) % capacity;
		queue[rear].id = id;
		strcpy(queue[rear].name, name);
		qprint();
	}
	else
	{
		rear = (rear + 1) % capacity;
		queue[rear].id = id;
		strcpy(queue[rear].name, name);
	}
}
int qFull(void)
{
	if ((rear + 1) % capacity == front && front != rear)
	{
		element* nQueue;
		int start;
		
		nQueue = (element*)malloc(sizeof(element) * capacity * 2);
		start = (front + 1) % capacity;

		if (start < 2)
			copy(queue + start, queue + capacity, nQueue);
		else
		{
			copy(queue + start, queue + capacity, nQueue);
			copy(queue, queue + rear + 1, nQueue + capacity - start);
		}

		front = capacity * 2 - 1;
		rear = capacity - 2;
		capacity *= 2;
		free(queue);
		queue = nQueue;

		printf("\nqueue capacity is doubled,\n");
		printf("current queue capacity is %d", capacity);

		return 1;
	}

	return 0;
}
void qEmpty(void)
{
	if (front == rear)
	{
		printf("queue is empty!\n");
		exit(stderr);
	}
}
void copy(element* a, element* b, element* c)
{
	while (a != b)
		*c++ = *a++;
}
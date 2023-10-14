#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct list* link;
typedef struct list
{
	int ban;
	int grade;
	link link;
} list;

link stack[3] = { NULL };

void insertStack(int num, int ban, int grade);
void printStack(int num);

int main(void)
{
	FILE* fp = NULL;
	int num, ban, grade;

	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("failed to open \"input.txt\"\n");
		exit(stderr);
	}
	//read file
	while (!feof(fp))
	{
		num = -1;
		fscanf(fp, "%d %d %d", &num, &ban, &grade);
		//disregard last \n
		if (num != -1)
			insertStack(num, ban, grade);
	}
	//close file
	if (fclose(fp))
	{
		printf("failed to close \"input.txt\"\n");
		exit(stderr);
	}
	//print stack
	printf("과목번호, 학반, 성적\n");
	printStack(0);
	printStack(1);
	printStack(2);

	return 0;
}
void insertStack(int num, int ban, int grade)
{
	link temp;
	temp = (link)malloc(sizeof(list));
	
	temp->ban = ban;
	temp->grade = grade;

	if (!stack[num])
	{
		temp->link = NULL;
		stack[num] = temp;
	}
	else
	{
		temp->link = stack[num];
		stack[num] = temp;
	}
}
void printStack(int num)
{
	link ptr = stack[num];

	printf("*********************\n");
	
	while (ptr)
	{
		printf("%8d%6d%6d\n", num, ptr->ban, ptr->grade);
		ptr = ptr->link;
	}
}
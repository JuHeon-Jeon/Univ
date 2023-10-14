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

link queue[3] = { NULL };
link rear[3] = { NULL };

void insertQueue(int num, int ban, int grade);
void printQueue(int num);

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
			insertQueue(num, ban, grade);
	}
	//close file
	if (fclose(fp))
	{
		printf("failed to close \"input.txt\"\n");
		exit(stderr);
	}
	//print stack
	printf("과목번호, 학반, 성적\n");
	printQueue(0);
	printQueue(1);
	printQueue(2);

	return 0;

}

void insertQueue(int num, int ban, int grade)
{
	link temp;
	temp = (link)malloc(sizeof(list));

	temp->ban = ban;
	temp->grade = grade;
	temp->link = NULL;


	if (!queue[num])
	{
		queue[num] = temp;
		rear[num] = temp;
	}
	else
	{
		rear[num]->link = temp;
		rear[num] = temp;
	}
}
void printQueue(int num)
{
	link ptr = queue[num];

	printf("*********************\n");

	while (ptr)
	{
		printf("%8d%6d%6d\n", num, ptr->ban, ptr->grade);
		ptr = ptr->link;
	}
}
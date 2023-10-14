#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { male, female };

typedef struct listNode* listPointer;
typedef struct listNode {
	char name[10];
	char job[20];
	int sex;
	listPointer link;
} listNode;

listPointer firstOrigin = NULL;
listPointer firstMale = NULL;
listPointer firstFemale = NULL;


void listAdd(listPointer* first, char name[10], char job[20], int sex);
void listSex(listPointer* firstOrigin, listPointer* first, int sex);
void listPrint(listPointer first);

int main(void)
{
	FILE* fp = NULL;
	char name[10] = { '\0' }, job[20] = { '\0' }, sexChar[10] = { '\0' };
	int sex = male;
	listPointer target = NULL;

	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}
	//read data & make list
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s\n", name, job, sexChar);
		//determine sex
		if (!strcmp("남자", sexChar))
			sex = male;
		else if (!strcmp("여자", sexChar))
			sex = female;
		else
		{
			printf("error sexChar!\n");
			exit(stderr);
		}

		listAdd(&firstOrigin, name, job, sex);
	}
	//close file
	if (fclose(fp) == EOF)
	{
		printf("error closing \"input.txt\"\n");
		exit(stderr);
	}
	//make list by sex
	listSex(&firstOrigin, &firstMale, male);
	listSex(&firstOrigin, &firstFemale, female);
	//print list
	printf("전체 리스트\n");
	listPrint(firstOrigin);
	printf("\n남자 리스트\n");
	listPrint(firstMale);
	printf("\n여자 리스트\n");
	listPrint(firstFemale);

	return 0;
}
void listAdd(listPointer* first, char name[10], char job[20], int sex)
{
	listPointer ptr = *first;

	listPointer tmp = NULL;
	tmp = (listPointer)malloc(sizeof(listNode));
	strcpy(tmp->name, name);
	strcpy(tmp->job, job);
	tmp->sex = sex;

	if (ptr)
	{
		while (ptr->link)
			ptr = ptr->link;
		ptr->link = tmp;
	}
	else
		*first = tmp;

	tmp->link = NULL;
}
void listSex(listPointer* firstOrigin, listPointer* first, int sex)
{
	listPointer ptr = *firstOrigin;

	while (ptr)
	{
		if (ptr->sex == sex)
			listAdd(first, ptr->name, ptr->job, sex);

		ptr = ptr->link;
	}
}
void listPrint(listPointer first)
{
	listPointer ptr = first;
	char sexChar[10];
	int index = 1;

	if (ptr)
		while (ptr)
		{
			if (ptr->sex == male)
				strcpy(sexChar, "남자");
			else
				strcpy(sexChar, "여자");

			printf("(%p, %s, %s, %s %p )  ", ptr, ptr->name, ptr->job, sexChar, ptr->link);

			if (!index)
				printf("\n");
			
			index = (index + 1) % 2;
			ptr = ptr->link;
		}
	else
		printf("list is empty!\n");
	
	printf("\n");
}
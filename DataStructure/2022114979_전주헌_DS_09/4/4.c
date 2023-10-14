#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int coef;
	int expon;
	listPointer link;
} listNode;


void push(int flag, listPointer* first, int coef, int expon);
void print(listPointer first);
listPointer addList(listPointer a, listPointer b);
void delList(listPointer* first);

int main(void)
{
	FILE* fp = NULL;
	int flag = 0; // 0 : default, 1 : ascend, -1 : descend
	char flagChar;
	int expon = -1, coef = 0;
	listPointer a = NULL;
	listPointer b = NULL;
	listPointer c = NULL;


	//open a.txt
	if (!(fp = fopen("a.txt", "r")))
	{
		printf("cannot open \"a.txt\"\n");
		exit(stderr);
	}
	//read a.txt
	fscanf(fp, "%c", &flagChar);
	if (flagChar == 'a')
		flag = 1;
	else if (flagChar == 'd')
		flag = -1;
	else
	{
		printf("cannot determine order!\n");
		exit(stderr);
	}

	while (!feof(fp))
	{
		coef = 0;
		expon = -1;

		fscanf(fp, "%d %d", &coef, &expon);

		if (coef != 0 && expon != -1)
			push(flag, &a, coef, expon);
	}

	flag = 0;
	//close a.txt
	if (fclose(fp))
	{
		printf("cannot close\"a.txt\"\n");
		exit(stderr);
	}
	//open b.txt
	if (!(fp = fopen("b.txt", "r")))
	{
		printf("cannot open \"b.txt\"\n");
		exit(stderr);
	}
	//read b.txt
	flagChar == NULL;
	fscanf(fp, "%c", &flagChar);
	if (flagChar == 'a')
		flag = 1;
	else if (flagChar == 'd')
		flag = -1;
	else
	{
		printf("cannot determine order!\n");
		exit(stderr);
	}

	while (!feof(fp))
	{
		coef = 0;
		expon = -1;

		fscanf(fp, "%d %d", &coef, &expon);

		if (coef != 0 && expon != -1)
			push(flag, &b, coef, expon);
	}

	flag = 0;
	//close b.txt
	if (fclose(fp))
	{
		printf("cannot close\"b.txt\"\n");
		exit(stderr);
	}

	//print a
	printf("%5c :\n", 'a');
	print(a);
	//print b
	printf("\n%5c :\n", 'b');
	print(b);
	//c = a + b
	c = addList(a, b);
	//print c
	printf("\na+b=c : \n");
	print(c);
	//delete list
	delList(&a);
	delList(&b);
	delList(&c);

	return 0;
}
void push(int flag, listPointer* first, int coef, int expon)
{
	listPointer ptr = *first;
	listPointer temp = NULL;
	temp = (listPointer)malloc(sizeof(listNode));
	temp->coef = coef;
	temp->expon = expon;

	switch (flag)
	{
	case 1: //ascend
		temp->link = *first;
		*first = temp;

		break;
	case -1: //descend
		if (ptr)
		{
			for (; ptr->link != NULL; ptr = ptr->link);
			ptr->link = temp;
		}
		else
			*first = temp;

		temp->link = NULL;

		break;
	default:
		printf("flag value corrputed\n");
		exit(stderr);
	}
}
void print(listPointer first)
{
	listPointer ptr = first;
	for (; ptr != NULL; ptr = ptr->link)
		printf("(%p : %+5dx^%d : %p)\n", ptr, ptr->coef, ptr->expon, ptr->link);
}
listPointer addList(listPointer a, listPointer b)
{
	listPointer out = NULL;
	int coef = 0;

	while (a && b)
	{
		if (a->expon > b->expon)
		{
			push(-1, &out, a->coef, a->expon);
			a = a->link;
		}
		else if (a->expon == b->expon)
		{
			coef = a->coef + b->coef;
			if (coef)
				push(-1, &out, coef, a->expon);
			a = a->link;
			b = b->link;
		}
		else
		{
			push(-1, &out, b->coef, b->expon);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)
		push(-1, &out, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		push(-1, &out, b->coef, b->expon);

	return out;
}
void delList(listPointer* first)
{
	listPointer ptr = *first;
	listPointer trail = NULL;

	while (ptr)
	{
		trail = ptr;
		ptr = ptr->link;
		free(trail);
	}
}

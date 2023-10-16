#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int coef;
	int expon;
	listPointer link;
} listNode;

listPointer avail = NULL;

void push(int flag, listPointer* first, int coef, int expon);
void print(listPointer first);
listPointer addList(listPointer a, listPointer b);
void delList(listPointer* first);
void rtnList(listPointer* first);
void printAvail(listPointer first);

int main(void)
{
	FILE* fp = NULL;
	int flag = 0; // 0 : default, 1 : ascend, -1 : descend
	char flagChar;
	int expon = -1, coef = 0;
	listPointer a = NULL;
	listPointer b = NULL;
	listPointer c = NULL;

	a = (listPointer)malloc(sizeof(listNode));
	a->link = NULL;
	b = (listPointer)malloc(sizeof(listNode));
	b->link = NULL;

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
	//return list
	rtnList(&a);
	rtnList(&b);
	rtnList(&c);
	//print avail
	printf("\navail : \n");
	printAvail(avail);
	//delete avail
	delList(&avail);

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
		temp->link = (*first)->link;

		if (!(*first)->link)
			temp->link = *first;
		(*first)->link = temp;

		break;
	case -1: //descend
		if ((*first)->link)
		{
			for (; ptr->link != *first; ptr = ptr->link);
			ptr->link = temp;
		}
		else
			(*first)->link = temp;

		temp->link = *first;

		break;
	default:
		printf("flag value corrputed\n");
		exit(stderr);
	}
}
void print(listPointer first)
{
	listPointer ptr = first;
	for (; ptr->link != first; ptr = ptr->link)
		printf("(%p : %+5dx^%d : %p)\n", ptr, ptr->coef, ptr->expon, ptr->link);
	printf("(%p : %+5dx^%d : %p)\n", ptr, ptr->coef, ptr->expon, ptr->link);
}
listPointer addList(listPointer a, listPointer b)
{
	listPointer ptrA = a->link, ptrB = b->link;
	listPointer out = NULL;
	out = (listPointer)malloc(sizeof(listNode));
	out->link = NULL;
	int coef = 0;

	while (ptrA != a && ptrB != b)
	{
		if (ptrA->expon > ptrB->expon)
		{
			push(-1, &out, ptrA->coef, ptrA->expon);
			ptrA = ptrA->link;
		}
		else if (ptrA->expon == ptrB->expon)
		{
			coef = ptrA->coef + ptrB->coef;
			if (coef)
				push(-1, &out, coef, ptrA->expon);
			ptrA = ptrA->link;
			ptrB = ptrB->link;
		}
		else
		{
			push(-1, &out, ptrB->coef, ptrB->expon);
			ptrB = ptrB->link;
		}
	}
	for (; ptrA != a; ptrA = ptrA->link)
		push(-1, &out, ptrA->coef, ptrA->expon);
	for (; ptrB != b; ptrB = ptrB->link)
		push(-1, &out, ptrB->coef, ptrB->expon);

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
void rtnList(listPointer* first)
{
	//need fix
	listPointer rtn = (*first)->link;

	(*first)->link = NULL;

	if (avail)
		(*first)->link = avail;

	avail = rtn;
}
void printAvail(listPointer first)
{
	listPointer ptr = first;
	for (; ptr->link != NULL; ptr = ptr->link)
		printf("(%p : %+5dx^%d : %p)\n", ptr, ptr->coef, ptr->expon, ptr->link);
	printf("(%p : %+5dx^%d : %p)\n", ptr, ptr->coef, ptr->expon, ptr->link);

}
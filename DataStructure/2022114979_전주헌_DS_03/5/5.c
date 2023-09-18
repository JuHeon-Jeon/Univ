#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
	float coef;
	int expon;
}term;


void padd(term* terms, int startA, int finishA, int startB, int finishB, int* startD, int* finishD, int* avail);
void pCreate(term* terms, char ch[], int start, int finish, int* avail);
void attach(term* terms, float coef, int expon, int* avail);
int compare(int a, int b);
void pPrint(term terms[], char ch[], int start, int finish);

int main(void)
{
	int startA = 0, finishA, startB, finishB, startD, finishD, avail = 0;
	term terms[MAX_TERMS];

	printf("<< D(x) = A(x) + B(x) >>\n");
	printf("Input the number of items of A(x) : ");
	scanf("%d", &finishA);
	printf("Input the number of items of B(x) : ");
	scanf("%d", &finishB);

	finishA--;
	finishB--;
	startB = finishA + 1;
	finishB += startB;

	printf("\ninput in descending order\n");
	pCreate(terms, "A(x)", startA, finishA, &avail);
	pCreate(terms, "B(x)", startB, finishB, &avail);
	
	padd(terms, startA, finishA, startB, finishB, &startD, &finishD, &avail);

	printf("\n");
	pPrint(terms, "A(x)", startA, finishA);
	pPrint(terms, "B(x)", startB, finishB);
	pPrint(terms, "D(x)", startD, finishD);

	return 0;
}

void padd(term* terms, int startA, int finishA, int startB, int finishB, int* startD, int* finishD, int* avail)
{
	float coef;
	*startD = *avail;

	while (startA <= finishA && startB <= finishB)
	{
		switch (compare(terms[startA].expon, terms[startB].expon))
		{
		case -1: //A < B
			attach(terms, terms[startB].coef, terms[startB].expon, avail);
			startB++;
			break;
		case 0: //A == B
			coef = terms[startA].coef + terms[startB].coef;
			if (coef)
				attach(terms, coef, terms[startA].expon, avail);
			startA++;
			startB++;
			break;
		case 1: //A > B
			attach(terms, terms[startA].coef, terms[startA].expon, avail);
			startA++;
			break;
		}
	}

	for (; startA <= finishA; startA++)
		attach(terms, terms[startA].coef, terms[startA].expon, avail);
	for (; startB <= finishB; startB++)
		attach(terms, terms[startB].coef, terms[startB].expon, avail);

	*finishD = *avail - 1;
}
void pCreate(term* terms, char ch[], int start, int finish, int* avail)
{
	float coef;
	int expon;

	printf("Ex) coefficient and exponent of %s = 10x^5 + 8x^3 + 7 (10 5, 8 3, 7 0) : ", ch);
	for (int i = 0; i <= finish - start; i++)
	{
		scanf("%f %d", &coef, &expon);
		attach(terms, coef, expon, avail);
	}
}
void attach(term* terms, float coef, int expon, int* avail)
{
	if (*avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(1);
	}
	terms[*avail].coef = coef;
	terms[(*avail)++].expon = expon;
}
int compare(int a, int b)
{
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}
void pPrint(term terms[], char ch[], int start, int finish)
{
	printf("%s = ", ch);

	if (terms[start].coef > 0)
		printf("%.2fx^%d ", terms[start].coef, terms[start].expon);
	else
		printf("%.2fx^%d ", terms[start].coef * -1, terms[start].expon);
	start++;

	for (; start <= finish; start++)
	{
		if (terms[start].expon > 0)
		{
			if (terms[start].coef > 0)
				printf("+ %.2fx^%d ", terms[start].coef, terms[start].expon);
			else
				printf("- %.2fx^%d ", terms[start].coef * -1, terms[start].expon);
		}
		else
		{
			if (terms[start].coef > 0)
				printf("+ %.2f ", terms[start].coef);
			else
				printf("- %.2f ", terms[start].coef * -1);
		}
	}

	printf("\n");
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;


void poly_print(char ch[], polynomial poly);
void polyAdd(polynomial a, polynomial b, polynomial* c);

int main(void)
{
	polynomial a, b, c;

	a.degree = 0;
	b.degree = 0;
	c.degree = 0;
	for (int i = 0; i < MAX_DEGREE; i++)
	{
		a.coef[i] = 0;
		b.coef[i] = 0;
		c.coef[i] = 0;
	}

	printf("<< C(x) = A(x) + B(x) >>\n");
	
	printf("Input the degree of items of A(x) : ");
	scanf("%d", &a.degree);
	printf("Input the coefficients of A(x) : ");
	for (int i = a.degree; i >= 0; i--)
		scanf("%f", &a.coef[i]);

	printf("Input the degree of items of B(x) : ");
	scanf("%d", &b.degree);
	printf("Input the coefficients of B(x) : ");
	for (int i = b.degree; i >= 0; i--)
		scanf("%f", &b.coef[i]);

	if (a.degree > b.degree)
		c.degree = a.degree;
	else
		c.degree = b.degree;

	polyAdd(a, b, &c);

	poly_print("A(X)", a);
	poly_print("B(X)", b);
	poly_print("C(X)", c);

	return 0;
}

void poly_print(char ch[], polynomial poly)
{
	printf("%s = ", ch);
	for (int i = poly.degree; i > 0; i--)
	{
		if (poly.coef[i] > 0)
			printf("+ %.2fx^%d ", poly.coef[i], i);
		else if (poly.coef[i] < 0)
			printf("- %.2fx^%d ", poly.coef[i] * -1, i);
	}
	if (poly.coef[0] > 0)
		printf("%.2f", poly.coef[0]);

	printf("\n");
}
void polyAdd(polynomial a, polynomial b, polynomial* c)
{
	int indexA = a.degree;
	int indexB = b.degree;

	while (indexA >= 0 && indexB >= 0)
	{
		if (indexA > indexB)
		{
			c->coef[indexA] = a.coef[indexA];
			indexA--;
		}
		else if (indexA == indexB)
		{
			c->coef[indexA] = a.coef[indexA] + b.coef[indexB];
			indexA--;
			indexB--;
		}
		else
		{
			c->coef[indexB] = b.coef[indexB];
			indexB--;
		}
	}

}
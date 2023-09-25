#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sumAry_f1(int ary[], int size);
int sumAry_f2(int* ary, int size);
int sumAry_f3(int ary[6], int size);


int main(void)
{
	int ary[] = { 1, 2, 3, 4, 5, 6, };

	printf("sumAry_f1() %d\n", sumAry_f1(ary, 6));
	printf("sumAry_f2() %d\n", sumAry_f2(ary, 6));
	printf("sumAry_f3() %d\n", sumAry_f3(ary, 6));

	return 0;
}
int sumAry_f1(int ary[], int size)
{
	int out = 0;
	for (int i = 0; i < size; i++)
		out += ary[i];

	return out;
}
int sumAry_f2(int* ary, int size)
{
	int out = 0;
	for (int i = 0; i < size; i++)
		out += *(ary + i);

	return out;
}
int sumAry_f3(int ary[6], int size)
{
	int out = 0;
	for (int i = 0; i < size; i++)
		out += ary[i];

	return out;
}

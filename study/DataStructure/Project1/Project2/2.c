#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int* p[3];

	for (int i = 0; i < 3; i++)
	{
		p[i] = (int*)malloc(sizeof(int));
		*p[i] = i + 2;
	}
	
	printf("������ �迭�� �迭��Ҹ� �̿��� a, b, c ���\n");
	for (int i = 0; i < 3; i++)
		printf("%c : %d ", 'a' + i, *p[i]);
	printf("\n");

	return 0;
}
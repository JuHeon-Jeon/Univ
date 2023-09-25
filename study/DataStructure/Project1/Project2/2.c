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
	
	printf("포인터 배열의 배열요소를 이용한 a, b, c 출력\n");
	for (int i = 0; i < 3; i++)
		printf("%c : %d ", 'a' + i, *p[i]);
	printf("\n");

	return 0;
}
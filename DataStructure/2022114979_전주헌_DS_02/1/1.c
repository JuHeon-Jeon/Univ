#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* func1(void);
void func2(int* pNum);
void func3(int** pNum);
char* func4(int num);


int main(void)
{
	int* pNum;
	char* pChar;

	pNum = func1(); // int ũ�⸸ŭ �����Ҵ� �޾� 10�� ������ ������ ������ ����
	printf("%d\n", *pNum);

	func2(pNum);// pNum�� ����Ű�� ���� 100���� ����
	printf("%d\n", *pNum);

	func3(&pNum); // pNum�� ����Ű�� ���� 200���� ����
	printf("%d\n", *pNum);

	pChar = func4(100); // pChar �� 100byte �Ҵ� ���� �޸𸮿� Ű����κ��� �Է� ���� ���ڿ� ����

	scanf("%s", pChar);
	printf("pChar contents = %s\n", pChar);

	free(pNum);
	free(pChar);
	return 0;
}

int* func1(void)
{
	int* pNum = NULL;

	pNum = (int*)malloc(sizeof(int));
	*pNum = 10;

	return pNum;
}
void func2(int* pNum)
{
	*pNum = 100;
}
void func3(int** pNum)
{
	**pNum = 200;
}
char* func4(int num)
{
	char* pChar = NULL;

	pChar = (char*)malloc(sizeof(char) * num);

	printf("�Է��� ���ڿ� : ");

	return pChar;
}

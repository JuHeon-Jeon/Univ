#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int nfind(char* target, char* pat);

int main(void)
{
	char target[1000], pat[1000]; //declare variables
	int out;

	printf("문자열을 입력하세요 : "); //get target
	if (!gets(target))
	{
		printf("failed to get string\n");
		exit(stderr);
	}

	printf("비교할 패턴을 입력하세요 : "); //get pat
	if (!gets(pat))
	{
		printf("failed to get string\n");
		exit(stderr);
	}

	out = nfind(target, pat);

	if (out != -1)
		printf("문자열 %d 번째부터 패턴이 시작됨..\n", out);
	else
		printf("문자열에서 패턴이 검출되지 않음\n");

	return 0;
}
int nfind(char* target, char* pat)
{
	int i = 0, j = 0, start = 0;	//declare varialbes and initialize
	int lastT = strlen(target) - 1;
	int lastP = strlen(pat) - 1;
	int endMatch = lastP;

	for (i = 0; endMatch <= lastT; endMatch++, start++) //if last char match, start matching
	{
		if (target[endMatch] == pat[lastP])
			for (j = 0, i = start; j < lastP && target[i] == pat[j]; i++, j++);
		if (j == lastP)
			return start;
	}
	return -1;
}
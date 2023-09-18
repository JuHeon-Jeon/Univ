#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void ab(char* str, int* count);
char* getch(void);

int main(void)
{
	char* str = NULL;
	int count = 0;

	printf("문자열을 입력하세요 : ");
	str = getch();

	ab(str, &count);

	printf("\n반복 횟수 : %d\n", count);

	return 0;
}

void ab(char* str, int* count)
{
	int size = 0, index = 0;
	char* pstr;
	char tmp1, tmp2;

	pstr = str;

	while (*pstr != '\0')
	{
		pstr++;
		size++;
	}
	size++;

	if (size > 1)
	{
		pstr = str;

		while (1)
		{
			tmp1 = *pstr;
			if (tmp1 != NULL)
				tmp2 = *(++pstr);
			else
				break;

			if (tmp2 != NULL)
			{
				if (tmp1 == 'a' && tmp2 == 'b')
				{
					pstr++;
					(*count)++;
				}
			}
			else
				break;
		}
	}
}

char* getch(void) //StackOverFlow 참고해서 만듦
{
	char tmp;
	char* ptmp = NULL, * sptr = NULL;
	int index = 0, size = 0;

	while (tmp = getc(stdin))
	{
		if (!(tmp == EOF || tmp == '\n'))
		{
			if (index >= size)
			{
				size += 16;
				ptmp = realloc(sptr, size);
				sptr = ptmp;
			}

			sptr[index] = tmp;
			index++;
		}
		else
			break;
	}

	if (index >= size)
	{
		size++;
		ptmp = realloc(sptr, size);
		sptr = ptmp;
	}
	sptr[index] = NULL;

	return sptr;
}
/*
https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
*/
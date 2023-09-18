#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stdnt
{
	char gwa[50];
	int grade;
	char name[50];
	int score;
} stdnt;

int main(void) //StackOverFlow 참조
{
	int size = 0, max = 0, min = 100, sum = 0, orderHigh, orderLow;
	float mean;
	char tmpch = 'a';
	stdnt* stdptr = NULL;

	FILE* fp = fopen("input.txt", "r");

	while (fread(&tmpch, 1, 1, fp))
	{
		if (tmpch == '\n')
			size++;
	}
	size++;
	
	fseek(fp, 0, SEEK_SET);

	stdptr = (stdnt*)malloc(sizeof(stdnt) * size);
	if (stdptr == NULL)
	{
		fprintf(stderr, "Memory Allocation Failed\n");
		return 1;
	}


	for (int i = 0; i < size; i++)
	{

		fscanf(fp, "%s\t%d\t%s\t%d", (stdptr + i)->gwa, &(stdptr + i)->grade, (stdptr + i)->name, &(stdptr + i)->score);
		sum += stdptr[i].score;
		if (max < stdptr[i].score)
		{
			orderHigh = i;
			max = stdptr[i].score;
		}
		if (min > stdptr[i].score)
		{
			orderLow = i;
			min = stdptr[i].score;
		}
	}

	fclose(fp);

	mean = (float)(sum) / size;

	printf("평균 성적 = %2f\n", mean);
	printf("성적이 가장 낮은 학생 : %-20s %-10d %-10s %10d\n", stdptr[orderLow].gwa, stdptr[orderLow].grade, stdptr[orderLow].name, stdptr[orderLow].score);
	printf("성적이 가장 높은 학생 : %-20s %-10d %-10s %10d\n", stdptr[orderHigh].gwa, stdptr[orderHigh].grade, stdptr[orderHigh].name, stdptr[orderHigh].score);
	
	free(stdptr);

	return 0;
}
/*
https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
*/
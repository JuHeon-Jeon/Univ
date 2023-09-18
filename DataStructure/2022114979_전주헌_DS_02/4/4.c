#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_SIZE 2001

void sort(int a[], int n);

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	
	srand(time(NULL));

	FILE* fp = NULL;
	if (!(fp = fopen("out.txt", "w")))
	{
		printf("error opening file!");
		exit(stderr);
	}

	fprintf(fp, "%-6c %-8s  %-8s  %-8s\n", 'n', "ascend", "descend", "random");
	for (n = 0; n <= 2000; n += step)
	{
		//descending order
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
				a[i] = n - i;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, "%-6d %-8f", n, duration);
		//ascending order
		repetitions = 0;
		start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
				a[i] = i;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, " %-8f", duration);
		//random order
		repetitions = 0;
		start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
				a[i] = rand();

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, " %-8f\n", duration);

		if (n == 100)
			step = 100;
	}

	fclose(fp);
}

void sort(int a[], int n)
{
	int min, index, tmp;

	for (int i = 0; i < n; i++)
	{
		index = i;
		min = a[i];
		for (int j = i; j < n; j++)
			if (min > a[j])
			{
				min = a[j];
				index = j;
			}
		tmp = a[i];
		a[i] = a[index];
		a[index] = tmp;
	}
}
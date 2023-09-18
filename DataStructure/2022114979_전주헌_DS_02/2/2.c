#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2001

void sort(int a[], int n);

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;

	FILE* fp = NULL;
	if (!(fp = fopen("out.txt", "w")))
	{
		printf("error opening file!");
		exit(stderr);
	}

	fprintf(fp, "%-6c time\n", 'n');
	for (n = 0; n <= 2000; n += step)
	{
		for (i = 0; i < n; i++)
			a[i] = n - i;

		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		fprintf(fp, "%-6d %f\n", n, duration);
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
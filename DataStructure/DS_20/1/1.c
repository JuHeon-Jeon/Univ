#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100

void inc_insertion_sort(int list[], int first, int last, int gap);
void shell_sort(int list[], int n);
void print_list(int list[], int n, int gap);


int main(void)
{
	FILE* fp = NULL;
	int size, input;
	int ary[MAX_SIZE];
	//get data from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	fscanf(fp, "%d", &size);

	printf("list[] data\n");
	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%d", &input);
		ary[i] = input;
		printf("%5d", input);
	}
	printf("\n\n");

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//shell sort
	shell_sort(ary, size);



	return 0;
}
void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;

	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
		print_list(list, n, gap);
	}
}
void print_list(int list[], int n, int gap)
{
	printf("gap is %8d ======>\n", gap);
	for (int i = 0; i < n; i++)
		printf("%5d", list[i]);
	printf("\n\n\n");
}
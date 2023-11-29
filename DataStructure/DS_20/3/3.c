#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100



void merge(int initList[], int mergedList[], int left, int mid, int right);
void mergePass(int initList[], int mergedList[], int n, int s);
void mergeSort(int list[], int n);
void print_list(int list[]);

int size;

int main(void)
{
	FILE* fp = NULL;
	int input;
	int ary[MAX_SIZE];
	//get data from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	fscanf(fp, "%d", &size);

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
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
	//mergesort
	printf("<<<<< executing itterative merge sort >>>>>\n");
	mergeSort(ary, size);
	//print sortlist
	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	print_list(ary);
}
void merge(int initList[], int mergedList[], int left, int mid, int right)
{
	int j, k, t;
	j = mid + 1;
	k = left;

	while (left <= mid && j <= right)
	{
		if (initList[left] <= initList[j])
			mergedList[k++] = initList[left++];
		else
			mergedList[k++] = initList[j++];
	}
	if (left > mid)
		for (t = j; t <= right; t++)
			mergedList[t] = initList[t];
	else
		for (t = left; t <= mid; t++)
			mergedList[k + t - left] = initList[t];
}
void mergePass(int initList[], int mergedList[], int n, int s)
{
	int i, j;
	for (i = 0; i < n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if ((i + s - 1 < n) && s > 1)
		merge(initList, mergedList, i, i + s - 1, n - 1);
	else
		for (j = i; j < n; j++)
			mergedList[j] = initList[j];
}
void mergeSort(int list[], int n)
{
	int s = 1;
	int extra[MAX_SIZE];

	while (s < n)
	{
		mergePass(list, extra, n, s);

		printf("segment size : %d\n", s);
		printf("%12s :", "a");
		print_list(list);
		printf("%12s :", "temp");
		print_list(extra);
		printf("\n");

		s *= 2;

		mergePass(extra, list, n, s);

		printf("segment size : %d\n", s);
		printf("%12s :", "temp");
		print_list(extra);
		printf("%12s :", "a");
		print_list(list);
		printf("\n");

		s *= 2;
	}
}
void print_list(int list[])
{
	for (int i = 0; i < size; i++)
		printf("%5d", list[i]);
	printf("\n");
}

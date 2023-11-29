#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100

int calls = 0;

void quickSort(int list[], int left, int right, int size);
void print_list(int list[], int size);

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
	//quick sort
	quickSort(ary, 0, size, size);
	//print call of quick sort
	printf("\ncalls of quick sort: %d\n", calls);
	//print sorted list
	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	print_list(ary, size);

	return 0;
}
void quickSort(int list[], int left, int right, int size)
{
	int pivot, i, j;

	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = list[left];
		int temp;

		if (right + 1 > size)
			j--;

		do {
			do {
				i++;
			} while ((list[i] < pivot) && (i < right));
			do {
				j--;
			} while (list[j] > pivot);

			if (i < j)
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		} while (i < j);

		temp = list[left];
		list[left] = list[j];
		list[j] = temp;

		printf("pivot = %d :", pivot);
		print_list(list, size);
		calls++;

		quickSort(list, left, j - 1, size);
		quickSort(list, j + 1, right, size);
	}
}
void print_list(int list[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%4d", list[i]);
	printf("\n");
}

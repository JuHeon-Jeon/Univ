#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 100

void adjust(int ary[], int root, int n);
void heapSort(int ary[], int n);

int main(void)
{
	FILE* fp = NULL;
	int key, size;
	int ary[MAX_SIZE];

	//get key from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	fscanf(fp, "%d", &size);

	for (int i = 1; i <= size; i++)
	{
		fscanf(fp, "%d", &key);
		ary[i] = key;
	}

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}

	printf("<<<<<<<<<< Input List >>>>>>>>>\n");
	for (int i = 1; i <= size; i++)
		printf("%d ", ary[i]);
	printf("\n\n");
	//execute heap sort
	printf("<<<<<<< executing heap sort >>>>>>>\n");

	for (int i = size / 2; i > 0; i--)
		adjust(ary, i, size);

	printf("after initialization of max heap...\n");
	for (int i = 1; i <= size; i++)
		printf("%d ", ary[i]);
	printf("\n\n\n\n");

	heapSort(ary, size);

	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 1; i <= size; i++)
		printf("%d ", ary[i]);
	printf("\n");


	return 0;
}
void adjust(int ary[], int root, int n)
{
	int child, temp;

	temp = ary[root];

	child = 2 * root;

	while (child <= n)
	{
		if ((child < n) && (ary[child] < ary[child + 1]))
			child++;

		if (temp > ary[child])
			break;
		else
		{
			ary[child / 2] = ary[child];
			child *= 2;
		}
	}
	ary[child / 2] = temp;
}
void heapSort(int ary[], int n)
{
	int i, j;
	int temp, count = 1;

	for (i = n - 1; i > 0; i--)
	{
		temp = ary[1];
		ary[1] = ary[i + 1];
		ary[i + 1] = temp;
		adjust(ary, 1, i);

		printf("step %d: Ãâ·Â %d :", count++, ary[i + 1]);
		for (j = 1; j <= i; j++)
			printf("%5d", ary[j]);
		printf("\n");
	}
}
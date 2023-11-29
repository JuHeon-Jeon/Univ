#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKETS 10
#define MAX_SIZE 100

typedef struct element* elementLink;
typedef struct element
{
	int data;
	elementLink link;
} element;

void radix_sort(int list[], int n);
void enqueue(elementLink* queue, int input);
elementLink dequeue(elementLink* queue);


int main(void)
{
	FILE* fp = NULL;
	int digits, input, size;
	int ary[MAX_SIZE];

	//get data from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	fscanf(fp, "%d %d", &digits, &size);
	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%d", &input);
		ary[i] = input;
	}

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//print input data
	printf("input data ---\n");
	for (int i = 0; i < size; i++)
		printf("%5d", ary[i]);
	printf("\n\n");
	//radix sort
	radix_sort(ary, digits, size);

	return 0;
}
void radix_sort(int list[], int digits, int n)
{
	int i, b, d, factor = 1;
	int count = 0;
	elementLink queue[BUCKETS];
	elementLink ptr = NULL;

	for (b = 0; b < BUCKETS; b++)
		queue[b] = NULL;

	for (d = 0; d < digits; d++)
	{
		for (i = 0; i < n; i++)
			enqueue(&queue[(list[i] / factor) % 10], list[i]);

		printf("step %d 자리 ---\n\n", count++);

		printf("Queue의 내용 ---\n");
		
		for (i = 0; i < BUCKETS; i++)
			printf("%5d", i);
		printf("\n");

		for (int j = 4; j > 0; j--)
		{
			for (i = 0; i < BUCKETS; i++)
			{
				ptr = queue[i];
				for (b = 1; b < j; b++)
				{
					if (ptr)
						ptr = ptr->link;
					else
						break;
				}
				if (ptr)
					printf("%5d", ptr->data);
				else
					printf("     ");
			}
			printf("\n\n");
		}

		for (b = i = 0; b < BUCKETS; b++)
			while (queue[b])
			{
				ptr = dequeue(&queue[b]);
				list[i++] = ptr->data;
			}
		factor *= 10;

		for (i = 0; i < 10; i++)
			printf("-----");
		printf("\n");
		for (i = 0; i < 10; i++)
		{
			printf("%5d", list[i]);
		}
		printf("\n\n");
	}

	printf("retult ---\n");
	for (i = 0; i < 10; i++)
	{
		printf("%5d", list[i]);
	}
	printf("\n\n");
}
void enqueue(elementLink* queue, int input)
{
	elementLink temp = *queue;
	elementLink temp2;

	temp2 = (elementLink)malloc(sizeof(element));
	temp2->data = input;
	temp2->link = NULL;

	if (temp)
	{
		for (temp; temp->link; temp = temp->link);

		temp->link = temp2;
	}
	else
		*queue = temp2;
}
elementLink dequeue(elementLink* queue)
{
	elementLink ptr = *queue;

	if (ptr)
	{
		*queue = ptr->link;

		return ptr;
	}
	else
	{
		printf("cannot dequeue, queue is empty!\n");
		exit(stderr);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

enum { FALSE, TRUE };

int main(void)
{
	int size = -1;
	int input1, input2, tmp;
	listPointer* seq;
	int* out;
	listPointer x = NULL, y = NULL, top = NULL;

	FILE* fp = NULL;
	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("failed to open \"input.txt\"\n");
		exit(stderr);
	}
	//read size
	fscanf(fp, "%d", &size);
	if (size == -1)
	{
		printf("error reading size!\n");
		exit(stderr);
	}

	seq = (listPointer*)malloc(sizeof(listPointer) * size);
	out = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++)
	{
		seq[i] = NULL;
		out[i] = FALSE;
	}
	//read file
	while (!feof(fp))
	{
		input1 = -1;
		input2 = -1;

		fscanf(fp, "%d %d", &input1, &input2);

		if (input1 != -1)
		{
			x = (listPointer)malloc(sizeof(listNode));
			x->data = input1;
			x->link = seq[input2];
			seq[input2] = x;

			x = (listPointer)malloc(sizeof(listNode));
			x->data = input2;
			x->link = seq[input1];
			seq[input1] = x;
		}

		x = NULL;
	}
	//close file
	if (fclose(fp) == EOF)
	{
		printf("failed to close \"input.txt\"\n");
		exit(stderr);
	}
	//print equivalence relation
	for (int i = 0; i < size; i++)
	{
		printf("%d : symmetric °ü°è:\n", i);
		
		x = seq[i];
		while (x)
		{
			printf("(%p %d %p)     ", x, x->data, x->link);
			x = x->link;
		}
		printf("\n");
		x = NULL;
	}
	//print equivalence class
	for (int i = 0; i < size; i++)
	{
		if (!out[i])
		{
			printf("\nNew Class: %5d", i);
			out[i] = TRUE;
			
			x = seq[i];
			top = NULL;

			for (;;)
			{
				while (x)
				{
					tmp = x->data;
					if (!out[tmp])
					{
						printf("%5d", tmp);
						out[tmp] = TRUE;

						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else
						x = x->link;
				}

				if (!top)
					break;
				x = seq[top->data];
				top = top->link;
			}
		}
	}


	return 0;
}
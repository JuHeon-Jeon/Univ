#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct listNode* listPointer;
typedef struct listNode
{
	int vertex;
	listPointer link;
} listNode;

void undir(listPointer** list, int vertex1, int vertex2);
void dir(listPointer** list, int vertex1, int vertex2);
void printList(listPointer* list, int sizeVertex);

int main(void)
{
	FILE* fp;
	int vertex1, vertex2;
	int sizeVertex, sizeEdge;
	char ch;
	//get info from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file\n");
		exit(stderr);
	}

	fscanf(fp, "%c %d %d", &ch, &sizeVertex, &sizeEdge);

	listPointer* adjList;
	adjList = (listPointer*)malloc(sizeof(listPointer) * sizeVertex);
	for (int i = 0; i < sizeVertex; i++)
	{
		adjList[i] = (listPointer)malloc(sizeof(listNode));
		adjList[i]->vertex = -1;
		adjList[i]->link = NULL;
	}
	//get edge from file and make list
	if (ch == 'u')
	{
		for (int i = 0; i < sizeEdge; i++)
		{
			fscanf(fp, "%d %d", &vertex1, &vertex2);
			undir(&adjList, vertex1, vertex2);
		}
	}
	else
	{
		for (int i = 0; i < sizeEdge; i++)
		{
			fscanf(fp, "%d %d", &vertex1, &vertex2);
			dir(&adjList, vertex1, vertex2);
		}
	}

	if (fclose(fp))
	{
		printf("cannot close file\n");
		exit(stderr);
	}
	//print
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	printList(adjList, sizeVertex);

	return 0;
}
void undir(listPointer** list, int vertex1, int vertex2)
{
	listPointer tmp = NULL;
	listPointer node = NULL;
	node = (listPointer)malloc(sizeof(listNode));
	node->vertex = vertex2;
	node->link = NULL;

	if ((*list)[vertex1]->link)
	{
		tmp = (*list)[vertex1]->link;
		(*list)[vertex1]->link = node;
		node->link = tmp;
	}
	else
		(*list)[vertex1]->link = node;

	listPointer node2;
	node2 = (listPointer)malloc(sizeof(listNode));
	node2->vertex = vertex1;
	node2->link = NULL;

	if ((*list)[vertex2]->link)
	{
		tmp = (*list)[vertex2]->link;
		(*list)[vertex2]->link = node2;
		node2->link = tmp;
	}
	else
		(*list)[vertex2]->link = node2;
}
void dir(listPointer** list, int vertex1, int vertex2)
{
	listPointer tmp = NULL;
	listPointer node = NULL;
	node = (listPointer)malloc(sizeof(listNode));
	node->vertex = vertex2;
	node->link = NULL;

	if ((*list)[vertex1]->link)
	{
		tmp = (*list)[vertex1]->link;
		(*list)[vertex1]->link = node;
		node->link = tmp;
	}
	else
		(*list)[vertex1]->link = node;
}
void printList(listPointer* list, int sizeVertex)
{
	listPointer ptr = NULL;
	for (int i = 0; i < sizeVertex; i++)
	{
		ptr = list[i];

		printf("adjList[%d] :", i);
		while (ptr)
		{
			if (ptr->vertex >= 0)
				printf("%5d", ptr->vertex);

			ptr = ptr->link;
		}
		printf("\n");
	}
}
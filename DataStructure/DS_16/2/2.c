#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode
{
	int vertex1;
	int vertex2;
	listPointer link1;
	listPointer link2;
} listNode;

void makeList(listPointer** list, int vertex1, int vertex2);
void printInorder(listPointer* list, int sizeVertex);
void printNumorder(listPointer* list, int sizeVertex);


int main(void)
{
	int sizeVertex, sizeEdge;
	int vertex1, vertex2;
	FILE* fp = NULL;
	//get vertices and edges
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file\n");
		exit(stderr);
	}

	fscanf(fp, "%d %d", &sizeVertex, &sizeEdge);
	//make adjacency multilist
	listPointer* adjList = NULL;
	adjList = (listPointer*)malloc(sizeof(listPointer) * sizeVertex);
	for (int i = 0; i < sizeVertex; i++)
	{
		adjList[i] = (listPointer)malloc(sizeof(listNode));
		adjList[i]->vertex1 = -1;
		adjList[i]->vertex2 = -1;
		adjList[i]->link1 = NULL;
		adjList[i]->link2 = NULL;
	}

	for (int i = 0; i < sizeEdge; i++)
	{
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		makeList(&adjList, vertex1, vertex2);
	}

	if (fclose(fp))
	{
		printf("cannot close file\n");
		exit(stderr);
	}
	//print
	printf("<<<<<<<<<< edges incident to each vertex >>>>>>>>>>\n\n");
	printInorder(adjList, sizeVertex);
	printf("\n");
	printNumorder(adjList, sizeVertex);

	return 0;
}
void makeList(listPointer** list, int vertex1, int vertex2)
{
	listPointer ptr = NULL;
	listPointer trail = NULL;
	listPointer node = NULL;
	int index = 1;
	node = (listPointer)malloc(sizeof(listNode));
	node->vertex1 = vertex1;
	node->vertex2 = vertex2;
	node->link1 = NULL;
	node->link2 = NULL;

	//vertex1's adventure
	ptr = (*list)[vertex1];
	trail = ptr;
	ptr = ptr->link1;

	while (ptr)
	{
		if (vertex1 == ptr->vertex1)
		{
			trail = ptr;
			ptr = ptr->link1;
			index = 1;
		}
		else
		{
			trail = ptr;
			ptr = ptr->link2;
			index = 2;
		}
	}
	
	if (index == 1)
		trail->link1 = node;
	else
		trail->link2 = node;
	
	//vertex2's adventure
	ptr = (*list)[vertex2];
	trail = ptr;
	ptr = ptr->link1;
	index = 1;

	while (ptr)
	{
		if (vertex2 == ptr->vertex1)
		{
			trail = ptr;
			ptr = ptr->link1;
			index = 1;
		}
		else
		{
			trail = ptr;
			ptr = ptr->link2;
			index = 2;
		}
	}

	if (index == 1)
		trail->link1 = node;
	else
		trail->link2 = node;
}
void printInorder(listPointer* list, int sizeVertex)
{
	listPointer ptr = NULL;
	
	printf("간선의 정점 출력 순서 - 입력데이터 순서대로\n");
	for (int i = 0; i < sizeVertex; i++)
	{
		ptr = list[i];
		ptr = ptr->link1;

		printf("edges incident to vertex %d : ", i);

		while (ptr)
		{
			printf("(%d, %d) ", ptr->vertex1, ptr->vertex2);

			if (i == ptr->vertex1)
				ptr = ptr->link1;
			else
				ptr = ptr->link2;
		}
		printf("\n");
	}
}
void printNumorder(listPointer* list, int sizeVertex)
{
	listPointer ptr = NULL;

	printf("간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (int i = 0; i < sizeVertex; i++)
	{
		ptr = list[i];
		ptr = ptr->link1;

		printf("edges incident to vertex %d : ", i);

		while (ptr)
		{
			if (i == ptr->vertex1)
			{
				printf("(%d, %d) ", ptr->vertex1, ptr->vertex2);

				ptr = ptr->link1;
			}
			else
			{
				printf("(%d, %d) ", ptr->vertex2, ptr->vertex1);

				ptr = ptr->link2;
			}
		}
		printf("\n");
	}
}
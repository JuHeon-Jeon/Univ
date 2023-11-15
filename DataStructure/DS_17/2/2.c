#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} node;

typedef struct queue* queuePointer;
typedef struct queue
{
	int vertex;
	queuePointer link;
} queue;

nodePointer* graph = NULL;
int* visited = NULL;
queuePointer front = NULL;
queuePointer rear = NULL;

void makeList(int vertex1, int vertex2);
void printList(int vertexSize);
void bfs(int index);
void addq(int vertex);
int delq(void);

int main(void)
{
	FILE* fp;
	int vertexSize, edgeSize;
	int vertex1, vertex2;
	//get vertex and edge from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}

	fscanf(fp, "%d %d", &vertexSize, &edgeSize);

	graph = (nodePointer*)malloc(sizeof(nodePointer) * vertexSize);
	for (int i = 0; i < vertexSize; i++)
	{
		graph[i] = (nodePointer)malloc(sizeof(node));
		graph[i]->vertex = i;
		graph[i]->link = NULL;
	}

	visited = (int*)malloc(sizeof(int) * vertexSize);
	for (int i = 0; i < vertexSize; i++)
		visited[i] = 0;
	//make adjacency list
	for (int i = 0; i < edgeSize; i++)
	{
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		makeList(vertex1, vertex2);
	}

	if (fclose(fp))
	{
		printf("cannot close file!\n");
		exit(stderr);
	}
	//print adjacency list
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	printList(vertexSize);
	//do bfs
	printf("<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
	for (int i = 0; i < vertexSize; i++)
	{
		for (int j = 0; j < vertexSize; j++)
			visited[j] = 0;

		printf("dfs<%d> :", i);
		bfs(i);
		printf("\n");
	}
	return 0;
}
void makeList(int vertex1, int vertex2)
{
	nodePointer ptr = NULL;
	nodePointer tmp = NULL;
	tmp = (nodePointer)malloc(sizeof(node));
	tmp->vertex = vertex2;
	tmp->link = NULL;

	if (graph[vertex1]->link)
	{
		ptr = graph[vertex1]->link;
		graph[vertex1]->link = tmp;
		tmp->link = ptr;
	}
	else
	{
		graph[vertex1]->link = tmp;
	}

	nodePointer tmp2 = NULL;
	tmp2 = (nodePointer)malloc(sizeof(node));
	tmp2->vertex = vertex1;
	tmp2->link = NULL;

	if (graph[vertex2]->link)
	{
		ptr = graph[vertex2]->link;
		graph[vertex2]->link = tmp2;
		tmp2->link = ptr;
	}
	else
		graph[vertex2]->link = tmp2;
}
void printList(int vertexSize)
{
	nodePointer ptr = NULL;
	for (int i = 0; i < vertexSize; i++)
	{
		ptr = graph[i];
		ptr = ptr->link;

		printf("graph[%d] :", i);
		while (ptr)
		{
			printf("%5d", ptr->vertex);

			ptr = ptr->link;
		}
		printf("\n");
	}
}
void bfs(int index)
{
	nodePointer ptr;
	front = rear = NULL;
	
	printf("%5d", index);
	
	visited[index] = 1;
	addq(index);

	while (front)
	{
		index = delq();
		
		for (ptr = graph[index]; ptr; ptr = ptr->link)
			if (!visited[ptr->vertex])
			{
				printf("%5d", ptr->vertex);
				addq(ptr->vertex);
				visited[ptr->vertex] = 1;
			}
	}

}
void addq(int vertex)
{
	queuePointer tmp = NULL;
	tmp = (queuePointer)malloc(sizeof(queue));
	tmp->vertex = vertex;
	tmp->link = NULL;

	if (front)
	{
		rear->link = tmp;
		rear = tmp;
	}
	else
	{
		front = tmp;
		rear = tmp;
	}
}
int delq(void)
{
	queuePointer tmp = front;

	if (tmp)
	{
		int rtn = tmp->vertex;

		front = front->link;

		free(tmp);

		return rtn;
	}
	else
	{
		printf("cannot delq queue is empty!\n");
		exit(stderr);
	}
}
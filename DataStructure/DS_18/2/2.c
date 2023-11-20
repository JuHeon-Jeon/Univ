#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 10000

int selected[INF];
int dist[INF];
int** weight;
int mincost = 0;

typedef struct element {
	int u;
	int v;
	int weight;
} element;

typedef struct node* nodePointer;
typedef struct node {
	element data;
	nodePointer link;
} node;

nodePointer list = NULL;

int get_min_vertex(int n);
void prim(int s, int n);
void push(element input);
element pop(void);



int main(void)
{
	FILE* fp = NULL;
	int u, v, value, edgeSize, vertexSize = -1;
	element data;
	//get edgesize
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file\n");
		exit(stderr);
	}

	fscanf(fp, "%d", &edgeSize);
	//get edges
	for (int i = 0; i < edgeSize; i++)
	{
		fscanf(fp, "%d %d %d", &u, &v, &value);
		data.u = u;
		data.v = v;
		data.weight = value;
		push(data);
	}
	//get vertex size
	nodePointer ptr = list;

	for (ptr; ptr; ptr = ptr->link)
	{
		if (vertexSize < ptr->data.u)
			vertexSize = ptr->data.u;
		else if (vertexSize < ptr->data.v)
			vertexSize = ptr->data.v;
	}
	vertexSize += 1;

	if (fclose(fp))
	{
		printf("cannot close file\n");
		exit(stderr);
	}
	//make weight
	weight = (int**)malloc(sizeof(int*) * vertexSize);
	for (int i = 0; i < vertexSize; i++)
		weight[i] = (int*)malloc(sizeof(int) * vertexSize);

	for (int i = 0; i < vertexSize; i++)
		for (int j = 0; j < vertexSize; j++)
			weight[i][j] = INF;

	while (list)
	{
		data = pop();
		u = data.u;
		v = data.v;
		value = data.weight;

		weight[u][v] = value;
		weight[v][u] = value;
	}
	//do prim
	prim(0, vertexSize);

	printf("최소비용 : %d", mincost);

	return 0;
}
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i])
		{
			v = i;
			break;
		}
	for (i = v + 1; i < n; i++)
		if (!selected[i] && (dist[i] < dist[v]))
			v = i;

	return v;
}
void prim(int s, int n)
{
	int i, u, v;
	int cur = -1, trail = -1;

	for (u = 0; u < n; u++)
	{
		dist[u] = INF;
		selected[u] = 0;
	}

	dist[s] = 0;

 	for (i = 0; i < n; i++)
	{
		u = get_min_vertex(n);
		selected[u] = 1;
		if (dist[u] == INF)
			return;

		trail = cur;
		cur = u;

		printf("선택 vertex : %d,", u);

		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];

		printf("%10s :", "distance");
		for (int z = 0; z < n; z++)
		{
			if (dist[z] != INF)
				printf("%5d", dist[z]);
			else
				printf("%5s", "INF");
		}

		if (trail >= 0)
		{
			printf("%10s edge : ", "선택");
			printf("(%d, %d) ", trail, cur);
			printf("distance : %d", dist[cur]);
			
			mincost += dist[cur];
		}
		printf("\n");
	}
}
void push(element input)
{
	nodePointer ptr, tmp = NULL;
	tmp = (nodePointer)malloc(sizeof(node));
	tmp->data = input;
	tmp->link = NULL;

	if (list)
	{
		ptr = list;
		for (ptr; ptr->link; ptr = ptr->link);
		ptr->link = tmp;
	}
	else
		list = tmp;
}
element pop(void)
{
	element rtn;
	if (list)
	{
		rtn = list->data;
		list = list->link;
	}
	else
	{
		printf("cannot pop : list is empty");
		exit(stderr);
	}

	return rtn;
}
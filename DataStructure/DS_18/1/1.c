#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF 10000
#define MAX_ELEMENT 100

typedef struct {
	int key;
	int u;
	int v;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType heap;

void insert_heap_edge(HeapType* h, int u, int v, int weight);
void insert_min_heap(HeapType* h, element e);
element delete_min_heap(HeapType* h);
void heapify(HeapType* h, int i);
void kruskal(int n);
int find(int i, int younion[]);
void yunion (int u, int v, int younion[]);
int getVertexSize(HeapType* h);

int mincost = 0;

int main(void)
{
	heap.heap_size = 0;
	int edgeSize, vertexSize, u, v, weight;
	FILE* fp = NULL;
	//get size from file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}
	fscanf(fp, "%d", &edgeSize);
	//get info from file
	for (int i = 0; i < edgeSize; i++)
	{
		fscanf(fp, "%d %d %d", &u, &v, &weight);
		insert_heap_edge(&heap, u, v, weight);
	}

	if (fclose(fp))
	{
		printf("cannot open file!\n");
		exit(stderr);
	}
	//do krusal
	vertexSize = getVertexSize(&heap);
	vertexSize++;
	kruskal(vertexSize);

	printf("\n최소비용 : %d", mincost);


	return 0;
}

void insert_heap_edge(HeapType* h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}
void insert_min_heap(HeapType* h, element e)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (e.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = e;
}
element delete_min_heap(HeapType* h)
{
	element rtn = h->heap[1];

	if (h->heap_size >= 1)
	{
		h->heap[1] = h->heap[h->heap_size];

		heapify(h, 1);
	}
	
	h->heap_size--;

	return rtn;
}
void heapify(HeapType* h, int i)
{
	int left = i * 2;
	int right = i * 2 + 1;
	element tmp;

	if (h->heap[left].key < h->heap[right].key && left <= h->heap_size)
	{
		if (h->heap[i].key > h->heap[left].key)
		{
			tmp = h->heap[i];
			h->heap[i] = h->heap[left];
			h->heap[left] = tmp;


			heapify(h, left);
		}
	}
	else if (h->heap[left].key > h->heap[right].key && right <= h->heap_size)
	{
		if (h->heap[i].key > h->heap[right].key)
		{
			tmp = h->heap[i];
			h->heap[i] = h->heap[right];
			h->heap[right] = tmp;

			heapify(h, right);
		}
	}

}
void kruskal(int n)
{
	int edge_accepted = 0;
	int uset, vset;
	element e;
	int younion[MAX_ELEMENT];

	for (int i = 0; i < 100; i++)
		younion[i] = -1;

	while (edge_accepted < (n - 1))
	{
		e = delete_min_heap(&heap);
		uset = find(e.u, younion);
		vset = find(e.v, younion);

		if (uset != vset)
		{
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			yunion(uset, vset, younion);
			mincost += e.key;
		}
	}

}
int find(int i, int* younion)
{
	if (i >= MAX_ELEMENT)
	{
		printf("error younion find : beyond MAX_ELEMENT\n");
		exit(stderr);
	}

	for (; younion[i] >= 0; i = younion[i]);

	return i;
}
void yunion(int u, int v, int* younion)
{
	if (u >= MAX_ELEMENT || v >= MAX_ELEMENT)
	{
		printf("error younion yunion : beyound MAX_ELEMENT\n");
		exit(stderr);
	}
	younion[u] = v;
}
int getVertexSize(HeapType* h)
{
	int rtn = 0;

	for (int i = 1; i <= h->heap_size; i++)
	{
		if (rtn < h->heap[i].v)
			rtn = h->heap[i].v;
		else if (rtn < h->heap[i].u)
			rtn = h->heap[i].u;
	}

	return rtn;
}
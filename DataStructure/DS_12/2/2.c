#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data;
	treePointer leftchild;
	treePointer rightchild;
} treeNode;
typedef struct nodeQueue {
	treePointer data;
	treePointer link;
} nodeQueue;

nodeQueue* queue = NULL;

void inorder(treePointer root);
void preorder(treePointer root);
void postorder(treePointer root);
void enqueue(treePointer node);
void dequeue(void);
treePointer getqueue(void);

int main(void)
{
	FILE* fp = NULL;
	treePointer root = NULL;
	treePointer node = NULL;
	treePointer ptr = NULL;
	char input;

	//open file
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}
	//read file & create binary tree
	printf("creating a complete binary tree\n");

	while (!feof(fp))
	{
		input = 0;
		node = NULL;
		ptr = NULL;
		fscanf(fp, "%c", &input);

		if (input != 0 && input != '\n')
		{
			node = (treePointer)malloc(sizeof(treeNode));
			node->data = input;
			node->leftchild = NULL;
			node->rightchild = NULL;

			if (!root)
				root = node;
			else
			{
				ptr = getqueue();

				if (!(ptr->leftchild))
					ptr->leftchild = node;
				else if (!(ptr->rightchild))
					ptr->rightchild = node;
				
				if (ptr->leftchild && ptr->rightchild)
					dequeue();
			}

			enqueue(node);
		}
	}

	//print binary tree;
	printf("\nthree binary tree traversals\n");

	printf("inorder traversal     : ");
	inorder(root);
	printf("\n");

	printf("preorder traversal    : ");
	preorder(root);
	printf("\n");

	printf("postorder traversal  : ");
	postorder(root);
	printf("\n");

	return 0;
}
void inorder(treePointer root)
{
	if (root)
	{
		inorder(root->leftchild);
		printf("%c ", root->data);
		inorder(root->rightchild);
	}
}
void preorder(treePointer root)
{
	if (root)
	{
		printf("%c ", root->data);
		preorder(root->leftchild);
		preorder(root->rightchild);
	}
}
void postorder(treePointer root)
{
	if (root)
	{
		postorder(root->leftchild);
		postorder(root->rightchild);
		printf("%c ", root->data);
	}
}
void enqueue(treePointer node)
{
	nodeQueue* ptr = queue;
	nodeQueue* temp = NULL;
	temp = (nodeQueue*)malloc(sizeof(nodeQueue));
	temp->data = node;
	temp->link = NULL;

	if (!ptr)
		queue = temp;
	else
	{
		for (; ptr->link != NULL; ptr = ptr->link);
		ptr->link = temp;
	}
}
void dequeue(void)
{
	nodeQueue* ptr = queue;

	if (!ptr)
	{
		printf("cannot dequeue, queue is empty!\n");
		exit(stderr);
	}

	queue = queue->link;
	free(ptr);
}
treePointer getqueue(void)
{
	if (queue)
		return queue->data;
	else
	{
		printf("cannot getqueue, queue is empty!\n");
		exit(stderr);
	}
}
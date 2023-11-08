#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

typedef struct treeNode* treePointer;
typedef struct treeNode {
	int key;
	int item;
	treePointer lchild;
	treePointer rchild;
} treeNode;

treePointer root = NULL;


void searchNprint(treePointer tree, int target);
treePointer modSearch(treePointer* node, int target);
int insert(treePointer* node, int num);
void inorder(treePointer node);

int main(void)
{
	int n, seed, num, success;
	//get seed and node number
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf("%d", &n);
	//exception
	if (n < 1 || n > 50)
	{
		success = 0;

		do
		{
			printf("\nthe number of nodes in BST must be less than and equal to 50! : ");
			scanf("%d", &n);

			if (n > 0 && n < 51)
				success = 1;
		} while (!success);
	}

	printf("%s", "seed : ");
	scanf("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);
	//generate BST (key == item)
	for (int i = 0; i < n; i++)
	{
		success = 0;

		do
		{
			num = rand() % MAX_SIZE + 1;
			success = insert(&root, num);
		} while (!success);
	
		printf("%4d", num);
	}
	//get key to search
	printf("\nthe key to search : ");
	scanf("%d", &n);
	//search
	printf("the search process : ");
	searchNprint(root, n);
	//inorder traversal
	printf("\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
	printf("\n");

	return 0;
}
void searchNprint(treePointer tree, int target)
{
	while (tree)
	{
		printf("%4d =>", tree->key);

		if (target == tree->key)
		{
			printf("\nthe element is in BST\n");
			return;
		}
		if (target < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}

	printf("\nthe element is not in BST\n");
}
treePointer modSearch(treePointer* node, int target)
{
	treePointer trail = NULL;
	treePointer ptr = *node;
	while (ptr)
	{
		if (target == ptr->key)
			return NULL;
		if (target < ptr->key)
		{
			trail = ptr;
			ptr = ptr->lchild;
		}
		else
		{
			trail = ptr;
			ptr = ptr->rchild;
		}
	}

	return trail;
}
int insert(treePointer* node, int num)
{
	treePointer ptr = NULL;
	treePointer temp = modSearch(node, num);

	if (temp || !(*node))
	{
		ptr = (treePointer)malloc(sizeof(treeNode));
		ptr->key = num;
		ptr->item = num;
		ptr->lchild = NULL;
		ptr->rchild = NULL;

		if (*node)
		{
			if (num < temp->key)
				temp->lchild = ptr;
			else
				temp->rchild = ptr;
		}
		else
			*node = ptr;

		return 1;
	}

	return 0;
}
void inorder(treePointer node)
{
	if (node)
	{
		inorder(node->lchild);
		printf("%4d", node->item);
		inorder(node->rchild);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data;
	treePointer leftchild;
	treePointer rightchild;
} treeNode;

void inorder(treePointer root);
void preorder(treePointer root);
void postorder(treePointer root);

int main(void)
{
	//create binary tree
	printf("creating a binary tree\n");

	treePointer root = NULL;
	treePointer node = NULL;
	treePointer ptr = NULL;

	node = (treePointer)malloc(sizeof(treeNode));
	node->data = 'A';
	node->leftchild = NULL;
	node->rightchild = NULL;
	root = node;

	node = NULL;
	node = (treePointer)malloc(sizeof(treeNode));
	node->data = 'B';
	node->leftchild = NULL;
	node->rightchild = NULL;
	root->leftchild = node;

	node = NULL;
	node = (treePointer)malloc(sizeof(treeNode));
	node->data = 'C';
	node->leftchild = NULL;
	node->rightchild = NULL;
	root->rightchild = node;

	node = NULL;
	node = (treePointer)malloc(sizeof(treeNode));
	node->data = 'D';
	node->leftchild = NULL;
	node->rightchild = NULL;
	root->leftchild->leftchild = node;

	node = NULL;
	node = (treePointer)malloc(sizeof(treeNode));
	node->data = 'E';
	node->leftchild = NULL;
	node->rightchild = NULL;
	root->leftchild->rightchild = node;

	//print tree
	printf("\nthree binary tree traversals\n");

	printf("inorder traversal     :\n");
	inorder(root);

	printf("\npreorder traversal    :\n");
	preorder(root);

	printf("\npostorder traversal   :\n");
	postorder(root);

	return 0;
}
void inorder(treePointer root)
{
	if (root)
	{
		inorder(root->leftchild);
		printf("(%p : %p  %c  %p)\n", root, root->leftchild, root->data, root->rightchild);
		inorder(root->rightchild);
	}
}
void preorder(treePointer root)
{
	if (root)
	{
		printf("(%p : %p  %c  %p)\n", root, root->leftchild, root->data, root->rightchild);
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
		printf("(%p : %p  %c  %p)\n", root, root->leftchild, root->data, root->rightchild);
	}
}
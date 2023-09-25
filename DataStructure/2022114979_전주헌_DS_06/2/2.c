#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define EXIT_ROW 4
#define EXIT_COL 5

typedef struct {
	int row;
	int col;
	int dir;
} element;

typedef struct {
	int vert;
	int horiz;
} direction;

direction dir[8];
element* stack;
top = -1;

void path(void);
void push(int row, int col, int dir);
element pop();

int main(void)
{
	FILE* fp = NULL;
	int row = 0, col = 0;
	int** maze, ** mark;

	dir[0].vert = -1; dir[0].horiz = 0; //dir initialize
	dir[1].vert = -1; dir[1].horiz = 1;
	dir[2].vert = 0; dir[2].horiz = 1;
	dir[3].vert = 1; dir[3].horiz = 1;
	dir[4].vert = 1; dir[4].horiz = 0;
	dir[5].vert = 1; dir[5].horiz = -1;
	dir[6].vert = 0; dir[6].horiz = -1;
	dir[7].vert = -1; dir[7].horiz = -1;


	if (!(fp = fopen("input.txt", "r"))) //open file
	{
		printf("failed to open \"input.txt\"");
		exit(stderr);
	}

	fscanf("%d, %d", &row, &col); //read row col

	stack = (element*)malloc(sizeof(element) * (row * col));

	row += 2; //make wall
	col += 2;

	maze = (int**)malloc(sizeof(int*) * row);
	*maze = (int*)malloc(sizeof(int) * col);

	mark = (int**)malloc(sizeof(int*) * row);
	*mark = (int*)malloc(sizeof(int) * col);

	for (int i = 0; i < row; i++) //initialize maze
		for (int j = 0; j < col; j++)
			maze[i][j] = 0;
	for (int i = 0; i < row; i++)
	{
		maze[i][0] = 1;
		maze[i][col - 1] = 1;		
	}
	for (int i = 0; i < col; i++)
	{
		maze[0][i] = 1;
		maze[row - 1][i] = 1;
	}

	for (int i = 0; i < row; i++) //initialize mark
		for (int j = 0; j < col; j++)
			mark[i][j] = 0;

	mark[1][1] = 1; //initalize first step
	push(1, 1, 2);

	path();

	return 0;
}
void path(void)
{
	int found = 0;
	element pos;
	int row = 0, col = 0, nRow = 0, nCol = 0, way;

	while (top > -1 && !found)
	{
		pos = pop();
		row = pos.row;
		col = pos.col;
		way = pos.dir;
		while (way < 8 && !found)
		{
			nRow = row + dir[way].vert;
			nCol = col + dir[way].horiz;
			if (nRow == EXIT_ROW && nCol == EXIT_COL)
				found = 1;
			else if (!maze[nRow][nCol] && !mark[nRow][nCol])
			{
				mark[nRow][nCol] = 1;
				push(row, col, ++way);
				row = nRow;
				col = nCol;
				way = 0;
			}
			else
				++way;
		}
	}
}
void push(int row, int col, int dir)
{
	stack[++top].row = row;
	stack[top].col = col;
	stack[top].dir = dir;
}
element pop()
{
	return stack[top--];
}
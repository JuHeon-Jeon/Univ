#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int row;
	int col;
	int val;
} sparceMatrix;


void fastTransponse(sparceMatrix* sM1, sparceMatrix* sM2);


int main(void)
{
	FILE* fpA = NULL, *fpB = NULL; //declare variables
	sparceMatrix *sM1, *sM2;
	int rows = 0, cols = 0, input = 0, count = 0;
	int** m1, ** m2;

	if (!(fpA = fopen("a.txt", "r"))) //read "a.txt"
	{
		printf("error opening \"a.txt\"\n");
		exit(stderr);
	}

	fscanf(fpA, "%d %d %d", &rows, &cols, &count); //read first line

	sM1 = (sparceMatrix*)malloc(sizeof(sparceMatrix) * (count + 1)); //allocate sM1
	if (!sM1)
	{
		printf("error allocating memory \"sM1\"\n");
		exit(stderr);
	}

	sM2 = (sparceMatrix*)malloc(sizeof(sparceMatrix) * (count + 1)); //allocate sM2
	if (!sM2)
	{
		printf("error allocating memory \"sM2\"\n");
		exit(stderr);
	}

	sM1[0].row = rows; //initialize sM1, sM2
	sM1[0].col = cols;
	sM1[0].val = count;

	sM2[0].row = cols;
	sM2[0].col = rows;
	sM2[0].val = count;

	for (int i = 1; i <= count; i++) //open "a.txt"
	{
		fscanf(fpA, "%d %d %d", &rows, &cols, &input);
		sM1[i].row = rows;
		sM1[i].col = cols;
		sM1[i].val = input;
	}

	if (fclose(fpA)) //fpA close
	{
		printf("error closing \"a.txt\"\n");
		exit(stderr);
	}

	fastTransponse(sM1, sM2);

	m1 = (int**)malloc(sizeof(int*) * sM1[0].row); //allocating m1
	for (int i = 0; i < sM1[0].row; i++)
		m1[i] = (int*)malloc(sizeof(int) * sM1[0].col);

	for (int i = 0; i < sM1[0].row; i++) //initialize m1
		for (int j = 0; j < sM1[0].col; j++)
			m1[i][j] = 0;

	for (int i = 1; i <= sM1[0].val; i++) //insert value in m1
	{
		rows = sM1[i].row;
		cols = sM1[i].col;
		m1[rows][cols] = sM1[i].val;
	}

	m2 = (int**)malloc(sizeof(int*) * sM2[0].row); //allocating m2
	for (int i = 0; i < sM2[0].row; i++)
		m2[i] = (int*)malloc(sizeof(int) * sM2[0].col);

	for (int i = 0; i < sM2[0].row; i++) //initialize m2
		for (int j = 0; j < sM2[0].col; j++)
			m2[i][j] = 0;

	for (int i = 1; i <= sM2[0].val; i++) //insert value in m2
	{
		rows = sM2[i].row;
		cols = sM2[i].col;
		m2[rows][cols] = sM2[i].val;
	}

	printf("A\n"); //print m1
	for (int i = 0; i < sM1[0].row; i++)
	{
		for (int j = 0; j < sM1[0].col; j++)
			printf("%5d", m1[i][j]);
		printf("\n");
	}

	printf("A\n"); //print m2
	for (int i = 0; i < sM2[0].row; i++)
	{
		for (int j = 0; j < sM2[0].col; j++)
			printf("%5d", m2[i][j]);
		printf("\n");
	}

	if (!(fpB = fopen("b.txt", "w"))) //open "b.txt"
	{
		printf("error opening \"b.txt\"\n");
		exit(stderr);
	}

	for (int i = 0; i <= sM2[0].val; i++) //write "b.txt"
		fprintf(fpB, "%d\t%d\t%d\n", sM2[i].row, sM2[i].col, sM2[i].val);

	if (fclose(fpB)) //fpB close
	{
		printf("error closing \"a.txt\"\n");
		exit(stderr);
	}

	free(sM1);
	free(sM2);
	free(*m1);
	free(m1);
	free(*m2);
	free(m2);


	return 0;
}
void fastTransponse(sparceMatrix* sM1, sparceMatrix* sM2)
{
	int numCols = sM1[0].col, numTerms = sM1[0].val, index; //declare variables
	int* rowTerms, * startingPos;

	rowTerms = (int*)malloc(sizeof(int) * numCols); //allocate rowTerms & startingPos
	startingPos = (int*)malloc(sizeof(int) * numCols);

	if (numTerms > 0)
	{
		for (int i = 0; i < numCols; i++) //initialize rowTerms
			rowTerms[i] = 0;
		for (int i = 1; i <= numTerms; i++) //insert value in rowTerms
			rowTerms[sM1[i].col]++;

		startingPos[0] = 1; //initialize startingPos;
		for (int i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		for (int i = 1; i <= numTerms; i++) //insert value in sM2
		{
			index = startingPos[sM1[i].col];
			sM2[index].row = sM1[i].col;
			sM2[index].col = sM1[i].row;
			sM2[index].val = sM1[i].val;
			startingPos[sM1[i].col]++;
		}
	}
	free(rowTerms);
	free(startingPos);
}
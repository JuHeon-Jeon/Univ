//need to write postfix to output!!!!!!!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 80

char input[MAX_STRING_SIZE];
precedence stack[MAX_STRING_SIZE];
int top;
char output[MAX_STRING_SIZE];
int endOut = 0;

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void postfix(void);
precedence getToken(char* symbol, int* n);
void writeToken(precedence token);
void push(precedence token);
precedence pop(void);

int main(void)
{
	FILE* fin, * fout;

	for (int i = 0; i < MAX_STRING_SIZE; i++)
	{
		input[i] = '\0';
		output[i] = '\0';
	}

	//open input.txt
	if (!(fin = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}
	//read input.txt
	fgets(input, MAX_STRING_SIZE, fin);
	//close input.txt
	if (fclose(fin) == EOF)
	{
		printf("error closing\"input.txt\"\n");
		exit(stderr);
	}
	//print open file's expression
	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("%-25s: %s\n", "infix expression", input);
	printf("%-25s: ", "postifx expression");
	//infix to postfix
	postfix();
	//print postfix

	//open output.txt
	if (!(fout = fopen("output.txt", "w")))
	{
		printf("error opening \"output.txt\"\n");
		exit(stderr);
	}
	//write postfix to output.txt

	//close output.txt
	if (fclose(fout) == EOF)
	{
		printf("error closing\"output.txt\"\n");
		exit(stderr);
	}

	return 0;
}
void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
			output[endOut++] = symbol;
		else if (token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
precedence getToken(char* symbol, int* n)
{
	char* tmp = NULL;

	if (*symbol == NULL)
	{
		if (tmp = strtok(input, " \n"))
			*symbol = *tmp;
		else
			*symbol = '\0';
	}
	else
	{
		if (tmp = strtok(NULL, " \n"))
			*symbol = *tmp;
		else
			*symbol = '\0';
	}

	if (*symbol == '+')
		return plus;
	else if (*symbol == '-')
		return minus;
	else if (*symbol == '*')
		return times;
	else if (*symbol == '/')
		return divide;
	else if (*symbol == '%')
		return mod;
	else if (*symbol == '\0')
		return eos;
	else
		return operand;

}
void writeToken(precedence token)
{

}
void push(precedence token)
{

}
precedence pop(void)
{

}

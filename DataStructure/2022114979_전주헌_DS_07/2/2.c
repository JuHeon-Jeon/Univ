#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 80

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;


char input[MAX_STRING_SIZE];
precedence stack[MAX_STRING_SIZE];
int top;
char output[MAX_STRING_SIZE];
int endOut = 0;
char* inputPtr = NULL;

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
	for (int i = 0; i < endOut; i++)
		printf("%c ", output[i]);
	printf("\n");
	//open output.txt
	if (!(fout = fopen("output.txt", "w")))
	{
		printf("error opening \"output.txt\"\n");
		exit(stderr);
	}
	//write postfix to output.txt
	for (int i = 0; i < endOut; i++)
		fprintf(fout, "%c ", output[i]);
	fprintf(fout, "\n");
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
	char symbol = NULL;
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
				writeToken(pop());
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				writeToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		writeToken(token);
}
precedence getToken(char* symbol, int* n)
{
	if (inputPtr)
		inputPtr++;
	else
		inputPtr = input;

	*symbol = *inputPtr;

	/*
	if (*symbol == NULL)
	{
		if (tmp = strtok(input, " \n"))
			*symbol = *tmp;
		else
			*symbol = '\0';
	}
	else
	{
		if (tmp = strtok(tmp, " \n"))
			*symbol = *tmp;
		else
			*symbol = '\0';
	}
	*/
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
	else if (*symbol == '(')
		return lparen;
	else if (*symbol == ')')
		return rparen;
	else if (*symbol == '\0' || *symbol == '\n')
		return eos;
	else
		return operand;

}
void writeToken(precedence token)
{
	char tmp;
	switch (token)
	{
	case plus:
		tmp = '+';
		break;
	case minus:
		tmp = '-';
		break;
	case times:
		tmp = '*';
		break;
	case divide:
		tmp = '/';
		break;
	case mod:
		tmp = '%';
		break;
	default:
		printf("error : wrong token case\n");
		exit(stderr);
	}

	output[endOut++] = tmp;
}
void push(precedence token)
{
	if (top + 1 > MAX_STRING_SIZE)
	{
		printf("error : stack is full\n");
		exit(stderr);
	}
	
	stack[++top] = token;
}
precedence pop(void)
{
	if (top - 1 < -1)

	{
		printf("error stack is empty\n");
		exit(stderr);
	}
	else
		return stack[top--];
}

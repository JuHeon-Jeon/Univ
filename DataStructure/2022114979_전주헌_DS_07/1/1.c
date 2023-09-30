#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 80

typedef enum {
	plus, minus, times, divide, mod, operand, eos
} precedence;

char input[MAX_STRING_SIZE];
int stack[MAX_STRING_SIZE];
int top;

int eval(void);
precedence getToken(char* symbol, int* n);
void push(int n);
int pop(void);

int main(void)
{
	FILE* fp = NULL;
	for (int i = 0; i < MAX_STRING_SIZE; i++)
		input[i] = '\0';

	if (!(fp = fopen("input.txt", "r")))
	{
		printf("error opening \"input.txt\"\n");
		exit(stderr);
	}
	//get input from file
	fgets(input, MAX_STRING_SIZE, fp);
	//print input to console
	printf("postfix expression : %s\n", input);
	//print eval value
	printf("the evaluation value : %d\n", eval());


	return 0;
}
int eval(void)
{
	precedence token;
	char symbol = NULL;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');
		else
		{
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 & op2);
				break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
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
void push(int n)
{
	if ((top + 1) > MAX_STRING_SIZE)
	{
		printf("error : stack is full\n");
		exit(stderr);
	}
	else
		stack[++top] = n;
}
int pop(void)
{
	if (top <= -1)
	{
		printf("error : stack is empty\n");
		exit(stderr);
	}
	else
		return stack[top--];
}
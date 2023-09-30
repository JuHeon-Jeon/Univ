#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void pushS(int *stack, int n, int* top);
int popS(int *stack, int* top);
void pushO(char* stack, char c, int* top);
char popO(char* stack, int* top);

int main(void)
{
	int size = -1, topStack = -1, topOut = -1, input = -1, current = -1;
	int stack[100001] = { -1 };
	char out[100001] = { '\0' };
	int found = 0, Npossible = 0;
	int num = 1;

	scanf("%d", &size);

	if (size < 0)
	{
		printf("error! size is negative");
		exit(stderr);
	}

	stack[0] = num++;
	topStack++;
	out[0] = '+';
	topOut++;

	for (int i = 0; i < size; i++)
	{
		if (Npossible)
			break;
		found = 0;
		
		scanf("%d", &input);
		
		while (!found)
		{
			current = stack[topStack];

			if (current == input) //pop stack if current == input
			{
				popS(stack, &topStack);
				pushO(out, '-' , &topOut);
				found = 1;
			}
			else if (current < input) //push num to stack if num <= size
			{
				if (num <= size)
				{
					pushS(stack, num, &topStack);
					pushO(out, '+', &topOut);
					num++;
				}
				else //if num > size it is impossible
				{
					printf("NO");
					Npossible = 1;
					break;
				}
			}
			else //current > input, impossible
			{
				Npossible = 1;
				printf("NO");
				break;
			}

			if (Npossible)
			{
				printf("NO");
				break;
			}
		}
	}

	if (found)
		for (int i = 0; i <= topOut; i++)
			printf("%c\n", out[i]);


	return 0;
}
void pushS(int* stack, int n, int* top)
{
	stack[++(*top)] = n;
}
int popS(int* stack, int* top)
{
	if (*top > -1)
	{
		(*top)--;
		return 0;
	}
	else
		return 1;
}
void pushO(char* stack, char c, int* top)
{
	stack[++(*top)] = c;
}
char popO(char* stack, int* top)
{
	if (*top > -1)
		return stack[(*top)--];
	else
	{
		printf("error popO!\n");
		exit(stderr);
	}
}

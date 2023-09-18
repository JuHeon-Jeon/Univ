#include <stdio.h>
#include <stdlib.h>

#define MEMINT(a, b) \
	if (((a) = malloc(sizeof(int))) == NULL) \
		{ \
			fprintf(stderr, "No Memory"); \
			exit(EXIT_FAILURE); \
		} \
	*(a) = (b); \
	fprintf(stdout, "%d\n", *(a)); \
	free((a));
#define MEMFLT(a, b) \
	if (((a) = malloc(sizeof(float))) == NULL) \
		{ \
			fprintf(stderr, "No Memory"); \
			exit(EXIT_FAILURE); \
		} \
	*(a) = (b); \
	fprintf(stdout, "%f\n", *(a)); \
	free((a));


int main(void)
{
	int* pi;
	float* pf;

	printf("an integer = ");
	MEMINT(pi, 1024);
	printf("a float = ");
	MEMFLT(pf, 3.14);

	return 0;
}
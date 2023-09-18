#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct hB {
	char* name;
	int age;
	int salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2);

int main(void)
{
	humanBeing person1, person2;

	person1.name = (char*)malloc(sizeof(char) * 1000);
	person2.name = (char*)malloc(sizeof(char) * 1000);
	person1.age = 0;
	person2.age = 0;
	person1.salary = 0;
	person2.salary = 0;

	printf("Input person1's name, age, salary : \n");
	gets(person1.name);
	scanf("%d", &(person1.age));
	while (getchar() != '\n');
	scanf("%d", &(person1.salary));
	while (getchar() != '\n');

	printf("Input person2's name, age, salary : \n");
	gets(person2.name);
	scanf("%d", &(person2.age));
	while (getchar() != '\n');
	scanf("%d", &(person2.salary));

	if (humansEqual(&person1, &person2))
		printf("The two human beings are the same\n");
	else
		printf("The two human beings are not the same\n");

}

int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if (strcmp(person1->name, person2->name))
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}
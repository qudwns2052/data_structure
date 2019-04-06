#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>

#define DATA_LEN 50000
#define id_LEN 10
#define name_LEN 11
#define phone_LEN 11


typedef struct student
{
	char id[id_LEN];
	char name[name_LEN];
	int number[phone_LEN];

}Student;

void Initstudent(Student * student)
{
	int i;

	int id[id_LEN - 1];
	int real_id = 0;
	int subidx = 1;
	id[0] = 1;
	id[1] = (rand() % 7) + 3;
	for (i = 2; i < id_LEN - 1; i++)
	{
		id[i] = rand() % 10;
	}
	for (i = 0; i < id_LEN - 1; i++)
	{
		real_id += subidx * id[id_LEN - 2 - i];
		subidx *= 10;
	}
	itoa(real_id, student->id, 10);
	student->id[id_LEN - 1] = '\0';


	for (i = 0; i < name_LEN - 1; i++)
	{
		student->name[i] = (rand() % 26) + 97;
	}
	student->name[name_LEN - 1] = '\0';

	student->number[0] = 0;
	student->number[1] = 1;
	student->number[2] = 0;
	for (i = 3; i < phone_LEN; i++)
	{
		student->number[i] = rand() % 10;
	}

}

void Printstudent(Student * student)
{
	int i, j;
	for (i = 0; i < DATA_LEN; i++)
	{
		printf("id=%s ", (student + i)->id);
		printf("  name=%s  ", (student + i)->name);
		printf("number= ");
		for (j = 0; j < phone_LEN; j++)
		{
			printf("%d", (student + i)->number[j]);
		}
		printf("\n");
	}
}


void Swap_Student(Student * student1, Student * student2)
{
	Student temp;

	memcpy(&temp, student1, sizeof(Student));
	memcpy(student1, student2, sizeof(Student));
	memcpy(student2, &temp, sizeof(Student));

}

#define STACK_LEN 100*DATA_LEN
int Stack[STACK_LEN];
int topindex;

void Init_Stack(void)
{
	topindex = -1;
}
void Push(int idx)
{
	if (topindex + 1 >= STACK_LEN)
		return;
	else
		Stack[++topindex] = idx;
}

int Pop(void)
{
	if (topindex == -1)
		return 0;
	else
		return Stack[topindex--];
}


void Quick_Sort_id(Student * student)
{
	int left = 0;
	int right = DATA_LEN - 1;
	
	int L;
	int R;

	char pivot[id_LEN];

	Init_Stack();

	Push(right);
	Push(left);

	while (topindex > -1)
	{
		left = Pop();
		right = Pop();

		if (right - left > 0)
		{
			memcpy(&pivot, (student + right)->id, sizeof(char)* id_LEN);
			L = left;
			R = right;


			while (1)
			{
				while (strcmp((student + L)->id, pivot) < 0)
					L++;
				while (strcmp((student + R)->id, pivot) > 0)
					R--;

				if (L >= R)
					break;

				Swap_Student(&student[L], &student[R]);
			}

			Swap_Student(&student[L], &student[right]);

			Push(right);
			Push(L + 1);
			Push(L - 1);
			Push(left);

		}
	}
}

void Quick_Sort(Student * student)
{
	clock_t start, end;

	start = clock();
	Quick_Sort_id(student);
	end = clock();
	printf("\nQuick Sort !\n\n학번 순으로 정렬\n---------------------------------\n");
	//	Printstudent(student);
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);
}


int main(void)
{
	srand((unsigned)time(NULL));

	int i;
	Student * student;

	student = (Student*)malloc(sizeof(Student)*DATA_LEN);

	for (i = 0; i < DATA_LEN; i++)
	{
		Initstudent(&student[i]);
	}

	//	Printstudent(student);

	Quick_Sort(student);


	free(student);

	system("pause");
	return 0;
}
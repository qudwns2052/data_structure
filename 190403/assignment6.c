#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 50000 // ������ 5���� ���� �ޱ� ���� ������ ���̸� ����
#define id_LEN 9 // �й� ���� ����
#define name_LEN 11	//�̸� ���� ����
#define phone_LEN 11 // ��ȭ��ȣ ���� ����


typedef struct student
{
	int id;
	char name[name_LEN];
	int number[phone_LEN];

}Student; // �л��� �й�, �̸�, ��ȭ��ȣ ������ ��� �ִ� ����ü ����

void Initstudent(Student * student)	//Student ����ü �ʱ�ȭ
{
	int i;

	int id[id_LEN];	//int �� �迭�� id�� ����� ���� ����
	int real_id = 0;	//�ٷ� ���� id�� �ϳ��� int�� �ޱ� ���� ����
	int subidx = 1;	// �ڸ��� �����ϱ� ���� ����
	id[0] = 1;	//�й� ù°�ڸ�
	id[1] = (rand() % 7) + 3;	//�й� ��°�ڸ� (3~9)�� ����
	for (i = 2; i < id_LEN; i++)	// �й� ��°�ڸ����ʹ� ���� �� ����
	{
		id[i] = rand() % 10;
	}
	for (i = 0; i < id_LEN; i++)	// �й� ���ڸ����� ��¥ id�� ����
	{
		real_id += subidx * id[id_LEN - 1 - i];
		subidx *= 10;	//�ڸ� �� ����
	}
	student->id = real_id;	// �й��� ��¥ id�� ����


	for (i = 0; i < name_LEN - 1; i++)	//�̸��� ����. �ҹ��� �������� ����
	{
		student->name[i] = (rand() % 26) + 97;
	}
	student->name[name_LEN - 1] = '\0';

	student->number[0] = 0;	//��ȭ��ȣ 0 1 0 ����
	student->number[1] = 1;
	student->number[2] = 0;
	for (i = 3; i < phone_LEN; i++)	// ��ȭ��ȣ �������� ����
	{
		student->number[i] = rand() % 10;
	}

}

void Printstudent(Student * student)	// Student ���� ���
{
	int i, j;
	for (i = 0; i < DATA_LEN; i += 500)	// 500�� �ǳ� �ٸ� ���
	{
		printf("id=%d ", (student + i)->id);
		printf("  name=%s  ", (student + i)->name);
		printf("number= ");
		for (j = 0; j < phone_LEN; j++)
		{
			printf("%d", (student + i)->number[j]);
		}
		printf("\n");
	}
}


void Swap_Student(Student * student1, Student * student2)	// Student�� �������� ���� ����
{
	Student temp;

	memcpy(&temp, student1, sizeof(Student));
	memcpy(student1, student2, sizeof(Student));
	memcpy(student2, &temp, sizeof(Student));

}

void Quick_Sort_id1(Student * student, int left, int right)	// �� �й� ���� (���)
{
	int L = left;	// ù �ε���
	int R = right;	// ������ �ε���
	int mid = (left + right) / 2;	// �߰� �ε���
	int pivot = (student + mid)->id;	// �Ǻ� ��ġ(�߾�)�� ���� ����


	// �Ʒ��� while���� ���Ͽ� pivot �������� ��, �� ũ�� ���� �� ����
	while (L <= R)
	{
		//pivot�� �߰� ���̰�, �� ��� student[L]->id, student[R]->id�� pivot�� ���ϴ� �߰� ������ �Ѿ�� ����� �� �� ����.
		while (pivot > (student + L)->id) //left���� �����ϸ� pivot �̻��� ���� ã��.
			L++;
		while (pivot < (student + R)->id) //right���� �����ϸ� pivot ���� ���� ã��.
			R--;
		//L, R ��� �ִ� pivot ��ġ���� �̵�.

		if (L <= R) //���� L�� R���ϸ�. (���� : L>R �κ��� �̹� ������ �� ������).
		{
			if (L != R)	//���� ���� ��츸. //L�� R�� ���ٸ� ��ȯ(SWAP)�� �ʿ� ���� �� ĭ�� ���ุ ���ָ� ��.
			{
				Swap_Student(&student[L], &student[R]);
			}
			L++; R--; //�׸��� L,R �� ĭ �� ����.
		}
	}


	//���� Ȯ���Ͽ� ����Լ� ���� / �Ǻ� �������� �� �츦 �ٽ� �����ϸ� ��
	if (left < R)
		Quick_Sort_id1(student, left, R);
	if (L < right)
		Quick_Sort_id1(student, L, right);
}


#define STACK_LEN 10*DATA_LEN

int Stack[STACK_LEN];
int topindex;

void Init_Stack(void)
{
	topindex = -1;
}
void Push(int data)
{
	if (topindex + 1 >= STACK_LEN)
		return;
	else
		Stack[++topindex] = data;
}

int Pop(void)
{
	if (topindex == -1)
		return 0;
	else
		return Stack[topindex--];
}

void Quick_Sort_id2(Student * student)
{
	int left = 0;
	int right = DATA_LEN - 1;
	
	int L;
	int R;

	int pivot;

	Init_Stack();

	Push(right);
	Push(left);

	while (topindex > -1)
	{
		left = Pop();
		right = Pop();

		if (right - left > 0)
		{
			pivot = (student + left)->id;
			L = left;
			R = right + 1;


			while (1)
			{
				do
				{
					L++;
				} while ((student + L)->id < pivot);
				do
				{
					R--;
				} while ((student + R)->id > pivot);


				if (L >= R)
					break;

				Swap_Student(&student[L], &student[R]);
			}

			Swap_Student(&student[left], &student[R]);

			Push(R - 1);
			Push(left);
			Push(right);
			Push(R + 1);

		}
	}
}

void Quick_Sort(Student * student)	// �� �й� ���� (�����)
{
	clock_t start, end;

	start = clock();
	Quick_Sort_id1(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\nQuick Sort ���!\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);

	for (int i = 0; i < DATA_LEN; i++)
	{
		Initstudent(&student[i]);
	}

	start = clock();
	Quick_Sort_id2(student);
	end = clock();
	printf("\nQuick Sort �����!\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);

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

	Quick_Sort(student);


	free(student);

	system("pause");
	return 0;
}
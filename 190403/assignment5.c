#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 50000 // ������ 5���� ���� �ޱ� ���� ������ ���̸� ����
#define id_LEN 10 // �й��� int���� �ƴ�, ���ڿ�ó�� ����� ���� ���̰� 9�� 1�� ���� 10���� ����
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
	for (i = 0; i < DATA_LEN; i += 500)
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

void Select_Sort_id(Student * student)
{
	int i, j;
	int least;

	for (i = 0; i < DATA_LEN - 1; i++)
	{
		least = i;
		for (j = i + 1; j < DATA_LEN; j++)
		{
			if (strcmp((student+least)->id,(student+j)->id) > 0)
			{
				least = j;
			}
		}

		if (i != least)
		{
			Swap_Student(&student[i], &student[least]);
		}

	}

}

void Select_Sort_name(Student * student)
{
	int i, j;
	int least;


	for (i = 0; i < DATA_LEN - 1; i++)
	{
		least = i;
		for (j = i + 1; j < DATA_LEN; j++)
		{
			if (strcmp((student + least)->name, (student + j)->name) > 0)
			{
				least = j;
			}
		}

		if (i != least)
		{
			Swap_Student(&student[i], &student[least]);
		}

	}

}

void Select_Sort(Student * student)
{
	clock_t start, end;
	
	start = clock();
	Select_Sort_id(student);
	end = clock();
	printf("\nSelect Sort !\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);


	start = clock();
	Select_Sort_name(student);
	end = clock();
	printf("\n�̸� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�̸� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);
}



void Bubble_Sort_id(Student * student)
{
	int i, j;

	for (i = 0; i < DATA_LEN - 1; i++)
	{
		for (j = 0; j < DATA_LEN - 1 - i; j++)
		{
			if (strcmp((student + j)->id, (student + (j + 1))->id) > 0)
			{
				Swap_Student(&student[j], &student[j + 1]);
			}
		}
	}

}

void Bubble_Sort_name(Student * student)
{
	int i, j;

	for (i = 0; i < DATA_LEN - 1; i++)
	{
		for (j = 0; j < DATA_LEN - 1 - i; j++)
		{
			if (strcmp((student + j)->name, (student + (j + 1))->name) > 0)
			{
				Swap_Student(&student[j], &student[j + 1]);
			}
		}
	}

}

void Bubble_Sort(Student * student)
{
	clock_t start, end;

	start = clock();
	Bubble_Sort_id(student);
	end = clock();
	printf("\nBubble Sort !\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);


	start = clock();
	Bubble_Sort_name(student);
	end = clock();
	printf("\n�̸� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�̸� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);
}



void Quick_Sort_id(Student * student, int left, int right)
{
	int L = left;
	int R = right;
	int mid = (left + right) / 2;
	char pivot[id_LEN];
	memcpy(&pivot, (student + mid)->id, sizeof(char)* id_LEN); //�Ǻ� ��ġ(�߾�)�� ���� ����.


	//�Ʒ��� while���� ���Ͽ� pivot �������� ��, �� ũ�� ���� �� ����. = Partition
	while (L <= R) 
	{
			//pivot�� �߰� ���̰�, �� ��� arr[L], arr[R]�� pivot�� ���ϴ� �߰� ������ �Ѿ�� ����� �� �� ����.
		while (strcmp(pivot, (student + L)->id) > 0) //left���� �����ϸ� pivot �̻��� ���� ã��.
			L++;
		while (strcmp(pivot, (student + R)->id) < 0) //right���� �����ϸ� pivot ���� ���� ã��.
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
	

	//���� Ȯ���Ͽ� ����Լ���.
	if (left < R)
		Quick_Sort_id(student, left, R);
	if (L < right)
		Quick_Sort_id(student, L, right);
}

void Quick_Sort_name(Student * student, int left, int right)
{
	int L = left;
	int R = right;
	int mid = (left + right) / 2;
	char pivot[name_LEN];
	memcpy(&pivot, (student + mid)->name, sizeof(char)* name_LEN); //�Ǻ� ��ġ(�߾�)�� ���� ����.

	//�Ʒ��� while���� ���Ͽ� pivot �������� ��, �� ũ�� ���� �� ����. = Partition
	while (L <= R) 
	{
		//pivot�� �߰� ���̰�, �� ��� arr[L], arr[R]�� pivot�� ���ϴ� �߰� ������ �Ѿ�� ����� �� �� ����.
		while (strcmp(pivot, (student + L)->name) > 0) //left���� �����ϸ� pivot �̻��� ���� ã��.
			L++;
		while (strcmp(pivot, (student + R)->name) < 0) //right���� �����ϸ� pivot ���� ���� ã��.
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


	//���� Ȯ���Ͽ� ����Լ���.
	if (left < R)
		Quick_Sort_name(student, left, R);
	if (L < right)
		Quick_Sort_name(student, L, right);
}


void Quick_Sort(Student * student)
{
	clock_t start, end;
	
	start = clock();
	Quick_Sort_id(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\nQuick Sort !\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);
		
	start = clock();
	Quick_Sort_name(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\n�̸� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�̸� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);

}


void Heap_Sort_id(Student *student)
{
	int i;
	int curpos;
	int parentpos;
	
	for (i = 0; i < DATA_LEN; i++)
	{
		curpos = i;
		parentpos = (curpos - 1) / 2;
		while (curpos > 0 && strcmp((student + parentpos)->id, (student + curpos)->id) < 0) //�θ��� �켱������ ������ �켱�������� ������ �ٲ�
		{
			Swap_Student(&student[parentpos], &student[curpos]);
			curpos = parentpos;
			parentpos = (curpos - 1) / 2;
		}
	}

	int pos = DATA_LEN;
	
	while (pos > 0)
	{
		Student temp;

		memcpy(&temp, &student[0], sizeof(Student));
		
		pos--;
		memcpy(&student[0], &student[pos], sizeof(Student));
		
		parentpos = 0;
	
	
		while (1)
		{
			int leftpos = (parentpos * 2) + 1;
			int rightpos = leftpos + 1;

			if (leftpos >= pos)
				break;


			if ((rightpos >= pos || strcmp((student + leftpos)->id, (student + rightpos)->id) >= 0) && strcmp((student + leftpos)->id, (student + parentpos)->id) > 0)
			{
				Swap_Student(&student[parentpos], &student[leftpos]);
				parentpos = leftpos;
			}
			else if (strcmp((student + rightpos)->id, (student + leftpos)->id) > 0 && strcmp((student + rightpos)->id, (student + parentpos)->id) > 0)
			{
				Swap_Student(&student[parentpos], &student[rightpos]);
				parentpos = rightpos;
			}
			else
				break;
		}

		memcpy(&student[pos],&temp ,sizeof(Student));

	}
}

void Heap_Sort_name(Student *student)
{
	int i;
	int curpos;
	int parentpos;

	for (i = 0; i < DATA_LEN; i++)
	{
		curpos = i;
		parentpos = (curpos - 1) / 2;
		while (curpos > 0 && strcmp((student + parentpos)->name, (student + curpos)->name) < 0) //�θ��� �켱������ ������ �켱�������� ������ �ٲ�
		{
			Swap_Student(&student[parentpos], &student[curpos]);
			curpos = parentpos;
			parentpos = (curpos - 1) / 2;
		}
	}

	int pos = DATA_LEN;
	

	while (pos > 0)
	{
		Student temp;

		memcpy(&temp, &student[0], sizeof(Student));

		pos--;
		memcpy(&student[0], &student[pos], sizeof(Student));

		parentpos = 0;

		while (1)
		{
			int leftpos = parentpos * 2 + 1;
			int rightpos = leftpos + 1;

			if (leftpos >= pos)
				break;


			if (rightpos >= pos || strcmp((student + leftpos)->name, (student + rightpos)->name) >= 0 && strcmp((student + leftpos)->name, (student + parentpos)->name) > 0)
			{
				Swap_Student(&student[parentpos], &student[leftpos]);
				parentpos = leftpos;
			}
			else if (strcmp((student + rightpos)->name, (student + leftpos)->name) > 0 && strcmp((student + rightpos)->name, (student + parentpos)->name) > 0)
			{
				Swap_Student(&student[parentpos], &student[rightpos]);
				parentpos = rightpos;
			}
			else
				break;
		}

		memcpy(&student[pos], &temp, sizeof(Student));
	}
}

void Heap_Sort(Student * student)
{
	clock_t start, end;

	start = clock();
	Heap_Sort_id(student);
	end = clock();
	printf("\nHeap Sort !\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);
	
	
	start = clock();
	Heap_Sort_name(student);
	end = clock();
	printf("\n�̸� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�̸� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);

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
	
	
	Select_Sort(student);
//	Bubble_Sort(student);
	Quick_Sort(student);
	Heap_Sort(student);



	system("pause");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 5000 // ������ 5õ���� �ޱ� ���� ������ ���̸� ����
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
	id[0] = 2;
	id[1] = 0;
	id[2] = 1;	//�й� ù°�ڸ�
	id[3] = (rand() % 7) + 3;	//�й� ��°�ڸ� (3~9)�� ����
	for (i = 4; i < id_LEN; i++)	// �й� ��°�ڸ����ʹ� ���� �� ����
	{
		id[i] = rand() % 10;
	}
	for (i = 0; i < id_LEN ; i++)	// �й� ���ڸ����� ��¥ id�� ����
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
	for (int i = 0; i < DATA_LEN; i += 100)	// 100�� �ǳ� �ٸ� ���
	{
		printf("id=%d ", (student + i)->id);
		printf("  name=%s  ", (student + i)->name);
		printf("number=");
		
		for (int j = 0; j < phone_LEN; j++)
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

void Select_Sort_id(Student * student)	// ���� �й� ����
{
	int i, j;
	int least;

	for (i = 0; i < DATA_LEN - 1; i++)
	{
		least = i;
		for (j = i + 1; j < DATA_LEN; j++)
		{
			if ((student + least)->id > (student + j)->id)	// least�� �й��� j�� �й����� �� ũ��
			{
				least = j;	// j�� least�� ��
			}
		}

		if (i != least)	// least�� �ٲ���� ���
		{
			Swap_Student(&student[i], &student[least]);	// �ּ��й��� i�� ��ȯ
		}

	}

}

void Select_Sort_name(Student * student)	// ���� �̸� ����
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

void Select_Sort(Student * student)	// ���� ���� �Լ�
{
	clock_t start, end;	// �ҿ� �ð� ����

	start = clock();	// �ҿ� �ð� ����
	Select_Sort_id(student);	// ���� �й� ����
	end = clock();	// �ҿ� �ð� ����
	printf("\nSelect Sort !\n\n�й� ������ ����\n---------------------------------\n");
	Printstudent(student);	// ���ĵ� �� ����Ʈ
	printf("\n>>>�й� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);


	start = clock();
	Select_Sort_name(student);	// ���� �̸� ����
	end = clock();
	printf("\n�̸� ������ ����\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>�̸� �������� �ҿ�ð�: %.3lf��\n---------------------------------\n", (end - start) / (double)1000);
}


void Quick_Sort_id(Student * student, int left, int right)	// �� �й� ����
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
		Quick_Sort_id(student, left, R);
	if (L < right)
		Quick_Sort_id(student, L, right);
}

void Quick_Sort_name(Student * student, int left, int right)	// �� �̸� ����
{
	int L = left;
	int R = right;
	int mid = (left + right) / 2;
	char pivot[name_LEN];
	memcpy(&pivot, (student + mid)->name, sizeof(char)* name_LEN);

	
	while (L <= R)
	{

		while (strcmp(pivot, (student + L)->name) > 0)
			L++;
		while (strcmp(pivot, (student + R)->name) < 0)
			R--;

		if (L <= R)
		{
			if (L != R)
			{
				Swap_Student(&student[L], &student[R]);
			}
			L++; R--;
		}
	}


	if (left < R)
		Quick_Sort_name(student, left, R);
	if (L < right)
		Quick_Sort_name(student, L, right);
}


void Quick_Sort(Student * student) // �� ���� �Լ� (���� ���� �Լ��� ������ ����)
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


void Heap_Sort_id(Student *student)	// �� �й� ���� (�ִ��� �̿�)
{
	int i;
	int curpos;	// ���� �켱������ ����Ű�� ����
	int parentpos;	// �θ��� �켱������ ����Ű�� ����

	for (i = 0; i < DATA_LEN; i++)	// �� �ݺ����� ����, ������ �θ� ������ �ڽĺ��� ���� ���� ������ ��
	{
		curpos = i;
		parentpos = (curpos - 1) / 2;	// �θ��� �켱������ ���
		while (curpos > 0 && (student + parentpos)->id < (student + curpos)->id) // �θ��� �켱������ ������ �켱�������� ������ �ٲ�
		{ 
			Swap_Student(&student[parentpos], &student[curpos]);
			curpos = parentpos;	// ������ �켱������ �θ��� �켱������ �ٲ�
			parentpos = (curpos - 1) / 2;	// �θ��� �켱������ ���
		}
	}

	int pos = DATA_LEN;	// �� ������ ���� ����Ŵ. while���� ���� pos--�� �ϱ� ������, DATA_LEN-1 �� �ƴ� DATA_LEN���� �ʱ�ȭ

	while (pos > 0)	// �� �ݺ����� ����, ������������ ������
	{
		Student temp;

		memcpy(&temp, &student[0], sizeof(Student));	// temp�� ��Ʈ ����� ���� ����

		pos--;	// ���� �ϳ��� ���� (�� �ݺ����� ���� �ٷ� ���� pos�� ��ġ�� ������)
		memcpy(&student[0], &student[pos], sizeof(Student));	// ��Ʈ ��忡 ���� ����Ű�� ����� ��, ��, Ʈ������ ���� ���� ���� ����������

		parentpos = 0;	// �� ������ ����


		while (1)	// ���� ��Ʈ ��忡 ���� ���� ���� ��������Ƿ�, �� �ݺ����� ���� �� ��ġ�� ã����
		{
			int leftpos = (parentpos * 2) + 1;	// �θ��� ���� �ڽ� ��带 ����Ŵ
			int rightpos = leftpos + 1;	// �θ��� ������ �ڽ� ��带 ����Ŵ

			if (leftpos >= pos)	// �θ��� ���� �ڽ� ��尡 �� ���� �����ϸ�
				break;	// �ݺ��� Ż��

			// ���� �ڽ� ����� �й��� ������ �ڽ��� ��庸�� ũ�� and ���� �ڽ� ����� �й��� �θ� �ڽ��� ��庸�� ũ�� 
			if ((rightpos >= pos || (student + leftpos)->id >= (student + rightpos)->id) && (student + leftpos)->id > (student + parentpos)->id)
			{
				Swap_Student(&student[parentpos], &student[leftpos]);	// �θ�� ���� �ڽ��� ����
				parentpos = leftpos;	// �θ�� ���� �ڽ� ���� �ٲ�
			}// ������ �ڽ� ����� �й��� ���� �ڽ� ����� �й����� ũ�� and ������ �ڽ� ����� �й��� �θ� ����� �й����� ũ��
			else if ((student + rightpos)->id > (student + leftpos)->id && (student + rightpos)->id > (student + parentpos)->id)
			{
				Swap_Student(&student[parentpos], &student[rightpos]);	// �θ�� ������ �ڽ��� ����
				parentpos = rightpos;	// �θ�� ������ �ڽ� ���� �ٲ�
			}
			else // �� ��ġ�� ã������
				break;
		}

		memcpy(&student[pos], &temp, sizeof(Student));	// temp�� ����� ���� ū ��带 �� �� ��忡 ������ ����

	}
}

void Heap_Sort_name(Student *student) // �� �̸� ����
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

void Heap_Sort(Student * student)	// �� ���� �Լ� (���� ���� �Լ��� ������ ����)
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

	Student * student;

	student = (Student*)malloc(sizeof(Student)*DATA_LEN);


	for (int i = 0; i < DATA_LEN; i++)
	{
		Initstudent(&student[i]);

		if (i != 0)	// �� ó���� ��ġ�°� �����Ƿ� i�� 0�� �� ����
		{
			for (int k = 0; k < i; k++)	// ����ó��. 0���� ~ ��� ���� �ε��� ������ �ݺ� / ��ȭ��ȣ
			{
				int cnt = 0;	// ��ȭ��ȣ�� ���ڸ��� �ٸ��� ǥ���ϱ� ���� ����
			
				for (int z = 0; z < phone_LEN; z++)	
				{
					if ((student + k)->number[z] != (student + i)->number[z])
					{
						cnt++;
						break;
					}
				}
				
				if (cnt == 0)
				{
					i--;
				}
			}

			for (int k = 0; k < i; k++)	// ����ó��. 0���� ~ ��� ���� �ε��� ������ �ݺ� / �й�
			{
				if ((student + k)->id == (student + i)->id)	// id�� ������,
				{
					i--;	// ���� �ε��� �ٽ� �ʱ�ȭ
					break;	// for�� Ż��
				}
			}
		}
	
		
	}

	Select_Sort(student);
	Quick_Sort(student);
	Heap_Sort(student);

	int k;
	scanf("%d", &k);

	return 0;
}
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 50000 // 데이터 5만명 분을 받기 위해 데이터 길이를 정함
#define id_LEN 9 // 학번 길이 설정
#define name_LEN 11	//이름 길이 설정
#define phone_LEN 11 // 전화번호 길이 설정


typedef struct student
{
	int id;
	char name[name_LEN];
	int number[phone_LEN];

}Student; // 학생의 학번, 이름, 전화번호 변수를 담고 있는 구조체 정의

void Initstudent(Student * student)	//Student 구조체 초기화
{
	int i;

	int id[id_LEN];	//int 형 배열로 id를 만들기 위해 선언
	int real_id = 0;	//바로 위의 id를 하나의 int로 받기 위해 선언
	int subidx = 1;	// 자리수 조절하기 위한 변수
	id[0] = 1;	//학번 첫째자리
	id[1] = (rand() % 7) + 3;	//학번 둘째자리 (3~9)만 나옴
	for (i = 2; i < id_LEN; i++)	// 학번 셋째자리부터는 랜덤 값 넣음
	{
		id[i] = rand() % 10;
	}
	for (i = 0; i < id_LEN; i++)	// 학번 끝자리부터 진짜 id에 넣음
	{
		real_id += subidx * id[id_LEN - 1 - i];
		subidx *= 10;	//자리 수 조절
	}
	student->id = real_id;	// 학번에 진짜 id를 넣음


	for (i = 0; i < name_LEN - 1; i++)	//이름을 생성. 소문자 랜덤으로 생성
	{
		student->name[i] = (rand() % 26) + 97;
	}
	student->name[name_LEN - 1] = '\0';

	student->number[0] = 0;	//전화번호 0 1 0 설정
	student->number[1] = 1;
	student->number[2] = 0;
	for (i = 3; i < phone_LEN; i++)	// 전화번호 랜덤으로 설정
	{
		student->number[i] = rand() % 10;
	}

}

void Printstudent(Student * student)	// Student 정보 출력
{
	int i, j;
	for (i = 0; i < DATA_LEN; i += 500)	// 500명씩 건너 뛰며 출력
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


void Swap_Student(Student * student1, Student * student2)	// Student의 정보들을 서로 변경
{
	Student temp;

	memcpy(&temp, student1, sizeof(Student));
	memcpy(student1, student2, sizeof(Student));
	memcpy(student2, &temp, sizeof(Student));

}

void Quick_Sort_id1(Student * student, int left, int right)	// 퀵 학번 정렬 (재귀)
{
	int L = left;	// 첫 인덱스
	int R = right;	// 마지막 인덱스
	int mid = (left + right) / 2;	// 중간 인덱스
	int pivot = (student + mid)->id;	// 피봇 위치(중앙)의 값을 받음


	// 아래의 while문을 통하여 pivot 기준으로 좌, 우 크고 작은 값 나열
	while (L <= R)
	{
		//pivot이 중간 값이고, 비교 대상 student[L]->id, student[R]->id는 pivot과 비교하니 중간 지점을 넘어가면 종료로 볼 수 있음.
		while (pivot > (student + L)->id) //left부터 증가하며 pivot 이상의 값을 찾음.
			L++;
		while (pivot < (student + R)->id) //right부터 감소하며 pivot 이하 값을 찾음.
			R--;
		//L, R 모두 최대 pivot 위치까지 이동.

		if (L <= R) //현재 L이 R이하면. (이유 : L>R 부분은 이미 정리가 된 상태임).
		{
			if (L != R)	//같지 않은 경우만. //L과 R이 같다면 교환(SWAP)은 필요 없고 한 칸씩 진행만 해주면 됨.
			{
				Swap_Student(&student[L], &student[R]);
			}
			L++; R--; //그리고 L,R 한 칸 더 진행.
		}
	}


	//조건 확인하여 재귀함수 실행 / 피봇 기준으로 좌 우를 다시 정렬하면 됨
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

void Quick_Sort(Student * student)	// 퀵 학번 정렬 (비재귀)
{
	clock_t start, end;

	start = clock();
	Quick_Sort_id1(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\nQuick Sort 재귀!\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);

	for (int i = 0; i < DATA_LEN; i++)
	{
		Initstudent(&student[i]);
	}

	start = clock();
	Quick_Sort_id2(student);
	end = clock();
	printf("\nQuick Sort 비재귀!\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
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

	Quick_Sort(student);


	free(student);

	system("pause");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 5000 // 데이터 5천명을 받기 위해 데이터 길이를 정함
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
	id[0] = 2;
	id[1] = 0;
	id[2] = 1;	//학번 첫째자리
	id[3] = (rand() % 7) + 3;	//학번 둘째자리 (3~9)만 나옴
	for (i = 4; i < id_LEN; i++)	// 학번 셋째자리부터는 랜덤 값 넣음
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
	for (i = 0; i < DATA_LEN; i += 100)	// 100명씩 건너 뛰며 출력
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

	// 퀵 비재귀
#define STACK_LEN 10 * DATA_LEN	// 퀵 비재귀 구현을 위해, 스택을 활용. 스택의 크기 선언

int Stack[STACK_LEN];	// 스택 선언
int topindex;	// 스택의 맨 위 인덱스를 가리키는 변수 선언

void Init_Stack(void)	// 스택 초기화
{
	topindex = -1;
}
void Push(int data)	// 스택에 데이터를 넣는 푸시 함수
{
	if (topindex + 1 >= STACK_LEN)
		return;
	else
		Stack[++topindex] = data;
}

int Pop(void)	// 스택에서 데이터를 빼내는 팝 함수
{
	if (topindex == -1)
		return 0;
	else
		return Stack[topindex--];
}

void Quick_Sort_id2(Student * student)	// 퀵 비재귀 함수
{
	int left = 0;	// 왼쪽 끝을 알리는 변수
	int right = DATA_LEN - 1;	// 오른쪽 끝을 알리는 변수
	
	int L;
	int R;

	int pivot;	// pivot값을 지정. 여기서는, 제일 왼쪽이 pivot이 됨

	Init_Stack();	// 스택 초기화

	Push(right);	// 오른쪽 끝 푸시
	Push(left);	// 왼쪽 끝 푸시

	while (topindex > -1)	// 스택이 빌 때까지. 즉, 정렬이 끝날 때까지 반복
	{
		left = Pop();	// 왼쪽 끝 지정
		right = Pop();	// 오른쪽 끝 지정

		if (right - left > 0)	// 왼쪽과 오른쪽이 엇갈리지 않았거나, 같지 않으면
		{
			pivot = (student + left)->id;	// 왼쪽 끝을 pivot으로 지정
			L = left;	// 왼쪽 끝부터. left+1이 아닌 이유는, 밑에 while문에서 1을 증가시키고 확인하기 때문
			R = right + 1;	// 오른쪽 끝부터. right + 1인 이유는, 밑에 while문에서 1을 감소시키고 확인하기 때문


			while (1)	//do while을 쓴 이유는, 마지막에 L과 R을 엇갈리게 하기 위함
			{
				do
				{
					L++;	//L값 먼저 증가
				} while ((student + L)->id < pivot);	// L의 학번이 pivot의 학번보다 클 때까지 찾음
				do
				{
					R--;	//R값 먼저 감소
				} while ((student + R)->id > pivot);	// R의 학번이 pivot의 학번보다 작을 때까지 찾음


				if (L >= R)	// L과 R이 엇갈리거나 같으면 멈춤
					break;

				Swap_Student(&student[L], &student[R]);	// L과 R을 스왑
			}

			Swap_Student(&student[left], &student[R]);	// 피봇과 R을 스왑
			// 현재 R자리에, pivot이 들어갔고, pivot 기준으로 pivot 왼쪽은 pivot보다 전부 작은 값, 오른쪽은 pivot보다 전부 큰 값이 있음. 따라서, pivot을 제외한 좌 우를 또 정렬해줌
			Push(R - 1);	// 만약, 인덱스가 1  2  3  4  pivot자리  5   6  7  8이면, 4의 index를 Push. 즉, pivot 바로 왼쪽의 index를 Push
			Push(left);	// 1의 index를 Push. 즉, 왼쪽 끝 index를 Push
			Push(right);	// 8의 index를 푸시. 즉, 오른쪽 끝 index를 Push
			Push(R + 1);	// 5의 index를 Push. 즉, pivot 바로 오른쪽의 index를 Push
			//	이렇게 Push하는 이유: 첫번째 Pop이 left가 되고, 두번째 Pop이 right가 되기 때문임
		}
	}
}

void Quick_Sort(Student * student, Student * copy_student)
{
	clock_t start, end;
	double Quick1;
	start = clock();
	Quick_Sort_id1(student, 0, DATA_LEN - 1);	// 퀵 재귀 정렬
	end = clock();
	Quick1 = (end - start) / (double)1000;
	printf("\nQuick Sort 재귀!\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>학번 퀵정렬 소요시간: %.3lf초\n---------------------------------\n", Quick1);



	double Quick2;
	start = clock();
	Quick_Sort_id2(copy_student);	// 퀵 비재귀 정렬
	end = clock();
	Quick2 = (end - start) / (double)1000;
	printf("\nQuick Sort 비재귀!\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(copy_student);
	printf("\n>>>학번 퀵정렬 소요시간: %.3lf초\n---------------------------------\n", Quick2);

	printf("결론!!!\n퀵 재귀 소요시간: %.3lf초\n퀵 비재귀 소요시간: %.3lf초\n", Quick1, Quick2);
}


int main(void)
{
	srand((unsigned)time(NULL));

	Student * student;

	student = (Student*)malloc(sizeof(Student)*DATA_LEN);

	Student * copy_student;	// 퀵 재귀, 비재귀 둘 다 학번을 기준으로 정렬하기 때문에 학생 정보를 복사하기 위해 선언

	copy_student = (Student*)malloc(sizeof(Student)*DATA_LEN);


	for (int i = 0; i < DATA_LEN; i++)
	{
		Initstudent(&student[i]);

		if (i != 0)	// 맨 처음은 겹치는게 없으므로 i가 0일 때 제외
		{
			for (int k = 0; k < i; k++)	// 예외처리. 0부터 ~ 방금 만든 인덱스 전까지 반복 / 전화번호
			{
				int cnt = 0;	// 전화번호가 한자리라도 다르면 표시하기 위한 변수

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

			for (int k = 0; k < i; k++)	// 예외처리. 0부터 ~ 방금 만든 인덱스 전까지 반복 / 학번
			{
				if ((student + k)->id == (student + i)->id)	// id가 같으면,
				{
					i--;	// 현재 인덱스 다시 초기화
					break;	// for문 탈출
				}
			}
		}


	}


	memcpy(copy_student, student, sizeof(Student)*DATA_LEN);	// 초기화된 학생정보를 copy_student에 복사


	Quick_Sort(student, copy_student);


	free(student);
	free(copy_student);

	return 0;
}
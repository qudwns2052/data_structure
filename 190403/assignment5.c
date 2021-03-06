#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DATA_LEN 50000 // 데이터 5만명 분을 받기 위해 데이터 길이를 정함
#define id_LEN 10 // 학번을 int형이 아닌, 문자열처럼 만들기 위해 길이가 9에 1을 더한 10으로 설정
#define name_LEN 11	//이름 길이 설정
#define phone_LEN 11 // 전화번호 길이 설정


typedef struct student
{
	char id[id_LEN];
	char name[name_LEN];
	int number[phone_LEN];

}Student; // 학생의 학번, 이름, 전화번호 변수를 담고 있는 구조체 정의

void Initstudent(Student * student)	//Student 구조체 초기화
{
	int i;

	int id[id_LEN - 1];	//int 형 배열로 id를 만들기 위해 선언
	int real_id = 0;	//바로 위의 id를 하나의 int로 받기 위해 선언
	int subidx = 1;	// 자리수 조절하기 위한 변수
	id[0] = 1;	//학번 첫째자리
	id[1] = (rand() % 7) + 3;	//학번 둘째자리 (3~9)만 나옴
	for (i = 2; i < id_LEN - 1; i++)	// 학번 셋째자리부터는 랜덤 값 넣음
	{
		id[i] = rand() % 10;
	}
	for (i = 0; i < id_LEN - 1; i++)	// 학번 끝자리부터 진짜 id에 넣음
	{
		real_id += subidx * id[id_LEN - 2 - i];
		subidx *= 10;	//자리 수 조절
	}
	itoa(real_id, student->id, 10);	//숫자를 문자열로 변환하여 학번에 저장
	student->id[id_LEN - 1] = '\0';


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


void Swap_Student(Student * student1, Student * student2)	// Student의 정보들을 서로 변경
{
	Student temp;

	memcpy(&temp, student1, sizeof(Student));
	memcpy(student1, student2, sizeof(Student));
	memcpy(student2, &temp, sizeof(Student));
	
}

void Select_Sort_id(Student * student)	// 학번 선택 정렬
{
	int i, j;
	int least;

	for (i = 0; i < DATA_LEN - 1; i++)
	{
		least = i;
		for (j = i + 1; j < DATA_LEN; j++)
		{
			if (strcmp((student+least)->id,(student+j)->id) > 0)	// least의 학번보다 j의 학번이 더 크면
			{
				least = j;	// j가 least가 됨. 여기서는 학번을 문자열로 바꿔 저장했기 때문에 strcmp를 사용함
			}
		}

		if (i != least)	// least가 바뀌었을 경우
		{
			Swap_Student(&student[i], &student[least]);	// 최소학번과 i를 교환
		}

	}

}

void Select_Sort_name(Student * student)	// 선택 이름 정렬. 위와 동일.
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

void Select_Sort(Student * student)	// 선택 정렬 함수
{
	clock_t start, end;	// 소요 시간 측정
	
	start = clock();	// 소요 시간 시작
	Select_Sort_id(student);	// 선택 학번 정렬
	end = clock();	// 소요 시간 종료
	printf("\nSelect Sort !\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);	// 정렬된 것 프린트
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);


	start = clock();
	Select_Sort_name(student);
	end = clock();
	printf("\n이름 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>이름 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);
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
	printf("\nBubble Sort !\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);


	start = clock();
	Bubble_Sort_name(student);
	end = clock();
	printf("\n이름 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>이름 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);
}



void Quick_Sort_id(Student * student, int left, int right)	// 퀵 학번 정렬
{
	int L = left;	// 첫 인덱스
	int R = right;	// 마지막 인덱스
	int mid = (left + right) / 2;	// 중간 인덱스
	char pivot[id_LEN];
	memcpy(&pivot, (student + mid)->id, sizeof(char)* id_LEN); // 피봇 위치(중앙)의 값을 받음


	// 아래의 while문을 통하여 pivot 기준으로 좌, 우 크고 작은 값 나열
	while (L <= R) 
	{
			//pivot이 중간 값이고, 비교 대상 student[L]->id, student[R]->id는 pivot과 비교하니 중간 지점을 넘어가면 종료로 볼 수 있음.
		while (strcmp(pivot, (student + L)->id) > 0) //left부터 증가하며 pivot 이상의 값을 찾음.
			L++;
		while (strcmp(pivot, (student + R)->id) < 0) //right부터 감소하며 pivot 이하 값을 찾음.
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
		Quick_Sort_id(student, left, R);
	if (L < right)
		Quick_Sort_id(student, L, right);
}

void Quick_Sort_name(Student * student, int left, int right)	// 퀵 이름 정렬 / 위와 동일
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


void Quick_Sort(Student * student) // 퀵 정렬 함수 (내용은 선택 정렬 함수와 같음)
{
	clock_t start, end;
	
	start = clock();
	Quick_Sort_id(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\nQuick Sort !\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);
		
	start = clock();
	Quick_Sort_name(student, 0, DATA_LEN - 1);
	end = clock();
	printf("\n이름 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>이름 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);

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
		while (curpos > 0 && strcmp((student + parentpos)->id, (student + curpos)->id) < 0) //부모의 우선순위가 현재의 우선순위보다 낮으면 바꿈
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
		while (curpos > 0 && strcmp((student + parentpos)->name, (student + curpos)->name) < 0) //부모의 우선순위가 현재의 우선순위보다 낮으면 바꿈
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

void Heap_Sort(Student * student)	// 힙 정렬 함수 (선택 정렬 함수와 같음)
{
	clock_t start, end;

	start = clock();
	Heap_Sort_id(student);
	end = clock();
	printf("\nHeap Sort !\n\n학번 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>학번 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);
	
	
	start = clock();
	Heap_Sort_name(student);
	end = clock();
	printf("\n이름 순으로 정렬\n---------------------------------\n");
	Printstudent(student);
	printf("\n>>>이름 선택정렬 소요시간: %.3lf초\n---------------------------------\n", (end - start) / (double)1000);

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
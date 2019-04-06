#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 9	//	스택 SIZE

int ftop = -1;	// 첫번째 스택 top 인덱스
int stop = -1;	// 두번째 스택 top 인덱스
int ftrain[MAX_SIZE];	// 첫번째 스택 선언
int strain[MAX_SIZE];

int FPush(int data)	// 첫번째 스택에 데이터 추가 함수
{
	ftrain[++ftop] = data;	// ftop 인덱스 증가 후 데이터 추가
	return data;	// 데이터 리턴
}

int SPush(int data)	// 두번째 스택에 데이터 추가 함수
{
	strain[++stop] = data;	
	return data;	
}

int FPop(void)	// 첫번째 스택에 데이터 제거 함수
{
	int temp = ftop;	// temp로 top 인덱스 저장

	ftop--;	// top 인덱스 감소

	return ftrain[temp];	// 스택의 맨 위 데이터 리턴
}

int SPop(void)	// 두번째 스택에 데이터 제거 함수
{
	int temp = stop;

	stop--;

	return strain[temp];
}

int FPeek(void) // 첫번째 스택에 맨 위 데이터 확인 함수
{
	if (ftop == -1)	// 만약, 스택이 비어있으면
		return -1;	// -1 리턴
	else
		return ftrain[ftop];	// 아니면, 맨 위 데이터 리턴
}

int SPeek(void)	// 두번째 스택에 맨 위 데이터 확인 함수
{
	if (stop == -1)
		return -1;
	else
		return strain[stop];
}

int cnt1 = 0;	// 횟수의 십의 자리 수
int cnt2 = 0;	// 횟수의 일의 자리 수

void Count(void)	// 횟수 조절 함수
{
	cnt2++;
	if (cnt2 > 9)	// 만약, cnt2가 두자리수로 넘어가면 -> cnt를 1 증가시키고, cnt2를 0으로 함
	{
		cnt1++;
		cnt2 = 0;
	}
}
int main(void)
{
	int str[MAX_SIZE];	// 열차 번호들을 int형 배열 선언
	int i;
	
	int value1 = 0;	// 첫번째 스택의 맨 위 데이터 저장
	int value2 = 0;	// 두번째 스택의 맨 위 데이터 저장

	int nextout = 1;	// 나가야 할 열차 번호 저장 변수 선언

	

	printf("열차 번호 입력 : ");
	
	for (i = 0; i < MAX_SIZE; i++)	// 열차 번호를 입력 받음
	{
		scanf("%d", &str[i]);
	}

	i = -1;	// 위에 반복문에서 i 값이 바뀌었기 때문에, -1로 초기화

	while (1)
	{
		if (nextout > MAX_SIZE)	// 모든 열차가 나가면
		{
			printf("종료(총 %d%d회)\n", cnt1, cnt2);	// 종료
			break;
		}

		i++;	// i를 증가시키며, 들어오는 열차 번호를 확인
		

		if (i + 1 > MAX_SIZE )	// 들어오는 열차가 없으면
		{
			while (1)
			{
				if (nextout > MAX_SIZE)	// 나갈 열차가 없으면
				{
					printf("종료(총 %d%d회)\n", cnt1, cnt2);	// 종료
					break;
				}
				else
				{
					if (value1 == nextout)	// 첫번째 스택의 맨 위가 나갈 차례면
					{
						Count();
						printf("%d%d : POP(1)\n", cnt1, cnt2);
						Count();
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());	// 첫번째 스택 맨 위 데이터 제거
						value1 = FPeek();	// 첫번째 스택 맨 위가 바뀌었으므로, value1이 가리키는 값을 변경해줌 
						nextout++;	// 열차가 하나 나갔으니, 다음 열차 인덱스로 변경
					}
					else if (value2 == nextout)	// 두번째 스택의 맨 위가 나갈 차례면
					{
						Count();
						printf("%d%d : POP(2)\n", cnt1, cnt2);
						Count();
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, SPop());
						value2 = SPeek();
						nextout++;
					}
					else  // 두 스택의 맨 위 둘 중 하나라도 못 나가는 상황이면
					{
						if (value1 < value2)	// 두번째 스택 맨 위 데이터가 첫번째 스택 맨 위 데이터보다 클 경우 -> 두번째 스택 맨 위 값을 첫번째 스택 맨위 값으로 옮김
						{						// 이를 통해, 두번째 스택 맨 위 바로 아래의 데이터를 확인 가능
							
							value1 = FPush(SPop());	// 두번째 스택 Pop 후 이를 첫번째 스택에 Push
							value2 = SPeek();	// 두번째 스택 맨 위 데이터가 변했으니 이를 조정해줌


							Count();
							printf("%d%d : POP(2)\n", cnt1, cnt2);

							Count();
							printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
						}
						else  // 바로 위와 정 반대인 상황이면 (첫번째 스택 맨위 데이터가 두번째 스택 맨위 데이터보다 더 클 경우)
						{
							value2 = SPush(FPop());
							value1 = FPeek();

							Count();
							printf("%d%d : POP(2)\n", cnt1, cnt2);

							Count();
							printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
						}
					}

				}

			}
			break;
		}
		else  // 들어오는 열차가 있으면
		{
			Count();
			printf("%d%d : IN(%d)\n", cnt1, cnt2, str[i]);


			if ((str[i]) == nextout)	// 들어오자마자 나갈 때
			{
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, str[i]);
				nextout++;	// 열차가 하나 나갔으니, 다음 열차 인덱스로 변경
			}
			else if (i == 0)	// 첫번째 열차일 경우, 바로 나가지 않는다면, 첫번째 스택에 저장
			{
				value1 = FPush(str[i]);
				Count();
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else if (i == 1)	// 두번째 열차일 경우, 바로 나가지 않는다면, 두번째 스택에 저장
			{
				value2 = SPush(str[i]);
				Count();
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
			}
			else if (value1 >= value2) // 첫번째 스택의 맨 위 값이 두번째 스택의 맨 위 값보다 클 경우 -> 첫번째 스택에 열차를 넣는 것이 유리함 -> Because, 첫번째 스택의 맨 위보다 두번째 스택의 맨 위가 먼저 밖으로 나가야 하기 때문
			{
				value1 = FPush(str[i]);	// 첫번재 스택에 열차를 저장하고, value1 값을 변경
				Count();
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else  // 바로 위와 정 반대일 경우
			{
				value2 = SPush(str[i]);
				Count();
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
			}
			if (value1 == nextout)	// 첫번째 스택이 바로 나갈 수 있는 상황이면
			{
				Count();
				printf("%d%d : POP(1)\n", cnt1, cnt2);
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());	// 첫번째 스택을 Pop
				value1 = FPeek();	// 맨 위 데이터 값으로 업데이트
				nextout++;	// 열차가 나갔으니, 다음 열차 인덱스로 변경
			}
			else if (value2 == nextout)	// 두번째 스택이 바로 나갈 수 있는 상황이면, 안에 코드는 바로 위와 거의 동일
			{
				Count();
				printf("%d%d : POP(2)\n", cnt1, cnt2);
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, SPop());
				value2 = SPeek();
				nextout++;
			}
		}

	}



	system("pause");
	return 0;
}
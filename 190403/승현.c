#include<stdio.h>
#include<stdlib.h>
#define STACK_LEN 9

int ftrain[STACK_LEN];
int strain[STACK_LEN];
int ftindex = -1;
int stindex = -1;
int a = 0; //횟수의 십의 자리
int b = 0; //횟수의 일의 자리 


int FPush(int data)
{
	++ftindex;
	return ftrain[ftindex] = data;
}

int SPush(int data)
{
	++stindex;
	return strain[stindex] = data;
}

int FPop(void)
{
	int temp = ftindex;
	ftindex--;
	return ftrain[temp];
}

int SPop(void)
{
	int temp = stindex;
	stindex--;
	return strain[temp];
}

int FPeek(void)
{
	if (ftindex == -1)
		return -1;
	else
		return ftrain[ftindex];
}

int SPeek(void)
{
	if (stindex == -1)
		return -1;
	else
		return strain[stindex];
}

void Count(void)
{
	b++;
	if (b >= 10)
	{
		a++;
		b = 0;
	}
}


int main(void)
{
	int arr[STACK_LEN];
	int num = 0; // arr의 첫번째 인덱스 값 
	int i = 1; // 열차의 숫자와 비교할 변수
	int value1 = 0; // ftindex의 값 
	int value2 = 0; // stindex의 값
	int train; // 한번에 받는 열차 숫자
	int n = 100000000; // train을 배열에 넣기 위해 필요한 변수
	int j = 0;

	printf("1부터9까지의 열차숫자를 입력하시오: ");
	scanf("%d", &train); //열차 숫자를 하나의 숫자로 입력받음 

	for (j = 0; j < 9; j++)
	{
		arr[num] = train / n;
		num++;
		train = train % n;
		n = n / 10;
	}

	num = 0;

	while (1)
	{
		if (num >= 10)   //finish input
		{
			while (1)
			{

				if (i >= 10) // 모든 열차가 빠져나갔을 때 
				{
					printf("종료(총%d%d회)", a, b);
					return 0;
				}

				if (value1 == i)
				{
					Count();
					printf("%d%d: OUT(%d)\n", a, b, FPop());
					value1 = FPeek();
					i++;
				}
				else if (value2 == i)
				{
					Count();
					printf("%d%d: OUT(%d)\n", a, b, SPop());
					value2 = SPeek();
					i++;
				}
				else //두 스택모두 탑에 있는 값이 나가야하는 수가 아닐때 
				{
					if (ftindex < stindex)
					{
						while (i != value2 && stindex != 0)
						{
							Count();								
							value1 = FPush(SPop());
							printf("%d%d: PUSH(%d, %d)\n", a, b, 1, FPush(SPop()));
							value2 = SPeek();
						}
					}
					else   // 인덱스가 같은 경우는 ftrain를 빼내는 것으로 생각
					{
						while (i != value1 && ftindex != 0)
						{
							Count();
							value2 = SPush(FPop());
							printf("%d%d: PUSH(%d, %d)\n", a, b, 2, SPush(FPop()));
							value1 = FPeek();
						}
					}
					
				}
			}
		}
		Count();
		printf("%d%d: IN(%d)\n", a, b, arr[num]);

		if (arr[num] == i)
		{
			Count();
			printf("%d%d: OUT(%d)\n", a, b, arr[num]);
			i++;
		}
		else
		{
			if (ftindex == -1)
			{
				Count();
				printf("%d%d: PUSH(%d, %d)\n", a, b, 1, FPush(arr[num]));
				value1 = FPeek();
			}
			else
			{
				Count();
				printf("%d%d: PUSH(%d, %d)\n", a, b, 2, SPush(arr[num]));
				value2 = SPeek();
			}

		}

		if (value1 == i)
		{
			Count();
			printf("%d%d: OUT(%d)\n", a, b, FPop());
			value1 = FPeek();
			i++;
		}
		else if (value2 == i)
		{
			Count();
			printf("%d%d: OUT(%d)\n", a, b, SPop());
			value2 = SPeek();
			i++;

		}

		num++;
	}


	return 0;
}
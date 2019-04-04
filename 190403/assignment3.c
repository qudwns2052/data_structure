#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 9

int ftop = -1;
int stop = -1;
int ftrain[MAX_SIZE];
int strain[MAX_SIZE];

//	예외처리 안했음

int FPush(int data)
{
	ftrain[++ftop] = data;
	return data;
}

int SPush(int data)
{
	strain[++stop] = data;
	return data;
}

int FPop(void)
{
	int temp = ftop;

	ftop--;

	return ftrain[temp];
}

int SPop(void)
{
	int temp = stop;

	stop--;

	return strain[temp];
}

int FPeek(void)
{
	if (ftop == -1)
		return -1;
	else
		return ftrain[ftop];
}

int SPeek(void)
{
	if (stop == -1)
		return -1;
	else
		return strain[stop];
}

int main(void)
{
	int str[MAX_SIZE];
	int i;
	
	int value1 = 0;
	int value2 = 0;

	int nextout = 1;

	int cnt1 = 0;
	int cnt2 = 0;

	printf("열차 번호 입력 : ");
	
	for (i = 0; i < MAX_SIZE; i++)
	{
		scanf("%d", &str[i]);
	}

	i = -1;

	while (1)
	{
		if (nextout > MAX_SIZE)
		{
			printf("종료(총 %d%d회)\n", cnt1, cnt2);
			break;
		}

		i++;
		

		if (i + 1 > MAX_SIZE )
		{
			while (1)
			{
				if (nextout > MAX_SIZE)
				{
					printf("종료(총 %d%d회)\n", cnt1, cnt2);
					break;
				}
				else
				{
					if (value1 == nextout)
					{
						cnt2++;
						if (cnt2 > 9)
						{
							cnt1++;
							cnt2 = 0;
						}
						printf("%d%d : POP(1)\n", cnt1, cnt2);
						cnt2++;
						if (cnt2 > 9)
						{
							cnt1++;
							cnt2 = 0;
						}
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());
						value1 = FPeek();
						nextout++;
					}
					else if (value2 == nextout)
					{
						cnt2++;
						if (cnt2 > 9)
						{
							cnt1++;
							cnt2 = 0;
						}
						printf("%d%d : POP(2)\n", cnt1, cnt2);
						cnt2++;
						if (cnt2 > 9)
						{
							cnt1++;
							cnt2 = 0;
						}
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, SPop());
						value2 = SPeek();
						nextout++;
					}
					else
					{
						if (value1 < value2)
						{
							
							value1 = FPush(SPop());
							value2 = SPeek();


							cnt2++;
							if (cnt2 > 9)
							{
								cnt1++;
								cnt2 = 0;
							}
							printf("%d%d : POP(2)\n", cnt1, cnt2);

							cnt2++;
							if (cnt2 > 9)
							{
								cnt1++;
								cnt2 = 0;
							}
							printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
						}
						else
						{
							value2 = SPush(FPop());
							value1 = FPeek();

							cnt2++;
							if (cnt2 > 9)
							{
								cnt1++;
								cnt2 = 0;
							}
							printf("%d%d : POP(2)\n", cnt1, cnt2);

							cnt2++;
							if (cnt2 > 9)
							{
								cnt1++;
								cnt2 = 0;
							}
							printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
						}
					}

				}

			}
			break;
		}
		else
		{
			cnt2++;
			if (cnt2 > 9)
			{
				cnt1++;
				cnt2 = 0;
			}
			printf("%d%d : IN(%d)\n", cnt1, cnt2, str[i]);


			if ((str[i]) == nextout)	//들어오자마자 나갈 때
			{
				cnt2++;
				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, str[i]);
				nextout++;
			}
			else if (i == 0)
			{
				value1 = FPush(str[i]);
				cnt2++;

				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else if (i == 1)
			{
				value2 = SPush(str[i]);
				cnt2++;

				if (cnt2 >= 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
			}
			else if (value1 >= value2)
			{
				value1 = FPush(str[i]);
				cnt2++;

				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else
			{
				value2 = SPush(str[i]);
				cnt2++;

				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
			}
			if (value1 == nextout)
			{
				cnt2++;
				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : POP(1)\n", cnt1, cnt2);
				cnt2++;
				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());
				value1 = FPeek();
				nextout++;
			}
			else if (value2 == nextout)
			{
				cnt2++;
				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : POP(2)\n", cnt1, cnt2);
				cnt2++;
				if (cnt2 > 9)
				{
					cnt1++;
					cnt2 = 0;
				}
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, SPop());
				value2 = SPeek();
				nextout++;
			}
		}

	}



	system("pause");
	return 0;
}
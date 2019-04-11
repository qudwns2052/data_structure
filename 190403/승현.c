#include<stdio.h>
#include<stdlib.h>
#define STACK_LEN 9

int ftrain[STACK_LEN];
int strain[STACK_LEN];
int ftindex = -1;
int stindex = -1;
int a = 0; //Ƚ���� ���� �ڸ�
int b = 0; //Ƚ���� ���� �ڸ� 


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
	int num = 0; // arr�� ù��° �ε��� �� 
	int i = 1; // ������ ���ڿ� ���� ����
	int value1 = 0; // ftindex�� �� 
	int value2 = 0; // stindex�� ��
	int train; // �ѹ��� �޴� ���� ����
	int n = 100000000; // train�� �迭�� �ֱ� ���� �ʿ��� ����
	int j = 0;

	printf("1����9������ �������ڸ� �Է��Ͻÿ�: ");
	scanf("%d", &train); //���� ���ڸ� �ϳ��� ���ڷ� �Է¹��� 

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

				if (i >= 10) // ��� ������ ���������� �� 
				{
					printf("����(��%d%dȸ)", a, b);
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
				else //�� ���ø�� ž�� �ִ� ���� �������ϴ� ���� �ƴҶ� 
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
					else   // �ε����� ���� ���� ftrain�� ������ ������ ����
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
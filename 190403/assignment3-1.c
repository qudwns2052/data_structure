#include <stdio.h>

#define MAX_SIZE 9	//	���� SIZE

int ftop = -1;	// ù��° ���� top �ε���
int stop = -1;	// �ι�° ���� top �ε���
int ftrain[MAX_SIZE];	// ù��° ���� ����
int strain[MAX_SIZE];	// �ι�° ���� ����

int FPush(int data)	// ù��° ���ÿ� ������ �߰� �Լ�
{
	ftrain[++ftop] = data;	// ftop �ε��� ���� �� ������ �߰�
	return data;	// ������ ����
}

int SPush(int data)	// �ι�° ���ÿ� ������ �߰� �Լ�
{
	strain[++stop] = data;
	return data;
}

int FPop(void)	// ù��° ���ÿ� ������ ���� �Լ�
{
	int temp = ftop;	// temp�� top �ε��� ����

	ftop--;	// top �ε��� ����

	return ftrain[temp];	// ������ �� �� ������ ����
}

int SPop(void)	// �ι�° ���ÿ� ������ ���� �Լ�
{
	int temp = stop;

	stop--;

	return strain[temp];
}

int FPeek(void) // ù��° ���ÿ� �� �� ������ Ȯ�� �Լ�
{
	if (ftop == -1)	// ����, ������ ���������
		return -1;	// -1 ����
	else
		return ftrain[ftop];	// �ƴϸ�, �� �� ������ ����
}

int SPeek(void)	// �ι�° ���ÿ� �� �� ������ Ȯ�� �Լ�
{
	if (stop == -1)
		return -1;
	else
		return strain[stop];
}

int cnt1 = 0;	// Ƚ���� ���� �ڸ� ��
int cnt2 = 0;	// Ƚ���� ���� �ڸ� ��

void Count(void)	// Ƚ�� ���� �Լ�
{
	cnt2++;
	if (cnt2 > 9)	// ����, cnt2�� ���ڸ����� �Ѿ�� -> cnt�� 1 ������Ű��, cnt2�� 0���� ��
	{
		cnt1++;
		cnt2 = 0;
	}
}
int main(void)
{
	int train;	// ���� ��ȣ���� �ѹ��� ���� int ���� ����
	int arr[MAX_SIZE]; // ���� ��ȣ���� ������ int�� �迭 ����
	int arr_cnt = 1;	// arr �迭�� ��ȣ���� �ֱ� ���� ���� ����
	int i;

	int value1 = 0;	// ù��° ������ �� �� ������ ����
	int value2 = 0;	// �ι�° ������ �� �� ������ ����

	int nextout = 1;	// ������ �� ���� ��ȣ ���� ���� ����



	printf("���� ��ȣ �Է� : "); // ���� ��ȣ�� �Է� ����

	scanf("%d", &train);

	for (i = 0; i < MAX_SIZE - 1; i++)	// ��ȣ�� 9�ڸ� �̹Ƿ� arr_cnt �ڸ����� ������ 
	{
		arr_cnt *= 10;

	}	// arr_cnt�� �ڸ����� train�� �� �� �ڸ����� ������

	for (i = 0; i < MAX_SIZE; i++)	// ���� ��ȣ�� arr �迭�� �ű�
	{
		arr[i] = train / arr_cnt;	// ���� ���� ���� �տ� �ִ� ���� ���� arr�� ����
		train -= arr[i] * arr_cnt;	// train���� �� ���ڸ��� ����
		arr_cnt /= 10;	// arr_cnt�� �ڸ����� �ϳ� ������
	}

	i = -1;	// ���� �ݺ������� i ���� �ٲ���� ������, -1�� �ʱ�ȭ

	while (1)
	{
		if (nextout > MAX_SIZE)	// ��� ������ ������
		{
			printf("����(�� %d%dȸ)\n", cnt1, cnt2);	// ����
			break;
		}

		i++;	// i�� ������Ű��, ������ ���� ��ȣ�� Ȯ��


		if (i + 1 > MAX_SIZE)	// ������ ������ ������
		{
			while (1)
			{
				if (nextout > MAX_SIZE)	// ���� ������ ������
				{
					printf("����(�� %d%dȸ)\n", cnt1, cnt2);	// ����
					break;
				}
				else
				{
					if (value1 == nextout)	// ù��° ������ �� ���� ���� ���ʸ�
					{
						Count();
						printf("%d%d : POP(1)\n", cnt1, cnt2);
						Count();
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());	// ù��° ���� �� �� ������ ����
						value1 = FPeek();	// ù��° ���� �� ���� �ٲ�����Ƿ�, value1�� ����Ű�� ���� �������� 
						nextout++;	// ������ �ϳ� ��������, ���� ���� �ε����� ����
					}
					else if (value2 == nextout)	// �ι�° ������ �� ���� ���� ���ʸ�
					{
						Count();
						printf("%d%d : POP(2)\n", cnt1, cnt2);
						Count();
						printf("%d%d : OUT(%d)\n", cnt1, cnt2, SPop());
						value2 = SPeek();
						nextout++;
					}
					else  // �� ������ �� �� �� �� �ϳ��� �� ������ ��Ȳ�̸�
					{
						if (ftop < stop)	// ���� ������ �� ������, ���� ������ 1���� ���� �� ���� ������.
						{
							while (value2 != nextout && stop != 0)
							{
								value1 = FPush(SPop());	// �ι�° ���� Pop �� �̸� ù��° ���ÿ� Push
								value2 = SPeek();	// �ι�° ���� top �� ����

								Count();
								printf("%d%d : POP(2)\n", cnt1, cnt2);

								Count();
								printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
							}
						}
						else    // ������ ������ �� ���ų�, �� ������ ������, ������ ������ 1���� ���� �� ���� ������.
						{
							while (value1 != nextout && ftop != 0)
							{
								value2 = SPush(FPop());
								value1 = FPeek();

								Count();
								printf("%d%d : POP(1)\n", cnt1, cnt2);

								Count();
								printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
							}
						}

						
					}

				}

			}
			break;
		}
		else  // ������ ������ ������
		{
			Count();
			printf("%d%d : IN(%d)\n", cnt1, cnt2, arr[i]);


			if ((arr[i]) == nextout)	// �����ڸ��� ���� ��
			{
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, arr[i]);
				nextout++;	// ������ �ϳ� ��������, ���� ���� �ε����� ����
			}
			else	// ù��° ������ ���, �ٷ� ������ �ʴ´ٸ�, ù��° ���ÿ� ����
			{
				if (FPeek() == -1)	// ������ ������ ����ִ� ���¸�, ù��° ���ÿ� ����
				{
					value1 = FPush(arr[i]);
					Count();
					printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
				}
				else  // �ٷ� ���� �ݴ��, �ι�° ���ÿ� ����
				{
					value2 = SPush(arr[i]);
					Count();
					printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
				}
			}
			if (value1 == nextout)	// ù��° ������ �ٷ� ���� �� �ִ� ��Ȳ�̸�
			{
				Count();
				printf("%d%d : POP(1)\n", cnt1, cnt2);
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, FPop());	// ù��° ������ Pop
				value1 = FPeek();	// �� �� ������ ������ ������Ʈ
				nextout++;	// ������ ��������, ���� ���� �ε����� ����
			}
			else if (value2 == nextout)	// �ι�° ������ �ٷ� ���� �� �ִ� ��Ȳ�̸�, �ȿ� �ڵ�� �ٷ� ���� ���� ����
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

	return 0;
}
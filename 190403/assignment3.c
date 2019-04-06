#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 9	//	���� SIZE

int ftop = -1;	// ù��° ���� top �ε���
int stop = -1;	// �ι�° ���� top �ε���
int ftrain[MAX_SIZE];	// ù��° ���� ����
int strain[MAX_SIZE];

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
	int str[MAX_SIZE];	// ���� ��ȣ���� int�� �迭 ����
	int i;
	
	int value1 = 0;	// ù��° ������ �� �� ������ ����
	int value2 = 0;	// �ι�° ������ �� �� ������ ����

	int nextout = 1;	// ������ �� ���� ��ȣ ���� ���� ����

	

	printf("���� ��ȣ �Է� : ");
	
	for (i = 0; i < MAX_SIZE; i++)	// ���� ��ȣ�� �Է� ����
	{
		scanf("%d", &str[i]);
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
		

		if (i + 1 > MAX_SIZE )	// ������ ������ ������
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
						if (value1 < value2)	// �ι�° ���� �� �� �����Ͱ� ù��° ���� �� �� �����ͺ��� Ŭ ��� -> �ι�° ���� �� �� ���� ù��° ���� ���� ������ �ű�
						{						// �̸� ����, �ι�° ���� �� �� �ٷ� �Ʒ��� �����͸� Ȯ�� ����
							
							value1 = FPush(SPop());	// �ι�° ���� Pop �� �̸� ù��° ���ÿ� Push
							value2 = SPeek();	// �ι�° ���� �� �� �����Ͱ� �������� �̸� ��������


							Count();
							printf("%d%d : POP(2)\n", cnt1, cnt2);

							Count();
							printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
						}
						else  // �ٷ� ���� �� �ݴ��� ��Ȳ�̸� (ù��° ���� ���� �����Ͱ� �ι�° ���� ���� �����ͺ��� �� Ŭ ���)
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
		else  // ������ ������ ������
		{
			Count();
			printf("%d%d : IN(%d)\n", cnt1, cnt2, str[i]);


			if ((str[i]) == nextout)	// �����ڸ��� ���� ��
			{
				Count();
				printf("%d%d : OUT(%d)\n", cnt1, cnt2, str[i]);
				nextout++;	// ������ �ϳ� ��������, ���� ���� �ε����� ����
			}
			else if (i == 0)	// ù��° ������ ���, �ٷ� ������ �ʴ´ٸ�, ù��° ���ÿ� ����
			{
				value1 = FPush(str[i]);
				Count();
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else if (i == 1)	// �ι�° ������ ���, �ٷ� ������ �ʴ´ٸ�, �ι�° ���ÿ� ����
			{
				value2 = SPush(str[i]);
				Count();
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
			}
			else if (value1 >= value2) // ù��° ������ �� �� ���� �ι�° ������ �� �� ������ Ŭ ��� -> ù��° ���ÿ� ������ �ִ� ���� ������ -> Because, ù��° ������ �� ������ �ι�° ������ �� ���� ���� ������ ������ �ϱ� ����
			{
				value1 = FPush(str[i]);	// ù���� ���ÿ� ������ �����ϰ�, value1 ���� ����
				Count();
				printf("%d%d : PUSH(1, %d)\n", cnt1, cnt2, value1);
			}
			else  // �ٷ� ���� �� �ݴ��� ���
			{
				value2 = SPush(str[i]);
				Count();
				printf("%d%d : PUSH(2, %d)\n", cnt1, cnt2, value2);
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



	system("pause");
	return 0;
}
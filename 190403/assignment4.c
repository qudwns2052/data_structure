#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE 21 // ť�� �ִ� ũ�� (20�� �ƴ� 21�� ���� ������ ����ť�� ���� �ÿ�, ����ִ� ���� �� �� ��츦 �Ѵ� Ȯ���ϱ� ����)

int findex = 0;	// ť�� ù��° �ε���	(In index)
int sindex = 0;	// ť�� �ι�° �ε���	(Out index)
					// ť�� FIFO�̹Ƿ�, �� �� ������ ����Ű�� �ε����� �ʿ��ϴٰ� ����
int cnt = 0;	// ť�� �����ϴ� ��� ����
char Queue[MAX_SIZE];	// ť ����

void ADDQUEUE(char ch)	// ť�� �����͸� �߰��ϴ� �Լ�
{
	if ((findex + 1 % MAX_SIZE) == sindex)	// ť�� �� á����
	{
		printf("ADDQUEUE(%c) Fail : Queue Full  Queue Size=%d/20\n", ch, cnt);	// ť�� ������ �߰� ���� �޼��� ���
		return;
	}

	findex++;

	findex = findex % MAX_SIZE;

	Queue[findex] = ch;	// first �ε��� ���� �� ť�� ������ �߰�

	cnt++;

	printf("ADDQUEUE(%c)	Queue Size=%d/20\n", ch, cnt);	// ť�� ������ �߰� ���� �޼���

}

void DELETEQUEUE(void)	// ť�� �����͸� ���� �Լ�
{
	if (findex == sindex)	// ť�� ���������
	{
		printf("DELETEQUEUE() Fail : Queue Empty  Queue Size=%d/20\n", cnt);	// ť�� ������ ���� ���� �޼���
		return;
	}

	sindex++;  // second �ε��� ����
	
	sindex = sindex % MAX_SIZE;

	cnt--;

	printf("DELETEQUEUE() = %c, Queue Size=%d/20\n", Queue[sindex], cnt);	// ť�� ������ ���� ���� �޼���


}

int main(void)
{
	char str[20];	// Ű����κ��� �Է� ���� ������ ������ �迭
	int i;
	int num;	// ���� �Է� �� num���� ��ȯ �� num ����ŭ DELETEQUEUE ����
	int strLen;	// str ���ڿ��� ���̸� ����� ����

	while (1)
	{
		printf(">>> ");
		scanf("%s", str);	// scanf�� ���ڿ� �Է� ����
		strLen = strlen(str);	// str ���ڿ� ���� ����
		if (strLen > 20)	// ����, 20���ڰ� ������
		{
			printf("�Է� ���ڿ� ũ�� : %d >>> ERROR (MAX_SIZE is 20)\n", strLen);	// �����޼��� ���
			continue;	// ���������� �ٽ� ����
		}
		else if ('A' <= str[0] && str[0] <= 'Z')	// ����, ���ڿ� �� ���� ���� �빮�ڸ� �ڿ��� �빮�ڶ� ���� (�������� �빮�ڷ� �Է��ϹǷ�)
		{	
			for (i = 0; i < strLen; i++)
			{
				ADDQUEUE(str[i]);	// ť�� �ϳ��� �߰�
			}
		}
		else if ('0' <= str[0] && str[0] <= '9')	// ����, ���ڿ� �� ���� ���ڸ� ���ڿ��� ���ڷ� ����
		{
			num = atoi(str);	// ���ڿ��� �����̹Ƿ�, ���ڷ� ��ȯ
			for (i = 0; i < num; i++)	// num ��ŭ
			{
				DELETEQUEUE();	// ť���� �ϳ��� ����
			}
		}
		else   // �ƴϸ�, �߸� �Է� �� ������ ����
		{
			printf("�Է� ���ڿ��� ���� �빮�ڷ� �̷�����ֽ��ϴ�.\n");	// ���� �޼��� ���
			continue;	// ���������� �ٽ� ����
		}
		
	}

	system("pause");
	return 0;
}
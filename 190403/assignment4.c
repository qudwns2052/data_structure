#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 20	// ť�� �ִ� ũ��

int findex = -1;	// ť�� ù��° �ε���	(In index)
int sindex = 0;		// ť�� �ι�° �ε���	(Out index)
					// ť�� FIFO�̹Ƿ�, �� �� ������ ����Ű�� �ε����� �ʿ��ϴٰ� ����
char Queue[MAX_SIZE];	// ť ����

void ADDQUEUE(char ch)	// ť�� �����͸� �߰��ϴ� �Լ�
{
	if (findex - sindex >= MAX_SIZE -1)	// ť�� �� á����
	{
		printf("ADDQUEUE(%c) Fail : Queue Full  Queue Size=20/20\n", ch);	// ť�� ������ �߰� ���� �޼��� ���
		return;
	}
	Queue[++findex] = ch;	// first �ε��� ���� �� ť�� ������ �߰�
	printf("ADDQUEUE(%c)	Queue Size=%d/20\n", ch, findex - sindex + 1);	// ť�� ������ �߰� ���� �޼���

}

void DELETEQUEUE(void)	// ť�� �����͸� ���� �Լ�
{
	if (findex + 1 <= sindex)	// ť�� ���������
	{
		printf("DELETEQUEUE() Fail : Queue Empty  Queue Size=0/20\n");	// ť�� ������ ���� ���� �޼���
		return;
	}

	printf("DELETEQUEUE() = %c, Queue Size=%d/20\n", Queue[sindex], findex - sindex);	// ť�� ������ ���� ���� �޼���
	sindex++;	// second �ε��� ����

}

int main(void)
{
	char str[MAX_SIZE];	// Ű����κ��� �Է� ���� ������ ������ �迭
	int i;
	int num;	// ���� �Է� �� num���� ��ȯ �� num ����ŭ DELETEQUEUE ����
	int strLen;	// str ���ڿ��� ���̸� ����� ����

	while (1)
	{
		printf(">>> ");
		scanf("%s", str);	// scanf�� ���ڿ� �Է� ����
		strLen = strlen(str);	// str ���ڿ� ���� ����
		if (strLen > MAX_SIZE)	// ����, 20���ڰ� ������
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
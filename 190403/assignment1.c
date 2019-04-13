#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE_STACK 100	// ������ �ִ� ũ��
#define MAX_SIZE_STR 100	// ���ڿ��� �ִ� ũ��

typedef int element;
typedef struct 
{
	element stack[MAX_SIZE_STACK];	// ����
	int top;	// top �ε���
}StackType;	// ���� ����ü ���� 

void init(StackType *s) 
{
	s->top = -1;	// ���� �ʱ�ȭ: top �ε����� -1�� ����
}

int is_empty(StackType *s) 
{
	return s->top == -1;	// ��������� 1 , �ƴϸ� 0 ����
}

int is_full(StackType *s) 
{
	return s->top == MAX_SIZE_STACK - 1;	// �� �������� 1, �ƴϸ� 0 ����
}

void push(StackType *s, element data) // ���ÿ� ������ �߰� �Լ�
{
	if (is_full(s))	// �� ��������, OUT
		exit(1);
	s->stack[++(s->top)] = data;	// �ƴϸ�, top �ε��� ���� �� data�� ���ÿ� ����
}

element pop(StackType *s) // ���ÿ� ������ ���� �Լ�
{
	if (is_empty(s))	// �� ��������, OUT
		exit(1);
	return s->stack[(s->top)--];	// �ƴϸ�, ������ �� �� �� return �� top �ε��� ����
}

element peek(StackType *s)	// ���ÿ� �� �� ������ Ȯ�� �Լ�
{
	if (is_empty(s))	// �� ��������, OUT
		exit(1);
	return s->stack[s->top];	// �ƴϸ�, ������ �� �� �� return
}


int prec(char op)	// �켱���� ��ȯ �Լ�
{
	switch (op) 
	{
	case '+': case '-': return 3;
	case '*': case '/': return 4;
	case '!': return 5;	// !�� �켱������ ()���� ������ *���� ����. ������, �ؿ� ����� ���ϰ� �ϱ� ���� !�� 5�� ��ȯ
	case '(': return 1;	// �켱������ !���� ������, ���⼭ return�ϴ� �켱������ ����
	case ')': return 2; // ���� ����
	}
	return -2;	// �����ڰ� �ƴϸ� -2 ����
}

char * infix_to_postfix(char exp[]) // �������� -> ������������ ��ȯ �Լ�
{
	int i;
	char ch, top_op;	// ���ڿ��� ���� �ϳ��� �ޱ� ���� ch ���� , ������ �� �� �����ڸ� pop �� �����ϱ� ���� top_op ����
	char *temp = malloc(sizeof(char)*MAX_SIZE_STR);	// ���ڿ��� �����ϴ� �� , �����Ҵ����� STR�� �ִ� ũ�� ��ŭ ����
	int idx = 0;	// temp �迭�� �ε����� ����Ű�� ��



	int len = strlen(exp);	// ���ڿ��� ���� ����


	StackType s;	// ���� ����
	init(&s);	// ���� �ʱ�ȭ


	for (i = 0; i < len; i++) 
	{
		ch = exp[i];	// ���ڿ��� �տ������� 1���� ����

		if (i < len - 2)	// ������ ���� ���, 5 * * 2  ��, 5 * �ڿ� 2ĭ�� ������ ������Ƿ�, �ڿ��� 2��° ���ʹ� Ȯ�� ���ϱ� ���� ���� ���� (exp �迭 ������ �ȳѾ� ������)
		{
			if (ch == '*' && exp[i + 1] == '*')	// ch�� ch+1�� *�� ���
			{
				ch = '!';	// ** = !�� ����
				i++;	// i+1�� �̹� *�̹Ƿ�, for�� �ѹ� �ǳ� ��
			}
		}


		
		switch (ch) 
		{
		
		case '+': case '-': case '*': case '/': case'!':	// �������� ���, �ڽź��� �켱������ ������ ���ÿ� ������, temp�� ����

			while (!is_empty(&s) && prec(peek(&s)) >= prec(ch))		// ������ ������� �ʰ�, AND ,���ÿ� ����Ǿ� �ִ� �� ���� �켱������ ���� �������� �켱�������� ���ų� �̻��̸�
			{
				temp[idx++] = ' ';	// �������� ����, �ǿ����� �ڸ��� �ذ�
				temp[idx++] = pop(&s);	// pop�� �ؼ� temp�� ����
			}
			push(&s, ch);	// ���ÿ� ������ push
			temp[idx++] = ' ';	// �������� ����, �ǿ����� �ڸ��� �ذ�	
			break;
			
		case '(':	// ���� ��ȣ�� ���, �׳� ����
			push(&s, ch);
			break;
		case ')':	// �ݴ� ��ȣ�� ���
			top_op = pop(&s);	// ���Ͽ� top_op�� ����
			while (top_op != '(')	// ���� ��ȣ�� ���� �� ����
			{
				temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
				temp[idx++] = top_op;	// temp�� �� �� �� ����
				top_op = pop(&s);	// ���Ͽ� top_op ����
			}
			break;

		default:	// �ǿ������� ���
			temp[idx++] = ch;	// temp�� �ٷ� ����
			break;
		}
	}

	while (!is_empty(&s))	// ������ �� ������
	{
		temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
		temp[idx++] = pop(&s);	// ���ÿ� ������ ���� temp�� ����
	}

	temp[idx] = '\0';	// ���ڿ� ���� �˸��� �ι��� ����
	return temp;	// temp ���ڿ� ����
}

void Calculate(char str[])	// ������������ ��ȯ������ ���� ���
{
	int i;
	int idx;	// temp �迭 �ε���
	int op1, op2;	// �ǿ����� 2�� pop �ޱ� ���� op1, op2 ����
	int integer;	// 
	int result;	// ���� ��� ����
	int m_temp = 1;	// ! �϶� ���� ��� ����
	int len = strlen(str);	// ���ڿ� ���� ���

	StackType s;	// ���� ����
	init(&s);	// ���� �ʱ�ȭ

	for (i = 0; i< len; i++)	// ���ڿ� ���� ���� �ݺ�
	{
		idx = 0;

		char temp[4] = { 0, };	//�ִ� 4�ڸ��� �ǿ����� OR ������ (�ݺ� ���� �Ź� �ʱ�ȭ)
		while (1) // �� while���� ����, temp �迭�� ����� ���� ������ ���� �����
		{
			if ((str[i] == ' ') || (str[i] == '\0'))	// ������ �����ų� str�� ������ while�� ����
				break;

			temp[idx] = str[i];		// temp�� ���� ����
			i++;	// i ���� (for�� i�� ���� ����: for���� i�� str ���ڿ� ���� ��ŭ �ݺ�������, ���⼭ str ���ڿ� ���̸� �б� ������ ���� ����)
			idx++;	// idx ����
		}	

		// = if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+' || temp[0] == '-' || temp[0] == '!')	//�����ڸ�, temp�� �ѹ� �޾����״� �˻�
		if (prec(temp[0]) > 2)	// �� ��� ������, ��ȣ�� prec�� 1, 2�� ���� ���� // �����ڸ�, temp[0]�� ���ڸ� �޾ұ� ������, temp[0]�� �˻�
		{
			op2 = pop(&s);	// �ǿ����� pop (������� ���� �ÿ�, �� �ڰ� �߿��ϹǷ�, op2���� �޾���)
			op1 = pop(&s);	// �ǿ����� pop

			switch (temp[0])	// ���� ����� �̷����
			{
			case '*':
				result = op1 * op2;
				break;
			case '/':
				result = op1 / op2;
				break;
			case '+':
				result = op1 + op2;
				break;
			case '-':
				result = op1 - op2;
				break;
			case '!':	// ������ ��
				for (int j = 0; j < op2; j++)	// op2 ��ŭ �ݺ�
				{
					m_temp *= op1;	// m_temp=1�� �����߱� ������, op1��  op2��ŭ ����ؼ� ������
				}
				result = m_temp; 
				break;
			}

			push(&s, result);	// ���� ����� �ٽ� ���ÿ� push
		}
		else  // �����ڰ� �ƴϸ�
		{
			integer = atoi(temp);	// atoi(a): a���ڿ��� ���ڷ� ��ȯ�ϴ� �Լ� <stdlib.h> �ȿ� ����
			push(&s, integer);	//���� �ֱ�
		}
		
	}

	printf("=%d\n", pop(&s));	// ���� ������� ���� �������� ���� ���̰�, ���� �ݺ��� ���� ���ÿ��� 1���� �����Ͱ� ����. �װ��� ���

}

int CatchError(char str[])	// ���� ��� �Լ�
{
	int i;
	int len = strlen(str);	// ���ڿ� ���� ����
	int index = 0;	// ��ȣ�� ¦�� �´��� ����ϱ� ���� ���� ����

	for (i = 0; i < len; i++)	// ��ȣ�� ¦�� �´��� + �����ڰ� ���޾� ������ �ʴ��� Ȯ��
	{
		if(i < len - 1)	// �ڿ��� 2��°������ Ȯ�������ν� str �迭 ������ ����� �ʰ� ��
			if (prec(str[i]) > 2 && prec(str[i + 1]) > 2)	// str[i]�� str[i+1]�� �� �� �ǿ������� ���
			{
				if (str[i] == '*' && str[i + 1] == '*')	// ������ ǥ���ϴ� ** �� ������ �ƴϹǷ�
					continue;	// �ݺ��� ���� �ö�
				else
					return i;	// ������ i��°�� i+1��° ���̿� �߻�
			}
		else if (prec(str[i]) == 1)	// ���� ��ȣ ���� Ȯ��
			index++;
		else if (prec(str[i]) == 2)	// �ݴ� ��ȣ ���� Ȯ��
			index--;
	}

	if (index > 0)	// ¦�� �� �´� ���: �ݴ� ��ȣ�� ������ ��
		return 1;
	else if (index < 0)	// ¦�� �� �´� ���: ���� ��ȣ�� ������ ��
		return 2;


	return -1;	// ���� ����

}
int main(void)
{
	char * i_str = { "2+(3*4)**2-12" };		// �������� ���ڿ�
//	char * i_str = { "2+(3*4**2-12" };
//	char * i_str = { "(11+3)*2**3-12" };	
//	char * i_str = { "2+(3+*4**2-12" };

	char * p_str;	// �������� ���ڿ�

	int Error;

	printf("�������� ǥ��: %s\n", i_str);

	int strLen = strlen(i_str);	// �������� ���ڿ� ���� ����

	Error = CatchError(i_str);	// �������� ���ڿ� ���� �˻�

	if (Error != -1)	// ���� �߻� ��
	{
		switch (Error)
		{
		case 1:	// �ݴ� ��ȣ�� ������ ��
			printf("%s(!) �� ��ġ�� ������ �ֽ��ϴ�. )�� �����մϴ�.\n", i_str);
			break;
		case 2:	// ���� ��ȣ�� ������ ��
			printf("(!)%s �� ��ġ�� ������ �ֽ��ϴ�. (�� �����մϴ�.\n", i_str);
			break;
		default:
			for (int i = 0; i < strLen; i++)	// str[Error]�� str[Error+1] ���̿��� ���� �߻�
			{
				if (i == Error)
				{
					printf("%c(!)", i_str[i]);
				}
				else
					printf("%c", i_str[i]);
			}
			printf(" �� ��ġ�� ������ �ֽ��ϴ�. ���ڰ� �;� �մϴ�.\n");
		}
		
		system("pause");
		return 0;
	}

	p_str = infix_to_postfix(i_str);	// ���� ���� -> ���� �������� ��ȯ , �����Ҵ� �� ���ڿ��� �Լ��� ��ȯ�ϰ� �̸� p_str�� ����
	

	printf("�������� ǥ��: %s\n", p_str);

	Calculate(p_str);	// ���� ���� ���

	free(p_str);	// �����Ҵ� ���� �޸� ��ȯ

	system("pause");
	return 0;
}
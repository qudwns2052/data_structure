#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE_STACK 100

#define MAX_SIZE_STR 100


// ���� ǥ����� ���� ǥ������� ��ȯ�Ѵ�
// �ǿ����ڴ� ������ ����Ѵ�
// �������� ��쿡�� �켱������ ���� �����Ѵ�

typedef int element;
typedef struct 
{
	element stack[MAX_SIZE_STACK];
	int top;
}StackType;

void init(StackType *s) 
{
	s->top = -1;
}

int is_empty(StackType *s) 
{
	return s->top == -1;
}

int is_full(StackType *s) 
{
	return s->top == MAX_SIZE_STACK - 1;
}

void push(StackType *s, element data) 
{
	if (is_full(s))
		exit(1);
	s->stack[++(s->top)] = data;
}

element pop(StackType *s) 
{
	if (is_empty(s))
		exit(1);
	return s->stack[(s->top)--];
}

element peek(StackType *s) 
{
	if (is_empty(s))
		exit(1);
	return s->stack[s->top];
}

// �켱���� ��ȯ �޼���
int prec(char op) 
{
	switch (op) 
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '!': return 3;	//!�� �켱������ ()���� ������ *���� ������.
	}
	return -1;
}

char * infix_to_postfix(char exp[]) 
{
	int i;
	char ch, top_op;
	char *temp = malloc(sizeof(char)*MAX_SIZE_STR);	// ���ڿ��� �����ϴ� ��
	int idx = 0;	//temp �迭�� �ε����� ����Ű�� ��



	int len = strlen(exp);


	StackType s;
	init(&s);


	for (i = 0; i < len; i++) 
	{
		ch = exp[i];

		if (i < len - 3)	//exp �迭 ������ �ȳѾ� ������
		{
			if (ch == '*' && exp[i + 1] == '*')
			{
				ch = '!';	//** = !�� ����
				i++;	//i+1�� �̹� *�̹Ƿ� for�� �ѹ� �ǳ� ��
			}
		}


		
		switch (ch) 
		{
			// �������� ���
		case '+': case '-': case '*': case '/': case'!':
			// �ڽź��� �켱 ������ ���� ����
			// Stack�� ��� ��� � ���帰��
			while (!is_empty(&s) && prec(peek(&s)) >= prec(ch))		//(������ ������� x AND �� �� ch�� >= ���� ch��)
			{
				temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
				temp[idx++] = pop(&s);	//	pop�� �ؼ� temp�� ����
			}
			push(&s, ch);
			temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
			break;


			// ��ȣ�� ���
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') 
			{
				temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
				temp[idx++] = top_op;	////temp�� �� �Ѱ� ����
				top_op = pop(&s);
			}
			break;


			// �ǿ������� ���
		default:
			temp[idx++] = ch;	//temp�� �ٷ� ����
			break;
		}
	}

	while (!is_empty(&s)) 
	{
		temp[idx++] = ' ';	// �������� n�ڸ��� �ذ�
		temp[idx++] = pop(&s);	//���ÿ� ������ �� temp�� �����ڱ�
	}

	temp[idx] = '\0';	//���ڿ� ���� �˸��� �ι��� ����
	return temp;
}

void Calculate(char str[])	//�������� ����ϱ�
{
	int i;
	int idx;	// temp �迭 �ε���
	int op1, op2;	//�ǿ����� 2�� pop �������� ����
	int integer;	//���ڸ� ����
	int result;	// ������
	char temp[4];	//�ִ� 4�ڸ��� �ǿ����� �Ǵ� ������

	int len = strlen(str);

	StackType s;
	init(&s);



	for (i = 0; i< len; i++)
	{
		idx = 0;
		while (1)
		{
			if ((str[i] == ' ') || (str[i] == '\0'))	// ���� �����ų� str �����ų� -> ����
				break;

			temp[idx] = str[i];		//temp�� str����
			printf("temp ���� %c\n", temp[idx]);
			i++;
			idx++;
		}	//temp��� �迭�� ����� ���� ������ ���� �����

		if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+' || temp[0] == '-' || temp[0] == '!')	//�����ڸ�, temp�� �ѹ� �޾����״� �˻�
		{
			op2 = pop(&s);
			op1 = pop(&s);
			printf("pop\npop\n");
			switch (temp[0])
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
			case '!':
				for (int j = 0; j < op2 - 1; j++)
				{
					op1 *= op1;
				}
				result = op1;
				break;
			}

			push(&s, result);
			printf("push ������ %d\n",result);
		}
		else
		{
			integer = atoi(temp);	//atoi(a): a���ڿ��� ���ڷ� ��ȯ�ϴ� �Լ� <stdlib.h> �ȿ� ����
			push(&s, integer);	//���� �ֱ�
			printf("push �ǿ����� %d\n", integer);
		}
		
	}

	printf("�����: %d\n", pop(&s));	//���� ������� ���� �������� ���� ��

}
int main(void)
{
	char * i_str = { "2+(3*4)**2-12" };		//infix str
	char * p_str;	// postfix str
	
	printf("�������� ǥ��: %s\n", i_str);

	p_str = infix_to_postfix(i_str);	// ���� -> ������ ��ȯ

	printf("�������� ǥ��: %s\n", p_str);

	Calculate(p_str);

	free(p_str);

	system("pause");
	return 0;
}
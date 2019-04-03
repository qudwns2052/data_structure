#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE_STACK 100

#define MAX_SIZE_STR 100


// 중위 표기법을 후위 표기법으로 변환한다
// 피연산자는 무조건 출력한다
// 연산자의 경우에는 우선순위에 따라 결정한다

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

// 우선순위 반환 메서드
int prec(char op) 
{
	switch (op) 
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '!': return 3;	//!의 우선순위는 ()보다 느리고 *보다 빠르다.
	}
	return -1;
}

char * infix_to_postfix(char exp[]) 
{
	int i;
	char ch, top_op;
	char *temp = malloc(sizeof(char)*MAX_SIZE_STR);	// 문자열을 저장하는 값
	int idx = 0;	//temp 배열의 인덱스를 가리키는 값



	int len = strlen(exp);


	StackType s;
	init(&s);


	for (i = 0; i < len; i++) 
	{
		ch = exp[i];

		if (i < len - 3)	//exp 배열 범위를 안넘어 가도록
		{
			if (ch == '*' && exp[i + 1] == '*')
			{
				ch = '!';	//** = !로 만듬
				i++;	//i+1은 이미 *이므로 for문 한번 건너 뜀
			}
		}


		
		switch (ch) 
		{
			// 연산자일 경우
		case '+': case '-': case '*': case '/': case'!':
			// 자신보다 우선 순위가 높은 것이
			// Stack에 계실 경우 어서 빼드린다
			while (!is_empty(&s) && prec(peek(&s)) >= prec(ch))		//(스택이 비어있지 x AND 맨 위 ch값 >= 현재 ch값)
			{
				temp[idx++] = ' ';	// 공백으로 n자리수 해결
				temp[idx++] = pop(&s);	//	pop을 해서 temp에 저장
			}
			push(&s, ch);
			temp[idx++] = ' ';	// 공백으로 n자리수 해결
			break;


			// 괄호의 경우
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') 
			{
				temp[idx++] = ' ';	// 공백으로 n자리수 해결
				temp[idx++] = top_op;	////temp에 팝 한거 저장
				top_op = pop(&s);
			}
			break;


			// 피연산자일 경우
		default:
			temp[idx++] = ch;	//temp에 바로 저장
			break;
		}
	}

	while (!is_empty(&s)) 
	{
		temp[idx++] = ' ';	// 공백으로 n자리수 해결
		temp[idx++] = pop(&s);	//스택에 남은거 다 temp에 때려박기
	}

	temp[idx] = '\0';	//문자열 끝을 알리는 널문자 삽입
	return temp;
}

void Calculate(char str[])	//후위수식 계산하기
{
	int i;
	int idx;	// temp 배열 인덱스
	int op1, op2;	//피연산자 2개 pop 받으려고 선언
	int integer;	//숫자를 받음
	int result;	// 연산결과
	char temp[4];	//최대 4자리수 피연산자 또는 연산자

	int len = strlen(str);

	StackType s;
	init(&s);



	for (i = 0; i< len; i++)
	{
		idx = 0;
		while (1)
		{
			if ((str[i] == ' ') || (str[i] == '\0'))	// 공백 만나거나 str 끝나거나 -> 종료
				break;

			temp[idx] = str[i];		//temp에 str전달
			printf("temp 대입 %c\n", temp[idx]);
			i++;
			idx++;
		}	//temp라는 배열에 공백과 공백 사이의 값이 저장됨

		if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+' || temp[0] == '-' || temp[0] == '!')	//연산자면, temp를 한번 받았을테니 검사
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
			printf("push 연산결과 %d\n",result);
		}
		else
		{
			integer = atoi(temp);	//atoi(a): a문자열을 숫자로 변환하는 함수 <stdlib.h> 안에 존재
			push(&s, integer);	//숫자 넣기
			printf("push 피연산자 %d\n", integer);
		}
		
	}

	printf("결과값: %d\n", pop(&s));	//최종 결과값은 스택 마지막에 남은 값

}
int main(void)
{
	char * i_str = { "2+(3*4)**2-12" };		//infix str
	char * p_str;	// postfix str
	
	printf("중위수식 표현: %s\n", i_str);

	p_str = infix_to_postfix(i_str);	// 중위 -> 후위로 변환

	printf("후위수식 표현: %s\n", p_str);

	Calculate(p_str);

	free(p_str);

	system("pause");
	return 0;
}
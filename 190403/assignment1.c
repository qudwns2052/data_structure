#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE_STACK 100	// 스택의 최대 크기
#define MAX_SIZE_STR 100	// 문자열의 최대 크기

typedef int element;
typedef struct 
{
	element stack[MAX_SIZE_STACK];	// 스택
	int top;	// top 인덱스
}StackType;	// 스택 구조체 정의 

void init(StackType *s) 
{
	s->top = -1;	// 스택 초기화: top 인덱스를 -1로 설정
}

int is_empty(StackType *s) 
{
	return s->top == -1;	// 비어있으면 1 , 아니면 0 리턴
}

int is_full(StackType *s) 
{
	return s->top == MAX_SIZE_STACK - 1;	// 꽉 차있으면 1, 아니면 0 리턴
}

void push(StackType *s, element data) // 스택에 데이터 추가 함수
{
	if (is_full(s))	// 꽉 차있으면, OUT
		exit(1);
	s->stack[++(s->top)] = data;	// 아니면, top 인덱스 증가 후 data를 스택에 저장
}

element pop(StackType *s) // 스택에 데이터 제거 함수
{
	if (is_empty(s))	// 꽉 차있으면, OUT
		exit(1);
	return s->stack[(s->top)--];	// 아니면, 스택의 맨 위 값 return 후 top 인덱스 감소
}

element peek(StackType *s)	// 스택에 맨 위 데이터 확인 함수
{
	if (is_empty(s))	// 꽉 차있으면, OUT
		exit(1);
	return s->stack[s->top];	// 아니면, 스택의 맨 위 값 return
}


int prec(char op)	// 우선순위 반환 함수
{
	switch (op) 
	{
	case '+': case '-': return 3;
	case '*': case '/': return 4;
	case '!': return 5;	// !의 우선순위는 ()보다 느리고 *보다 빠름. 하지만, 밑에 계산을 편하게 하기 위해 !를 5로 반환
	case '(': return 1;	// 우선순위는 !보다 높지만, 여기서 return하는 우선순위는 낮음
	case ')': return 2; // 위와 같음
	}
	return -2;	// 연산자가 아니면 -2 리턴
}

char * infix_to_postfix(char exp[]) // 중위수식 -> 후위수식으로 변환 함수
{
	int i;
	char ch, top_op;	// 문자열의 문자 하나씩 받기 위해 ch 선언 , 스택의 맨 위 연산자를 pop 시 저장하기 위해 top_op 선언
	char *temp = malloc(sizeof(char)*MAX_SIZE_STR);	// 문자열을 저장하는 값 , 동적할당으로 STR의 최대 크기 만큼 선언
	int idx = 0;	// temp 배열의 인덱스를 가리키는 값



	int len = strlen(exp);	// 문자열의 길이 저장


	StackType s;	// 스택 선언
	init(&s);	// 스택 초기화


	for (i = 0; i < len; i++) 
	{
		ch = exp[i];	// 문자열을 앞에서부터 1개씩 접근

		if (i < len - 2)	// 제곱이 있을 경우, 5 * * 2  즉, 5 * 뒤에 2칸이 무조건 따라오므로, 뒤에서 2번째 부터는 확인 안하기 위해 조건 선언 (exp 배열 범위를 안넘어 가도록)
		{
			if (ch == '*' && exp[i + 1] == '*')	// ch와 ch+1이 *일 경우
			{
				ch = '!';	// ** = !로 만듬
				i++;	// i+1은 이미 *이므로, for문 한번 건너 뜀
			}
		}


		
		switch (ch) 
		{
		
		case '+': case '-': case '*': case '/': case'!':	// 연산자일 경우, 자신보다 우선순위가 높은게 스택에 있으면, temp로 빼줌

			while (!is_empty(&s) && prec(peek(&s)) >= prec(ch))		// 스택이 비어있지 않고, AND ,스택에 저장되어 있는 맨 위의 우선순위가 현재 연산자의 우선순위보다 같거나 이상이면
			{
				temp[idx++] = ' ';	// 공백으로 인해, 피연산자 자리수 해결
				temp[idx++] = pop(&s);	// pop을 해서 temp에 저장
			}
			push(&s, ch);	// 스택에 연산자 push
			temp[idx++] = ' ';	// 공백으로 인해, 피연산자 자리수 해결	
			break;
			
		case '(':	// 여는 괄호의 경우, 그냥 넣음
			push(&s, ch);
			break;
		case ')':	// 닫는 괄호의 경우
			top_op = pop(&s);	// 팝하여 top_op에 저장
			while (top_op != '(')	// 여는 괄호를 만날 때 까지
			{
				temp[idx++] = ' ';	// 공백으로 n자리수 해결
				temp[idx++] = top_op;	// temp에 팝 한 것 저장
				top_op = pop(&s);	// 팝하여 top_op 저장
			}
			break;

		default:	// 피연산자일 경우
			temp[idx++] = ch;	// temp에 바로 저장
			break;
		}
	}

	while (!is_empty(&s))	// 스택이 빌 때까지
	{
		temp[idx++] = ' ';	// 공백으로 n자리수 해결
		temp[idx++] = pop(&s);	// 스택에 남은거 전부 temp에 저장
	}

	temp[idx] = '\0';	// 문자열 끝을 알리는 널문자 삽입
	return temp;	// temp 문자열 리턴
}

void Calculate(char str[])	// 후위수식으로 변환했으니 이제 계산
{
	int i;
	int idx;	// temp 배열 인덱스
	int op1, op2;	// 피연산자 2개 pop 받기 위해 op1, op2 선언
	int integer;	// 
	int result;	// 연산 결과 저장
	int m_temp = 1;	// ! 일때 연산 결과 저장
	int len = strlen(str);	// 문자열 길이 계산

	StackType s;	// 스택 선언
	init(&s);	// 스택 초기화

	for (i = 0; i< len; i++)	// 문자열 길이 까지 반복
	{
		idx = 0;

		char temp[4] = { 0, };	//최대 4자리수 피연산자 OR 연산자 (반복 마다 매번 초기화)
		while (1) // 이 while문을 통해, temp 배열에 공백과 공백 사이의 값이 저장됨
		{
			if ((str[i] == ' ') || (str[i] == '\0'))	// 공백을 만나거나 str이 끝나면 while문 종료
				break;

			temp[idx] = str[i];		// temp에 문자 전달
			i++;	// i 증가 (for문 i와 같은 이유: for문의 i는 str 문자열 길이 만큼 반복하지만, 여기서 str 문자열 길이를 읽기 때문에 같이 따라감)
			idx++;	// idx 증가
		}	

		// = if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+' || temp[0] == '-' || temp[0] == '!')	//연산자면, temp를 한번 받았을테니 검사
		if (prec(temp[0]) > 2)	// 이 경우 때문에, 괄호의 prec을 1, 2로 각각 설정 // 연산자면, temp[0]만 문자를 받았기 때문에, temp[0]만 검사
		{
			op2 = pop(&s);	// 피연산자 pop (나누기와 제곱 시에, 앞 뒤가 중요하므로, op2부터 받아줌)
			op1 = pop(&s);	// 피연산자 pop

			switch (temp[0])	// 실제 계산이 이루어짐
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
			case '!':	// 제곱일 때
				for (int j = 0; j < op2; j++)	// op2 만큼 반복
				{
					m_temp *= op1;	// m_temp=1로 선언했기 때문에, op1을  op2만큼 계속해서 곱해줌
				}
				result = m_temp; 
				break;
			}

			push(&s, result);	// 연산 결과를 다시 스택에 push
		}
		else  // 연산자가 아니면
		{
			integer = atoi(temp);	// atoi(a): a문자열을 숫자로 변환하는 함수 <stdlib.h> 안에 존재
			push(&s, integer);	//숫자 넣기
		}
		
	}

	printf("=%d\n", pop(&s));	// 최종 결과값은 스택 마지막에 남은 값이고, 위에 반복을 통해 스택에는 1개의 데이터가 남음. 그것을 출력

}

int CatchError(char str[])	// 에러 잡는 함수
{
	int i;
	int len = strlen(str);	// 문자열 길이 저장
	int index = 0;	// 괄호의 짝이 맞는지 계산하기 위한 변수 선언

	for (i = 0; i < len; i++)	// 괄호가 짝이 맞는지 + 연산자가 연달아 나오지 않는지 확인
	{
		if(i < len - 1)	// 뒤에서 2번째까지만 확인함으로써 str 배열 범위를 벗어나지 않게 함
			if (prec(str[i]) > 2 && prec(str[i + 1]) > 2)	// str[i]와 str[i+1]이 둘 다 피연산자일 경우
			{
				if (str[i] == '*' && str[i + 1] == '*')	// 제곱을 표현하는 ** 은 오류가 아니므로
					continue;	// 반복문 위로 올라감
				else
					return i;	// 오류는 i번째와 i+1번째 사이에 발생
			}
		else if (prec(str[i]) == 1)	// 여는 괄호 갯수 확인
			index++;
		else if (prec(str[i]) == 2)	// 닫는 괄호 갯수 확인
			index--;
	}

	if (index > 0)	// 짝이 안 맞는 경우: 닫는 괄호가 부족할 때
		return 1;
	else if (index < 0)	// 짝이 안 맞는 경우: 여는 괄호가 부족할 때
		return 2;


	return -1;	// 에러 없음

}
int main(void)
{
	char * i_str = { "2+(3*4)**2-12" };		// 중위수식 문자열
//	char * i_str = { "2+(3*4**2-12" };
//	char * i_str = { "(11+3)*2**3-12" };	
//	char * i_str = { "2+(3+*4**2-12" };

	char * p_str;	// 후위수식 문자열

	int Error;

	printf("중위수식 표현: %s\n", i_str);

	int strLen = strlen(i_str);	// 중위수식 문자열 길이 저장

	Error = CatchError(i_str);	// 중위수식 문자열 에러 검사

	if (Error != -1)	// 에러 발생 시
	{
		switch (Error)
		{
		case 1:	// 닫는 괄호가 부족할 때
			printf("%s(!) 이 위치에 오류가 있습니다. )가 부족합니다.\n", i_str);
			break;
		case 2:	// 여는 괄호가 부족할 때
			printf("(!)%s 이 위치에 오류가 있습니다. (가 부족합니다.\n", i_str);
			break;
		default:
			for (int i = 0; i < strLen; i++)	// str[Error]와 str[Error+1] 사이에서 오류 발생
			{
				if (i == Error)
				{
					printf("%c(!)", i_str[i]);
				}
				else
					printf("%c", i_str[i]);
			}
			printf(" 이 위치에 오류가 있습니다. 숫자가 와야 합니다.\n");
		}
		
		system("pause");
		return 0;
	}

	p_str = infix_to_postfix(i_str);	// 중위 수식 -> 후위 수식으로 변환 , 동적할당 된 문자열을 함수가 반환하고 이를 p_str로 받음
	

	printf("후위수식 표현: %s\n", p_str);

	Calculate(p_str);	// 후위 수식 계산

	free(p_str);	// 동적할당 받은 메모리 반환

	system("pause");
	return 0;
}
#include <stdio.h>
#include <windows.h>
#define True 1
#define False 0
typedef struct stack
{
	int top;
	int capacity;
	int * data;
}Stack;

void StackInit(Stack * s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (int*)malloc(sizeof(int)*s->capacity);
}

int is_empty(Stack * s)
{
	if (s->top == -1)
		return True;
	else
		return False;
}

int is_full(Stack * s)
{
	if (s->top + 1 == s->capacity)
		return True;
	else
		return False;
}

void Push(Stack * s, int data)
{
	if (is_full(s))
	{
		s->capacity *= 2;
		s->data = (int*)realloc(s->data, sizeof(int)*s->capacity);
	}

	s->top++;
	s->data[s->top] = data;
}

int Pop(Stack * s)
{
	if (is_empty(s))
		return -1;

	return s->data[s->top--];
}

int Peek(Stack * s)
{
	if (is_empty(s))
		return -1;

	return s->data[s->top];
}

int Prec(char ch)
{
	switch (ch)
	{
	case '[': case ']':
		return 3;
	case '{': case '}':
		return 2;
	case '(': case ')':
		return 1;
	default:
		return 4;
	}
}

int Check(Stack * s, char * str)
{
	int i = 0;
	char ch;

	while (str[i] != '\0')
	{
		ch = str[i];

		switch (ch)
		{
			
		case '[': case '{': case '(':
			if (Prec(Peek(s)) >= Prec(ch))
				Push(s, ch);
			else
				return -1;
			break;
		case ']': case '}': case ')':
			if (Prec(Peek(s)) == Prec(ch))
				Pop(s);
			else
				return -1;
		default:
			break;
		}
		i++;
	}

	if (is_empty(s))
		return 1;
	else
		return -1;

}
int main(void)
{
	char * str = "{2+(7-(3+2))-3}-2";
	Stack * s;
	s = (Stack*)malloc(sizeof(Stack));

	StackInit(s);

	int result;
	
	result = Check(s, str);

	if (result == 1)
		printf("괄호검사 성공\n");
	else
		printf("실패!!!!\n");

	free(s);


	system("pause");
	return 0;
}
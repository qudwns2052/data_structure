#include <stdio.h>
#include <windows.h>

typedef struct stack
{
	int stackArr[100];
	int top;
}Stack;

Stack * Create(void)
{
	Stack * tempstack;

	tempstack = malloc(sizeof(Stack));
	tempstack->top = -1;
	return tempstack;
}
void push(Stack * pstack, int Data)
{
	pstack->stackArr[++(pstack->top)] = Data;
}

int Pop(Stack *pstack)
{
	return pstack->stackArr[pstack->top--];
}


int main(void)
{
	Stack *s;

	s = Create();
	int num = 5;
	push(s, num);

	printf("%d", Pop(s));
	
	system("pause");
	return 0;
}
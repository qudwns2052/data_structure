#include <stdio.h>
#include <stdlib.h>

// stack push pop set find check 
typedef int data;

typedef struct stack
{
	int count;
	data * stack;
}stack;

void set(stack * pstack)
{
	pstack->count = -1;
	pstack->stack = (int *)malloc(sizeof(int) * ((pstack->count) + 2));
};

void stackmemory(stack * pstack)
{
	realloc(pstack->stack, sizeof(int)*((pstack->count) + 2));
};

void push(stack * pstack, data num)
{
	stackmemory(pstack);
	pstack->count = pstack->count + 1;
	pstack->stack[pstack->count] = num;
};

int pop(stack * pstack)
{
	int temp = pstack->stack[pstack->count];
	pstack->count--;
	return temp;
};



int main()
{
	stack stack;
	int a = 0;
	set(&stack);
	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		push(&stack, a);
	}

	printf("%d", pop(&stack));
}
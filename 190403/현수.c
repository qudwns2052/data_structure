#include <stdio.h>
#include <stdlib.h>
#define len 4
typedef int data;

typedef struct stack
{
	data data[len];
	int count;
}stack;

void setstack(stack * pstack)
{
	pstack->count = -1;
	pstack->data[len] = { 0, };
};

int scheck(stack * pstack)
{
	if (pstack->count < len)
	{
		return 1;
	}

	else
	{
		return -1;
	}
};

void push(stack * pstack, data num)
{
	if (scheck(pstack) == 1)
	{
		pstack->count++;
		pstack->data[pstack->count] = num;
	}
	else if (scheck(pstack) == -1)
	{
		printf("½ºÅÃÀÌ ²Ë Ã¡½À´Ï´Ù.");
	}
};

int pop(stack * pstack)
{
	int temp = pstack->data[pstack->count];
	//pstack->data[pstack->count] = 0;
	pstack->count = pstack->count - 1;
	return temp;
};

int find(stack * pstack, int num)
{
	for (int i = 0; i < pstack->count; i++)
	{
		if (pstack->data[i] == num)
		{
			return num;
		}
	}

	return -1;
};

int main()
{
	int a = 0;
	struct stack stack;
	setstack(&stack);

	for (int i = 0; i < len; i++)
	{
		scanf("%d", &a);
		push(&stack, a);
	}

	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));

	printf("%d", find(&stack, 5));

}
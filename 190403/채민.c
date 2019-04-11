#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef int element;
typedef struct
{
	element* data;
	int top;
	int size;
}stack;


void push(stack* s, element e)
{
	s->data = (element*)realloc(s->data, s->size * sizeof(element));
	s->data[++(s->top)] = e;
	s->size++;
	printf("%d", s->data[s->top]);
}

void pop(stack* s)
{
	if (s->top < 0)   exit(1);
	else printf("%d", s->data[(s->top)--]);
}

int main()
{
	stack* even;
	even->data = (element*)malloc(sizeof(element));
	stack* odd;
	odd->data = (element*)malloc(sizeof(element));
	even->top = -1;   even->size = even->top + 2;
	odd->top = -1;    odd->size = odd->top + 2;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		int e = rand() % 100;
		if (e % 2 == 0)   push(even, e);
		else   push(odd, e);
	}
	pop(even);
	pop(odd);

	free(even->data); free(odd->data);

}
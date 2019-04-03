#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int element;
int size; // 추가부분
typedef struct
{
	element *data;
	int top;
}stack;

void push(stack* s, element item)
{
	s->top++;
	size = s->top + 2; //추가부분
	s->data = (element*)realloc(s->data, size * sizeof(element)); //변경부분
	s->data[s->top] = item;
	printf("%d", item);
}

element pop(stack* s)
{
	if (s->top < 0) exit(0);
	else return s->data[(s->top)--];
}

int main()
{
	stack s;
	s.top = -1;	//top초기화
	s.data = (element*)malloc(sizeof(element));
	push(&s, 2);
	push(&s, 4);
	push(&s, 5);
	printf("\n\n%d", pop(&s));
	free(s.data);

	system("pause");
	return 0;
}
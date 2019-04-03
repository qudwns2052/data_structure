#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int element;
int size; // �߰��κ�
typedef struct
{
	element *data;
	int top;
}stack;

void push(stack* s, element item)
{
	s->top++;
	size = s->top + 2; //�߰��κ�
	s->data = (element*)realloc(s->data, size * sizeof(element)); //����κ�
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
	s.top = -1;	//top�ʱ�ȭ
	s.data = (element*)malloc(sizeof(element));
	push(&s, 2);
	push(&s, 4);
	push(&s, 5);
	printf("\n\n%d", pop(&s));
	free(s.data);

	system("pause");
	return 0;
}
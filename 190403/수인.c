#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  STACK_LEN 100

typedef struct {
	int data[STACK_LEN];
	int top;
}Stack;

void StackInit(Stack * s) {
	s->top = -1;
}

int IsFull(Stack * s) {
	return (s->top == (STACK_LEN)-1); //���� �� á��  
}

void push(Stack * s, int item) {
	if (IsFull(s)) {
		printf("������ �� á���ϴ�\n");
		return;
	}
	else {
		(s->top)++;
		s->data[(s->top)] = item;
	}
}


int  IsEmpty(Stack * s) {
	return (s->top == -1);
}

int pop(Stack * s) {
	if (IsEmpty(s)) {
		printf("������ ����ֽ��ϴ� \n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

void printStack(Stack * s) {
	while (s->top != -1) {
		printf("%d \n", pop(s));
	}
	printf("\n\n");
}

int main(void)
{
	Stack EvenStack;
	Stack OddStack;

	int i = 0;
	int num = 0;
	srand((unsigned)time(NULL));

	while (i < 10) {
		num = rand() % 100;
		if (num % 2 == 0) {
			push(&EvenStack, num);
		}
		else {
			push(&OddStack, num);
		}
		i++;
	}
	printf("¦�����:");
	printStack(&EvenStack);
	printf("Ȧ�����:");
	printStack(&OddStack);
}
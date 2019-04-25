#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 21
#define True 1
#define False 0

typedef struct queue
{
	int front;
	int rear;
	int data[MAX_SIZE];
}Queue;

int is_full(Queue * q)
{
	if ((q->rear + 1) % MAX_SIZE == q->front)
		return True;
	else
		return False;
}

int is_empty(Queue * q)
{
	if (q->rear == q->front)
		return True;
	else
		return False;
}

Queue * QueueInit(void)
{
	Queue * q = (Queue*)malloc(sizeof(Queue));
	q->rear = 0;
	q->front = 0;

	return q;
}

void Push(Queue *q, int data)
{
	if (is_full(q))
		return;
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = data;
}

int Pop(Queue *q)
{
	if (is_empty(q))
		return 'X';
	q->front = (q->front + 1) % MAX_SIZE;
	return q->data[q->front];
}

int main(void)
{
	int num;
	char * str = (char*)malloc(sizeof(char)*MAX_SIZE);
	Queue * q;

	q= QueueInit();

	while (1)
	{
		scanf("%s", str);
		for (int i = 0; str[i] != '\0'; i++)
			Push(q, str[i]);

		

		scanf("%d", &num);

		

		if (num == 0)
			break;

		for (int i = 0; i < num; i++)
			printf("%c\n", Pop(q));

	}


	system("pause");
	return 0;
}
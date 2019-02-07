#include <stdio.h>
#include "Deque.h"

int main(void)
{
	Deque deq;
	DequeInit(&deq);

	DQAddFirst(&deq, 3);
	DQAddFirst(&deq, 2);
	DQAddFirst(&deq, 1);

	DQAddLast(&deq, 4);
	DQAddLast(&deq, 5);
	DQAddLast(&deq, 6);

	while (!DQIsEmpty(&deq))
		printf("%d ", DQRemoveFirst(&deq));

	printf("\n\n");

	DQAddFirst(&deq, 3);
	DQAddFirst(&deq, 2);
	DQAddFirst(&deq, 1);

	DQAddLast(&deq, 4);
	DQAddLast(&deq, 5);
	DQAddLast(&deq, 6);

	while (!DQIsEmpty(&deq))
		printf("%d ", DQRemoveLast(&deq));

	int i;
	scanf("%d", &i);

	return 0;

}
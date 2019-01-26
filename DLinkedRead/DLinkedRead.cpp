#include "stdafx.h"
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node * next;
} Node;


int main()
{
	Node * head = NULL;
	Node * tail = NULL;
	Node * cur = NULL;

	Node * newNode = NULL;
	int readData;

	head = (Node*)malloc(sizeof(Node));
	tail = head;


	while (1)
	{
		printf("자연수 입력: ");
		scanf("%d", &readData);
		if (readData < 1)
			break;

		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = NULL;

		tail->next = newNode;
		tail = newNode;

	}
	printf("\n");

	printf("입력 받은 데이터의 전체출력! \n");
	
	
	cur = head;

		while (cur->next != NULL)
		{
			cur = cur->next;
			printf("%d ", cur->data);
		}
	
	printf("\n\n");

	Node * delNode = head;
	Node * delNextNode = head->next;

	while (delNextNode != NULL)

	{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다. \n", delNode->data);
			free(delNode);
		
	}

	return 0;
}


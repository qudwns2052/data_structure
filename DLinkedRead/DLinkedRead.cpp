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
		printf("�ڿ��� �Է�: ");
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

	printf("�Է� ���� �������� ��ü���! \n");
	
	
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

			printf("%d��(��) �����մϴ�. \n", delNode->data);
			free(delNode);
		
	}

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Node
{
	int id;
	char name[10];
	char number[12];
	struct Node * fnext;
	struct Node * snext;

}Node;


Node * MakeDummy(void)
{
	Node * newnode = (Node*)malloc(sizeof(Node));
	newnode->fnext = NULL;
	newnode->snext = NULL;

	return newnode;
}
Node * MakeNode(void)
{
	Node * newnode = (Node*)malloc(sizeof(Node));
	char name[10];
	char number[12];

	int id = ((rand() % 7) + 13) * 10000000 + (rand() % 1000) * 10000 + (rand() % 10000);

	for (int i = 0; i < 9; i++)
	{
		name[i] = rand() % 26 + 65;
	}
	name[9] = '\0';


	number[0] = '0';
	number[1] = '1';
	number[2] = '0';
	for (int i = 3; i < 7; i++)
	{
		number[i] = rand() % 10 + '0';
		number[i + 4] = rand() % 10 + '0';
	}
	number[11] = '\0';

	newnode->id = id;
	strcpy(newnode->name, name);
	strcpy(newnode->number, number);
	newnode->fnext = NULL;
	newnode->snext = NULL;


	return newnode;
}

void SortId(Node * node, Node * newnode)
{
	Node * temp = node->fnext;
	Node * front = node;

	while (temp != NULL)
	{
		if (temp->id > newnode->id)
			break;
		temp = temp->fnext;
		front = front->fnext;
	}

	newnode->fnext = front->fnext;
	front->fnext = newnode;
}


void SortName(Node * node, Node * newnode)
{
	Node * temp = node->snext;
	Node * front = node;

	while (temp != NULL)
	{
		if (strcmp(temp->name, newnode->name) > 0)
			break;
		temp = temp->snext;
		front = front->snext;
	}

	newnode->snext = front->snext;
	front->snext = newnode;

}

void MakeManyNode(Node * node)
{
	Node * temp = NULL;

	for (int i = 0; i < 10000; i++)
	{
		temp = MakeNode();
		SortId(node, temp);
		SortName(node, temp);
	}
}

void PrintSortId(Node * node)
{
	Node * temp = node->fnext;

	while (temp != NULL)
	{
		printf("%d\t%s\t%s\n", temp->id, temp->name, temp->number);
		temp = temp->fnext;
	}
}

void PrintSortName(Node * node)
{
	Node * temp = node->snext;

	while (temp != NULL)
	{
		printf("%d\t%s\t%s\n", temp->id, temp->name, temp->number);
		temp = temp->snext;
	}
}

int main(void)
{
	srand((unsigned)time(NULL));


	Node * node = MakeDummy();

	MakeManyNode(node);


	while (1)
	{
		int num;

		printf("(1) 학번 순\n");
		printf("(2) 이름 순\n");
		printf("메뉴 선택 (0 : 종료) >> ");

		scanf("%d", &num);

		if (num == 1)
		{
			PrintSortId(node);
		}
		else if (num == 2)
		{
			PrintSortName(node);
		}
		else if (num == 0)
		{
			return 0;
		}
		else
		{
			printf("잘못 입력하셨습니다. 다시 입력하세요.\n");
		}
	}

	system("pause");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Node
{
	char name[10];
	char number[14];
	struct Node * next;

}Node;

int cntnode = 0;

Node * MakeDummy(void)
{
	Node * newnode = (Node*)malloc(sizeof(Node));
	newnode->next = NULL;
	return newnode;
}
Node * MakeNode(void)
{
	Node * newnode = (Node*)malloc(sizeof(Node));
	char name[10];
	char number[14];

	for (int i = 0; i < 9; i++)
	{
		name[i] = rand() % 26 + 65;
	}
	name[9] = '\0';


	number[0] = '0';
	number[1] = '1';
	number[2] = '0';
	number[3] = '-';
	number[8] = '-';
	for (int i = 4; i < 8; i++)
	{
		number[i] = rand() % 10 + '0';
		number[i + 5] = rand() % 10 + '0';
	}
	number[13] = '\0';

	strcpy(newnode->name, name);
	strcpy(newnode->number, number);
	newnode->next = NULL;

	cntnode++;

	return newnode;
}

void MakeTenNode(Node * node)
{
	Node * temp = node;

	for (int i = 0; i < 10; i++)
	{
		temp->next = MakeNode();
		temp = temp->next;
	}

}

void InsertNode(Node * node, char * name, char * number)
{
	Node * newnode = (Node*)malloc(sizeof(Node));

	strcpy(newnode->name, name);
	strcpy(newnode->number, number);
	newnode->next = NULL;

	cntnode++;

	Node * temp = node;

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newnode;
	printf("(%s %s가 입력되었습니다)\n", name, number);
}

void FindNode(Node * here)
{
	printf("(찾았습니다) %s\n", here->number);
}

void CheckName(Node * node, char * name)
{
	Node * temp = node->next;

	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
		{
			FindNode(temp);
			return;
		}
		temp = temp->next;
	}

	char number[14];
	printf("(존재하지 않는 이름입니다. 전화번호를 입력하세요)\n전화번호 >>> ");
	scanf("%s", number);
	getchar();

	InsertNode(node, name, number);
}

void PrintNode(Node * node)
{
	Node * temp = node->next;

	while (temp != NULL)
	{
		printf("%s\t%s\n", temp->name, temp->number);
		temp = temp->next;
	}
}

void SortNode(Node * node)
{
	Node * temp = NULL;
	Node * sub = NULL;

	for (int i = 0; i < cntnode - 1; i++)
	{
		temp = node;
		for (int j = 0; j < cntnode - i - 1; j++)
		{
			if (strcmp(temp->next->name, temp->next->next->name) > 0)
			{
				sub = temp->next->next;
				if (temp->next->next->next != NULL)
					temp->next->next = temp->next->next->next;
				else
					temp->next->next = NULL;
				sub->next = temp->next;
				temp->next = sub;
			}
			temp = temp->next;
		}
	}

	PrintNode(node);
	printf("(정렬완료)\n");

}

void DeleteNode(Node * node, char * subname)
{
	Node * temp = node->next;
	Node * front = node;
	
	char name[10];
	int i = 0;
	while (subname[i + 5] != '\0')
	{
		name[i] = subname[i + 5];
		i++;
	}
	name[i] = '\0';


	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
		{
			front->next = temp->next;

			printf("(%s\t%s가 삭제되었습니다)\n", temp->name, temp->number);

			cntnode--;

			free(temp);
			return;
		}
		temp = temp->next;
		front = front->next;
	}
	printf("(%s(이)라는 사람을 찾지 못했습니다)\n", name);
}

int main(void)
{
	srand((unsigned)time(NULL));


	Node * node = MakeDummy();
	
	MakeTenNode(node);


	while (1)
	{
		char str[20];

		printf("(%d명의 데이터가 있습니다)\n", cntnode);
		printf(">> ");
		
		fgets(str, 20, stdin);
		
		str[strlen(str) - 1] = '\0';

		if (strncmp(str, "목록", 2) == 0) PrintNode(node);
		else if (strncmp(str, "정렬", 2) == 0) SortNode(node);
		else if (strncmp(str, "삭제", 2) == 0) DeleteNode(node, str);
		else CheckName(node, str);

	}

	system("pause");
	return 0;
}
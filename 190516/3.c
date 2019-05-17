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
	struct Node * left;
	struct Node * right;

}Node;


Node * MakeDummy(void)
{
	Node * newnode = (Node*)malloc(sizeof(Node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->id = 0;

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
	newnode->left = NULL;
	newnode->right = NULL;


	return newnode;
}

void BinarySearchTree(Node * node, Node * newnode)
{
	Node * temp = node;
	Node * sub = NULL;

	while (temp != NULL)
	{
		sub = temp;

		if (temp->id > newnode->id)
		{
			temp = temp->left;
			if (temp == NULL)	sub->left = newnode;
		}
		else
		{
			temp = temp->right;
			if (temp == NULL)	sub->right = newnode;
		}
	}

}

void InOrderSearch(Node * node)
{
	if (node == NULL)
		return;

	InOrderSearch(node->left);
	printf("%d\n", node->id);
	InOrderSearch(node->right);

}


void MakeManyNode(Node * node, int *ids)
{
	Node * temp = NULL;
	

	for (int i = 0; i < 9000; i++)
	{
		temp = MakeNode();
		BinarySearchTree(node, temp);
	}

	for (int i = 0; i < 1000; i++)
	{
		temp = MakeNode();
		ids[i] = temp->id;
		BinarySearchTree(node, temp);
	}

}

int randcnt = 0;

void Searchid(Node * node, int id)
{
	Node * temp = node;
	while (temp != NULL)
	{
		if (temp->id == id) break;
		else if (temp->id > id)	temp = temp->left;
		else temp = temp->right;
	}

	if (temp == NULL) 
	{
		printf("%d\t(없음)\n", id);
		return;
	}

	printf("%d\t%s\n", temp->id, temp->name);
	randcnt++;

}

void MakeRandid(int * randids)
{
	for (int i = 0; i < 10000; i++)
	{
		randids[i] = ((rand() % 7) + 13) * 10000000 + (rand() % 1000) * 10000 + (rand() % 10000);
	}
}

int main(void)
{
	srand((unsigned)time(NULL));

	int ids[1000];
	int randids[10000];
	

	Node * node = MakeDummy();

	MakeManyNode(node,ids);

	MakeRandid(randids);

	printf("Step 1. 중위순회하기\n\n");

	InOrderSearch(node->right);

	printf("\nStep 2. 데이터 탐색하기\n\n");

	for (int i = 0; i < 1000; i++)
	{
		Searchid(node, ids[i]);
	}

	printf("\nStep 3. 랜덤한 학번으로 검색하기\n\n"); 
	
	randcnt = 0;

	for (int i = 0; i < 10000; i++)
	{
		Searchid(node, randids[i]);
	}
	printf("총 %d개 발견\n", randcnt);


	system("pause");
	return 0;
}
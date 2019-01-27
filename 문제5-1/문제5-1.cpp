#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "CLinkedList.h"
#include "Employee.h"

Employee * WHOWHO(List * plist, char * name, int day);
void Show(Employee * who);

int main()
{
	List list;
	ListInit(&list);
	Employee * who;

	who = (Employee*)malloc(sizeof(Employee));
	who->empNum = 1111;
	strcpy_s(who->name,sizeof(who->name), "A");
	LInsert(&list, who);

	who = (Employee*)malloc(sizeof(Employee));
	who->empNum = 2222;
	strcpy_s(who->name, sizeof(who->name), "B");
	LInsert(&list, who);
	
	who = (Employee*)malloc(sizeof(Employee));
	who->empNum = 3333;
	strcpy_s(who->name, sizeof(who->name), "C");
	LInsert(&list, who);

	who = (Employee*)malloc(sizeof(Employee));
	who->empNum = 4444;
	strcpy_s(who->name, sizeof(who->name), "D");
	LInsert(&list, who);
   
	printf("A 이후 7일뒤 \n");
	who = WHOWHO(&list, "A", 7);
	Show(who);

	printf("B 이후 7일뒤 \n");
	who = WHOWHO(&list, "B", 7);
	Show(who);

	printf("D 이후 3일뒤 \n");
	who = WHOWHO(&list, "D", 3);
	Show(who);

	if (LFirst(&list, &who))
	{
		free(who);

		for (int i = 0; i < LCount(&list) - 1; i++)
		{
			LNext(&list, &who);
			free(who);
		}

	}
	
	return 0;
}


Employee * WHOWHO(List * plist, char * name, int day)
{
	int i, num;
	Employee * ret;

	num = LCount(plist);

	LFirst(plist, &ret);

	if (strcmp(ret->name, name) != 0)
	{
		for (i = 0; i < num - 1; i++)
		{
			LNext(plist, &ret);
			if (strcmp(ret->name, name) == 0)
				break;
		}
		if (i >= num - 1)
			return NULL;
	}

	for (i = 0; i < day; i++)
		LNext(plist, &ret);

	return ret;

}

void Show(Employee * who)
{
	printf("이름: %s \n", who->name);
	printf("사번: %d \n\n", who->empNum);
}

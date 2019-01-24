#include "stdafx.h"
#include "NameCard.h"
#include "ArrayList.h"
#include <stdlib.h>


int main()
{
	List list;
	NameCard * pcard;
	ListInit(&list);

	pcard = MakeNameCard("�ֺ���", "010-6244-2052");
	LInsert(&list, pcard);

	pcard = MakeNameCard("�㼱��", "010-6560-4985");
	LInsert(&list, pcard);

	pcard = MakeNameCard("��ȣ��", "010-9084-2052");
	LInsert(&list, pcard);

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "�㼱��") == 0)
			ShowNameCardInfo(pcard);
		else
			while(LNext(&list,&pcard))
				if (NameCompare(pcard, "�㼱��") == 0)
				{
					ShowNameCardInfo(pcard);
					break;
				}
	}

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "�ֺ���") == 0)
			ChangePhoneNum(pcard, "010-9312-2052");
		else
			while (LNext(&list, &pcard))
				if (NameCompare(pcard, "�ֺ���") == 0)
				{
					ChangePhoneNum(pcard, "010-9312-2052");
					break;
				}
	}

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "��ȣ��") == 0)
		{
			pcard = LRemove(&list);
			free(pcard);
		}
		else
			while(LNext(&list, &pcard))
				if (NameCompare(pcard, "��ȣ��") == 0)
				{
					pcard = LRemove(&list);
					free(pcard);
					break;
				}
	}

	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &pcard))
	{
		ShowNameCardInfo(pcard);
		while (LNext(&list, &pcard))
			ShowNameCardInfo(pcard);
	}

    return 0;
}


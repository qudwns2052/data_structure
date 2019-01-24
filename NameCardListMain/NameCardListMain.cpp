#include "stdafx.h"
#include "NameCard.h"
#include "ArrayList.h"
#include <stdlib.h>


int main()
{
	List list;
	NameCard * pcard;
	ListInit(&list);

	pcard = MakeNameCard("최병준", "010-6244-2052");
	LInsert(&list, pcard);

	pcard = MakeNameCard("허선아", "010-6560-4985");
	LInsert(&list, pcard);

	pcard = MakeNameCard("최호락", "010-9084-2052");
	LInsert(&list, pcard);

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "허선아") == 0)
			ShowNameCardInfo(pcard);
		else
			while(LNext(&list,&pcard))
				if (NameCompare(pcard, "허선아") == 0)
				{
					ShowNameCardInfo(pcard);
					break;
				}
	}

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "최병준") == 0)
			ChangePhoneNum(pcard, "010-9312-2052");
		else
			while (LNext(&list, &pcard))
				if (NameCompare(pcard, "최병준") == 0)
				{
					ChangePhoneNum(pcard, "010-9312-2052");
					break;
				}
	}

	if (LFirst(&list, &pcard))
	{
		if (NameCompare(pcard, "최호락") == 0)
		{
			pcard = LRemove(&list);
			free(pcard);
		}
		else
			while(LNext(&list, &pcard))
				if (NameCompare(pcard, "최호락") == 0)
				{
					pcard = LRemove(&list);
					free(pcard);
					break;
				}
	}

	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &pcard))
	{
		ShowNameCardInfo(pcard);
		while (LNext(&list, &pcard))
			ShowNameCardInfo(pcard);
	}

    return 0;
}


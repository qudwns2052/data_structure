#include "stdafx.h"
#include "ArrayList.h"

int main()
{
	List list;
	int data;
	ListInit(&list);

	int sum = 0;
	int i;

	for (i = 0; i < 9; i++)
		LInsert(&list, i + 1);

	if (LFirst(&list, &data))
	{
		sum += data;
	
		while (LNext(&list, &data))
			sum += data;
	}

	printf("���� �������� ��: %d \n", LCount(&list));
	printf("����Ʈ�� ����� ��: %d\n", sum);

	if (LFirst(&list, &data))
	{
		if (data % 2 == 0 || data % 3 == 0)
			LRemove(&list);
		while (LNext(&list, &data))
		{
			if (data % 2 == 0 || data % 3 == 0)
				LRemove(&list);
		}
	}

	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);
		
		while (LNext(&list, &data))
			printf("%d ", data);
	}

	printf("\n\n");
	

    return 0;
}


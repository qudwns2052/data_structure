#include <stdio.h>
#include <stdlib.h>
// push pop set memory

typedef int num;

typedef struct data
{
	int count;
	num * data;
}data;

void set(data * pdata)
{
	pdata->count = -1;
	pdata->data = (int *)malloc(sizeof(int) * ((pdata->count) + 2));
};

void memory(data * pdata)
{
	realloc(pdata->data, sizeof(num) * ((pdata->count + 2)));
};

void push(data * pdata, int num)
{
	memory(pdata);
	pdata->count = pdata->count + 1;
	pdata->data[pdata->count] = num;
};

int pop(data * pdata)
{
	int temp;
	if (pdata->count != -1)
	{
		temp = pdata->data[pdata->count];
		pdata->data[pdata->count] = 0;
		pdata->count = pdata->count - 1;
		return temp;
	}
};

int main()
{
	int a = 0;
	int odd = 0;
	int even = 0;
	data evenstack;
	data oddstack;
	set(&evenstack);
	set(&oddstack);

	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &a);

		if (a % 2 == 1)
		{
			push(&oddstack, a);
			printf("Ȧ : %d\n", pop(&oddstack));
		}

		else if (a % 2 == 0)
		{
			push(&evenstack, a);
			printf("¦ : %d \n", pop(&evenstack));
		}

		fflush(stdin);
	}


	system("pause");
	return 0;
}
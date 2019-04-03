#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 20

int findex = -1;
int sindex = 0;
char Queue[MAX_SIZE];

void ADDQUEUE(char ch)
{
	if (findex - sindex >= 19)
	{
		printf("ADDQUEUE(%c) Fail : Queue Full  Queue Size=20/20\n", ch);
		return;
	}
	Queue[++findex] = ch;
	printf("ADDQUEUE(%c)	Queue Size=%d/20\n", ch, findex - sindex + 1);

}

void DELETEQUEUE(void)
{
	if (findex + 1 <= sindex)
	{
		printf("DELETEQUEUE() Fail : Queue Empty  Queue Size=0/20\n");
		return;
	}

	printf("DELETEQUEUE() = %c, Queue Size=%d/20\n", Queue[sindex], findex - sindex);
	sindex++;

}

int main(void)
{
	char str[20];
	int i;
	int num;
	int strLen;

	while (1)
	{
		printf(">>> ");
		scanf("%s", str);
		strLen = strlen(str);
		if (strLen > MAX_SIZE)
		{
			printf("ERROR (MAX_SIZE is 20)\n");
			continue;
		}
		else if ('A' <= str[0] && str[0] <= 'Z')
		{
			for (i = 0; i < strLen; i++)
			{
				ADDQUEUE(str[i]);
			}
		}
		else
		{
			num = atoi(str);
			for (i = 0; i < num; i++)
			{
				DELETEQUEUE();
			}
		}

	}





	system("pause");
	return 0;
}
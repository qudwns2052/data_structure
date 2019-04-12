#include <stdio.h>
#include <windows.h>

#define STACK_LEN 20

int stack_x[STACK_LEN];
int stack_y[STACK_LEN];
int index_x = -1;
int index_y = -1;

void Push(int x, int y)
{
	stack_x[++index_x] = x;
	stack_y[++index_y] = y;
	printf("Push(%d, %d)\n", x, y);
}

void Pop(void)
{
	index_x--;
	index_y--;
}

int Peek_x(void)
{
	return stack_x[index_x];
}

int Peek_y(void)
{
	return stack_y[index_y];
}


int main(void)
{
	int arr[25][19] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
	{1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
	{1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1},
	{1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1},
	{1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
	{1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1},
	{1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int x = 1;
	int y = 1;
	int cnt;
	char direct;
	char before_direct = 'A';

	while (x != 23 || y != 17)
	{
		cnt = 0;

		if (arr[x][y + 1] != 1 && arr[x][y + 1] != 'X')
		{
			if (before_direct != 'W')
			{
				cnt++;
				direct = 'E';
			}
		}
		if (arr[x + 1][y] != 1 && arr[x + 1][y] != 'X')
		{
			if (before_direct != 'N')
			{
				cnt++;
				direct = 'S';
			}
		}
		if (arr[x][y - 1] != 1 && arr[x][y - 1] != 'X')
		{
			if (before_direct != 'E')
			{
				cnt++;
				direct = 'W';
			}
		}
		if (arr[x - 1][y] != 1 && arr[x - 1][y] != 'X')
		{
			if (before_direct != 'S')
			{
				cnt++;
				direct = 'N';
			}
		}

		if (cnt == 0)
		{
			arr[x][y] = 'X';
			x = Peek_x();
			y = Peek_y();
			before_direct = 'A';
			Pop();
			printf("Pop(%d, %d)\n", x, y);
		}
		else
		{
			if(cnt>1)
				Push(x, y);

			switch (direct)
			{
			case 'N':
				arr[x--][y] = 'X';
				arr[x--][y] = 'X';
				break;
			case 'W':
				arr[x][y--] = 'X';
				arr[x][y--] = 'X';
				break;
			case 'S':
				arr[x++][y] = 'X';
				arr[x++][y] = 'X';
				break;
			case 'E':
				arr[x][y++] = 'X';
				arr[x][y++] = 'X';
				break;
			}
			before_direct = direct;
		}
	}
	
	arr[x][y] = 'X';

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (arr[i][j] > 1)
				printf("%2c", arr[i][j]);
			else
				printf("%2d", arr[i][j]);
		}
		printf("\n");
	}

	



	system("pause");
	return 0;
}
/*��α�:yk209.tistory.com
  �����ֽź�:���� ����*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define BOARD_HEIGHT 20 // ������
#define BOARD_WIDTH 10  // ������
#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

#define CBLOCK_X 13
#define CBLOCK_Y 2
#define DELAY 100//����
#define RAND 4//����

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int static score = 0; //��������
int static level = 1; //���ӷ���
int static speed = 180;
int curX, curY; //�ܼ�Ŀ��
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };
int block[][4][4] = {
	/*��
	  ����*/
	{
		{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0}},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0}},
	{
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0}},
	{
		{1,1,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{0,0,0,0}},
		/* �� ��° ���
			 ��
		 ����     */
	{
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{1, 1, 1, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },

		/* �� ��° ���
				��
			  ����    */
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0} },

			/* �� ��° ���

				  �����   */
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0} },
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0} },

				/* �ټ� ��° ���

					  ���
					  ���      */
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },


					/* ���� ��° ���
							���
						  ���      */
					{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0} },
					{
						{0, 1, 0, 0},
						{0, 1, 1, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 0} },
					{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0} },
					{
						{0, 1, 0, 0},
						{0, 1, 1, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 0} },

						/* �ϰ� ��° ���

							  ���
								���    */
						{
							{0, 0, 0, 0},
							{1, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 1, 0},
							{0, 1, 1, 0},
							{0, 1, 0, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 0, 0},
							{1, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 1, 0},
							{0, 1, 1, 0},
							{0, 1, 0, 0},
							{0, 0, 0, 0} },

};
void removeCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setCursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
COORD getCursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
}
//void showBlock(int rotation);

void showBoard(void)
{
	int x, y;

	//�߾� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		setCursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}
	//���� ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�
		setCursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}
	//������ ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�
		setCursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}

	//�𼭸��� �� ����
	board[20][0] = 1;
	board[20][11] = 1;



	//������ ���� ����
	//setCursor(6,2);
	//for(y=0; y<=BOARD_HEIGHT; y++){
	//	for(x=0; x<=BOARD_WIDTH+1; x++){
	//		setCursor(4+(x*2),2+y);
	//		printf("%d ",board[y][x]);
	//	}
	//	printf("\n");
	//}


	puts(" ");
}

void initial(int x, int y)
{
	curX = x;
	curY = y;
	setCursor(x, y);
}

//removeBlock�Լ� �۵��� ���� or �ƴ���Ȯ��
int detect(int rotation, int move1, int move2)
{
	int x, y;
	int arrX, arrY; //�迭��ǥ����
	COORD pos = getCursor();

	arrX = pos.X + move1;
	arrY = pos.Y + move2;

	arrX = (arrX / 2) - 2;
	arrY = arrY - BOARD_Y;


	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block[rotation][y][x] == 1) && board[arrY + y][arrX + x] == 1)
				return 1;  //����� ���� ��ħ
		}
	}
	return 0;  //��ġ�� ����

}

//��������
void showBlock(int rotation)
{
	int x, y;
	COORD cursor = getCursor();
	int prove;
	//int n=(rotation-1)%4;
	prove = detect(rotation, 0, 0);
	if (prove == 0)
	{
		//�ܼ�â��ġ ����, �迭������ 1�� �����,0�� ��¾���
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf("��");
			}
		}
		setCursor(cursor.X, cursor.Y);
	}
}


void removeBlock(int rotation, int move1, int move2)
{
	int pr;
	int x, y;

	COORD cursor = getCursor();

	pr = detect(rotation, move1, move2);

	if (pr == 0)
	{
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf(" ");
			}
		}
		setCursor(cursor.X + move1, cursor.Y + move2);
	}
}


//��� �����ǿ��� 1�ν�
void boardConginition(int n, int move1, int move2)
{
	int x1, y1;
	COORD pos = getCursor();

	int arrX = pos.X + move1;  //�ܼ���ǥ ��
	int arrY = pos.Y + move2;  //�ܼ���ǥ ��
	int x, y;

	/*Ŀ����ġ����->�迭��ġ���� ����*/
	arrX = arrX / 2 - 2; //�ܼ���ǥ->�迭 �� ��ȯ��
	arrY = arrY - 2;	 //�ܼ���ǥ->�迭 �� ��ȯ��

	//�����ǿ��� ��� �̵��� 1�ν�
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block[n][y][x] == 1)
			{
				board[arrY + y][arrX + x] = 1;
			}
		}
	}
	return;

}

/*�迭,��� �ű�*/
void array_down(int column)
{
	int y, x;

	/*board�迭 �� �� �ٿ�*/
	for (y = column; y >= 0; y--)
	{
		for (x = 1; x <= 10; x++)
		{
			board[y][x] = board[y - 1][x];
		}
	}
	/*board�迭 0�࿡ 0����*/
	for (x = 1; x <= 10; x++)
		board[0][x] = 0;

	/*board�迭 1�� ��ü ��� */
	for (y = 1; y <= 19; y++)
	{
		for (x = 1; x <= 10; x++)
		{
			setCursor((BOARD_X)+x * 2 + 1, y + BOARD_Y);
			if (board[y][x] == 1)
				printf("��");
			else
				printf("  ");
		}
	}

}
//���� ���ھ� ���
void scoreLevel(void)
{

	setCursor(40, 3);
	printf("�ڷ���10 ���� Ŭ�����");
	setCursor(40, 5);
	printf("����:%d\n", level);
	setCursor(40, 7);
	printf("����:%d\n", score);
}
//���� ���ھ� ���
void countScore(void)
{
	score += 10;
	if (score % 30 == 0)
	{
		level += 1;
		speed -= 30;
	}
	scoreLevel();
}
/* 1~10���� ���� �� ��ü�� 1�εǸ� ��ϻ����.
	������� array_down�Լ� ���� */
void control(void)
{
	int i;
	int x, y;
	int z = 0;

	//19����� �����ؼ� 1����� �ݺ�
	for (y = 19; y >= 1; y--)
	{
		//��������� 4�� �ݺ�
		for (z = 0; z < 4; z++)
		{
			i = 0;
			//1������ 10������ ����
			for (x = 1; x < 11; x++)
			{
				//�����
				if (board[y][x] == 1)
				{
					i++;
					//1�� 10���� �� ��� ����
					if (i == 10)
					{
						for (x = 1; x < 11; x++)
						{
							setCursor((x + 2) * 2, y + 2);
							printf("  ");
						}
						//�� �������� ��� ������
						countScore();
						array_down(y);
					}

				}
			}
		}
	}


}

int gameOver(int rotation)
{
	if (detect(rotation, 0, 0))
		return 5; //���� ��
	else
		return 0;
}

int gameWin(void)
{
	if (level == 10)
		return 1; //���ӽ�
	else
		return 0;
}

void moveBlock(void)
{

	int n;
	int kb;
	int prove;
	int winOver;//���Ӱ��
	srand(time(NULL));
	int c = 2;

	/*���� ����~��*/
	while (1)
	{

		initial(CBLOCK_X, CBLOCK_Y); //��� ���� ��ġ ��ǥ 

		// n=(rand()%RAND)*4;//��������
		//n=rand()%RAND;
		n = rand() % 7;//��� ��� ����
		n = n * 4;
		// n = 6;

		if (gameWin())
		{
			setCursor(35, 20);
			printf("GAME WIN");
			getchar();
			exit(1);
		}
		if (gameOver(n))
			break;


		/*��� �Ѱ� ��~�� �̵�*/
		while (1)
		{
			int ww = 0;
			int var;
			int k = 0;
			int tmp;
			/*��� �Ʒ��� �̵�*/

			while (!_kbhit())
			{
				//��� ��
				showBlock(n);
				//������ Ÿ��
				Sleep(DELAY + speed);
				//�Ʒ��̵��� 1�ִ��� Ȯ��
				if (detect(n, 0, 1) == 1)
				{
					ww = 1;
					boardConginition(n, 0, 0);//���� ���� �迭 1�߰�
					control();
					break;
				}
				removeBlock(n, 0, 1);  //board�迭 +1�� 
			}
			/*detect�Լ����� �迭�� 1�߽߰� ����*/
			if (ww == 1)
				break;

			kb = _getch();
			/*����Ű*/
			switch (kb)
			{
			case LEFT:
				removeBlock(n, -2, 0);
				showBlock(n);
				break;
			case RIGHT:
				removeBlock(n, 2, 0);
				showBlock(n);
				break;
			case UP:

				// ù�������Ѵ�.
				k = n / 4;
				k *= 4;

				// �������� ���������ΰ�?
				if ((n + 1) <= (k + 3))
				{
					k = n + 1;
				}

				prove = detect(k, 0, 0);
				if (prove == 0)
				{
					removeBlock(n, 0, 0);
					n = k;
					showBlock(n);
					break;
				}
				break;
			case DOWN:
				removeBlock(n, 0, 2);
				//showBlock(n);
				break;
			case SPACE:
				while (1)
				{
					removeBlock(n, 0, 1);
					if (detect(n, 0, 1) == 1)
					{
						showBlock(n);
						boardConginition(n, 0, 0);
						break;
					}

				}


			}

		}

	}

	setCursor(35, 20);
	printf("GAME OVER");
}




int main()
{
	removeCursor(); //Ŀ�� ������ ����

	setCursor(2, 1); //����ǥ�� ������ġ ����
	showBoard(); //���� ���
	scoreLevel();

	moveBlock(); //���� ��� ������

	getchar();

}

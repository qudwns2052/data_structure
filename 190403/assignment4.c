#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 20	// 큐의 최대 크기

int findex = -1;	// 큐의 첫번째 인덱스	(In index)
int sindex = 0;		// 큐의 두번째 인덱스	(Out index)
					// 큐는 FIFO이므로, 앞 뒤 각각을 가리키는 인덱스가 필요하다고 생각
char Queue[MAX_SIZE];	// 큐 생성

void ADDQUEUE(char ch)	// 큐에 데이터를 추가하는 함수
{
	if (findex - sindex >= MAX_SIZE -1)	// 큐가 꽉 찼으면
	{
		printf("ADDQUEUE(%c) Fail : Queue Full  Queue Size=20/20\n", ch);	// 큐에 데이터 추가 실패 메세지 출력
		return;
	}
	Queue[++findex] = ch;	// first 인덱스 증가 후 큐에 데이터 추가
	printf("ADDQUEUE(%c)	Queue Size=%d/20\n", ch, findex - sindex + 1);	// 큐에 데이터 추가 성공 메세지

}

void DELETEQUEUE(void)	// 큐에 데이터를 빼는 함수
{
	if (findex + 1 <= sindex)	// 큐가 비어있으면
	{
		printf("DELETEQUEUE() Fail : Queue Empty  Queue Size=0/20\n");	// 큐에 데이터 빼기 실패 메세지
		return;
	}

	printf("DELETEQUEUE() = %c, Queue Size=%d/20\n", Queue[sindex], findex - sindex);	// 큐에 데이터 빼기 성공 메세지
	sindex++;	// second 인덱스 증가

}

int main(void)
{
	char str[MAX_SIZE];	// 키보드로부터 입력 받은 내용을 저장할 배열
	int i;
	int num;	// 숫자 입력 시 num으로 변환 후 num 수만큼 DELETEQUEUE 진행
	int strLen;	// str 문자열의 길이를 계산할 변수

	while (1)
	{
		printf(">>> ");
		scanf("%s", str);	// scanf로 문자열 입력 받음
		strLen = strlen(str);	// str 문자열 길이 저장
		if (strLen > MAX_SIZE)	// 만약, 20글자가 넘으면
		{
			printf("입력 문자열 크기 : %d >>> ERROR (MAX_SIZE is 20)\n", strLen);	// 에러메세지 출력
			continue;	// 위에서부터 다시 진행
		}
		else if ('A' <= str[0] && str[0] <= 'Z')	// 만약, 문자열 맨 앞이 영어 대문자면 뒤에도 대문자라 가정 (예제에서 대문자로 입력하므로)
		{	
			for (i = 0; i < strLen; i++)
			{
				ADDQUEUE(str[i]);	// 큐에 하나씩 추가
			}
		}
		else if ('0' <= str[0] && str[0] <= '9')	// 만약, 문자열 맨 앞이 숫자면 문자열을 숫자로 가정
		{
			num = atoi(str);	// 문자열이 숫자이므로, 숫자로 변환
			for (i = 0; i < num; i++)	// num 만큼
			{
				DELETEQUEUE();	// 큐에서 하나씩 제거
			}
		}
		else   // 아니면, 잘못 입력 한 것으로 간주
		{
			printf("입력 문자열은 영어 대문자로 이루어져있습니다.\n");	// 에러 메세지 출력
			continue;	// 위에서부터 다시 진행
		}
		
	}

	system("pause");
	return 0;
}
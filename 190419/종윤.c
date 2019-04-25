#include<stdio.h>

void prime_number(int n) 
{
	int i, j, count = 0;
	int arr[100] = { 0};
	for (i = 2; i < n; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0) {
				break;
			}
			if (i == j) {
				arr[count] = i;
				count++;
			}
		}
	}
	for (i = 0; i < count; i++) 
	{
		printf("%d ", arr[i]);
	}
}

int main() {
	prime_number(100);

	int k;

	scanf("%d", &k);
	return 0;
}
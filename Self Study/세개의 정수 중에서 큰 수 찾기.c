#include <stdio.h>

int main() {
	int a;
	int b;
	int c;

	printf("3개의 정수를 입력하기: \n");
	scanf_s("%d %d %d", &a, &b, &c);

	if (a > b) {
		if (a > c) {
			printf("가장 큰 수는 %d입니다.\n", a);
		}
	}
	if (b > a) {
		if (b > c) {
			printf("가장 큰 수는 %d입니다.\n", b);
		}
	}
	if (c > a) {
		if (c > b) {
			printf("가장 큰 수는 %d입니다.\n", c);
		}
	}
	if (a == b && (a > c) || a == c && (a > b) || b == c && (b > a)) {
		printf("가장 크면서 같은 정수가 2개이상이 존재합니다.\n");
		if (a == b) {
			printf("가장 큰 수인 두개의 정수 %d\n", a);
			printf("첫번째 정수와 두번째 정수가 같습니다.\n");
		}
		if (b == c) {
			printf("가장 큰 수인 두개의 정수 %d\n", b);
			printf("두번째 정수와 세번째 정수가 같습니다.");
		}
		if (a == c) {
			printf("가장 큰 수인 두개의 정수 %d\n", c);
			printf("첫번째 정수와 세번째 정수가 같습니다\n.");
		}
	}
	else {
		printf("모든 정수가 동일합니다.\n");
	}
	printf("Program closed\n");
}

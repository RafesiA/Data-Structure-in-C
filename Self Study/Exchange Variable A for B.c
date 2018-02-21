#include <stdio.h>

int main() {
	int a = 100;
	int b = 111;
	int tmp;
	char scan;

	printf("Variable a value = %d\n", a);
	printf("Variable b value = %d\n\n", b);

	printf("Switching varaible a, b \n");
	printf("Continue? Y/N\n");
	scanf_s("%c", &scan);
	printf("Your answer is %c\n\n", scan);

	if (scan == 'Y' || scan == 'y') {
		tmp = a;
		a = b;
		b = tmp;
		printf("Successfully changed\n\n");
		printf("Variable a is now %d\n", a);
		printf("And Variable b is now %d\n", b);
		printf("Using Temp variable tmp value is %d\n", tmp);
	}
	else if (scan == 'N' || scan == 'n') {
		printf("You chosen No\n");
	}
	printf("Program ended successful");
	return 0;
}

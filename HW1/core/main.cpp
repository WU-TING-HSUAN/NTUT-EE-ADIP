#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int a(), b(), c();

int main() {
	int input;
	printf("½d¨Ò");
	printf("\n");
	printf("1 : HW1.2");
	printf("\n");
	printf("2 : HW1.3");
	printf("\n");
	printf("3 : HW2");
	printf("\n");
	printf("½Ð¿é¤J¸¹½X:");
	scanf("%d", &input);
	printf("\n");
	if (input == 1) {
		a();
	}
	if (input == 2) {
		b();
	}
	if (input == 3) {
		c();
	}
}
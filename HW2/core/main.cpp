#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int one_one(), one_two(), one_three(), two_one(), three_one(), five();

int main() {
	int input;
	printf("範例");
	printf("\n");
	printf("1 : HW2_1_1");
	printf("\n");
	printf("2 : HW2_1_2");
	printf("\n");
	printf("3 : HW2_1_3");
	printf("\n");
	printf("4 : HW2_1");
	printf("\n");
	printf("5 : HW3_1");
	printf("\n");
	printf("6 : HW5(請注意D8需要跑特別久，需等大概30秒)");
	printf("\n");
	printf("請輸入號碼:");
	scanf("%d",&input);
	printf("\n");
	if (input == 1) {
		one_one();
	}
	if (input == 2) {
		one_two();
	}
	if (input == 3) {
		one_three();
	}
	if (input == 4) {
		two_one();
	}
	if (input == 5) {
		three_one();
	}
	if (input == 6) {
		five();
	}
}
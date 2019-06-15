/*
	This program swaps vars without extra memory
*/

#include <stdio.h>

void swap(int *a, int *b);

int main() {
	int a = 16;
	int b = 25;
	printf("Before\n");
	printf("a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("After\n");
	printf("a = %d, b = %d\n", a, b);
	return 0;
}

void swap(int *a, int *b) {
	*a = *b - *a;
	*b = *b - *a;
	*a = *b + *a;
}
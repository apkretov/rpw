#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

void test1() {
	int a[] = { 0, 1, 2 };
	int b[][3] = { {0, 1, 2}, {3, 4, 5} };

	printf("*a = %d\n", *a);
	printf("*b[1] = %d\n", *b[1]);
}

typedef struct {
	char c;
	int i;
	double d;
} s;
s arrs[2];

typedef union {
	char c;
	int i;
	double d;
} u;
u arru[2];

void test2() {
	printf("arrs[1].c = %c\tarrs[1].i = %d\tarrs[1].d = %d\n", arrs[1].c, arrs[1].i, arrs[1].d);
	printf("arrs[1].c = %c\tarrs[1].i = %d\tarrs[1].d = %d\n", arru[1].c, arru[1].i, arru[1].d);

	printf("\nsizeof(s) = %d\n", sizeof(s));
	printf("sizeof(arrs) = %d\n", sizeof(arrs));

	printf("\nsizeof(u) = %d\n", sizeof(u));
	printf("sizeof(arru) = %d\n", sizeof(arru));
}

int main(int argc, char* agrv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	test1();
	test2();

	return 0;
}

#endif
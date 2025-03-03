#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	union {
		char c;
		int i;
		double d;
	} u;
	
	printf("sizeof u = %zd\n\n", sizeof u);

	u.c = 'a';
	putchar(u.c);

	u.i = 111;
	printf("\n\n%d\n", u.i);
	putchar(u.c);

	u.i = 1111;
	printf("\n\n%d\n", u.i);
	putchar(u.c);

	printf("\n\n%f\n", u.d);

	return 0;
}
#endif
#include <stdio.h>

#undef ON
#ifdef ON
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	f1();
	mine1();
	mine2();
}
#endif

static f1() {
	char *s = "hello, world";

	printf(":%10s:\n", s);
	printf(":%-10s:\n", s);
	printf(":%20s:\n", s);
	printf(":%-20s:\n", s);
	printf(":%20.10s:\n", s);
	printf(":%-20.10s:\n", s);
	printf(":%.10s:\n", s);
}

static mine1() {
	double d = 10.222222222222222;

	printf("\n%10.3lf\n", d);
	printf("%010.3lf\n", d);
	printf("%-10.3lf\n", d);
}

static mine2() {
	char s[] = "test string with %*s";
	int len = 5;

	printf("\n:%.*s:\n", len, s);
}
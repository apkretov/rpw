#include <stdio.h>
#pragma warning(disable:4996) // c++ - Remove secure warnings (_CRT_SECURE_NO_WARNINGS) from projects by default in Visual Studio - Stack Overflow @ https://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis
#include <locale.h>

static f1() {
	int i;
	float x;
	char name[50];

	(void)scanf("%d %f %s", &i, &x, name);
	printf("%d %f %s\n", i, x, name);
}

static f2() {
	int i;
	float x;
	char name[50];
	
	puts("Enter 56789 0123 45a72");
	(void)scanf("%2d %f %*d %2s", &i, &x, name); // 56789 0123 45a72 присвоит i значение 56, x - 789.0, пропустит 0123 и поместит в name строку "45".
	printf("scnaf 1: %d %f %s\n", i, x, name);
	(void)scanf("%s", name); // ѕри следующем обращении к любой процедуре ввода рассмотрение начнетс€ с буквы a.
	printf("scanf 2: %s\n", name);
}

static f3() { /* rudimentary desk calculator */
	double sum, v;
	sum = 0;
	while (scanf("%lf", &v) != EOF)
		printf("\t%.2f\n", sum += v);
}

static f4_eng() {
	int day, month, year;
	char monthname[20];

	printf("Enter day monthname year: ");
	if (scanf("%d %s %d", &day, monthname, &year) == 3)
		printf("%d %s %d\n", day, monthname, year);
	else {
		puts("Follow the pattern!");
		return;
	}
	
	printf("\nEnter month/day/year: ");
	if (scanf("%d/%d/%d", &month, &day, &year) == 3)
		printf("%d/%d/%d\n", month, day, year);
	else {
		puts("Follow the pattern!");
		return;
	}
}

#include "1_09.h"
static f5_eng() {
	int day, month, year;
	char monthname[20], line[512];

	printf("Enter 'day monthname year' or 'month/day/year': ");
	while (getline(line, sizeof(line)) > 0) {
		if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
			printf("valid: %s\n", line); /* 25 Dec 1988 form */
		else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
			printf("valid: %s\n", line); /* mm/dd/yy form */
		else
			printf("invalid: %s\n", line); /* invalid form */
	}
}

static mine1() {
	char c; // scanf_s | Programmer's Wiki | Fandom @ https://code.fandom.com/wiki/Scanf_s
	printf("Enter a letter: ");
	scanf_s("%c", &c, 1);
	printf("%c\n", c);
}

static mine2() {
	char s[4];
	printf("Enter a string: ");
	scanf_s("%s", s, 4);
	printf("%s\n", s);
}

static mine3() {
	char name[] = "temp111";
	int n;
	(void)sscanf(name, "temp%d", &n);
	printf("%d\n", n);
}

#undef ON
#ifdef ON
main() {
	setlocale(LC_ALL, "RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	//f1();
	//f2();
	//f3();
	//f4_eng();
	//f5_eng();
	//mine1();
	//mine2();
	mine3();
}
#endif
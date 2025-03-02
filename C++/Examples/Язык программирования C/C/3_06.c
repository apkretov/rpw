#include <stdio.h>
#include "3_05.h"

void itoa_3_06(n, s)   /*convert n to characters in s */
int n;
char s[];
{
	int i, sign;

	if ((sign = n) < 0)   /* record sign */
		n = -n;     /* make n positive */
	i = 0;
	do {    /* generate digits in reverse order */
		s[i++] = n % 10 + '0';/* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse_3_05(s);
}

#undef ON
#ifdef ON
int main(int argc, char* argv[]) {
	printf("\nFile: %s\tLine: %d\n", __FILE__, __LINE__);

	char s[512];
	int n = 1230456;

	itoa_3_06(n, s);
	printf("itoa_3_06(1230456): \"%s\"\n", s);
	
	return 0;
}
#endif

#undef EX_3_04
#ifdef EX_3_04

#include <stdio.h>
#include <limits.h>
#include "1_09.h"

#define LEN CHAR_BIT * sizeof(unsigned) 

static itob(unsigned n, char s[]) {
	const int base = 2;
	int i = 0;
	char in[LEN];
	do {
		in[i++] = n % base + '0';
	} while ((n /= base) > 0);
	in[i] = '\0';
	reverse_1_09(in, s);
    s = in;
}

static itoh(unsigned n, char s[]) {
	const int base = 16, dec = 10;
	int i = 0, h;
	char in[LEN];
	do {
		if ((h = n % base) < dec)
			in[i++] = h + '0';
		else
			in[i++] = h - dec + 'a';
	} while ((n /= base) > 0);
	in[i] = '\0';
	reverse_1_09(in, s);
    s = in;
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    unsigned n = 255;
    char b[LEN], h[LEN];

    printf("%d\n", n);

    itob(n, b);
    printf("%s\n", b);

    itoh(n, h);
    printf("%s\n", h);

    return 0;
}
#endif

#undef EX_3_04_1 // Solution by Paul Griffiths @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_5#Solution_by_Paul_Griffiths
#ifdef EX_3_04_1
#include <stdlib.h>
#include <stdio.h>
#include "3_05.h" //MINE for reverse().

void itob(int n, char s[], int b);
//ORIG void reverse(char s[]);

int main(void) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    char buffer[10];
    int i;

    for (i = 2; i <= 20; ++i) {
        itob(255, buffer, i);
        printf("Decimal 255 in base %-2d : %s\n", i, buffer);
    }
    return 0;
}

static void itob(int n, char s[], int b) { /*  Stores a string representation of integer n in s[], using a numerical base of b. Will handle up to base-36 before we run out of digits to use.  */
    static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //!!!
    int i, sign;

    if (b < 2 || b > 36) {
        fprintf(stderr, "EX_3_04_1: Cannot support base %d\n", b);
        exit(EXIT_FAILURE); //TEMPLATE
    }

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse_3_05(s);
}
#endif

#undef EX_3_04_2 // Solution by seankndy @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_5#Solution_by_seankndy
#ifdef EX_3_04_2

#include <stdio.h>
#include "3_05.h" //MINE for reverse().

void itob(int n, char s[], int b);
//ORIG void reverse(char s[]);

int main(void) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int n;
	char s[100];

	for (int i = 2; i <= 20; i++) {
		itob(255, s, i);
		printf("decimal 255 in base %-2d : %s\n", i, s);
	}

	return 0;
}

static void itob(int n, char s[], int b) {
	int i, sign, r;

	sign = n;
	i = 0;
	do {
		r = n % b;
		if (sign < 0)
			r = -r;
		s[i++] = (r > 9 ? (r - 10 + 'A') : (r + '0'));
	} while (n /= b);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	reverse_3_05(s);
}

/*ORIG
static void reverse(char s[]) {
	int i, j, t;

	for (j = 0; s[j] != '\0'; j++)
		;
	for (i = 0, --j; j > i; i++, j--) {
		t = s[j];
		s[j] = s[i];
		s[i] = t;
	}
}
*/
#endif

#undef EX_3_05
#ifdef EX_3_05

#define _CRT_SECURE_NO_WARNINGS // OR: #pragma warning(disable:4996) // For scanf vs. scanf_s. //TEMPLATE

#include <stdio.h>
#include "3_05.h"

#define MINWIDTH 8
#define MAXLEN 64

static void itoa_3_06(int n, char s[], int w) {
	int i = 0, sign;
	sign = n;
	if (sign < 0)
		n = -n;
	do // Compile the number string in a reverse order.
		s[i++] = n % 10 + '0';
	while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < w) // Pad spaces till the minimal width.
		s[i++] = ' ';
	s[i] = '\0';
	reverse_3_05(s);
}

int main(int argc, char* argv[]) {
	printf("File: %s\t Line: %d\n\n", __FILE__, __LINE__);

	char s[MAXLEN];
	int n;

	printf("Enter positive/negative numbers to convert to strings, EOF to terminate.\n");
	while (scanf("%d", &n) == 1) { // c - Using scanf in a while loop - Stack Overflow @ https://stackoverflow.com/questions/2970880/using-scanf-in-a-while-loop
		itoa_3_06(n, s, MINWIDTH);
		printf("%s\n", s);
	}

	return 0;
}
#endif
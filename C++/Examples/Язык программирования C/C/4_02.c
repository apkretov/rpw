#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAXLINE 512

#undef ON
#ifdef ON

#include "1_09.h"

main()  /* rudimentary desk calculator */
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	double sum, atof_4_02();
	char line[MAXLINE];

	sum = 0;
	while (getline(line, MAXLINE) > 0)
		printf("\t%.2f\n", sum += atof_4_02(line));
}
#endif

double atof_4_02(s) /* convert string s to double */
char s[];
{
	double val, power;
	int  i, sign;

	for (i = 0; s[i] == ' ' || s[i] == '\n' || s[i] == '\t'; i++)
		;       /* skip white space */
	sign = 1;
	if (s[i] == '+' || s[i] == '-')   /* sign */
		sign = (s[i++] == '+') ? 1 : -1;
	for (val = 0; s[i] >= '0' && s[i] <= '9'; i++)
		val = 10 * val + s[i] - '0';
	if (s[i] == '.')
		i++;
	for (power = 1; s[i] >= '0' && s[i] <= '9'; i++) {
		val = 10 * val + s[i] - '0';
		power *= 10;
	}
	return(sign * val / power);
}

#undef EX_4_02
#ifdef EX_4_02

#include <math.h>
#include <ctype.h>

#define EOF '\x4' // Ctrl + D for a string. //TEMPLATE
#define VAL(i, n) (n = n * 10 + s[i] - '0') //TEMPLATE

static double atofscien(const char s[]) {
	int i = 0, sign, signx = 1;
	double val = 0, valx = 0, power = 1;

	while (isspace(s[i])) // Skip spaces.
		++i;

	if (s[i] == '-') { // Define the sign.
		sign = -1;
		++i;
	}
	else if (s[i] == '+') {
		sign = 1;
		++i;
	}
	else
		sign = 1;

	for (; isdigit(s[i]); ++i) // The value before the decimal point.
		VAL(i, val);
	for (++i; isdigit(s[i]); ++i) { // The value after decimal point.
		power *= 10;
		VAL(i, val);
	}
	if (s[++i] == '-') { // Define the exponent sign.
		signx = -1;
		++i;
	}
	for (; isdigit(s[i]); ++i) // The exponent power value.
		VAL(i, valx);
	return sign * val / power * pow(10, signx * valx);

}

int main(int argc, char* argv[]) {
	printf("File: %s\t Line: %d\n\n", __FILE__, __LINE__);

	char s[MAXLINE];
	int r;

	printf("Enter number strings in a scientific notation, EOF to terminate.\n");
	r = scanf("%s", s);
	while (r == 1 && s[0] != EOF) { //TEMPLATE
		printf("String: %s\t Number: %f\n", s, atofscien(s));
		r = scanf("%s", s);
	}

	return 0;
}

#endif
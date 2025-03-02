#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include "1_09.h"

#ifdef ON

#define MAXLINE 512 /* maximum input line size */

int main() {  /* find longest line */
	setlocale(LC_ALL, "RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int len; /* current line length */
	int max; /* maximum length seen so far */
	char line[MAXLINE]; /* current input line */
	char save[MAXLINE]; /* longest line, saved */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(line, save);
		}
	if (max > 0) /* there was a line */
		printf("%s", save);

	return 0;
}
#endif

#undef EX_02_1

getline(s, lim) /* get line into s, return length */
char s[];
int lim; 
{
	int c = 0, i;
#ifndef EX_02_1
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
#else
	for (i = 0; i < lim - 1; ++i)
		if ((c = getchar()) != EOF)
			if (c != '\n')
				s[i] = c;
			else
				break;
		else
			break;
#endif
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return(i);
}

static copy(s1, s2) /* copy s1 to s2; assume s2 big enough */
char s1[], s2[]; {
	int i;

	i = 0;
	while ((s2[i] = s1[i]) != '\0')
		++i;
}

void reverse_1_09(char in[], char out[]) {
	int i = 0, j = 0;
	while (in[i] != '\0')
		++i;
	--i;
	while (i >= 0)
		out[j++] = in[i--];
	out[j] = '\0';
}

#undef EX_1_15
#ifdef EX_1_15

#define MINLEN 80
#define MAXLEN 1000

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, len = 0;
	char line[MAXLEN];
	while (len < MAXLEN - 1 && (c = getchar()) != EOF) {
		if (c != '\n')
			line[len++] = c;
		else {
			if (len >= MINLEN) {
				line[len] = '\0';
				printf("\n%s\n", line);
			}
			len = 0;
		}
	}
	return 0;
}
#endif

#undef EX_1_16 // Solution by vladkir @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_18#Solution_by_vladkir
#ifdef EX_1_16

#define MAXLEN 512

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, len = 0, i;
	char line[MAXLEN];
	
	while (len < MAXLEN - 1 && (c = getchar()) != EOF) {
		if (c != '\n')
			line[len++] = c;
		else {
			for (i = len - 1; i >= 0 && (line[i] == ' ' || line[i] == '\t'); --i)
				;
			if (i >= 0) {
				line[i + 1] = '\0';
				printf("%s|\n", line);
			}
			len = 0;
		}
	}
}
#endif

#undef EX_1_17
#ifdef EX_1_17
#define MAXLEN 512
int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s[] = "Check", rev[MAXLEN];
	reverse_1_09(s, rev);
	printf("%s\t%s", s, rev);
}
#endif

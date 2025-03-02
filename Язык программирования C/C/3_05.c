#include "2_03_3.h"

/* ORIG
reverse_3_05(s)    // reverse string s in place
char s[];
*/
void reverse_3_05(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen_2_03_3(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

#undef EX_3_02
#ifdef EX_3_02

#include <stdio.h>
#include <ctype.h>
#include "1_09.h"

#define MAXLEN 512

static void expand(const char s1[], char s2[]) {
	int i = 0, j = 0;
	char c;

	while (s1[i] != '\0') {
		if (s1[i] == '-' && i > 0 && isalnum(s1[i + 1]) && s1[i - 1] < s1[i + 1]) { // Skip a leading or trailing hyphen. Embracing a hyphen, the characters must be positioned in an ascending order.
			if (isdigit(s1[i - 1]) && isdigit(s1[i + 1]) || isalpha(s1[i - 1]) && isalpha(s1[i + 1])) { // Both empbracing characters must be of the same kind: a digit or a letter.
				for (c = s1[i - 1] + 1; c < s1[i + 1]; ++c)
					s2[j++] = c;
				++i;
				continue;
			}
		}
		s2[j++] = s1[i++];
	}
	s2[j] = '\0';

	return;
}

int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s1[MAXLEN], s2[MAXLEN];

	while (getline(s1, MAXLEN) > 0) {
		expand(s1, s2);
		printf("%s\n", s2);
	}

	return 0;
}

#endif

#undef ON
#ifdef ON

#include <stdio.h>

main() { /* count digits, white space, others */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int  c, i, nwhite, nother;
	int  ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;

	printf("digits =");
	for (i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf("\nwhite space = %d, other = %d\n", nwhite, nother);
}
#endif

#undef EX_1_12 // ENG: EX_1_13
#ifdef EX_1_12
#include <stdio.h>

#define MAXLEN 20

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c;
	int len[MAXLEN], nc = 0;

	for (int i = 0; i < MAXLEN; ++i)
		len[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n')
			++nc;
		else if (nc > 0) {
			++len[nc < MAXLEN ? nc - 1 : MAXLEN - 1];
			nc = 0;
		}
	}

	for (int i = 0; i < MAXLEN; ++i) {
		printf("\n%2d: ", i + 1);
		for (int j = 0; j < len[i]; ++j)
			printf("|");
	}
}
#endif
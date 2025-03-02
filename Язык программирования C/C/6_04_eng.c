#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "6_03.h"

static struct key {
	char* word;
	int  count;
} keytab[] = {
	"break", 0,
	"case", 0,
	"char", 0,
	"continue", 0,
	"default", 0,
	/* ... */
	"unsigned", 0,
	"while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(struct key))

int getword(char*, int);
struct key* binsearch(char*, struct key*, int);

#undef ON
#ifdef ON
main() { /* count C keywords; pointer version */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char word[MAXWORD];
	struct key* p;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((p = binsearch(word, keytab, NKEYS)) != NULL)
				p->count++;
	for (p = keytab; p < keytab + NKEYS; p++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
	return 0;
}
#endif

/* binsearch: find word in tab[0]...tab[n-1] */
struct key* binsearch(char* word, struct key* tab, int n)
{
	int cond;
	struct key* low = &tab[0];
	struct key* high = &tab[n];
	struct key* mid;
	while (low < high) {
		mid = low + (high - low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}
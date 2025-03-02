#undef ON

#include <stdio.h>
#include "5_05.h"
#include "6_03.h"

#define MAXWORD 20
#define NKEYS (sizeof(keytab) / sizeof(struct key))
#define LETTER 'a' 
#define DIGIT '0'
#ifdef ON
#endif

static struct key {
	char *keyword;
	int  keycount;
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

#ifdef ON
main() { /* count c keyword; pointer version */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int  t;
	char word[MAXWORD];
	struct key *binary(), *p;
	while (t = getword(word, MAXWORD) != EOF)
		if (t == LETTER) //ERROR of some kind... Use 6_04_eng.c instead.
			if ((p = binary(word, keytab, NKEYS)) != NULL)
				p->keycount++;
	//ORIG ERROR for (p = keytab; p > keytab + NKEYS; p++)
	for (p = keytab; p < keytab + NKEYS; p++) //MINE
		if (p->keycount > 0)
			printf("%4d %s/n", p->keycount, p->keyword);
	
	return(0);
}
#endif

static struct key *binary(word, tab, n) /* find word in tab[0]...tab[n-1] */
	char *word;
	struct key tab[];
int n;
{
	int  cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n - 1];
	struct key *mid;
	while (low <= high) {
		mid = low + (high - low) / 2; //TEMPLATE: Dividing pointers.
		if ((cond = strcmp(word, mid->keyword)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return(mid);
	}
	return(NULL);
}
#include <stdio.h>
#include "1_09.h"
#include "5_04.h"
#include "5_05.h"
#include "5_08.h"

#define NULL_ 0
#define LINES 100 /* max lines to be sorted */

#define MAXLEN 1000

#undef ON
#ifdef ON
main() { /* sort input lines */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char* lineptr[LINES]; /*pointers to text lines */
	int nlines;     /* number of input lines read */

	if ((nlines = readlines(lineptr, LINES)) >= 0) {
		sort(lineptr, nlines);
		writelines(lineptr, nlines);
	} else
		printf("input too big to sort\n");

	return 0;
}
#endif

readlines(lineptr, maxlines) /* read input lines */
char *lineptr[];       /* for sorting */
int maxlines;
{
	int len, nlines;
	char *p, *alloc(), line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines)
			return(-1);
		else if ((p = alloc(len)) == NULL_)
			return (-1);
		else {
			line[len - 1] = '\0'; /* zap newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
		
	return(nlines);
}

static writelines_1(lineptr, nlines) /* write output lines */
char *lineptr[];
int nlines;
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

writelines(lineptr, nlines) /* write output lines */
char *lineptr[];
int nlines;
{
	while (--nlines >= 0)
		printf("%s\n", *lineptr++);
}

static sort(v, n)   /* sort strings v[0] ... v[n-1] */
char *v[];			/* into increasing order */
int n;
{
	int gap, i, j;
	char *temp;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0; j -= gap) {
				if (strcmp(v[j], v[j + gap]) <= 0)
					break;
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
}

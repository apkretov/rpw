#include <stdio.h>
#include "4_02.h"
#include "5_05.h"
#include "5_08.h"

#define LINES 100 /* max number of lines to be sorted */

#undef ON
#ifdef ON
main(argc, argv) /* sort input lines */
int argc;
char *argv[];
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char *lineptr[LINES]; /* pointers to text lines */
	int nlines; /* number of input lines read */
	int strcmp(), numcmp(); /* comparsion functions */
	int swap(); /* exchange function */
	int numeric = 0; /* 1 if numeric sort */

	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n')
		numeric = 1;
	if (nlines = readlines(lineptr, LINES) >= 0) {
		if (numeric)
			sort(lineptr, nlines, numcmp, swap);
		else
			sort(lineptr, nlines, strcmp, swap);
		writelines(lineptr, nlines); //ERROR: Only one line is written. Use 5_12_eng.c instead.
	} else
		printf("input too big to sort\n");
}
#endif

static sort(v, n, comp, exch) /* sort strings v[0] ... v[n-1] */ //ERROR: It does not sort. Use 5_12_eng.c instead.
char *v[];           /* into increasing order */
int n;
int(*comp)(), (*exch)();
{
	int gap, i, j;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0; j -= gap) {
				if ((*comp)(v[j], v[j + gap]) <= 0)
					break;
				(*exch)(&v[j], &v[j + gap]);
			}
}

static numcmp(s1, s2) /* compare s1 and s2 numerically */
char *s1, *s2;
{
	double atof_4_02(), v1, v2;

	v1 = atof_4_02(s1);
	v2 = atof_4_02(s2);
	if (v1 < v2)
		return(-1);
	else if (v1 > v2)
		return(1);
	else
		return (0);
}

static swap(px, py) /* interchange *px and *py */
char *px[], *py[];
{
	char *temp;

	temp = *px;
	*px = *py;
	*py = temp;
}

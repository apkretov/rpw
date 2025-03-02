#include <stdio.h> // c:\_\apk\My_Docs\_06\Misc\Books, courses\C++\язык программировани€ C\The C Programming Language- Brian W. Kernighan, Dennis M. Ritchie.pdf @ page 140.
#include <string.h>
#include "5_08.h" //MINE

#define MAXLINES 5000 /* max #lines to be sorted */

char* lineptr[MAXLINES]; /* pointers to text lines */
//ORIG int readlines(char* lineptr[], int nlines);
//ORIG void writelines(char* lineptr[], int nlines);

void qsort_5_12_eng(void* lineptr[], int left, int right, int (*comp)(void*, void*));
int numcmp(char*, char*);

#undef ON
#ifdef ON
int main(int argc, char* argv[]) { /* sort input lines */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort_5_12_eng((void**)lineptr, 0, nlines - 1, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}
#endif

static void qsort_5_12_eng(void* v[], int left, int right, int (*comp)(void*, void*)) { /* qsort: sort v[left]...v[right] into increasing order */
	int i, last;
	void swap(void* v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_5_12_eng(v, left, last - 1, comp);
	qsort_5_12_eng(v, last + 1, right, comp);
}

#include <stdlib.h>
static int numcmp(char* s1, char* s2) { /* numcmp: compare s1 and s2 numerically */
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

static void swap(void* v[], int i, int j) {
	void* temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
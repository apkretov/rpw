#include <stdio.h>
#include "4_05.h"

#define SIZE 3

static swap(px, py)    /* interchange *px and *py */
int* px, * py;
{
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}

#undef ON
#ifdef ON
int main(int agrc, char* agrv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int n, v, array[SIZE];

	for (n = 0; n < SIZE && getint(&v) != EOF; n++)
		array[n] = v;
	for (n = 0; n < SIZE; ++n)
		printf("%d\t", array[n]);
}
#endif

static getint(pn) /* get next integer from input */
int* pn;
{
	int c, sign;

	while ((c = getch()) == ' ' || c == '\n' || c == '\t') /* skip white space */
		; 
	sign = 1;
	if (c == '+' || c == '-') { /* record sign */
		sign = (c == '+') ? 1 : -1;
		c = getch();
	}
	for (*pn = 0; c >= '0' && c <= '9'; c = getch())
		*pn = 10 * *pn + c - '0';
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	
	return(c);
}
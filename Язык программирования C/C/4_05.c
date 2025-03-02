#include <stdio.h>
#include "4_05.h" // For #defines there.

#define BUFSIZE  100
static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0; /* next free position in buf */

getch() { /* get a (possibly pushed back) character */
	return((bufp > 0) ? buf[--bufp] : getchar());
}

ungetch(c)  /* push character back on input */
int c;
{
	if (bufp > BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

getop(s, lim) /* get next operator or operand */
char s[];
int lim;
{
	int i, c;

	while ((c = getch()) == ' ' || c == '\t' || c == '\n')
		;
	if (c != '.' && (c < '0' || c > '9'))
		return(c);
	s[0] = c;
	for (i = 1; (c = getchar()) >= '0' && c <= '9'; i++)
		if (i < lim)
			s[i] = c;
	if (c == '.') {   /* collect fraction */
		if (i < lim)
			s[i] = c;
		for (i++; (c = getchar()) >= '0' && c <= '9'; i++)
			if (i < lim)
				s[i] = c;
	}
	if (i < lim) { /* number is ok */
		ungetch(c);
		s[i] = '\0';
		return (NUMBER);

	} else { /* it's too big; skip rest of line */
		while (c != '\n' && c != EOF)
			c = getchar();
		s[lim - 1] = '\0';
		return (TOOBIG);
	}
}
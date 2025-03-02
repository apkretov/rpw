#include <stdio.h>

#define NULL 0  /* pointer value for error report */
#define ALLOCSIZE 1000  /* size of available space */

static char allocbuf[ALLOCSIZE];/* storage for alloc */
static char* allocp = allocbuf; /* next free position */

char* alloc(n)  /* return pointer to n characters */
int n;
{
	if (allocp + n <= allocbuf + ALLOCSIZE) {
		allocp += n;
		return(allocp - n); /* old p */
	} else         /* not enough room */
		return(NULL);
}

free_5_04(p)    /* free storage pointed by p */
char* p;
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

strlen_5_04(s)       /* return length of string s */
char* s;
{
	char* p = s;

	while (*p != '\0')
		p++;
	return(p - s);
}
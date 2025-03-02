#include <stdio.h>
#include "5_05.h"

#define SIZE 256

#undef ON
#ifdef ON
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char* t = "tttttttt";
	char s[SIZE];

	strcpy(s, t);
	printf("t\t%s\n", t);
	printf("s\t%s\n\n", s);
	
	printf("strcmp(s, t) = %d\n", strcmp(s, t));
	printf("strcmp(s, \"aaaaaaaaa\") = %d\n\n", strcmp(s, "aaaaaaaaa"));

	printf("strcmp_pointer_mine(s, t) = %d\n", strcmp_pointer_mine(s, t));
	printf("strcmp_pointer_mine(s, \"aaaaaaaaa\") = %d\n",   strcmp_pointer_mine(s, "aaaaaaaaa"));
	printf("strcmp_pointer_mine(s, \"zzzzzzzzz\") = %d\n\n", strcmp_pointer_mine(s, "zzzzzzzzz"));

	printf("strcmp_pointer_mine(s, \"zaaaaaaaa\") = %d\n",   strcmp_pointer_mine(s, "zaaaaaaaa"));
	printf("strcmp_pointer_mine(s, \"azzzzzzzz\") = %d\n\n", strcmp_pointer_mine(s, "azzzzzzzz"));

	printf("strcmp_pointer_mine(s, \"aaaaaaaaz\") = %d\n", strcmp_pointer_mine(s, "aaaaaaaaz"));
	printf("strcmp_pointer_mine(s, \"zzzzzzzza\") = %d\n", strcmp_pointer_mine(s, "zzzzzzzza"));

	return 0;
}
#endif

static strcpy_array(s, t)    /* copy t to s */
char s[], t[];
{
	int i;
	i = 0;
	while ((s[i] = t[i]) != '\0')
		i++;
}

static strcpy_pointer_1(s, t)  /* copy t to s; pointer version 1 */
char *s, *t;
{
	while ((*s = *t) != '\0') {
		s++;
		t++;
	}
}

static strcpy_pointer_2(s, t)  /* copy t to s; pointer version 2 */
char *s, *t;
{
	while ((*s++ = *t++) != '\0')
		;
}

strcpy(s, t) /* copy t to s; pointer version 3 */ /*MINE: strcpy_pointer_3*/
char *s, *t;
{
	while (*s++ = *t++)
		;
}


static strcmp_array(s, t) /* return <0 if s<t, 0 if s==t, >0 if s>t */
char s[], t[];
{
	int i;

	i = 0;
	while (s[i] == t[i])
		if (s[i++] == '\0')
			return(0);
	return(s[i] - t[i]);
}

int strcmp(s, t) /* return <0 if s<t, 0 if s==t, >0 if s>t */ /*MINE: strcmp_pointer*/
char *s, *t;
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return(0);
	return(*s - *t);
}


static strcmp_pointer_mine(s, t)
char *s, *t;
{
	for (; *s && *s == *t; ++s, ++t)
		;
	return (*s - *t);
}

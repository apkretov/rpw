#include <stdio.h>
#include "5_04.h"
#include "5_05.h"

#define NULL 0

char *strsave(s) /* save string s somewhere */
char *s;
{
	char *p, *alloc();

	if ((p = alloc(strlen_5_04(s) + 1)) != NULL)
		strcpy(p, s);
	return(p);
}

static *strsave_unrecommended(s) /* save string s somewhere */ {
	char *p;

	if ((p = alloc(strlen_5_04(s) + 1)) != NULL)
		strcpy(p, s);
	return(p);
}

#undef ON
#ifdef ON
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char* p;

	p = strsave("correct");
	printf("%s\n", p);
	free_5_04(p);

	p = strsave_unrecommended("unrecommended");
	printf("%s\n", p);
	free_5_04(p);

	return 0;
}
#endif
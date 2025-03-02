#undef ON
#ifdef ON

#include <stdio.h>
#include <ctype.h> // isupper - C++ Reference @ http://www.cplusplus.com/reference/cctype/isupper/

main() { /* convert input to lower case */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c;

	while ((c = getchar()) != EOF)
		putchar(isupper(c) ? tolower(c) : c);
}
#endif
#undef ON
#ifdef ON

#include <stdio.h>

main() { /* copy input to output; 2nd version */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c;

	while ((c = getchar()) != EOF)
		putchar(c);
}

#endif
#include <stdio.h>

#undef ON
#ifdef ON
main(argc, argv) /* echo arguments; 3rd version */
int argc;
char *argv[];
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	while (--argc > 0)
		printf((argc > 1) ? "%s " : "%s\n", *++argv);
}
#endif
#include <stdio.h>

#undef ON
#ifdef  ON
main(argc, argv) /* echo arguments; 2nd version */
int argc;
char *argv[];
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	while (--argc > 0)
		printf("%s%c", *++argv, (argc > 1) ? ' ' : '\n');
}
#endif 

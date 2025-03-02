#include <stdio.h>

#undef ON
#ifdef ON
main(int argc, char* argv[]) { /* echo arguments; 1st version */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int i;

	for (i = 1; i < argc; i++)
		printf("%s%c", argv[i], (i < argc - 1) ? ' ' : '\n');
}
#endif

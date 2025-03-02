#include <stdio.h>
#include <stdlib.h>
#include "7_06.h"

#undef ON
#ifdef ON
main(argc, argv)  /*cat: concatenate files*/
int argc;
char* argv[]; {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	FILE* fp, * fopen();
	if (argc == 1)  /*no args; copy standard input*/
		filecopy(stdin);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "cat: can't open,%s\n", *argv);
				(void)getchar(); // MINE
				exit(1);
			} else {
				filecopy(fp);
			}
	exit(0);
}
#endif
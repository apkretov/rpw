#include <stdio.h>
#include "7_06.h"

#define getchar() getc(stdin) // Функции getchar и putchar могут быть определены в терминалах getc, putc, stdin и stdout следующим образом:
#define putchar(c) putc(c, stdout)

filecopy(fp)  /*copy file fp to standard output*/
FILE* fp;
{
	int c;
	while ((c = getc(fp)) != EOF)
		putc(c, stdout);
}

#undef ON
#ifdef ON
main(argc, argv) /*cat: concatenate files*/
int argc;
char* argv[];
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	FILE* fp, * fopen();
	
	if (argc == 1) /*no args; copy standard input*/
		filecopy(stdin);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("cat: can't open %s\n", *argv);
				break;
			} else {
				filecopy(fp);
				fclose(fp);
			}
}
#endif

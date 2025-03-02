#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // 7.6 Error Handling - Stderr and Exit @ The C Programming Language- Brian W. Kernighan, Dennis M. Ritchie.pdf, page 193.

#undef ON
#ifdef ON
int main(int argc, char* argv[]) { /* cat: concatenate files, version 2 */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	FILE* fp;
	void filecopy(FILE*, FILE*);
	char* prog = argv[0]; /* program name for errors */
	if (argc == 1) /* no args; copy standard input */
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}
			else {
				filecopy(fp, stdout);
				fclose(fp);
			}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}
#endif
//ORIG #include "syscalls.h"
int lseek(int, long, int); //MINE: Forward explicit declarations as per Qt warnings.
int read(int, char*, int);

static int get(int fd, long pos, char *buf, int n) { /*get: read n bytes from position pos */
	if (lseek(fd, pos, 0) >= 0) /* get to pos */
		return read(fd, buf, n);
	else
		return -1;
}

#include <stdio.h>
#include <stdlib.h>		
#include <fcntl.h>

#define PERMS 0666 /* RW for owner, group, others */
#define FILENAME "Makefile"
#define POS 100L
#define N 200

#undef LIN
#ifdef LIN
int main() {
	int f1, n;
	char buf[BUFSIZ]; //TEMPLATE

	if ((f1 = open(FILENAME, O_RDONLY, 0)) == -1) {
		fprintf(stderr, "Can't open %s...\n", FILENAME);
		exit(EXIT_FAILURE);
	}
	if ((n = get(f1, POS, buf, N)) >= 0)
		printf("File %s contains the following %d characters from position %ld onwards:\n\n%s\n\n", FILENAME, n, POS, buf);
	else
		exit(EXIT_FAILURE);

	return 0;
}
#endif

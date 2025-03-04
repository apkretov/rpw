//C - Error Handling @ https://www.tutorialspoint.com/cprogramming/c_error_handling.htm
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main () {
	FILE* pf;
	int errnum;
	pf = fopen("unexist.txt", "rb"); //In order to open a file as a binary file, a "b" character has to be included in the mode string. @ http://www.cplusplus.com/reference/cstdio/fopen/
	if (pf == NULL) {
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
	} else
		fclose (pf);
	return 0;
}

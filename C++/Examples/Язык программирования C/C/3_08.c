#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h> // For strcmp() & strcpy().
#include "1_09.h"

#undef ON
#ifdef ON

#define MAXLINE 512 /* maximum input line size */

int main() {  /* find longest line */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char line[MAXLINE]; /* current input line */
	char save[MAXLINE] = ""; /* longest line, saved */

	while (getline(line, MAXLINE) > 0) {

		if (strcmp(line, save))
			printf("%s", line);
		strcpy(save, line);
	}
	return 0;
}
#endif

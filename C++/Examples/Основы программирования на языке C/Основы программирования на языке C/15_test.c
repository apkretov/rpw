#ifdef ON

#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>

/* getenv example: getting path */ // getenv @ https://cplusplus.com/reference/cstdlib/getenv/
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* getenv */

int main() {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char *pPath;
	pPath = getenv("PATH");
	if (pPath != NULL)
		printf("The current path is: %s\n", pPath);
	
	return 0;
}
#endif

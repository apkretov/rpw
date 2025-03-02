#include <stdio.h>

#ifdef ON
main () {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int a[] = {0, 10, 20};
	int* pa = &a;
	printf("%d\n", *(++pa));
	getchar();
	return 0;
}
#endif

static strlen_5_03(s)       /* return length of string s */
char *s;
{
	int n;

	for (n = 0; *s != '\0'; s++)
		n++;
	return(n);
}
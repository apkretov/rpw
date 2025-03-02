#include <stdio.h>
#include "1_09.h"

#define MAXLINE 512

#undef ON
#ifdef ON

main()  /* find all lines matching a pattern */
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char line[MAXLINE];

	while (getline(line, MAXLINE) > 0)
		if (index(line, "the") >= 0)
			printf("%s", line);
}
#endif

index(s, t) /* return index of t in s, -1 if none */
char s[], t[];
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (t[k] == '\0')
			return(i);
	}
	return(-1);
}

#undef EX_4_01
#ifdef EX_4_01

#include <string.h>

static int rindex(const char s[], const char t[]) {
	int i, j, k, len;
	
	len = strlen(t);
	if (len == 0)
		return -1;
	for (i = strlen(s) - len - 1; i >= 0; --i) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
			;
		if (t[k] == '\0')
			return i;
	}
	
	return -1;
}

int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	
	char line[MAXLINE];
	int r;
	
	while (getline(line, MAXLINE) > 0)
		if ((r = rindex(line, "the")) >= 0)
			printf("rindex: %d\tline: %s", r, line);

	return 0;
}

#endif
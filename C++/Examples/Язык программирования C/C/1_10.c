#undef ON
#ifdef ON

#include <stdio.h>
#define MAXLINE 1000   /* max. input line size*/

char line[MAXLINE];  /* input line */
char save[MAXLINE]; /* longest line saved here*/
int max; /*length of longest line seen so far*/

main() { /*find longest line; specialized version*/
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int len;
	extern int max;
	extern char save[];
	max = 0;

	while ((len = getline()) > 0)
		if (len > max) {
			max = len;
			copy();
		}
	if (max > 0)  /* there was a line */
		printf("%s", save);
	return 0;
}

#define EX_1_18
#ifdef EX_1_18
static getline() {
	int c, i = 0;
	
	while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')	
		line[i++] = '\n';
	line[i] = '\0';
	
	return(i);
}
#endif

#ifndef EX_1_18
static getline() { /* specialized version */
	int c, i;
	extern char line[];

	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	//ORIG ERR ++i;
	if (c == '\n') //MINE
		line[i++] = '\n'; //MINE
	line[i] = '\0';
	return(i);
}
#endif

static copy() { /* specialized version */
	int i;
	extern char line[], save[];

	i = 0;
	while ((save[i] = line[i]) != '\0')
		++i;
}
#endif
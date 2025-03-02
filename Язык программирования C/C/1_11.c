#undef EX_1_19
#ifdef EX_1_19

#include <stdio.h>

#define TABSIZE 8

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c != '\t')
			putchar(c);
		else {
			for (int i = nc; i <= TABSIZE; ++i)
				printf("%d", i);
			nc = 0;
		}
		if (nc == TABSIZE || c == '\n')
			nc = 0;
	}
}
#endif

#undef EX_1_20
#ifdef EX_1_20

#define TABSIZE 8

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, len = 0, i;

	while ((c = getchar()) != EOF) {
		if (c != ' ') {
			if (len > 0) {
				entab(len);
				len = 0;
			}
			putchar(c);
		} else
			++len;
	}
	return 0;
}

static entab(int len) {
	for (int i = 0; i < len / TABSIZE; ++i) {
		putchar('\t');
		putchar('|');
	}
	for (int i = 0; i < len % TABSIZE; ++i) {
		putchar(' ');
		putchar('|');
	}
}
#endif

#undef EX_1_21 // As per note 10.
#ifdef EX_1_21
#define MAXLINE 40
#define MAXWORD 1000
#define YES 1
#define NO 0

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, lenword = 0, lenline = 0, inword = NO;
	char word[MAXWORD];

	while ((c = getchar()) != EOF && lenword <= MAXWORD) {
		++lenline;
		if (c == ' ') { // Space?
			if (lenline > MAXLINE) { // Not in line?
				putchar('\n');
				lenline = 0;
			}
			if (inword) { // After a symbol?
				printWord(word, &lenword, &lenline);
			} 
			putchar(c);
			inword = NO;
		} else {
			if (c == '\n') { // Enter?
				if (inword) // Print a word before enter.
					printWord(word, &lenword, &lenline);
				putchar(c);
				inword = NO;
				lenline = 0;
			} else {
				word[lenword++] = c;
				inword = YES;
			}
		}
	}

	if (inword) // Print the last word.
		printWord(word, &lenword, &lenline);

	return 0;
}

static printWord(const char word[], int* lenword, int* lenline) {
	if (*lenline > MAXLINE) { // Will not the word and the space after it be in line?
		putchar('\n');
		*lenline = 0;
	}

	for (int i = 0; i < *lenword; ++i)
		putchar(word[i]);
	*lenline += (*lenword + 1);
	*lenword = 0;
}
#endif

#undef EX_1_21_1 // Solution by Rckskio @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_22#Solution_by_Rckskio
#ifdef EX_1_21_1
#include <stdio.h>
#define LINELENGTH	50	/* n-th column of input */

int main(void) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int i, c;
	i = 0;
	while ((c = getchar()) != EOF) {
		++i;
		putchar(c);
		if (i >= LINELENGTH && c == ' ') {
			putchar('\0');
			i = 0;
			putchar('\n');
		}
	}
	return 0;
}
#endif

#undef EX_1_22
#ifdef EX_1_22

//A test program:
//int a; // a
//int b; /* b and other variables */
//int c; /* c and other variables */ int d; /* d */

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	const char slash = '/', asterick = '*';
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == slash) {
			c = getchar();
			if (c == slash) { // Skip an entire comment line.
				while (getchar() != '\n')
					;
				putchar('\n');
			} else if (c == asterick) // Skip a comment block till its closing end.
				while (!(getchar() == asterick && getchar() == slash))
					;
		} else
			putchar(c);
	}
	
	return 0;
}
#endif

#undef EX_1_23
#ifdef EX_1_23

#include <stdio.h>
#include <stdbool.h> // Use of bool in C - GeeksforGeeks @ https://www.geeksforgeeks.org/bool-in-c/

// c++ - Multi-line DEFINE directives? - Stack Overflow @ https://stackoverflow.com/questions/6281368/multi-line-define-directives
//Test programs:
#define PROG "int a; /* a */\n"\
	"int b; /* b and other variables */\n"\
	"int c; /* c and other variables */ int d; /* d */"

// Error.
//#define PROG "int a; /* a */\n"\
//	"int b; /* b and other variables \n"\
//	"int c; /* c and other variables */ int d; /* d */"

//#define PROG "int a; // a\n"

//#define PROG "int b; /* b and other variables */\n"
//#define PROG "int b; /* b and other variables \n" // Error.

static char* checkComments(char* pProg) { // Check a comment block. Return the pointer to the end of the comment. Otherwise return the pointer to '\0';
	const char slash = '/', asterick = '*';
	char c;

	printf("\nValidating the comment:\n");
	c = *(++pProg);
	if (c == slash) { // Skip an entire comment line.
		while ((c = *(++pProg)) != '\n' && c != '\0') {
			putchar(c);
		}
	} else if (c == asterick) { // Skip a comment block till its closing end.
		while (!((c = *(++pProg)) == asterick && (c = *(++pProg)) == slash) && c != '\0') {
			putchar(c);
		}
		if (c == '\0')
			printf("\nError: the block comment is not closed - no closing '*/'\n");
	}
	return pProg;
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	const char* prog = PROG;
	char* pProg = prog;
	char c;
	
	printf("The program:\n%s\n\n", prog);

	while ((c = *pProg) != '\0') {
		switch (c) {
		case '/':
			pProg = checkComments(pProg);
			break;
		case '(':
			//TO DO: Find the closing counterpart.
			break;
		case '{':
			//TO DO: Find the closing counterpart.
			break;
		case '[':
			//TO DO: Find the closing counterpart.
			break;
		case '\'':
			//TO DO: Find the closing counterpart.
			break;
		case '"':
			//TO DO: Find the closing counterpart.
			break;
		}
		++pProg;
	}

	return 0;
}
#endif
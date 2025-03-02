#include <stdio.h>
#include "1_09.h"
#include "4_01.h"

#define MAXLINE 1000

#undef ON
#ifdef ON
main(argc, argv) /* find pattern from first argument */
int argc;
char *argv[];
{
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char line[MAXLINE], c;
	long lineno = 0;
	int except = 0, number = 0;
	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) { /*Язык программирования С. Брайан Керниган, Деннис Ритчи.pdf, page 129 @ https://codernet.ru/books/c_plus/yazyk_programmirovaniya_c_brajan_kernigan_dennis_ritchi/ */
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				break;
			}
		}
	}
	if (argc != 1)
		printf("usage: find -x -n pattern\n");
	else
		while (getline(line, MAXLINE) > 0) {
			lineno++;
			if ((index(line, *argv) >= 0) != except) {
				if (number)
					printf("%ld: ", lineno);
				printf("%s", line);
			}
		}
}
#endif
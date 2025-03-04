#ifdef ON

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>

int main() { // strtok @ https://cplusplus.com/reference/cstring/strtok/
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

#ifdef _1

	char str[] = "- This, a sample string.";
	char* pch;

	printf("Splitting string \"%s\" into tokens:\n", str);
	pch = strtok(str, " ,.-");
	while (pch != NULL) {
		printf("%s\n", pch);
		pch = strtok(NULL, " ,.-");
	}

#elif !_2

	typedef struct {
		int i;
		double d;
		char c;
	} s;

	typedef union {
		int i;
		double d;
		char c;
	} u;

	s arrs[10] = {{1, 2.0, 'a'}};
	u arru[10] = {{1}};

	for (size_t i = 0; i < 10; ++i)
		printf("%d ", arrs[i].i);
	puts("");

	for (size_t i = 0; i < 10; ++i)
		printf("%d ", arru[i].i);
	puts("");

#endif

	return 0;
}

#endif
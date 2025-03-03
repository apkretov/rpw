#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

void main() {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int a = 10;
	printf("%d", ++a);
}

#endif

// 11
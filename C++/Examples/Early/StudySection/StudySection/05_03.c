#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int b;

int main() {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	
	int c;
	return 0;
}

int a;
#endif
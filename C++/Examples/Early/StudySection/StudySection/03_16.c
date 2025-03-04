#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main(void) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int a = 9;
	float x;

	x = a / 2;
	printf("%f", x);
	
	return 0;
}
#endif

// 4.000000
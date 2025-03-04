#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int i = 10, j = 20;
	if (i = 5) && if (j = 10)
		printf("Have a nice day");
	return 0;
}
#endif
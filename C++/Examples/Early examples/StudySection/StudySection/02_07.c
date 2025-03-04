#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	void show() {
		printf("SKY");
	}
	
	show();

	return 0;
}
#endif
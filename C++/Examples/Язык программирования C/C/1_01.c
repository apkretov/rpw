#ifdef ON

#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "RU"); //TEMPLATE
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__); //TEMPLATE

	printf("hello, world!\n");
	
	return 0;
}
#endif

#ifdef EX_1_02

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	printf("Start\n");
	printf("\a"); // Sound.
	printf("\nEnd\n");
}
#endif
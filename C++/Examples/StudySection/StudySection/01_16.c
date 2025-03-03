#define ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char arr[5] = "The End";
	
	printf("%s", arr);

	return 0;
}
#endif

// The E╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╠╜╛Oо♣e
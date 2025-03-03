#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

void f(const int arr[]) { // an array argument
	printf("*arr = %d\n", *arr);
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	const int id = 0; // an identifier
	const int arr[] = {0, 1, 2}; // an array

	printf("id = %d\n", id);
	printf("arr[0] = %d\n", arr[0]);
	f(arr);

	return 0;
}
#endif

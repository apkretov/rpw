#ifndef ON

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char str[] = "Hello, world! How are you today?"; // В Си какой функцией можно выделить из строки лексемы, разделенные любым из множества символов, входящих во вторую заданную строку? @ https://gptgo.ai
	char delim[] = " ,!"; // разделители

	char *token = strtok(str, delim); // получаем первую лексему

	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, delim); // получаем следующую лексему
	}

	return 0;
}

#endif

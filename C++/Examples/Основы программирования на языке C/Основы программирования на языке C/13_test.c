#ifndef ON

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char str[] = "Hello, world! How are you today?"; // � �� ����� �������� ����� �������� �� ������ �������, ����������� ����� �� ��������� ��������, �������� �� ������ �������� ������? @ https://gptgo.ai
	char delim[] = " ,!"; // �����������

	char *token = strtok(str, delim); // �������� ������ �������

	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, delim); // �������� ��������� �������
	}

	return 0;
}

#endif

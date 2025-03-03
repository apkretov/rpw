#undef ON
#ifdef ON

#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	auto int a = 10;
	
	{
		auto int a = 15;
		printf("%d ", a);
	}
	printf("%d", a);

	return 1;
}
#endif
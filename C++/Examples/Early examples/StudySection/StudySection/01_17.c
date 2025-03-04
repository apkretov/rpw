#undef ON
#ifdef ON
#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int a = 0, b = 1, c = 3, ans;
	
	ans = (a == 0 ? (b == 1 ? 3 : 5) : 0);
	printf("ans = %d\n", ans);
	
	return 0;
}
#endif

// ans = 3
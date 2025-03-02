#undef ON
#ifdef ON

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char c;
	c = getchar();
	putchar(c);
	return 0;
}
#endif

#undef EX_1_07
#ifdef EX_1_07

#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, prev = 0;
	while((c = getchar()) != EOF) {
		if (c == ' ' && prev == ' ')
			continue;
		prev = c;
		putchar(c);
	}
	return 0;
}

#endif

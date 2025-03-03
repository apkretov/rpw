#undef ON
#ifdef ON

void mine() {
	printf("#include can be placed at any position in a file.\n");
}

int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	mine();
	return 0;
}

#include <stdio.h>

#endif

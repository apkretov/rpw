#include <stdio.h>
#include <locale.h>

static union utype {
	int i;
	float f;
	//OFF double d; // 8 bytes // the structure is big enough to hold the ``widest'' member @ The C Programming Language- Brian W. Kernighan, Dennis M. Ritchie.pdf, page 177.
	char c;
	char* cp;
};
typedef union utype u;

static struct stype {
	int i;
	float f;
	//OFF double d; // 8 bytes
	char c;
	char* cp;
};
typedef struct stype s;

#undef ON
#ifdef ON
main() {
	setlocale(LC_ALL, "RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	mine1();
	//mine2();
	
	return 0;
}
#endif

static mine1() {
	printf("size of utype:\t%d\nsize of stype:\t%d\n\n\n", sizeof(u), sizeof(s));
}

static mine2() {
	u uarr[2];
	s sarr[2];
	char carr[] = "ab";

	printf("sizeof(uarr):\t%d\n", sizeof(uarr));
	printf("sizeof(sarr):\t%d\n\n", sizeof(sarr));

	printf("&(int)uarr[0]: %d\n", (int)&uarr[0]);
	printf("&(int)uarr[1]: %d\n", (int)&uarr[1]);
	printf("(int)&uarr[1] - (int)&uarr[0]:\t%d\n\n", (int)&uarr[1] - (int)&uarr[0]);

	printf("&(int)sarr[0]: %d\n", (int)&sarr[0]);
	printf("&(int)sarr[1]: %d\n", (int)&sarr[1]);
	printf("(int)&sarr[1] - (int)&sarr[0]:\t%d\n\n", (int)&sarr[1] - (int)&sarr[0]);

	printf("sizeof(carr):\t%d\n", sizeof(carr));
	printf("carr addresses:\t%d\t%d\t%d\n\n", (int)&carr[0], (int)&carr[1], (int)&carr[2]);
}

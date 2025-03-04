//Определение порядка байтов @https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D1%80%D1%8F%D0%B4%D0%BE%D0%BA_%D0%B1%D0%B0%D0%B9%D1%82%D0%BE%D0%B2#%D0%9E%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BF%D0%BE%D1%80%D1%8F%D0%B4%D0%BA%D0%B0_%D0%B1%D0%B0%D0%B9%D1%82%D0%BE%D0%B2
//Endianness @ https://en.wikipedia.org/wiki/Endianness

#include <stdio.h>

unsigned short x = 1; /* 0x0001 */

int main(void) {
	printf("unsigned short x = %d\n", x);
	printf("*((unsigned char *) &x) = %d\n", *((unsigned char *) &x));
	printf("Endianness is %s.\n\n", *((unsigned char *) &x) == 0 ? "big-endian" : "little-endian");

	printf("sizeof(char) = %lu\n", sizeof(char));
	printf("sizeof(short) = %lu\n", sizeof(short));
	printf("sizeof(int) = %lu\n", sizeof(int));
	printf("sizeof(long) = %lu\n", sizeof(long));
	printf("sizeof(long long) = %lu\n\n", sizeof(long long));

	printf("sizeof(float) = %lu\n", sizeof(float));
	printf("sizeof(double) = %lu\n", sizeof(double));
	printf("sizeof(long double) = %lu\n", sizeof(long double));

	return 0;
}

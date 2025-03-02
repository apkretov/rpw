#undef ON
#ifdef ON

#include <iostream>
using std::cout;
using std::endl;

#include <bitset>
using std::bitset;

#define BITS 16

static bitset<BITS> getbits(unsigned x, unsigned p, unsigned n) { /* get n bits from position p */ 
	cout << bitset<BITS>(x) << endl;
	cout << bitset<BITS>(~(~unsigned(0) << n)) << endl;
	cout << bitset<BITS>(x >> (p + 1 - n)) << endl;

	return x >> (p + 1 - n) & ~(~unsigned(0) << n);
	//a = ~TYPE(0) >> (BITS - n);
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << getbits(0707, 6, 3) << endl;
	return 0;
}
#endif

#undef EX_2_05
#ifdef EX_2_05

#include <iostream>
using std::cout;
using std::endl;

#include <bitset>
using std::bitset;

#define BITS 32

static bitset<BITS> getbits(unsigned x, unsigned p, unsigned n) {
	cout << bitset<BITS>(x) << endl;
	/*OFF
	cout << bitset<BITS>(~(~unsigned(0) >> n)) << endl;
	cout << bitset<BITS>(x << (p + 1 - n)) << endl;
	*/
	return x << (p + 1 - n) & ~(~unsigned(0) >> n);
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << getbits(0307070707070707070707, 6, 3) << endl;
	return 0;
}
#endif

#undef EX_2_06
#ifdef EX_2_06

#include <iostream>
using std::cout;
using std::endl;
using std::oct; // Output Formatting @ http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html
using std::dec;

#include <bitset>
using std::bitset;

#include <climits> // For CHAR_BIT = 8.

static void wordlength(int n) {
	const unsigned bytes = sizeof(int);
	const unsigned bits = bytes * CHAR_BIT;

	cout << "Bit format of octal number " << oct << n << ": " << bitset<bits>(n) << endl;
	cout << "Bytes in int: " << dec << bytes << endl;
	cout << "Bits in int: " << bits << endl;
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int n = 0107070;
	wordlength(n);
	return 0;
}
#endif

#undef EX_2_07
#ifdef EX_2_07
#include <iostream>
using std::cin;
using std::cout;
using std::oct;
#include <bitset>
using std::bitset;
#include <climits>

#define BITS CHAR_BIT * 2

static void rightrot() {
	const int b = 3;
	unsigned short n = 0707;
	unsigned short mask;
	
	cout << "Octal n: " << oct << n << "\nBinary n: " << bitset<BITS>(n) << '\n';
	mask = ~(~unsigned short(0) << b) << BITS - b;
	cout << "\nRotating mask: " << bitset<BITS>(mask) << '\n';
	n = n >> b | mask; /* n >>= b; n |= mask; // std::byte - cppreference.com @ https://en.cppreference.com/w/cpp/types/byte */
	cout << "Octal n: " << n << "\nBinary n: " << bitset<BITS>(n) << '\n';
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	rightrot();
	return 0;
}
#endif

#undef EX_2_07_1 // Solution by Bob Wightman (Cat 1) @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_2:Exercise_8#Solution_by_Bob_Wightman_(Cat_1)
#ifdef EX_2_07_1

#include <stdio.h>
#include <limits.h>

static unsigned int rightrot(unsigned int x, unsigned int n) {
	size_t s = sizeof(x) * CHAR_BIT; /* calculate number of bits in type */ //!!!
	size_t p;

	if (n < s) /* limit shift to range 0 - (s - 1) */ //!!!
		p = n;
	else
		p = n % s;

	if ((0 == x) || (0 == p)) /* if either is zero then the original value is unchanged */
		return x;
	return (x >> p) | (x << (s - p));
}

int main(void) { /* Driver based on yours but runs the shift values beyond the size of an unsigned integer on any system */
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	unsigned int val;
	unsigned int pos;
	unsigned int max = sizeof(pos) * CHAR_BIT + 1;

	for (val = 0; val < 700; val += 49) 
		for (pos = 0; pos < max; ++pos)	
			printf("%u, %d: %u\n", val, pos, rightrot(val, pos));
}
#endif

#undef EX_2_07_2 // Solution by Cromagnon (Category 1) @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_2:Exercise_8#Solution_by_Cromagnon_(Category_1)
#ifdef EX_2_07_2

#include <stdio.h>
#include <limits.h>

#define TYPE   char //!!!
#define SAMPLE 0XAB
#define NUM    3

static unsigned TYPE rightrot(unsigned TYPE x, TYPE n) { /* rightrot: rotate to the right by n bit positions */
	unsigned int s;

	s = sizeof x * CHAR_BIT; //!!!
	n = n % s;
	return (x >> n) | (x << (s - n));
}

int main(void) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	printf("%X\n", rightrot(SAMPLE, NUM));
	return 0;
}
#endif

#undef EX_2_08
#ifdef EX_2_08

#include <iostream>
using std::cout;
#include <bitset>
using std::bitset;
#include <climits>

#define TYPE unsigned char
#define BITS CHAR_BIT * sizeof(TYPE)

static TYPE invert(TYPE x, const int p, const int n) {
	TYPE m;
	m = ~TYPE(0);
	m >>= (BITS - n);
	m <<= (p - n);
	cout << bitset<BITS>(m) << '\n';
	return x ^ m;

}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	TYPE x;
	const int p = 6, n = 4;
	x = 0b00001111;
	cout << bitset<BITS>(x) << '\n';
	
	x = invert(x, p, n);
	cout << bitset<BITS>(x) << '\n';
	
	return 0;
}
#endif
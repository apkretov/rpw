#undef ON
#ifdef ON

#include <iostream>
using std::cout;
#include <bitset>;
using std::bitset;
#include <climits>

void constexpr_and_Constant_Expressions() {
	bool b = 42; //	b is true
	int i = b; // i has value 1
	i = 3.14; // i has value 3
	double pi = i; // pi has value 3.0
	unsigned char c = -1; // assuming 8-bit	chars, c has value 255
	signed char c2 = 256; // assuming 8-bit	chars, the value of	c2 is undefined

	cout << c << "\t\t" << c2 << '\n';
	cout << bitset<CHAR_BIT>(c) << '\t' << bitset<CHAR_BIT>(c2) << '\n';
	cout << int(c) << "\t\t" << int(c2) << '\n';
}

void f2() {
	unsigned u = 10;
	int i = -42;
	
	std::cout << i + i << std::endl; // prints -84
	std::cout << u + i << std::endl; // if 32-bit ints, prints 4294967264
}

void f3() {
	unsigned u1 = 42, u2 = 10;
	std::cout << u1 - u2 << std::endl; // ok: result is 32
	std::cout << u2 - u1 << std::endl; // ok: but the result will wrap around
}

void f4() {
	for (int i = 10; i >= 0; --i)
		std::cout << i << std::endl;
}

void f5() {
	// WRONG: u can never be less than 0; the condition will always succeed
	for (unsigned u = 10; u >= 0; --u)
		std::cout << u << std::endl;
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//f1();
	//f2();
	//f3();
	//f4();
	f5();

	return 0;
}
#endif

#undef EX_02_04
#ifdef EX_02_04

#include <iostream>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	unsigned u = 10, u2 = 42;

	std::cout << u2 - u << std::endl;
	std::cout << u - u2 << std::endl << std::endl;
	
	int i = 10, i2 = 42;

	std::cout << i2 - i << std::endl;
	std::cout << i - i2 << std::endl;
	std::cout << i - u << std::endl;
	std::cout << u - i << std::endl;

	//MINE
	unsigned u3 = 0 - 1;
	std::cout << std::endl << u3 << std::endl;
}

#endif
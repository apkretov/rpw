#ifdef ON

#include <iostream>
#include <bitset>
#include "../../stdafx.h"
using namespace std;

void Defining_and_Initializing_bitsets() {
	bitset<32> bitvec(1U); // 32 bits; low-order bit is 1, remaining bits are 0
	cout << "bitset<32> bitvec(1U) = " << bitvec << '\n'; //MINE
}

void Initializing_a_bitset_from_an_unsigned_Value() {
	bitset<13> bitvec1(0xbeef); // bits are 1111011101111 // bitvec1 is smaller than the initializer; high-order bits from the initializer are discarded
	bitset<20> bitvec2(0xbeef); // bits are 00001011111011101111 // bitvec2 is larger than the initializer; high-order bits in bitvec2 are set to zero
	bitset<128> bitvec3(~0ULL); //TEST! //																													bits 0 . . . 63 are one; 63 . . . 127 are zero // on machines with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 ones

	//MINE
	cout << "bitset<13> bitvec1(0xbeef) = " << bitvec1 << '\n';
	cout << "bitset<20> bitvec2(0xbeef) = " << bitvec2 << '\n';
	cout << "bitset<128> bitvec3(~0ULL) = " << bitvec3 << '\n';
}

void Initializing_a_bitset_from_a_string() {
	bitset<32> bitvec4("1100"); //TEST //																													bits 2 and 3 are 1, all others are 0
	cout << R"(bitset<32> bitvec4("1100") = )" << bitvec4 << '\n'; //MINE

	string str("1111111000000011001101");
	bitset<32> bitvec5(str, 5, 4); //TEST //																												four bits starting at str[5], 1100
	bitset<32> bitvec6(str, str.size() - 4); //TEST //																										use last four characters

	//MINE
	cout << "\nstr = " << str;
	cout << "\tstr.size() = " << str.size() << '\n';
	cout << "bitset<32> bitvec5(str, 5, 4) = " << bitvec5 << '\n';
	cout << "bitset<32> bitvec6(str, str.size() - 4) = " << bitvec6 << '\n';
}

int main() {
	print_file_line();

	//Defining_and_Initializing_bitsets();
	//Initializing_a_bitset_from_an_unsigned_Value();
	Initializing_a_bitset_from_a_string();
}
#endif

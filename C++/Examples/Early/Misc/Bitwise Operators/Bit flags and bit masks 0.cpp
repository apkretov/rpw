//3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
#include "stdafx.h"

void definingBitBlagsInCpp14() { //Because C++14 supports binary literals, this is easiest in C++14:
	const unsigned char option0 = 0b0000'0001; // represents bit 0 // Define 8 separate bit flags (these can represent whatever you want)
	const unsigned char option1 = 0b0000'0010; // represents bit 1
	const unsigned char option2 = 0b0000'0100; // represents bit 2 
	const unsigned char option3 = 0b0000'1000; // represents bit 3
	const unsigned char option4 = 0b0001'0000; // represents bit 4
	const unsigned char option5 = 0b0010'0000; // represents bit 5
	const unsigned char option6 = 0b0100'0000; // represents bit 6
	const unsigned char option7 = 0b1000'0000; // represents bit 7
}

void definingBitBlagsInCpp11OrEarlier1() { //Because C++11 doesn’t support binary literals, we have to use other methods to set the symbolic constants.
	const unsigned char option0 = 0x1; // hex for 0000 0001 // Define 8 separate bit flags (these can represent whatever you want)
	const unsigned char option1 = 0x2; // hex for 0000 0010
	const unsigned char option2 = 0x4; // hex for 0000 0100
	const unsigned char option3 = 0x8; // hex for 0000 1000
	const unsigned char option4 = 0x10; // hex for 0001 0000
	const unsigned char option5 = 0x20; // hex for 0010 0000
	const unsigned char option6 = 0x40; // hex for 0100 0000
	const unsigned char option7 = 0x80; // hex for 1000 0000
}

void definingBitBlagsInCpp11OrEarlier2() {
	const unsigned char option0 = 1 << 0; // 0000 0001 // Define 8 separate bit flags (these can represent whatever you want)
	const unsigned char option1 = 1 << 1; // 0000 0010
	const unsigned char option2 = 1 << 2; // 0000 0100
	const unsigned char option3 = 1 << 3; // 0000 1000
	const unsigned char option4 = 1 << 4; // 0001 0000
	const unsigned char option5 = 1 << 5; // 0010 0000
	const unsigned char option6 = 1 << 6; // 0100 0000
	const unsigned char option7 = 1 << 7; // 1000 0000
}

int main() {
    
	return 0;
}


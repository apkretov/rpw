#include "stdafx.h" //3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
#include <iostream>

int main() {
	const unsigned char isHungry = 1 << 0; // 0000 0001 // Define a bunch of physical/emotional states
	const unsigned char isSad = 1 << 1; // 0000 0010
	const unsigned char isMad = 1 << 2; // 0000 0100
	const unsigned char isHappy = 1 << 3; // 0000 1000
	const unsigned char isLaughing = 1 << 4; // 0001 0000
	const unsigned char isAsleep = 1 << 5; // 0010 0000
	const unsigned char isDead = 1 << 6; // 0100 0000
	const unsigned char isCrying = 1 << 7; // 1000 0000
 
	unsigned char me = 0; // all flags/options turned off to start
	me |= isHappy | isLaughing; // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing
 
	std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n'; // Query a few states (we'll use static_cast<bool> to interpret the results as a boolean value rather than an integer)
	std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';
 
	return 0;
}
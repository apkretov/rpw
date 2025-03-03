#ifdef ON

#include <iostream>
#include <bitset>
#include <format>
#include "../../stdafx.h"
using namespace std;

void Operations_on_bitsets() { //TEST //MINE: See all the operations.
	bitset<32> bitvec(1U); // 32 bits; low-order bit is 1, remaining bits are 0
	{
		cout << "bitset<32> bitvec(1U): " << bitvec << '\n'; //MINE

		cout << boolalpha; //MINE
		bool is_set = bitvec.any(); // true, one bit is set
		cout << "bitvec.any(): " << is_set << '\n'; //MINE

		bool is_not_set = bitvec.none(); // false, one bit is set
		cout << "bitvec.none(): " << is_not_set << '\n'; //MINE

		bool all_set = bitvec.all(); // false, only one bit is set
		cout << "bitvec.all(): " << all_set << '\n'; //MINE

		size_t onBits = bitvec.count(); // returns 1
		cout << "bitvec.count(): " << onBits << '\n'; //MINE

		size_t sz = bitvec.size(); // returns 32
		cout << "bitvec.size(): " << sz << '\n'; //MINE

		bitvec.flip(); // reverses the value of all the bits in bitvec
		cout << "bitvec.flip(): " << bitvec << '\n'; //MINE

		bitvec.reset(); // sets all the bits to 0
		cout << "bitvec.reset(): " << bitvec << '\n'; //MINE

		bitvec.set(); // sets all the bits to 1
		cout << "bitvec.set(): " << bitvec << "\n\n"; //MINE
	}
	{
		bitvec.flip(0); // reverses the value of the first bit
		cout << "bitvec.flip(0): " << bitvec << '\n'; //MINE

		bitvec.set(bitvec.size() - 1); // turns on the last bit
		cout << "bitvec.set(bitvec.size() - 1): " << bitvec << '\n'; //MINE

		bitvec.set(0, 0); // turns off the first bit
		cout << "bitvec.set(0, 0): " << bitvec << '\n'; //MINE

		size_t i = 1; //MINE
		bitvec.reset(i); // turns off the ith bit
		cout << "i = " << i << "\tbitvec.reset(i): " << bitvec << '\n'; //MINE

		bitvec.test(0); // returns false because the first bit is off
		cout << "bitvec.test(0): " << bitvec.test(0) << '\n'; //MINE
	}
	{
		bitvec[0] = 0; // turn off the bit at position 0
		cout << "\nbitvec[0] = 0: " << bitvec << '\n'; //MINE

		bitvec[31] = bitvec[0]; // set the last bit to the same value as the first bit
		cout << "bitvec[31] = bitvec[0]: " << bitvec << '\n';

		bitvec[0].flip(); // flip the value of the bit at position 0
		cout << "bitvec[0].flip(): " << bitvec << '\n';

		~bitvec[0]; // equivalent operation; flips the bit at position 0
		cout << "~bitvec[0]: " << ~bitvec[0] << '\n';

		bool b = bitvec[0]; // convert the value of bitvec[0] to bool
		cout << "bool b = bitvec[0]: " << b << '\n';
	}
}

void Retrieving_the_Value_of_a_bitset() {
	//MINE
	auto bitvec3 = bitset<32>(string("1111"));
	cout << "bitvec3 = " << bitvec3 << '\n';

	unsigned long ulong = bitvec3.to_ulong();
	cout << "ulong = " << ulong << endl;
}

void bitset_IO_Operators() {
	bitset<16> bits;
	cout << "Enter up to 16 1 or 0 characters: ";
	cin >> bits; //TEST! //																																			read up to 16 1 or 0 characters from cin
	cout << "bits: " << bits << endl; // print what we just read
}

void Using_bitsets() { //TEST //MINE: See all the operations.
	bool status;
	using bs = bitset<30>;

	unsigned long quizA = 0; // this value is used as a collection of bits // version using bitwise operators
	cout << "bs(quizA): " << bs(quizA) << '\n'; //MINE
	quizA |= 1UL << 27; // indicate student number 27 passed
	cout << "quizA |= 1UL << 27: " << bs(quizA) << '\n'; //MINE
	status = quizA & (1UL << 27); // check how student number 27 did
	cout << format("quizA & (1UL << 27): {}\n", status); //MINE
	quizA &= ~(1UL << 27); // student number 27 failed
	cout << "quizA &= ~(1UL << 27): " << bs(quizA) << '\n'; //MINE

	bitset<30> quizB; // allocate one bit per student; all bits initialized to 0 // equivalent actions using the bitset library
	cout << "\nquizB: " << quizB << '\n'; //MINE
	quizB.set(27); // indicate student number 27 passed
	cout << "quizB.set(27): " << quizB << '\n'; //MINE
	status = quizB[27]; // check how student number 27 did
	cout << format("quizB[27]: {}\n", status); //MINE
	quizB.reset(27); // student number 27 failed
	cout << "quizB.reset(27): " << quizB << '\n'; //MINE
}

int main() {
	print_file_line();

	//Operations_on_bitsets();
	//Retrieving_the_Value_of_a_bitset();
	//bitset_IO_Operators();
	Using_bitsets();
}
#endif

#ifdef EX_17_10

#include <iostream>
#include <bitset>
#include "../../stdafx.h">
using namespace std;

int main() {
	print_file_line();

	constexpr size_t bits = 22;
	bitset<bits> n1(string("1000000010000100101110"));
	bitset<bits> n2;
	cout << "n1 = " << n1 << '\n';
	cout << "n2 = " << n2 << '\n';

	n2.set(1);
	n2.set(2);
	n2.set(3);
	n2.set(5);
	n2.set(8);
	n2.set(13);
	n2.set(21);
	cout << "n2 = " << n2 << '\n';
}
#endif

#ifdef EX_17_11_1

#include <iostream>
#include <bitset>
#include <format>
#include "../../stdafx.h">
using namespace std;

class Resp {
public:
	void set(size_t pos) {
		n.set(pos);
	}

	bool test(size_t pos) const {
		return n.test(pos);
	}

	void print(ostream &os) const {
		os << n;
	}
private:
	constexpr static size_t size = 10;
	bitset<size> n;
};

int main() {
	print_file_line();

	Resp resp;
	resp.print(cout); cout << '\n';
	resp.set(9);
	resp.print(cout); cout << '\n';
	cout << format("resp.test(9) = {}\n", resp.test(9));
}
#endif

#ifdef EX_17_11_2 // ch17/ex17_11_12_13.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch17/ex17_11_12_13.cpp

#include "../../stdafx.h"> 
#include "17_02_2.h" 
using namespace std;

int main() {
	print_file_line();

	string s = "1010101";
	Quiz<10> quiz(s);
	cout << quiz << endl;
}
#endif

#ifdef EX_17_13 // ch17/ex17_11_12_13.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch17/ex17_11_12_13.cpp

#include "../../stdafx.h"
#include "17_02_2.h" 
using namespace std;


void testMoveCtor() { //MINE
	timer t;
	for (size_t i = 0; i < 1000; i++) {
#ifdef _1
		Quiz<1000> quiz(string("101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101"));
#else //_2
		string s("101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101101010110101011010101");
		Quiz<1000> quiz(s);
#endif
	}
}

void EX_17_13_1() {
	constexpr size_t sz = 10;
	Quiz<sz> corAnswer(string("1010001101"));
	Quiz<sz> stuAnswer(string("1010101001"));

	cout << AS_KV(corAnswer) << '\n';
	cout << AS_KV(stuAnswer) << '\n';

	cout << AS_KV(grade(corAnswer, stuAnswer)) << '\n';
}

int main() {
	print_file_line();

	EX_17_13_1();
	
	cout << '\n';
	testMoveCtor();
}
#endif

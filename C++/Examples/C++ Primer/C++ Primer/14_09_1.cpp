#ifdef ON

#include <iostream>
#include <string>
#include <numbers>
#include "../../stdafx.h"
using namespace std;

void Defining_a_Class_with_a_Conversion_Operator() {
	class SmallInt { //VER1
	public:
		SmallInt(int i = 0) : val(i) {
			cout << "\nConstructor"; //MINE
			printThis();
			if (i < 0 || i > 255)
				throw out_of_range("Bad SmallInt value");
		}

		SmallInt(const SmallInt &s) : val(s.val) { //MINE
			cout << "\nCopy constructor";
			printThis();
		}

		explicit SmallInt(SmallInt &&s) noexcept : val(s.val) { //MINE
			cout << "\nMove constructor";
			printThis();
		}

		SmallInt &operator=(const SmallInt &rhs) { //MINE
			cout << "\nCopy-assignment operator";
			printThis();
			val = rhs.val;
			printThis();
			return *this;
		}

		SmallInt &operator=(SmallInt &&rhs) noexcept { //MINE
			cout << "\nMove-assignment operator";
			printThis();
			val = rhs.val;
			printThis();
			return *this;
		}

		void printThis() const { //MINE
			cout << "\nthis = " << this << "\tval = " << val;
		}

		operator int() const { //TEST!!
			cout << "\nint conversion operator"; //MINE
			printThis(); //MINE
			return val;
		}

		//MINE
		explicit operator double() const { //TEST!!
			cout << "\ndouble conversion operator";
			printThis();
			return val;
		}
	private:
		size_t val;
	};

#ifndef _1
	cout << "SmallInt si:"; //MINE
	SmallInt si;
	cout << "\n\nsi.printThis():"; //MINE
	si.printThis(); //MINE

	cout << "\n\nsi = 4:"; //MINE
	si = 4; //TEST! //																																												implicitly converts 4 to SmallInt then calls SmallInt::operator=
	cout << "\n\nsi.printThis():"; //MINE
	si.printThis(); //MINE

	cout << "\n\nsi + 3 ="; //MINE
	//ORIG si + 3; //TEST! // 																																										implicitly converts si to int followed by integer addition
	cout << si + 3; //MINE
	cout << "\n\nsi.printThis():"; //MINE
	si.printThis(); //MINE

	//MINE
	cout << "\n\nauto res1 = si + 3";
	auto res1 = si + 3;
	cout << "\nres1 = " << res1;

	//MINE
	cout << "\n\nauto res2 = 3 + si";
	auto res2 = 3 + si;
	cout << "\nres2 = " << res2;

	//MINE
	cout << "\n\nauto res3 = numbers::pi + static_cast<double>(si)";
	auto res3 = numbers::pi + static_cast<double>(si); //TEST!!
	cout << "\nres3 = " << res3;
	cout << '\n';

	cout << '\n';

#elif! _2
	cout << "SmallInt si = 3.14:\n"; //MINE
	// the double argument is converted to int using the built-in conversion
	SmallInt si = 3.14; //TEST //																																									calls the SmallInt(int) constructor

	cout << "\nsi + 3.14 =\n"; //MINE
	// the SmallInt conversion operator converts si to int;
	//ORIG si + 3.14; // that int is converted to double using the built-in conversion
	cout << si + 3.14 << '\n';
#endif

#ifdef OFF
	{
		class SmallInt;
		operator int(SmallInt &); // error: nonmember
		class SmallInt {
		public:
			int operator int() const; // error: return type
			operator int(int = 0) const; // error: parameter list
			operator int *() const { return 42; } // error: 42 is not a pointer
		};

	}
#endif
}

void explicit_Conversion_Operators() {
	class SmallInt { //VER2
	public:
		SmallInt(int i = 0) : val(i) {
			if (i < 0 || i > 255)
				throw out_of_range("Bad SmallInt value");
		}

		explicit operator int() const { //TEST!!! //																																			the compiler won’t automatically apply this conversion
			return val;
		}
		// other members as before
	private:
		size_t val;
	};

	SmallInt si = 3; // ok: the SmallInt constructor is not explicit
	//TEST! si + 3; //																																											error: implicit is conversion required, but operator int is explicit
	static_cast<int>(si) + 3; //TEST! //																																						ok: explicitly request the conversion
}

int main(int argc, char *argv[]) {
	print_file_line();

	Defining_a_Class_with_a_Conversion_Operator();
	//explicit_Conversion_Operators();

	return 0;
}
#endif
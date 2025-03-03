#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

#ifndef constexpr_Constructors
	class Debug {
	public:
		//ORIG constexpr Debug(bool b = true) : hw(b), io(b), other(b) {} //TEST!!
		explicit constexpr Debug(bool b = true) : hw(b), io(b), other(b) {} //TEST!! //MINE
		constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {} //TEST!!
		
		//ORIG constexpr bool any() { 
		constexpr bool any() const { //MINE //TEST!!
			return hw || io || other; 
		} 
		
		void set_io(bool b) { 
			io = b; 
		}

		void set_hw(bool b) { 
			hw = b; 
		}

		void set_other(bool b) { 
			hw = b; 
		}

	private:
		bool hw; // hardware errors other than IO errors
		bool io; // IO errors
		bool other; // other errors
	};

	//ORIG constexpr Debug io_sub(false, true, false); // debugging IO
	//ORIG if (io_sub.any()) // equivalent to if(true)
	if (constexpr Debug io_sub(false, true, false); io_sub.any()) //TEST! //MINE // debugging IO // equivalent to if(true)
		cerr << "print appropriate error messages" << endl;
	
	//ORIG constexpr Debug prod(false); // no debugging during production
	//ORIG if (prod.any()) // equivalent to if(false)
	if (constexpr Debug prod(false); prod.any()) //MINE // no debugging during production // equivalent to if(false)
		cerr << "print an error message" << endl;
#endif

	return 0;
}

#endif

#ifdef EX_07_55

#include <iostream>
#include <string>
using namespace std;

struct Data1 {
	constexpr Data1(string s_init) : s(s_init) {}
	string s;
};

struct Data2 {
	constexpr Data2(char s_init) : s(s_init) {}
	char s;
};

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	/* you.com
	The reason the second code works compared to the first code is that the second code uses a `char` parameter in the constructor of the `Data` struct, while the first code uses a `string` parameter.
	In C++, a `constexpr` variable must be initialized with a constant expression that can be evaluated at compile - time.In the first code, the `constexpr Data d("abc")` statement tries to initialize a `Data` object with a non - constant expression, as the string `"abc"` is not a constant expression.This results in a compilation error.
	On the other hand, in the second code, the `constexpr Data d('a')` statement initializes a `Data` object with a character literal, which is a constant expression.Therefore, the code compiles successfully.
	It's important to note that `constexpr` variables must be initialized with constant expressions, which can include literals, `constexpr` variables, and certain other expressions that can be evaluated at compile-time.
	*/
	//TEST! constexpr Data1 d1("abc");
	constexpr Data2 d2('a');
	
	return 0;
}
#endif

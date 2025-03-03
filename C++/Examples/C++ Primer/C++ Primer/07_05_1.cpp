#ifdef ON

#include <iostream>
using namespace std;
#ifdef Order_of_Member_Initialization
#include "07_05_1.h"
#elif !Delegating_Constructors
#include "07_05_2.h"
#endif

void mine() {
	cout << "Sales_data s...\n";
	Sales_data s;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef Order_of_Member_Initialization
	class X {
		int i;
		int j;
	public:
		//TEST!! X(int val) : j(val), i(j) {} //																																				undefined: i is initialized before j
	};
#elif !Default_Arguments_and_Constructors
	//MINE
	Sales_data str("test");
	print(cout, str);
	cout << '\n';
#endif

	mine();

	return 0;
}
#endif

#ifdef EX_07_36

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	struct X {
		X(int i, int j) : base(i), rem(base %j) {}
		//ORIG int rem, base;
		int base, rem; //MINE
	};

	return 0;
}

#elif EX_07_38

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	struct S {
		string str;
		S(istream &is = cin) {
			is >> str;
		}
#ifndef EX_07_39
		S(const string &s /* //TEST = "" */) : str(s) {}
#endif
	};

	S s1;
	cout << s1.str << '\n';
	S s2("abc");
	cout << s2.str << '\n';

	return 0;
}

#endif

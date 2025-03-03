#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "16_04_1.h"
using namespace std;

void Writing_a_Variadic_Function_Template() {
	int i = 0; //MINE
	string s = "words"; //MINE

	print(cout, i, s, 42); // two parameters in the pack
}

int main() {
	print_file_line();

	Writing_a_Variadic_Function_Template();
	cout << '\n';
}
#endif

#ifdef EX_16_53

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
ostream &print(ostream &os, const T &t) {
	return os << "t = " << t;
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest) { 
	//os << "t = " << t << '\t' << "sizeof...(rest) = " << sizeof...(rest) << '\n';
	os << "t = " << t << '\t';
	cout << "sizeof...(rest) = " << sizeof...(rest);
	cout << '\t' << "sizeof...(Args) = " << sizeof...(Args) << '\n';
	return print(os, rest...);
}

int main() {
	print_file_line();

	cout << "print(cout, 1, 2, 3, 4, 5):\n";
	print(cout, 1, 2, 3, 4, 5);
	cout << '\n';
}
#endif

#ifdef EX_16_54

#include <iostream>
#include "../../stdafx.h"
#include "16_04_1.h"
using namespace std;

struct MyStruct {
	int i{};
};

int main() {
	print_file_line();

	//ERR print(cout, 42, "words", MyStruct{});
}
#endif

#ifdef EX_16_55

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest) { // this version of print will be called for all but the last element in the pack
	os << t << ", "; // print the first argument
	return print(os, rest...); // recursive call; print the other arguments
}

template <typename T>
ostream &print(ostream &os, const T &t) { // function to end the recursion and print the last element // this function must be declared before the variadic version of print is defined
	return os << t; // no separator after the last element in the pack
}

int main() {
	print_file_line();

	//ERR print(cout, 42, "words");
}
#endif

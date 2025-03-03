#include <iostream>
#include <vector>
#include <cstdlib>
#include "06_03_2.h"
using namespace std;

const string &How_Values_Are_Returned::shorterString(const string &s1, const string &s2) { // return a reference to the shorter of two strings
	return s1.size() <= s2.size() ? s1 : s2;
}

string How_Values_Are_Returned::make_plural(size_t ctr, const string &word, const string &ending) { // return the plural version of word if ctr is greater than 1
	return (ctr > 1) ? word + ending : word;
}

#ifdef ON
namespace Never_Return_a_Reference_or_Pointer_to_a_Local_Object {
#ifdef ON
	const string &manip() { //																																											disaster: this function returns a reference to a local object
		string ret;
		if (!ret.empty()) // transform ret in some way
			return ret; // WRONG: returning a reference to a local object!
		else
			return "Empty"; // WRONG: "Empty" is a local temporary string
	}

#elif ON
	const int &mine1() {  
	int i{111};
	return i;
}

#elif ON
	const int *mine2() { 
	int i{222};
	return &i;
	}

#elif ON
	const string &mine3() {
	string s{"aaa"};
	return s;
	}

#elif ON
	const string *mine4() {
	string s{"bbb"};
	return &s;
	}
#endif
}

namespace Reference_Returns_Are_Lvalues { 
	char &get_val(string &str, string::size_type scr_ix) {
		return str[scr_ix]; // get_val assumes the given index is valid
	}
}

namespace List_Initializing_the_Return_Value {
	vector<string> process() {
		// ...
		// expected and actual are strings
		string expected{"expected"}, actual{"actual"}; //MINE
		if (expected.empty())
			return {}; // return an empty vector
		else if (expected == actual)
			return {"functionX", "okay"}; // return list-initialized vector
		else
			return {"functionX", expected, actual};
	}
}

namespace Recursion {
	int factorial(int val) { // calculate val!, which is 1 * 2 * 3 ... * val
		if (val > 1)
			return factorial(val - 1) * val;
		return 1;
	}

	int fact_Page_202(int val) { // factorial of val is val * (val - 1) * (val - 2) ... * ((val - (val - 1)) * 1)
		int ret = 1; // local variable to hold the result as we calculate it
		while (val > 1)
			ret *= val--; // assign ret * val to ret and decrement val
		return ret; // return the result
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << How_Values_Are_Returned::shorterString("aa", "bbb") << '\n';
	string v{"aa"}, b{"bbb"};
	cout << How_Values_Are_Returned::shorterString(v, b) << '\n';

	cout << make_plural(2, "word", "s") << '\n'; //MINE

#ifndef ON
	//cout << "manip().empty(): " << boolalpha << Never_Return_a_Reference_or_Pointer_to_a_Local_Object::manip().empty() << '\n';
	//cout << Never_Return_a_Reference_or_Pointer_to_a_Local_Object::mine1() << '\n';
	//cout << *Never_Return_a_Reference_or_Pointer_to_a_Local_Object::mine2() << "\n\n";
	//cout << Never_Return_a_Reference_or_Pointer_to_a_Local_Object::mine3() << "\n\n";
	//cout << *Never_Return_a_Reference_or_Pointer_to_a_Local_Object::mine4() << "\n\n";

#elif ON
	string s("v value");
	cout << s << endl; // prints a value
	Reference_Returns_Are_Lvalues::get_val(s, 0) = 'A'; // changes s[0] to A
	cout << s << endl; // prints A value
	//ERR How_Values_Are_Returned::shorterString("hi", "bye") = "X"; // error: return value is const

#elif ON
	vector<string> v = List_Initializing_the_Return_Value::process();
	for (auto &i : v)
		cout << i << ' ';
	cout << '\n';

#elif ON
	cout << Recursion::factorial(3) << '\n';
	cout << Recursion::fact_Page_202(3) << '\n';
#endif

	{ // Return from main
		bool some_failure{};
		if (some_failure)
			return EXIT_FAILURE;
		else
			return EXIT_SUCCESS;
	}
}
#endif

#ifdef  EX_06_30

#include <iostream>
using namespace std;

bool str_subrange(const string &str1, const string &str2) { // incorrect return values, this code will not compile
	if (str1.size() == str2.size()) // same sizes: return normal equality test
		return str1 == str2; // ok: == returns bool

	auto size = (str1.size() < str2.size()) ? str1.size() : str2.size(); // find the size of the smaller string; conditional operator, see § 4.7 (p. 151)
	for (decltype(size) i = 0; i != size; ++i) { // look at each element up to the size of the smaller string
		if (str1[i] != str2[i])
			return; // error #1: no return value; compiler should detect this error
	}
	// error #2: control might flow off the end of the function without a return // the compiler might not detect this error
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	str_subrange("aaa", "bbb");

	return 0;
}
#endif

#ifdef  EX_06_32

#include <iostream>
using namespace std;

int &get(int *arry, int index) { 
	return arry[index];
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int ia[10];
	for (int i = 0; i != 10; ++i)
		get(ia, i) = i;

	for (auto i : ia)
		cout << i << ' ';
	cout << '\n';

	return 0;
}
#endif

#ifdef  EX_06_33

#include <iostream>
#include <vector>
using namespace std;

void print_vec(const vector<int> &v, vector<int>::size_type scr_ix) {
	if (scr_ix < v.size()) {
		cout << v.at(scr_ix) << ' ';
		print_vec(v, scr_ix + 1);
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v{0, 1, 2, 3};
	print_vec(v, 0);
	cout << '\n';

	return 0;
}
#endif
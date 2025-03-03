#ifdef ON

#include <functional>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

vector<string> svec = {"Hello", "World"}; //MINE

void Using_Member_Functions_as_Callable_Objects() {
	auto fp = &string::empty; // fp points to the string empty function
	//TEST! find_if(svec.begin(), svec.end(), fp); //																									error: must use .* or ->* to call a pointer to member
}

void Using_function_to_Generate_a_Callable() {
	function<bool(const string &)> fcn = &string::empty; //TEST!
	find_if(svec.begin(), svec.end(), fcn);

	vector<string *> pvec;
	function<bool(const string *)> fp = &string::empty; //TEST
	find_if(pvec.begin(), pvec.end(), fp); // fp takes a pointer to string and uses the ->* to call empty
}

void Using_mem_fn_to_Generate_a_Callable() {
	find_if(svec.begin(), svec.end(), mem_fn(&string::empty)); //TEST!

	auto f = mem_fn(&string::empty); // f takes a string or a string*
	f(*svec.begin()); // ok: passes a string object; f uses .* to call empty
	f(&svec[0]); // ok: passes a pointer to string; f uses .-> to call empty
}

void mine() { // Perplexity
	auto f = mem_fn(&string::empty); //TEST! //																											Create a function object using mem_fn to call the empty member function of the string class

	string str = "Test"; // Call the empty member function on a string object
	cout << boolalpha;
	cout << "Calling empty on a string object: " << f(str) << '\n';

	string *ptr = &svec[0]; // Call the empty member function on a pointer to a string object
	cout << "\n*ptr = " << *ptr << '\n';
	cout << "Calling empty on a pointer to a string object: " << f(ptr) << '\n';
}

void Using_bind_to_Generate_a_Callable() {
	//ORIG auto it = find_if(svec.begin(), svec.end(), bind(&string::empty, _1)); // bind each string in the range to the implicit first argument to empty
	auto it = find_if(svec.begin(), svec.end(),	bind(&string::empty, placeholders::_1)); //TEST! //MINE
	cout << boolalpha << "No empty string in the svec vector: " << (it == svec.end()) << '\n'; //MINE

	//ORIG auto f = bind(&string::empty, _1);
	auto f = bind(&string::empty, placeholders::_1); //MINE
	f(*svec.begin()); // ok: argument is a string f will use .* to call empty
	f(&svec[0]); // ok: argument is a pointer to string f will use .-> to call empty
}

int main() {
	print_file_line();

	//mine();
	Using_bind_to_Generate_a_Callable();

	return 0;
}
#endif

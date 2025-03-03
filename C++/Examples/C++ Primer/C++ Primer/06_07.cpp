#ifdef ON

#include <iostream>
using namespace std;

namespace Pointers_to_Functions {
	bool lengthCompare(const string &, const string &); // compares lengths of two strings
	//ORIG bool (*pf)(const string &, const string &); // pf points to a function returning bool that takes two const string references // uninitialized
}

namespace Using_Function_Pointers {
	using namespace Pointers_to_Functions;
	//ORIG pf = lengthCompare; // pf now points to the function named lengthCompare
	//ORIG pf = &lengthCompare; // equivalent assignment: address-of operator is optional
	bool (*pf)(const string &, const string &) = lengthCompare; //MINE
	//TEST! bool (*pf)(const string &, const string &) = &lengthCompare; //MINE

	bool b1 = pf("hello", "goodbye"); // calls lengthCompare
	//TEST! bool b2 = (*pf)("hello", "goodbye"); //																																					equivalent call
	bool b3 = lengthCompare("hello", "goodbye"); //																																					equivalent call
}

namespace Function_Pointer_Parameters {
	using namespace Pointers_to_Functions;
	using namespace Using_Function_Pointers;
	//OFF void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &)); // third parameter is a function type and is automatically treated as a pointer to function
	void useBigger(const string &s1, const string &s2, bool (*pf)(const string &, const string &)); // equivalent declaration: explicitly define the parameter as a pointer to function

	//TEST! typedef bool Func(const string &, const string &); //																															Func and Func2 have function type
	//TEST! typedef decltype(lengthCompare) Func2; //																																		equivalent type
	
	//TEST! typedef bool(*FuncP)(const string &, const string &); //																														FuncP and FuncP2 have pointer to function type
	//TEST! typedef decltype(lengthCompare) *FuncP2; //																																	equivalent type

	//TEST! void useBigger(const string &, const string &, Func);
}

namespace Returning_a_Pointer_to_Function {
	using F = int(int *, int); //																																							F is a function type, not a pointer
	using PF = int(*)(int *, int); //TEST! //																																				PF is a pointer type

	//TEST! PF f1(int); //																																									ok: PF is a pointer to function; f1 returns a pointer to function
	//TEST!! F f1(int); //																																									error: F is a function type; f1 can’t return a function
	//TEST! F *f1(int); //																																									ok: explicitly specify that the return type is a pointer to function

	//TEST! int (*f1(int))(int *, int); 

	//TEST! auto f1(int) -> int(*)(int *, int);
}

namespace Using_auto_or_decltype_for_Function_Pointer_Types {
	string::size_type sumLength(const string &, const string &);
	string::size_type largerLength(const string &, const string &);
	
	//TEST! decltype(sumLength) *getFcn(const string &); //																																	depending on the value of its string parameter, getFcn returns a pointer to sumLength or to largerLength
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

#undef EX_06_56
#ifdef EX_06_56

#include <iostream>
#include <vector>
using namespace std;

namespace EX_06_54 {
	int f(int, int);
	vector<decltype(f) *> arr;
}

using namespace EX_06_54;

namespace EX_06_55 {
	int add(int n1, int n2) {
		return n1 + n2;
	}

	int substract(int n1, int n2) {
		return n1 - n2;
	}

	int multiply(int n1, int n2) {
		return n1 * n2;
	}

	int divide(int n1, int n2) {
		return n1 / n2;
	}

	void store_fp() {
		arr.push_back(add);
		arr.push_back(substract);
		arr.push_back(multiply);
		arr.push_back(divide);
	}
}

using namespace EX_06_55;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	store_fp();

	for (auto i : arr)
		cout << i(10, 2) << '\n';
	
	return 0;
}
#endif
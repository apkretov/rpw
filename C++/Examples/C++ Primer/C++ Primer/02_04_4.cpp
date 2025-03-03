#ifdef ON

#include <iostream>
using std::cout;

/*
you.com: Why is get_size() const?
In C++, functions can be declared as const to indicate that they do not modify the state of the object they are called on. This is useful for ensuring the correctness of your code, and for allowing certain optimizations to be made by the compiler.
In the provided code, get_size() is marked as const, which means that it does not modify the state of any objects. Specifically, it does not modify any member variables of a class instance, nor does it call any non - const member functions.
However, simply marking a function as const does not automatically make its return value a constant expression. A constant expression is an expression whose value is computable at compile-time. In order for sz to be a constant expression, get_size() would need to be declared as constexpr.
So, get_size() is declared as const to indicate that it does not modify the state of any objects, but it is not declared as constexpr, which means that its return value is not necessarily a constant expression.
*/

const int get_size() {
	return 111;
}

const void test(int &i) {
	i = 0;
}

void constexpr_and_Constant_Expressions() {
	const int max_files = 20; // max_files is a constant expression
	const int limit = max_files + 1; // limit is a constant expression
	int staff_size = 27; // staff_size is not a constant expression
	const int sz = get_size(); // sz is not a constant expression

	//ERR ++sz;
	cout << sz << '\n';
}

constexpr int size() { //MINE
	return 10;
}

void constexpr_Variables() {
	//TEST! constexpr int mf = 20; //																																								20 is a constant expression
	//TEST! constexpr int limit = mf + 1; //																																						mf + 1 is a constant expression
	//TEST! constexpr int sz = size(); //																																							ok only if size is a constexpr function
}

void Pointers_and_constexpr () {
	{
		const int *p = nullptr; //TEST //																																							p is a pointer to a const int
		constexpr int *q = nullptr; //TEST!!! //																																					q is a const pointer to int
	}

	constexpr int *np = nullptr; // np is a constant pointer to int that is null
	//TEST!! //																																														i and j must be defined outside any function
	int j = 0;
	constexpr int i = 42; // type of i is const int
	//TEST!! constexpr const int *p = &i; //																																						p is a constant pointer to the const int i
	//TEST!! constexpr int *p1 = &j; //																																								p1 is a constant pointer to the int j
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//constexpr_and_Constant_Expressions();
	Pointers_and_constexpr();

	return 0;
}
#endif

#ifdef EX_02_32

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//TEST int null = 0, *p = null;

	return 0;
}
#endif

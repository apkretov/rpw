#undef ON
#ifdef ON

#include <iostream>
using std::cout;

void mine() {
	const int ci = 111;
	const int& r1 = ci;
	const int& r2{222};
	//ERR int& r3{333};

	//ERR r2 = 333;
	cout << r2 << '\n';
}

void constexpr_and_Constant_Expressions() {
	const int ci = 1024;
	const int& r1 = ci; // ok: both reference and underlying object are
	//OFF const r1 = 42; // error: r1 is a reference to const 
	//OFF int &r2 = ci; // error: non const reference to a const object
}

void f2() {
	int i = 42;
	const int &r1 = i; // we can bind a const int& to a plain int object
	const int &r2 = 42; // ok: r1 is a reference to const
	const int &r3 = r1 * 2; // ok: r3 is a reference to const
	//OFF int &r4 = r1 * 2; // error: r4 is a plain, nonconst reference //MINE: Only a const reference can refer to a number (which is a constant): r1 * 2 is a number.

	//ERR r1 = 222; //MINE
}

void f3() {
	double dval = 3.14;
	const int &ri = dval;
	cout << ri << '\n';

	dval = 2.7; //MINE
	cout << ri << '\n';

	//MINE
	//ERR int *pi = &dval;
	double *const p = &dval;
	double const *const pc = &dval;
	//ERR *pc = 0;
	*p = 0;
	cout << *pc << '\n';
}

void f4() {
	int i = 42;
	int &r1 = i; // r1 bound to i
	const int &r2 = i; // r2 also bound to i; but cannot be used to change i
	const double &r3 = i; //MINE
	
	r1 = 0; // r1 is not const; i is now 0
	//ERR r2 = 0; // error: r2 is a reference to const
	cout << i << '\n';
	cout << r2 << '\n';
	cout << r3 << '\n'; //MINE
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//mine();
	f3();
	//f4();

	return 0;
}
#endif
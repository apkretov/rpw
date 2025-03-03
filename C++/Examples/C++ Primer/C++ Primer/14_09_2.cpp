#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#undef Argument_Matching_and_Mutual_Conversions
#ifdef Argument_Matching_and_Mutual_Conversions
// usually a bad idea to have mutual conversions between two class types
struct B;
struct A {
	A() = default;
	A(const B &); //TEST! //																																									converts a B to an A
	// other members
};

A::A(const B &b) { //MINE
	cout << "A constructor\n";
} 

struct B {
	operator A() const; //TEST! //																																								also converts a B to an A
	// other members
};

A f(const A &); //TEST!

B::operator A() const { //MINE
	cout << "B operator A()\n";
	return A();
}

A f(const A &a) { //MINE
	cout << "f(const A &a)\n";
	return a;
}

void Argument_Matching_and_Mutual_Conversions_() {
	B b;
	//TEST! A a = f(b); //																																										error ambiguous: f(B::operator A()) // or f(A::A(const B&))
	
	A a1 = f(b.operator A()); //TEST! //																																						ok: use B’s conversion operator
	A a2 = f(A(b)); //TEST! //																																									ok: use A’s constructor
}

#elif! Ambiguities_and_Multiple_Conversions_to_Built_in_Types
struct A {
	A(int = 0); // usually a bad idea to have two
	A(double); // conversions from arithmetic types
	operator int() const; // usually a bad idea to have two
	operator double() const; // conversions to arithmetic types
	// other members
};

A::A(int) { //MINE
	cout << "Constructor A(int = 0)\n";
}

A::A(double) { //MINE
	cout << "Constructor A(double)\n";
}

A::operator int() const { //MINE
	cout << "A::operator int()\n";
	return int{};
}

A::operator double() const { //MINE
	cout << "A::operator double()\n";
	return double{};
}

void f2(long double);

void f2(long double) { //MINE
	cout << "f2(long double)\n";
}

void Ambiguities_and_Multiple_Conversions_to_Built_in_Types_() {
	A a;
	//TEST! f2(a); //																																												error ambiguous: f(A::operator int()) // or f(A::operator double())
	f2(a.operator int()); //MINE
	f2(a.operator double()); //MINE

	//ORIG long lg;
	long lg{}; //MINE
	//TEST! A a2(lg); //																																											error ambiguous: A::A(int) or A::A(double)
	A a2(static_cast<double>(lg)); //MINE

	short s = 42;
	A a3(s); //TEST! //																																												promoting short to int is better than converting short to double // uses A::A(int)
}
#endif

#ifndef Overloaded_Functions_and_Converting_Constructors
struct C {
	C(int);
	// other members
};

struct D {
	D(int);
	// other members
};

C::C(int) { //MINE
	cout << "C constructor\n";
}

D::D(int) { //MINE
	cout << "D constructor\n";
}

void manip(const C &);

void manip(const D &);

void manip(const C &) { //MINE
	cout << "manip(const C &)\n";
}

void manip(const D &) { //MINE
	cout << "manip(const D &)\n";
}

void Overloaded_Functions_and_Converting_Constructors_() {
	//TEST! manip(10); //																																										error ambiguous: manip(C(10)) or manip(D(10))
	manip(C(10)); //TEST! //																																									ok: calls manip(const C &)
}
#endif

#ifndef Overloaded_Functions_and_User_Defined_Conversion
struct E {
	E(double);
	// other members
};

E::E(double) { //MINE
	cout << "E constructor\n";
}

void manip2(const C &);
void manip2(const E &);

void manip2(const C &) { //MINE
	cout << "manip2(const C &)\n";
}

void manip2(const E &) { //MINE
	cout << "manip2(const E &)\n";
}

void Overloaded_Functions_and_User_Defined_Conversion_() {
	//TEST! manip2(10); //																																										error ambiguous: two different user-defined conversions could be used // manip2(C(10) or manip2(E(double(10)))

	//MINE
	manip2(C(111));
	manip2(E(222.2));
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	
#ifdef Argument_Matching_and_Mutual_Conversions
	Argument_Matching_and_Mutual_Conversions_();
#elif! Ambiguities_and_Multiple_Conversions_to_Built_in_Types
	//Ambiguities_and_Multiple_Conversions_to_Built_in_Types_();
#endif
	//Overloaded_Functions_and_Converting_Constructors_();
	Overloaded_Functions_and_User_Defined_Conversion_();

	return 0;
}
#endif

#ifdef EX_14_50

#include "../../stdafx.h"
#include "14_09_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	LongDouble ldObj(111.1);
	
	cout << "\nint ex1 = ldObj:\n";
	//ERR int ex1 = ldObj;
	int ex1 = ldObj.operator double();
	cout << "ex1 = " << ex1 << '\n';
		
	cout << "\nfloat ex2 = ldObj:\n";
	float ex2 = ldObj;
	cout << "ex2 = " << ex2 << '\n';

	return 0;
}
#endif

#ifdef EX_14_51

#include "../../stdafx.h"
#include "14_09_2.h"
using namespace std;

#ifndef CALC_INT
void calc(int) {
	cout << "calc(int)\n";
}
#endif

void calc(LongDouble) {
	cout << "calc(LongDouble)\n";
}

int main(int argc, char *argv[]) {
	print_file_line();

	double dval{};
	calc(dval); //TEST! // which calc?

	calc(LongDouble(dval));

	return 0;
}
#endif
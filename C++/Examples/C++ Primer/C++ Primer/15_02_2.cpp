#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#undef Classes_Used_as_a_Base_Class
#ifndef Classes_Used_as_a_Base_Class
#include "15_02_2_2.h"
void Derived_Class_Objects_and_the_Derived_to_Base_Conversion() {
	Quote item; // object of base type
	Bulk_quote bulk; // object of derived type
	Quote *p = &item; // p points to a Quote object
	p = &bulk; // p points to the Quote part of bulk
	Quote &r = bulk; // r bound to the Quote part of bulk
}
#endif

#ifdef Inheritance_and_static_Members
class Base {
public:
	static void statmem();
};

class Derived : public Base {
	void f(const Derived &);
};

void Derived::f(const Derived &derived_obj) {
	Base::statmem(); //TEST //																																										ok: Base defines statmem
	Derived::statmem(); //TEST //																																									ok: Derived inherits statmem
	//																																																ok: derived objects can be used to access static from base
	derived_obj.statmem(); //TEST //																																								accessed through a Derived object
	statmem(); //TEST //																																											accessed through this object
}
#endif

#ifdef Declarations_of_Derived_Classes
//TEST! class Bulk_quote : public Quote; //																																							error: derivation list can’t appear here
class Bulk_quote; // ok: right way to declare a derived class
#endif

#ifdef Classes_Used_as_a_Base_Class
class Quote; // declared but not defined
//TEST class Bulk_quote : public Quote { /*...*/ }; //																																				error: Quote must be defined

void Classes_Used_as_a_Base_Class_() {
	class Base { /* ... */ };
	class D1 : public Base { /* ... */ };
	class D2 : public D1 { /* ... */ };
}
#endif

void Preventing_Inheritance() {
	class NoDerived final { /* */ }; //TEST!! //																																					NoDerived can’t be a base class
	class Base { /* */ };
	//																																																Last is final; we cannot inherit from Last
	class Last final : Base { /* */ }; //TEST!! //																																					Last can’t be a base class
	//TEST!! class Bad : NoDerived { /* */ }; //																																						error: NoDerived is final
	//TEST!! class Bad2 : Last { /* */ }; //																																							error: Last is final
}

void There_Is_No_Implicit_Conversion_from_Base_to_Derived() {
	Quote base;
	//TEST! Bulk_quote *bulkP = &base; //																																							error: can’t convert base to derived
	//TEST! Bulk_quote &bulkRef = base; //																																							error: can’t convert base to derived
	
	//MINE
	Bulk_quote b;
	Quote &r = b, *p = &b;

	Bulk_quote bulk;
	Quote *itemP = &bulk; //																																										ok: dynamic type is Bulk_quote
	//TEST! Bulk_quote *bulkP = itemP; //																																							error: can’t convert base to derived
	Bulk_quote *bulkP2 = dynamic_cast<Bulk_quote *>(itemP); //TEST! //MINE
}

void and_No_Conversion_between_Objects() {
	Bulk_quote bulk; // object of derived type
	Quote item(bulk); //TEST! //																																									uses the Quote::Quote(const Quote&) constructor
	item = bulk; //TEST! //																																											calls Quote::operator=(const Quote&)
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	//and_No_Conversion_between_Objects();
	Preventing_Inheritance();

	return 0;
}
#endif

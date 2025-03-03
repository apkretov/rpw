#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_02_1.h"
#include "15_06.h"
#include "15_04_2.h"
using namespace std;

void Class_Scope_under_Inheritance() {
	Bulk_quote bulk;
	cout << bulk.isbn();
}

void Name_Lookup_Happens_at_Compile_Time() {
	Bulk_quote bulk;
	Bulk_quote *bulkP = &bulk; // static and dynamic types are the same
	Quote *itemP = &bulk; // static and dynamic types differ
	bulkP->discount_policy(); // ok: bulkP has type Bulk_quote*
	//TEST! itemP->discount_policy(); //																																							error: itemP has type Quote*
}

void Name_Collisions_and_Inheritance() {
	struct Base {
		Base() : mem(0) {}
	protected:
		int mem;
	};
	
	struct Derived : Base {
		Derived(int i) : mem(i) {} // initializes Derived::mem to i 
		//TEST! //																																													Base::mem is default initialized
		int get_mem() {
			return mem; //TEST //																																									returns Derived::mem
		}
#ifndef Using_the_Scope_Operator_to_Use_Hidden_Members
		int get_base_mem() {
			return Base::mem; //TEST!
		}
#endif 
	protected:
		int mem; // hides mem in the base
	};

	Derived d(42);
	cout << d.get_mem() << endl; // prints 42
	cout << d.get_base_mem() << '\n'; //MINE
}

#ifdef As_Usual_Name_Lookup_Happens_before_Type_Checking
struct Base {
	int memfcn();
};
	
struct Derived : Base {
	int memfcn(int); // hides memfcn in the base
};
	
void As_Usual_Name_Lookup_Happens_before_Type_Checking_() {
	Derived d; 
	Base b;
	b.memfcn(); // calls Base::memfcn
	d.memfcn(10); // calls Derived::memfcn
	//TEST! d.memfcn(); //																																											error: memfcn with no arguments is hidden
	d.Base::memfcn(); //TEST! //																																									ok: calls Base::memfcn
}

#elif! Virtual_Functions_and_Scope
class Base {
public:
	virtual int fcn() {
		cout << "Base::fcn()\n"; //MINE
		return 0; //MINE
	}
};
	
class D1 : public Base {
public: // hides fcn in the base; this fcn is not virtual // D1 inherits the definition of Base::fcn()
	int fcn(int) { //TEST! //																																										parameter list differs from fcn in Base
		cout << "D1::fcn(int)\n"; //MINE
		return 0; //MINE
	}

	virtual void f2() { // new virtual function that does not exist in Base
		cout << "D1::f2()\n"; //MINE
	}

#ifdef EX_15_06 //MINE
	int fcn() {
		cout << "D1::fcn()\n";
		return 0;
	}
#endif
};
	
class D2 : public D1 {
public:
	int fcn(int) { // nonvirtual function hides D1::fcn(int)
		cout << "D2::fcn(int)\n"; //MINE
		return 0; //MINE
	}

#define FCN //MINE
#ifdef FCN //MINE
	int fcn() { // overrides virtual fcn from Base
		cout << "D2::fcn()\n"; //MINE
		return 0; //MINE
	}
#endif

	void f2() { // overrides virtual f2 from D1
		cout << "D2::f2()\n"; //MINE
	}
};

void mine() {
	Base *pb;
	D1 d1, *pd1 = &d1;

	pb = &d1;
	pb->fcn(); //TEST!
	
	d1.fcn(111);
	pd1->fcn(111);
	pd1->Base::fcn(); //TEST!

#ifndef FCN
	D2 d2;
	pb = &d2;
	pb->fcn(); //TEST!
#endif
}

void Calling_a_Hidden_Virtual_through_the_Base_Class() {
	Base bobj; 
	D1 d1obj; 
	D2 d2obj;
	Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;

	bp1->fcn(); // virtual call, will call Base::fcn at run time
	bp2->fcn(); // virtual call, will call Base::fcn at run time
	bp3->fcn(); // virtual call, will call D2::fcn at run time

	D1 *d1p = &d1obj; 
	D2 *d2p = &d2obj;

	//TEST bp2->f2(); //																																											error: Base has no member named f2
	d1p->f2(); // virtual call, will call D1::f2() at run time
	d2p->f2(); // virtual call, will call D2::f2() at run time

	Base *p1 = &d2obj; 
	D1 *p2 = &d2obj; 
	D2 *p3 = &d2obj;

	//TEST! p1->fcn(42); //																																											error: Base has no version of fcn that takes an int
	p2->fcn(42); // statically bound, calls D1::fcn(int)
	p3->fcn(42); // statically bound, calls D2::fcn(int)
}
#endif

int main(int agrc, char *agrv[]) {
	print_file_line();
	
	//Name_Collisions_and_Inheritance();
	mine();
	//Calling_a_Hidden_Virtual_through_the_Base_Class();
	
	return 0;
}
#endif
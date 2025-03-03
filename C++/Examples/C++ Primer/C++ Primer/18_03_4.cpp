#ifdef ON

#include "../../stdafx.h"
#include "18_03_4.h"
using namespace std;

#pragma region Normal Conversions to Base Are Supported
	void dance(const Bear &) { cout << "Bear dance\n"; }
	void rummage(const Raccoon &) { cout << "Raccoon rummage\n"; }
	ostream &operator<<(ostream &, const ZooAnimal &); // { return cout << "ZooAnimal\n"; }

void Normal_Conversions_to_Base_Are_Supported() {
	Panda ying_yang;
#ifndef OFF
	dance(ying_yang); // ok: passes Panda object as a Bear
	rummage(ying_yang); //TEST //																														ok: passes Panda object as a Raccoon
	cout << ying_yang; // ok: passes Panda object as a ZooAnimal
#endif
	cout << '\n'; //MINE
}
#pragma endregion

int main() {
	print_file_line();
	
	Normal_Conversions_to_Base_Are_Supported();

	return 0;
}
#endif

#ifdef EX_18_28

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct Base {
	void bar(int) { cout << "Base::bar(int)\n"; } // public by default
protected:
	int ival;
};

struct Derived1 : virtual public Base {
	void bar(char) { cout << "Derived1::bar(char)\n"; } // public by default
	void foo(char) { cout << "Derived1::foo(char)\n"; }
protected:
	char cval;
};

struct Derived2 : virtual public Base {
	void foo(int) { cout << "Derived2::foo(int)\n"; } // public by default
protected:
	int ival;
	char cval;
};

struct VMI : public Derived1, public Derived2 {
#pragma region With qualification
	void foo(int) { //TEST
		cout << "VMI::foo(int):\n"; 
		Derived1::foo(' ');
		Derived2::foo(0);
		Base::ival = 0;
		Derived2::ival = 0;
		Derived1::cval = ' ';
		Derived2::cval = ' ';
	}
#pragma endregion
};

int main() {
	print_file_line();

	VMI vmi;
#pragma region Without qualification
	vmi.bar(' ');
#pragma endregion
#pragma region With qualification
	cout << '\n';
	vmi.foo(0);
#pragma endregion
	return 0;
}
#endif

#ifdef PERPLEXITY

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class A {
	public: int x;
};

#ifdef NON_VIRTUAL
class B : public A {};
class C : public A {};
#else //VIRTUAL //TEST!!
class B : virtual public A {};
class C : virtual public A {};
#endif

class D : public B, public C {};

int main() {
	print_file_line();

	D d;
	d.x = 111; //TEST!!
}
#endif
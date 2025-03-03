#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifdef protected_Members
class Base {
protected:
	int prot_mem; // protected member
};

class Sneaky : public Base {
	friend void clobber(Sneaky &); // can access Sneaky::prot_mem
	friend void clobber(Base &); // can’t access Base::prot_mem
	int j; // j is private by default

	void test() { //MINE
		prot_mem = 0;
		Base b{};
		//TEST! b.prot_mem = 0;
		Sneaky s{};
		s.j = s.prot_mem = 0; //TEST!
	}
};

void clobber(Sneaky &s) { // ok: clobber can access the private and protected members in Sneaky objects
	s.j = s.prot_mem = 0; //TEST!
}

void clobber(Base &b) { // error: clobber can’t access the protected members in Base
	//TEST! b.prot_mem = 0;
}

#elif public_private_and_protected_Inheritance
class Base {
public:
	void pub_mem(); // public member
protected:
	int prot_mem; // protected member
private:
	char priv_mem; // private member
};

struct Pub_Derv : public Base {
	int f() {
		return prot_mem; // ok: derived classes can access protected members
	}

	char g() {
		//TEST return priv_mem; //																																										error: private members are inaccessible to derived classes
	}
};

struct Priv_Derv : private Base {
	int f1() const { // private derivation doesn’t affect access in the derived class
		return prot_mem;
	}
};

void public_private_and_protected_Inheritance() {
	Pub_Derv d1; // members inherited from Base are public
	Priv_Derv d2; // members inherited from Base are private
	d1.pub_mem(); // ok: pub_mem is public in the derived class
	//TEST! d2.pub_mem(); //																																											error: pub_mem is private in the derived class
}

struct Derived_from_Public : public Pub_Derv {
	int use_base() {
		return prot_mem; // ok: Base::prot_mem remains protected in Pub_Derv
	}
};

struct Derived_from_Private : public Priv_Derv {
	int use_base() {
		//TEST! return prot_mem; //																																										error: Base::prot_mem is private in Priv_Derv
	}
};

#elif! Friendship_and_Inheritance
#ifndef protected_Members
class Base {
protected:
	int prot_mem; // protected member
#ifndef Friendship_and_Inheritance
	// added friend declaration; other members as before
	friend class Pal; //TEST! //																																									Pal has no access to classes derived from Base
#endif
};

class Sneaky : public Base {
	friend void clobber(Sneaky &); // can access Sneaky::prot_mem
	friend void clobber(Base &); // can’t access Base::prot_mem
	int j; // j is private by default
};
#endif

class Pal {
public:
	int f(Base b) {
		return b.prot_mem; //TEST! //																																									ok: Pal is a friend of Base
	}

	int f2(Sneaky s) {
		//TEST! return s.j; //																																											error: Pal not friend of Sneaky
	}

	int f3(Sneaky s) { //																																												access to a base class is controlled by the base class, even inside a derived object
		return s.prot_mem; //TEST! //																																									ok: Pal is a friend
	}
};

class D2 : public Pal { //																																												D2 has no access to protected or private members in Base
public:
	int mem(Base b) {
		//TEST! return b.prot_mem; //																																									error: friendship doesn’t inherit
	}
};
#endif

void Exempting_Individual_Members() {
	class Base {
	public:
		size_t size() const {
			return n;
		}
	protected:
		size_t n;
	};

	class Derived : private Base { // note: private inheritance
	public:
		using Base::size; //TEST!!! //																																									maintain access levels for members related to the size of the object
	protected:
		using Base::n; //TEST!
	};

#ifndef	MINE
	Derived d{};
	cout << "d.size() = " << d.size() << '\n';

	struct Derived2 : Derived {
		size_t print_n() const {
			return n; //TEST!
		}
	};
	Derived2 d2{};
	cout << "\nd2.size() = " << d2.size() << '\n'; //TEST!
	cout << "d2.print_n() = " << d2.print_n() << '\n';
#endif
}

void Default_Inheritance_Protection_Levels() {
	//ORIG class Base { /* ... */ };
	class Base { //MINE
	public:
		int i;
	};

	struct D1 : Base { /* ... */ };	//TEST! //																																						public inheritance by default
	class D2 : Base { /* ... */ }; //TEST! //																																						private inheritance by default

	//MINE
	D1 d1{};
	D2 d2{};
	d1.i;
	//TEST! d2.i;

}

int main(int argc, char *argv[]) {
	print_file_line();

	Exempting_Individual_Members();

	return 0;
}
#endif

#ifdef EX_15_18

#include <iostream>
#include "../../stdafx.h"
//#include "15_05.h"
using namespace std;

#ifndef public_private_and_protected_Inheritance
class Base {
public:
	void pub_mem(); // public member
#ifndef EX_15_18
	int pub_mem_mine;
#endif
protected:
	int prot_mem; // protected member
private:
	char priv_mem; // private member
};

struct Pub_Derv : public Base {
	int f() {
		return prot_mem; // ok: derived classes can access protected members
	}

	char g() {
		//TEST return priv_mem; //																																										error: private members are inaccessible to derived classes
	}
};

struct Priv_Derv : private Base {
	int f1() const { // private derivation doesn’t affect access in the derived class
		return prot_mem;
	}
};

struct Derived_from_Public : public Pub_Derv {
	int use_base() {
		return prot_mem; // ok: Base::prot_mem remains protected in Pub_Derv
	}
};

struct Derived_from_Private : public Priv_Derv {
	int use_base() {
		//TEST! return prot_mem; //																																										error: Base::prot_mem is private in Priv_Derv
	}
};

#ifndef EX_15_18
struct Prot_Derv : protected Base {
	int f() const {
		return pub_mem_mine + prot_mem;
	}
};

struct Derived_from_Protected : public Prot_Derv {
	int f() const {
		return pub_mem_mine + prot_mem;
	}
};
#endif
#endif

int main(int argc, char *argv[]) {
	print_file_line();

	Pub_Derv d1{};
	Priv_Derv d2{};
	Prot_Derv d3{};
	Derived_from_Public dd1{};
	Derived_from_Private dd2{};
	Derived_from_Protected dd3{};

	Base *p = &d1; // d1 has type Pub_Derv
	//TEST!! p = &d2; // d2 has type Priv_Derv
	//TEST!! p = &d3; // d3 has type Prot_Derv
	p = &dd1; //TEST // dd1 has type Derived_from_Public
	//TEST p = &dd2; // dd2 has type Derived_from_Private
	//TEST p = &dd3; // dd3 has type Derived_from_Protected

	return 0;
}
#endif

#ifdef EX_15_19

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef public_private_and_protected_Inheritance
class Base {
public:
	void pub_mem(); // public member
#ifndef EX_15_18
	int pub_mem_mine;
#endif
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
protected:
	int prot_mem; // protected member
private:
	char priv_mem; // private member
};

struct Pub_Derv : public Base {
	int f() {
		return prot_mem; // ok: derived classes can access protected members
	}

	char g() {
		//TEST return priv_mem; //																																										error: private members are inaccessible to derived classes
	}
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
};

struct Priv_Derv : private Base {
	int f1() const { // private derivation doesn’t affect access in the derived class
		return prot_mem;
	}
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
};

struct Derived_from_Public : public Pub_Derv {
	int use_base() {
		return prot_mem; // ok: Base::prot_mem remains protected in Pub_Derv
	}
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
};

struct Derived_from_Private : public Priv_Derv {
	int use_base() {
		//TEST! return prot_mem; //																																										error: Base::prot_mem is private in Priv_Derv
	}
#ifdef EX_15_19
	//TEST!! void memfcn(Base &b) {
	b = *this;
}
#endif
};

#ifndef EX_15_18
struct Prot_Derv : protected Base {
	int f() const {
		return pub_mem_mine + prot_mem;
	}
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
};

struct Derived_from_Protected : public Prot_Derv {
	int f() const {
		return pub_mem_mine + prot_mem;
	}
#ifndef EX_15_19
	void memfcn(Base &b) {
		b = *this;
	}
#endif
};
#endif
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif
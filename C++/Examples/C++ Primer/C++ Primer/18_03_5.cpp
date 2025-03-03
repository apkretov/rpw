#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "18_03_5.h"
using namespace std;

#pragma region Constructor and Destructor Order
#ifdef ORIG
class Character { /* ... */ };
class BookCharacter : public Character { /* ... */ };
class ToyAnimal { /* ... */ };
class TeddyBear : public BookCharacter,
	public Bear, public virtual ToyAnimal { /* ... */
};

#else //MINE
struct Character { 
	Character() { cout << "Character::Character()\n"; }
};

struct BookCharacter : public Character { 
	BookCharacter() { cout << "BookCharacter::BookCharacter()\n"; }	
};

struct ToyAnimal { 
	ToyAnimal() { cout << "ToyAnimal::ToyAnimal()\n"; }
};

struct TeddyBear : 
	public BookCharacter,
	public Bear, //TEST!
	public virtual ToyAnimal { //TEST!
		TeddyBear() { cout << "TeddyBear::TeddyBear()\n"; }
	};
#endif 
#pragma endregion

int main() {
	print_file_line();
	
	Panda panda("Panda", true);
	//TeddyBear teddyBear;
	cout << '\n';
	
	return 0;
}
#endif

#ifdef EX_18_29

#include <iostream>
#include "vld.h"
#include "../../stdafx.h"
using namespace std;

struct Class {
	Class() { cout << "Class::Class()\n"; }
	virtual ~Class() { cout << "Class::~Class()\n"; }
};

struct Base : public Class {  
	Base() { cout << "Base::Base()\n"; }
	virtual ~Base() { cout << "Base::~Base()\n"; }
};

struct D1 : virtual public Base {  
	D1() { cout << "D1::D1()\n"; }
	virtual ~D1() { cout << "D1::~D1()\n"; }
};

struct D2 : virtual public Base {  
	D2() { cout << "D2::D2()\n"; }
	virtual ~D2() { cout << "D2::~D2()\n"; }
};

struct MI : public D1, public D2 {  
	MI() { cout << "MI::MI()\n"; }
	virtual ~MI() { cout << "MI::~MI()\n"; }
};

struct Final : public MI, public Class { //TEST!
	Final() { cout << "Final::Final()\n"; }
	virtual ~Final() { cout << "Final::~Final()\n"; }
};

void a() {
	Final final;
	cout << '\n'; //MINE
}

void c() {
	Base *pb; 
	Class *pc; 
	MI *pmi; 
	D2 *pd2;

	//TEST! pb = new Class; // (a)

	pc = new Base; //MINE
	cout << '\n'; //MINE
	delete pc; //MINE
	cout << '\n'; //MINE

	pc = new Final; //(b)
	//ERR pmi = pb; //(c)
	//OFF pd2 = pmi; //(d)

	cout << '\n'; //MINE
	delete pc; //MINE
}

int main() {
	print_file_line();

	//a();
	c();
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_18_30

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class Class {
public:
	Class() { cout << "Class::Class()\n"; }
	virtual ~Class() { cout << "Class::~Class()\n"; }
};

class Base : public Class {
public:
	Base() { cout << "Base::Base()\n"; }
	explicit Base(int i) : ival(i) { cout << "Base::Base(int i)\n";	}
	Base(const Base &b) : ival(b.ival) { cout << "Base::Base(const Base &b)\n";	}
	Base(Base &&b) noexcept : ival(b.ival) { cout << "Base::Base(Base &&b) noexcept\n";	}

	Base &operator=(const Base &rhs) { 
		cout << "Base::operator=(const Base &rhs)\n"; 
		ival = rhs.ival; 
		return *this; 
	}

	Base &operator=(Base &&rhs) noexcept {
		cout << "Base::operator=(Base &&rhs) noexcept\n";
		ival = rhs.ival;
		return *this;
	}

	virtual ~Base() { cout << "Base::~Base()\n"; }
	int get_ival() const & { return ival; }
	int get_ival() && { return ival; }
	void set_ival(int i) { ival = i; }
private:
	int ival{};
};

class D1 : virtual public Base {
public:
	D1() { cout << "D1::D1()\n"; }
	explicit D1(int i) : Base(i) { cout << "D1::D1(int i)\n"; }
	D1(const D1& d1) : Base(d1) { cout << "D1::D1(const D1& d1)\n"; }
	virtual ~D1() { cout << "D1::~D1()\n"; }
};

class D2 : virtual public Base {
public:
	D2() { cout << "D2::D2()\n"; }
	D2(const D2& d2) : Base(d2) { cout << "D2::D2(const D2& d2)\n"; }
	explicit D2(int i) : Base(i) { cout << "D2::D2(int i)\n"; }
	virtual ~D2() { cout << "D2::~D2()\n"; }
};

class MI : public D1, public D2 {
public:
	MI() { cout << "MI::MI()\n"; }
	explicit MI(int i) : D1(i), D2(i) { cout << "MI::MI(int i)\n"; }
	MI(const MI &mi) : D1(mi), D2(mi) { cout << "MI::MI(const MI &mi)\n"; }
	virtual ~MI() { cout << "MI::~MI()\n"; }
};

class Final : public MI, public Class {
public:
	Final() { cout << "Final::Final()\n"; }

	explicit Final(int i) : MI(i), Class(), 
	Base(i) //TEST! //																																	you.com: Explicitly call the Base constructor with the desired value. Otherwise the MI class constructor initializes the Base part of Final before the Class part, resulting in the ival member being set to 0.
	{ cout << "Final::Final(int i)\n"; } 

	Final(const Final &f) : MI(f), Class(),
	Base(f) //TEST! //																																	Ref. you.com above.
	{ cout << "Final::Final(const Final &f)\n"; }

	virtual ~Final() { cout << "Final::~Final()\n"; }
};

int main() {
	print_file_line();

	cout << "Final f1(111):\n";
	Final f1(111);
	cout << '\n';

	cout << "Final f2(f1):\n";
	Final f2(f1);
	cout << '\n';

	cout << "f1.get_ival() = " << f1.get_ival() << '\n';
	cout << "f2.get_ival() = " << f2.get_ival() << '\n';
	cout << '\n';

	return 0;
}
#endif

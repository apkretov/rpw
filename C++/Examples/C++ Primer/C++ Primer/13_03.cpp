#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Writing_Our_Own_swap_Function
class HasPtr {
	friend void swap(HasPtr &, HasPtr &);
	// other members as in § 13.2.1 (p. 511)
#ifndef Classes_That_Act_Like_Values
	friend ostream &operator<<(ostream &out, const HasPtr &ph); //MINE
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}
	HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) {} //TEST! //																															each HasPtr has its own copy of the string to which ps points
#ifndef Using_swap_in_Assignment_Operators
	HasPtr &operator=(HasPtr); //MINE
#endif
	~HasPtr() {
		delete ps;
	}
//ORIG private:
	string *ps;
	int i;
};

ostream &operator<<(ostream &out, const HasPtr &hp) { //MINE
	out << *hp.ps;
	//OFF out << '\t' << hp.i;
	return out;
#endif
};
#endif

#ifndef Using_swap_in_Assignment_Operators
HasPtr &HasPtr::operator=(HasPtr rhs) { //TEST!! //																																					note rhs is passed by value, which means the HasPtr copy constructor // copies the string in the right-hand operand into rhs
	//																																																swap the contents of the left-hand operand with the local variable rhs
	swap(*this, rhs); // rhs now points to the memory this object had used
	return *this; // rhs is destroyed, which deletes the pointer in rhs
}

inline void swap(HasPtr &lhs, HasPtr &rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps); //TEST! //																																								swap the pointers, not the string data
	swap(lhs.i, rhs.i); // 																																											swap the int members
}
#endif

#ifndef swap_Functions_Should_Call_swap_Not_std_swap
struct Foo {
	HasPtr h;
};

void swap(Foo &lhs, Foo &rhs) {
#ifdef _1
	//TEST!! std::swap(lhs.h, rhs.h); //																																							WRONG: this function uses the library version of swap, not the HasPtr version
	// swap other members of type Foo
#elif! _2
	using std::swap; //TEST!!
	swap(lhs.h, rhs.h); //TEST!! //																																									uses the HasPtr version of swap
	// swap other members of type Foo
#endif
}

void mine() {
	Foo f1, f2;

	f1.h.ps = new string("f1");
	f2.h.ps = new string("f2");

	cout << f1.h << '\t' << f2.h << '\n';
	swap(f1, f2);
	cout << f1.h << '\t' << f2.h << '\n';
}
#endif

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	//Swap();
	mine();

	return 0;
}
#endif

#ifdef EX_13_30

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class HasPtr {
	friend void swap(HasPtr &, HasPtr &);
	friend ostream &operator<<(ostream &, const HasPtr&);
public:
	HasPtr(const string &s = string(), int ival = 0) : ps(new string(s)), i(ival) {}
	HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) { cout << "Copy-constructor\n"; }
#ifdef MINE
	HasPtr &operator=(const HasPtr &);
#elif !ORIG
	HasPtr &operator=(HasPtr);
#endif
	~HasPtr() { delete ps; }
	string *getPs() { return ps; }
	void setPs(string *);
	int getI() { return i; }
	void setI(int ival) { i = ival; }
private:
	string *ps;
	int i{};
};

#ifdef MINE
HasPtr &HasPtr::operator=(const HasPtr &p) {
	setPs(p.ps);
	i = p.i;
	return *this;
}
#elif !ORIG
HasPtr &HasPtr::operator=(HasPtr p) {
	cout << "operator=\n";
	swap(*this, p);
	return *this;
}
#endif

void HasPtr::setPs(string *p) {
	auto temp = new string(*p);
	delete ps;
	ps = temp;
}

void swap(HasPtr &lhs, HasPtr &rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	cout << "swap\n";
}

ostream &operator<<(ostream &out, const HasPtr &p) {
	out << *p.ps << '\t' << p.i;
	return out;
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	HasPtr p1("p1", 1), p2(p1), p3("p3", 3);
	cout << p1 << '\n' << p2 << '\n' << p3 << "\n\n";

	string newstr("p2");
	p2.setPs(&newstr);
	p2.setI(2);
	cout << p1 << '\n' << p2 << '\n' << p3 << "\n\n";

	p3 = p1;
	cout << p1 << '\n' << p2 << '\n' << p3 << "\n\n";

	swap(p1, p2);
	cout << p1 << '\n' << p2 << '\n' << p3 << "\n\n";

	return 0;
}
#endif
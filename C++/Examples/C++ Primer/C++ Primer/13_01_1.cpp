#ifdef ON

#include <iostream>
#include <string>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void The_Copy_Constructor() {
	class Foo {
	public:
		Foo(); //																																													default constructor
		//TEST! Foo(const Foo &); //																																								copy constructor
		// ...
	};
}

#ifndef Suppressing_Implicit_Conversions_Defined_by_Constructors
class Sales_data { //VER09
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend istream &read(istream &, Sales_data &);
	friend ostream &print(ostream &, const Sales_data &);

public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p *n) {}
	explicit Sales_data(const string &s) : bookNo(s) {}
	explicit Sales_data(istream &);
#ifndef The_Synthesized_Copy_Constructor
	Sales_data(const Sales_data &);
#endif
	string isbn() const { // remaining members as before
		return bookNo;
	}

	Sales_data &combine(const Sales_data &); // other members as before

	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif

void Copy_Initialization() {
	string dots(10, '.'); //																																										direct initialization
	//TEST! string s(dots); //																																										direct initialization
	//TEST! string s2 = dots; //																																									copy initialization
	string null_book = "9-999-99999-9"; //																																							copy initialization
	string nines = string(100, '9'); //																																								copy initialization
}

void Constraints_on_Copy_Initialization() {
	//TEST! vector<int> v1(10); //																																									ok: direct initialization
	//TEST! vector<int> v2 = 10; // 																																								error: constructor that takes a size is explicit
	//TEST! void f(vector<int>); //																																									f’s parameter is copy initialized
	//OFF f(10); //																																														error: can’t use an explicit constructor to copy an argument
	//TEST f(vector<int>(10)); //																																									ok: directly construct a temporary vector from an int
}

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_13_05

#include <iostream>
using namespace std;

class HasPtr {
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {
		cout << "HasPtr constructor: *ps = " << *ps << '\n';
	}

	HasPtr(const HasPtr &);
	~HasPtr();
private:
	string *ps;
	int i;
};

HasPtr::HasPtr(const HasPtr &hp) : ps(new string(*hp.ps)), i(hp.i) { // ch13/ex13_05.h @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch13/ex13_05.h // ch13/13.5.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.5.cpp
	cout << "HasPtr copy-constructor: *ps = " << *ps << '\n';
}

HasPtr::~HasPtr() {
	cout << "HasPtr destructor: *ps = " << *ps << '\n';
	delete ps;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	HasPtr hp1("aaa"), hp2(hp1);

	return 0;
}
#endif
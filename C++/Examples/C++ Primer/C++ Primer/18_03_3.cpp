#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "18_03_3.h"
using namespace std;

void Class_Scope_under_Multiple_Inheritance() {
	Panda ying_yang("ying_yang"); //MINE
	
	double d = ying_yang.max_weight();
	cout << "ying_yang.max_weight() = " << d << "\n\n"; //MINE
	
	//MINE
	double d1 = ying_yang.ZooAnimal::max_weight(); //TEST!
	cout << "ying_yang.ZooAnimal::max_weight() = " << d1 << '\n';
	double d2 = ying_yang.Endangered::max_weight();
	cout << "ying_yang.Endangered::max_weight() = " << d2 << "\n\n";
}

int main() {
	print_file_line();

	Class_Scope_under_Multiple_Inheritance();

	return 0;
}
#endif

#ifdef EX_18_26

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

struct Base1 {
	void print(int i) const { cout << "Base1::print(int i): i = " << i << '\n'; } // public by default
protected:
	int ival;
	double dval;
	char cval;
private:
	int *id;
};

struct Base2 {
	void print(double) const; // public by default
protected:
	double fval;
private:
	double dval;
};

struct Derived : public Base1 {
	void print(string) const; // public by default
protected:
	string sval;
	double dval;
};

struct MI : public Derived, public Base2 {
	void print(vector<double>); // public by default
	void print(int i) { Base1::print(i); }
protected:
	int *ival;
	vector<double> dvec;
};

int main() {
	print_file_line();

	MI mi;
	mi.print(42);

	return 0;
}
#endif

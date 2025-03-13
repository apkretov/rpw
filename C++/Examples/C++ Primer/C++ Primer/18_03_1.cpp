#ifndef ON

#include "../../stdafx.h"
using namespace std;

class ZooAnimal { //MINE
	string name_;
public:
	explicit ZooAnimal(const string &name) : name_(name) {}
	string name() const { return name_; }
};

#pragma region Multiple Inheritance
struct Bear : public ZooAnimal {
	using ZooAnimal::ZooAnimal; //MINE
};
#pragma endregion //Multiple Inheritance

class Endangered { //MINE
	bool is_endangered_;
public:
	explicit Endangered(bool is_endangered) : is_endangered_(is_endangered) {}
	bool isEndangered() const { return is_endangered_; }
};

#pragma region Multiple Inheritance
struct Panda : public Bear, public Endangered {
	explicit Panda(const string &name) : Bear(name), Endangered(true) {} //MINE
};
#pragma endregion //Multiple Inheritance

#pragma region Inherited Constructors and Multiple Inheritance
struct Base1 {
	Base1() = default;
	Base1(const string &) {} //TEST
	Base1(shared_ptr<int>) {}
};

struct Base2 {
	Base2() = default;
	Base2(const string &) {} //TEST
	Base2(int) {}
};

struct D1 : public Base1, public Base2 { //TEST! //																											error: D1 attempts to inherit D1::D1(const string&) from both base classes
	using Base1::Base1; // inherit constructors from Base1
	using Base2::Base2; // inherit constructors from Base2
};

struct D2 : public Base1, public Base2 {
	using Base1::Base1; // inherit constructors from Base1
	using Base2::Base2; // inherit constructors from Base2
	D2(const string &s) : Base1(s), Base2(s) {} //TEST! //																									D2 must define its own constructor that takes a string
	D2() = default; //TEST! //																																needed once D2 defines its own constructor
};
#pragma endregion //Inherited Constructors and Multiple Inheritance

void mine() {
	D1 d11;
	D1 d12(111);
	//TEST! D1 d2("hello");

	D2 d21;
	D2 d22(make_shared<int>(111));
	D2 d23("hello");
}

void Copy_and_Move_Operations_for_Multiply_Derived_Classes() {
	Panda ying_yang("ying_yang");
	Panda ling_ling = ying_yang; // uses the copy constructor
}

int main() {
	print_file_line();

	mine();

	return 0;
}
#endif

#ifdef EX_18_21

#include <iostream>
#include "../../stdafx.h"

namespace EX_18_21 {
	class CAD {};
	class Vehicle {};
	class List {};
	class istream {};
	class ostream {};

	class CADVehicle : public CAD, /*MINE*/public Vehicle { /*...*/ }; // (a)
	//ERR class DblList : public List, public List { ... }; // (b)
	class iostream : public istream, public ostream { /*...*/ }; // (c)
}

int main() {
	print_file_line();

	return 0;
}
#endif

#ifdef EX_18_22

#include "../../stdafx.h"
#include "18_03_1_2.h"
using namespace std;

int main() {
	print_file_line();

	MI mi;

	return 0;
}
#endif

#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Classes, Namespaces, and Scope
#ifdef _1
namespace A {
	int i;

	namespace B {
		int i; // hides A::i within B
		int j;

		int f1() {
			int j; // j is local to f1 and hides A::B::j
			return i; // returns B::i
		}
	} // namespace B is closed and names in it are no longer visible

	int f2() {
		//TEST return j; //																																error: j is not defined
		return B::j; //MINE
	}

	int j = i; // initialized from A::i
}
#else //_2
namespace A {
	int i = 111; //MINE //ORIG int i;
	int k;

	class C1 {
	public:
		C1() : i(0), j(0) {} // ok: initializes C1::i and C1::j
		int f1() { return k; } // returns A::k
		//TEST int f2() { return h; } // error: h is not defined
		int f3();
	private:
		int i; // hides A::i within C1
		int j;
	};

	int h = i; // initialized from A::i
}

int A::C1::f3() { // member f3 is defined outside class C1 and outside namespace A 
	return h; //TEST! //																																	ok: returns A::h
} 
#endif
#pragma endregion

void mine1() {
	//cout << "A::f2() = " << A::f2() << '\n'; //MINE

	A::C1 c;
	cout << "c.f3() = " << c.f3() << '\n';
}

void Argument_Dependent_Lookup_and_Parameters_of_Class_Type() {
	string s;
	cin >> s;

	operator>>(cin, s); //TEST!
	operator<<(cout, s);

	using std::operator>>; //TEST! //																													needed to allow cin >> s
	std::operator>>(std::cin, s); // ok: explicitly use	std:: >>
}

#pragma region Friend Declarations and Argument-Dependent Lookup
namespace A {
	class C { // two friends; neither is declared apart from a friend declaration // these functions implicitly are members of namespace A
		friend void f2(); // won’t be found, unless otherwise declared
		friend void f(const C &) { // found by argument-dependent lookup
			cout << "A::f(const C &)\n"; //MINE
		}
	};
}
#pragma endregion

int main() {
	print_file_line();

	//mine1();
	//Argument_Dependent_Lookup_and_Parameters_of_Class_Type();

#pragma region Friend Declarations and Argument-Dependent Lookup
	A::C cobj;
	f(cobj); //TEST!! //																																	ok: finds A::f through the friend declaration in A::C
	//TEST f2(); // error: A::f2 not declared
#pragma endregion

	return 0;
}
#endif

#ifdef EX_18_18_1

#include <iostream>
#include "../../stdafx.h"

struct struct_string {
	std::string mem1;
};

struct struct_int {
	int mem1;
};

void swap(struct_string &v1, struct_string &v2) noexcept {
	using std::swap;
	swap(v1.mem1, v2.mem1);
}

void swap(struct_int &v1, struct_int &v2) noexcept {
	using std::swap;
	swap(v1.mem1, v2.mem1);
}

template <typename T>
void print(const T &t1, const T &t2) {
	std::cout << "t1: " << t1.mem1 << '\n';
	std::cout << "t2: " << t2.mem1 << '\n';
}

int main() {
	print_file_line();

	struct_string s1{"one"};
	struct_string s2{"two"};
	
	print(s1, s2);
	swap(s1, s2);
	print(s1, s2);

	struct_int i1{1};
	struct_int i2{2};	
	
	std::cout << '\n';
	print(i1, i2);
	swap(i1, i2);
	print(i1, i2);

	return 0;
}
#endif

#ifdef EX_18_18_2
#include <iostream>
#include <utility>
#include "../../stdafx.h"

template <typename T>
void swap(T &v1, T &v2) {
	using std::swap;
	swap(v1.mem1, v2.mem1);
}

template <typename T>
void print(const T &t1, const T &t2) {
	std::cout << "t1: " << t1.mem1 << '\n';
	std::cout << "t2: " << t2.mem1 << '\n';
}

struct struct_string {
	std::string mem1;
};

struct struct_int {
	int mem1;
};

template <typename T, typename U>
void print_swap(const U &u1, const U &u2) {
	T s1(u1);
	T s2(u2);

	print(s1, s2);
	swap(s1, s2);
	print(s1, s2);
}

int main() {
	print_file_line();

	print_swap<struct_string>(struct_string{"one"}, struct_string{"two"});
	std::cout << '\n';
	print_swap<struct_int>(struct_int{1}, struct_int{2});

	return 0;
}
#endif

#ifdef EX_18_19

#include <iostream>
#include "../../stdafx.h"

struct struct_string {
	std::string mem1;
};

struct struct_int {
	int mem1;
};

template <typename T>
void print(const T &t1, const T &t2) {
	std::cout << "t1: " << t1.mem1 << '\n';
	std::cout << "t2: " << t2.mem1 << '\n';
}

int main() {
	print_file_line();

	struct_string s1{"one"};
	struct_string s2{"two"};

	print(s1, s2);
	std::swap(s1, s2);
	print(s1, s2);

	struct_int i1{1};
	struct_int i2{2};

	std::cout << '\n';
	print(i1, i2);
	std::swap(i1, i2);
	print(i1, i2);

	return 0;
}
#endif

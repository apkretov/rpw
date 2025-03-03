#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Violating the Exception Specification // this function will compile, even though it clearly violates its exception specification
void f() noexcept { // promises not to throw any exception
	throw exception(); //TEST! //																														violates the exception specification
}
#pragma endregion

#pragma region BACKWARD COMPATIBILITY: EXCEPTION SPECIFICATIONS
void recoup(int) noexcept; // recoup doesn’t throw
void recoup(int) throw(); //TEST!! //																													equivalent declaration
#pragma endregion

#pragma region Arguments to the noexcept Specification
void recoup(int) noexcept(true); //TEST //																												recoup won’t throw
void alloc(int) noexcept(false); //TEST //																												alloc can throw
#pragma endregion

//MINE
void recoup(int) noexcept {/*empty*/}
void alloc(int) {/*empty*/}

#pragma region The noexcept Operator
void The_noexcept_Operator() {
	//TEST!! noexcept(recoup(i)) //																														true if calling recoup can’t throw, false otherwise
	cout << format("noexcept(recoup(0)) = {}\n", noexcept(recoup(0))); //MINE
}

void g() noexcept; //MINE
void f() noexcept(noexcept(g())); //TEST!! //																											f has same exception specifier as g
#pragma endregion

void Exception_Specifications_and_Pointers_Virtuals_and_Copy_Control() {
	void (*pf1)(int) noexcept = recoup; //TEST!! //																										both recoup and pf1 promise not to throw
	void (*pf2)(int) = recoup; //TEST!! //																												ok: recoup won’t throw; it doesn’t matter that pf2 might
	//TEST pf1 = alloc; //																																error: alloc might throw but pf1 said it wouldn’t
	pf2 = alloc; // ok: both pf2 and alloc might throw

#ifdef OFF
	class Base {
	public:
		virtual double f1(double) noexcept; // doesn’t throw
		virtual int f2() noexcept(false); // can throw
		virtual void f3(); // can throw
	};

	class Derived : public Base {
	public:
		//TEST!! double f1(double); //																													error: Base::f1 promises not to throw
		int f2() noexcept(false); // ok: same specification as Base::f2
		void f3() noexcept; //TEST!! //																													ok: Derived f3 is more restrictive
	};
#endif
}

int main() {
	print_file_line();
	
	The_noexcept_Operator();

	return 0;
}
#endif

#ifdef EX_18_08

#include <iostream>
#include "../../stdafx.h"
#include "18_01_4_1.h"
#include "18_01_4_2.h"
using namespace std;

int main() {
	print_file_line();
	
	Blob<int> bi{ 1,2,3,4,5 };
	Blob<string> bs{ "a","an","the" };

	cout << "bi: " << bi << '\n';
	cout << "bs: " << bs << '\n';	

	return 0;
}
#endif
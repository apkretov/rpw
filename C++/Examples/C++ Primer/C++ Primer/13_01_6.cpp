#ifdef ON

#include <iostream>
#include <memory>
using namespace std;

void Defining_a_Function_as_Deleted() {
	struct NoCopy {
		NoCopy() = default; // use the synthesized default constructor
		NoCopy(const NoCopy &) = delete; //TEST!! //																																						no copy
		NoCopy &operator=(const NoCopy &) = delete; //TEST!! //																																			no assignment
		~NoCopy() = default; // use the synthesized destructor
		// other members
	};
}

void The_Destructor_Should_Not_be_a_Deleted_Member() {
	struct NoDtor {
		NoDtor() = default; // use the synthesized default constructor
		~NoDtor() = delete; // we can’t destroy objects of type NoDtor
	};
	
	//TEST!! NoDtor nd; //																																												error: NoDtor destructor is deleted
	//TEST!! NoDtor *p = new NoDtor(); //																																								ok: but we can’t delete p
	//TEST!! delete p; //																																												error: NoDtor destructor is deleted
}

void private_Copy_Control() {
	class PrivateCopy {
		PrivateCopy(const PrivateCopy &); //TEST! //																																					no access specifier; following members are private by default; see § 7.2 (p. 268) // copy control is private and so is inaccessible to ordinary user code
		PrivateCopy &operator=(const PrivateCopy &);
		// other members
	public:
		PrivateCopy() = default; // use the synthesized default constructor
		//OFF ~PrivateCopy(); // users can define objects of this type but not copy them
	};

	//MINE
	PrivateCopy pc1;
	//TEST!! PrivateCopy pc2(pc1); 
	//TEST!! PrivateCopy pc3 = pc1; 
}

void mine() {
	class A {
		A(const A &) = default;
		A &operator=(const A &) = default;
	public:
		A() = default;
		int i{};

		unique_ptr<A> operator()() { //TEST!
			unique_ptr<A> a2(new(A));
			a2->i = this->i;
			return a2;
		}
	};

	A a1;
	a1.i = 1;
	//TEST A a2(a1); 
	//TEST! auto a3 = a1();
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Defining_a_Function_as_Deleted();
	//The_Destructor_Should_Not_be_a_Deleted_Member();
	mine();

	return 0;
}
#endif
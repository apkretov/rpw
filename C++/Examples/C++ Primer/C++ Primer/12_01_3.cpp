#ifdef ON

#include <iostream>
using namespace std;

#ifndef Using_shared_ptrs_with_new

void f() {
	shared_ptr<double> p1; // shared_ptr that can point at a double
	shared_ptr<int> p2(new int(42)); // p2 points to an int with value 42

	{
		//TEST! shared_ptr<int> p1 = new int(1024); //																																					error: must use direct initialization
		shared_ptr<int> p2(new int(1024)); //																																							ok: uses direct initialization
	}
}

#ifdef _1
shared_ptr<int> clone(int p) {
	//TEST!! return new int(p); //																																										error: implicit conversion to shared_ptr<int>
}

#elif! _2
shared_ptr<int> clone(int p) {
	return shared_ptr<int>(new int(p)); //TEST!! //																																						ok: explicitly create a shared_ptr<int> from int*
}
#endif
#endif

#ifndef Dont_Mix_Ordinary_Pointers_and_Smart_Pointers
void process(shared_ptr<int> ptr) { // ptr is created and initialized when process is called
	// use ptr
} // ptr goes out of scope and is destroyed

void f1() {
	shared_ptr<int> p(new int(42)); // reference count is 1
	process(p); // copying p increments its count; in process the reference count is 2
	int i = *p; // ok: reference count is 1
}

void f2() {
	int *x(new int(1024)); // dangerous: x is a plain pointer, not a smart pointer
	//TEST! process(x); //																																												error: cannot convert int* to shared_ptr<int>
	process(shared_ptr<int>(x)); //																																										legal, but the memory will be deleted!
	//TEST!! int j = *x; //																																												undefined: x is a dangling pointer!
}
#endif

void and_Dont_Use_get_to_Initialize_or_Assign_Another_Smart_Pointer() {
	shared_ptr<int> p(new int(42)); // reference count is 1
	int *q = p.get(); //TEST! //																																										ok: but don’t use q in any way that might delete its pointer
	{ // new block
		shared_ptr<int>(q); //TEST!! //																																									undefined: two independent shared_ptrs point to the same memory
	} //																																																block ends, q is destroyed, and the memory to which q points is freed
	int foo = *p; //TEST! //																																											undefined; the memory to which p points was freed
}

void Other_shared_ptr_Operations() {
	shared_ptr<int> p; //MINE

	//TEST! p = new int(1024); //																																										error: cannot assign a pointer to a shared_ptr
	p.reset(new int(1024)); //TEST!! //																																									ok: p points to a new object

#ifdef ERR
	if (!p.unique())
		p.rexset(new string(*p)); // we aren’t alone; allocate a new copy
	*p += newVal; // now that we know we’re the only pointer, okay to change this object
#endif
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//f2();
	and_Dont_Use_get_to_Initialize_or_Assign_Another_Smart_Pointer();

	return 0;
}
#endif

#ifdef EX_12_10

#include <iostream>
using namespace std;

void process(shared_ptr<int> ptr) {
	cout << *ptr << '\n';
	*ptr *= 2;
	cout << *ptr << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	shared_ptr<int> p(new int(42));
	
	process(shared_ptr<int>(p)); //TEST! 
	cout << *p << '\n'; //TEST! 

	return 0;
}
#endif

#ifdef EX_12_11

#include <iostream>
using namespace std;

void process(shared_ptr<int> ptr) {
	cout << *ptr << '\n';
	*ptr *= 2;
	cout << *ptr << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	shared_ptr<int> p(new int(42));

	process(shared_ptr<int>(p.get())); //TEST!!
	cout << *p << '\n'; //TEST!!

	return 0;
}
#endif

#ifdef EX_12_12

#include <iostream>
using namespace std;

void process(shared_ptr<int> ptr) {
	cout << "*ptr = " << *ptr << '\n';
	*ptr *= 2;
	cout << "*ptr = " << *ptr << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto p = new int();
	auto sp = make_shared<int>();
	cout << "*sp = " << * sp << '\n'; //TEST!! //MINE

	process(sp); //TEST!! // (a)
	//TEST! process(new int()); // (b)
	//TEST! process(p); // (c)
	process(shared_ptr<int>(p)); // (d)

	return 0;
}
#endif

#ifdef EX_12_13

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto sp = make_shared<int>();
	auto p = sp.get();

	cout << __LINE__ << endl;
	try {
		delete p; //TEST!!
	}
	catch (const exception &e) {
		cerr << e.what() << '\n';
	}
	cout << __LINE__ << endl;

	return 0;
}
#endif

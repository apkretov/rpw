#ifdef ON

#include <iostream>
using namespace std;
#include "12_01_4.h"
using namespace Smart_Pointers_and_Dumb_Classes;
using namespace Using_Our_Own_Deletion_Code;

void unique_ptr_() {
	unique_ptr<double> p1; // unique_ptr that can point at a double
	unique_ptr<int> p2(new int(42)); // p2 points to int with value 42
	{
		unique_ptr<string> p1(new string("Stegosaurus"));
		//TEST! unique_ptr<string> p2(p1); //																																							error: no copy for unique_ptr
		unique_ptr<string> p3;
		//TEST! p3 = p2; //																																												error: no assign for unique_ptr

		//																																																transfers ownership from p1 (which points to the string Stegosaurus) to p2
		//TEST! unique_ptr<string> p2(p1.release()); //																																					release makes p1 null
		{
			unique_ptr<string> p3(new string("Trex"));
		}
		//																																																transfers ownership from p3 to p2
		//TEST! p2.reset(p3.release());																																									// reset deletes the memory to which p2 had pointed

		//TEST! p2.release(); //																																										WRONG: p2 won’t free the memory and we’ve lost the pointer
		//TEST! auto p = p2.release(); //																																								ok, but we must remember to delete(p)
	}
}

#ifndef Passing_and_Returning_unique_ptrs
#ifndef _1
unique_ptr<int> clone(int p) { //TEST!! 
	return unique_ptr<int>(new int(p)); //																																								ok: explicitly create a unique_ptr<int> from int*
}

#elif! _2
unique_ptr<int> clone(int p) {
	unique_ptr<int> ret(new int(p));
	// ...
	return ret;
}
#endif
#endif

namespace Passing_a_Deleter_to_unique_ptr {
	void f(destination &d /* other needed parameters */) {
		connection c = connect(&d); // open the connection
		// when p is destroyed, the connection will be closed
		unique_ptr<connection, decltype(end_connection) *> p(&c, end_connection);
		// use the connection
		// when f exits, even if by an exception, the connection will be properly closed
	}
}

connection mine2() {
	connection c;
	return c;
}

void mine1() {
	cout << __LINE__ << '\n';
	//auto c1 = std::move(mine2());
	auto c2 = mine2();
	cout << __LINE__ << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	auto pi = clone(111);
	cout << *pi << '\n';
	
	//destination d;
	//Passing_a_Deleter_to_unique_ptr::f(d);
	//mine1();

	return 0;
}
#endif

#ifdef EX_12_16

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	struct s {
		int i;
	};

	auto sp1 = make_shared<s>(), sp2(sp1);
	auto up1 = unique_ptr<s>(new(s));
	//ERR auto up2(up1);
	decltype(up1) up3;
	//ERR up3 = up1;

	return 0;
}
#endif

#ifdef EX_12_17

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int ix = 1024, *pi = &ix, *pi2 = new int(2048);
	typedef unique_ptr<int> IntP;

	//OFF IntP p0(ix); // (a)
	IntP p1(pi); // (b)
	IntP p2(pi2); // (c)
	IntP p3(&ix); // (d)
	IntP p4(new int(2048)); // (e)
	IntP p5(p2.get()); // (f)

	return 0;
}
#endif

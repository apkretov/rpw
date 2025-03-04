#include "stdafx.h" //C++/CLI Threading: Part I @ http://www.drdobbs.com/cpp/ccli-threading-part-i/184402018
using namespace System;
using namespace System::Threading;

public ref class C {
	static Object^ Lock = gcnew Object; /*1*/

public:
	static void F1() {
		Monitor::Enter(C::typeid); /*2*/
		try { /*perform some operation(s)*/	} /*3*/
		finally { Monitor::Exit(C::typeid); }
	}

	static void F2() {
		Monitor::Enter(C::typeid);
		// ...
		Monitor::Exit(C::typeid);
	}

	static void F3() {
		Monitor::Enter(Lock); /*4*/
		// ...
		Monitor::Exit(Lock);
	}

	static void F4() {
		Monitor::Enter(Lock);
		// ...
		Monitor::Exit(Lock);
}	};

int main(array<System::String ^> ^args) {
	return 0;
}

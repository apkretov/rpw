#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Local_Classes_May_Not_Use_Variables_from_the_Function_s_Scope // Local Classes May Not Use Variables from the Function’s Scope
int a, val;
namespace Local_Classes_May_Not_Use_Variables_from_the_Function_s_Scope {
	void foo(int val) {
		static int si;
		enum Loc { a = 1024, b };

		struct Bar { // Bar is local to foo
			Loc locVal; // ok: uses a local type name
			int barVal;
			void fooBar(Loc l = a) { // ok: default argument is Loc::a
				//TEST! barVal = val; //																													error: val is local to foo
				barVal = ::val; // ok: uses a global object
				barVal = si; // ok: uses a static local object
				locVal = b; // ok: uses an enumerator
			}
		};
		// ...
	}
}
#pragma endregion

#pragma region Nested Local Classes
void foo() {
	class Bar {
	public:
		// ...
		class Nested; // declares class Nested
	};
	// definition of Nested
	class Bar::Nested {
		// ...
	};
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif
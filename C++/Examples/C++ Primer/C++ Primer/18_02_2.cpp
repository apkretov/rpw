#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Namespace Aliases
namespace cplusplus_primer {
	/* . . . */
	namespace QueryLib { //MINE
		struct Query {}; //MINE
	}
};

namespace primer = cplusplus_primer; //TEST!!

namespace Qlib = cplusplus_primer::QueryLib; //TEST!
Qlib::Query	q;
#pragma endregion

#pragma region using Directives and Scope
namespace A { // namespace A and function f are defined at global scope
	int i, j;
}

void f() {
	using namespace A; // injects the names from A into the global scope
	cout << i * j << endl; // uses i and j from namespace A
	// ...
}
#pragma endregion

#pragma region using Directives Example
namespace blip {
	int i = 16, j = 15, k = 23;
	// other declarations
}

int j = 0; // ok: j inside blip is hidden inside a namespace

void manip() {
	using namespace blip; //TEST! //																													using directive; the names in blip are ‘‘added’’ to the global scope // clash between ::j and blip::j
	++i; // detected only if j is used // sets blip::i to 17
	//TEST! ++j; //																																		error ambiguous: global j or blip::j?
	++::j; // ok: sets global j to 1
	++blip::j; // ok: sets blip::j to 16
	int k = 97; // local k hides blip::k
	++k; // sets local k to 98
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_18_16

#include <iostream>
#include "../../stdafx.h"
using namespace std;

namespace Exercise {
	int ivar = 111; //ORIG = 0;
	double dvar = 0;
	const int limit = 1000;
}

int ivar = 222; //ORIG = 0;

// position 1
#ifndef DECLARATIONS_AT_POSITION_1
//TEST! using Exercise::ivar;
using Exercise::dvar;
using Exercise::limit;
#endif

#ifdef DIRECTIVE_AT_POSITION_1
using namespace Exercise;
#endif

void manip() {
	// position 2
#ifdef DECLARATIONS_AT_POSITION_2
	using Exercise::ivar; 
	//TEST using Exercise::dvar;
	using Exercise::limit;
#endif

#ifdef DIRECTIVE_AT_POSITION_2
using namespace Exercise;
#endif

	double dvar = 3.1416;
	int iobj = limit + 1;

	++ivar; //TEST
	cout << "ivar = " << ivar << '\n';

	++::ivar; //TEST
	cout << "::ivar = " << ::ivar << '\n';
}

int main() {
	print_file_line();

	manip();

	return 0;
}
#endif

#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Base_Classes_and_Deleted_Copy_Control_in_the_Derived
class B {
public:
	B() = default; //MINE //ORIG: B();
	B(const B &) = delete;
	// other members, not including a move constructor
};

class D : public B {
	// no constructors
};

void Base_Classes_and_Deleted_Copy_Control_in_the_Derived_() {
	D d; //																																															ok: D’s synthesized default constructor uses B’s default constructor
	//TEST!! D d2(d); //																																												error: D’s synthesized copy constructor is deleted
	//TEST!! D d3(std::move(d)); //																																									error: implicitly uses D’s deleted copy constructor
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_15_07_2

#include <iostream>
#include "../../stdafx.h"
#include "15_07_2.h"
#include "15_06.h"
#include "15_04_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
	Bulk_quote b;
	
	return 0;
}
#endif
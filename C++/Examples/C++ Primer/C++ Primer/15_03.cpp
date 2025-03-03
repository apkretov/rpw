#ifdef ON

#include "../../stdafx.h"
#include "15_02_2_2.h"
#include "15_01_2.h" //This must not be included prior to 15_02_2_2.h.
using namespace std;

void Calls_to_Virtual_Functions_May_Be_Resolved_at_Run_Time() {
	Quote base("0-201-82470-1", 50);
	print_total(cout, base, 10); // calls Quote::net_price
	Bulk_quote derived("0-201-82470-1", 50, 5, .19);
	print_total(cout, derived, 10); // calls Bulk_quote::net_price

	base = derived; // copies the Quote part of derived into base
	base.net_price(20); // calls Quote::net_price
}

#ifndef The_final_and_override_Specifiers
struct B {
	virtual void f1(int) const;
	virtual void f2();
	void f3();
};

struct D1 : B {
	void f1(int) const override; //																																									ok: f1 matches f1 in the base
	//TEST void f2(int) override; //																																								error: B has no f2(int) function
	//TEST! void f2(int); //MINE
	//TEST! void f3() override; //																																									error: f3 not virtual
	//TEST void f4() override; //																																									error: B doesn’t have a function named f4
};

struct D2 : B {
	// inherits f2() and f3() from B and overrides f1(int)
	void f1(int) const final; // subsequent classes can’t override f1(int)
};
struct D3 : D2 {
	void f2(); // ok: overrides f2 inherited from the indirect base, B
	//TEST! void f1(int) const; //																																									error: D2 declared f2 as final
};
#endif

void Circumventing_the_Virtual_Mechanism() {
	const Bulk_quote base, *baseP = &base; //MINE
	double undiscounted = baseP->Quote::net_price(42); //TEST! //																																	calls the version from the base class regardless of the dynamic type of baseP
}

int main(int argc, char *argv[]) {
	print_file_line();

	Calls_to_Virtual_Functions_May_Be_Resolved_at_Run_Time();

	return 0;
}
#endif

#ifdef EX_15_13

#include "15_03.h"
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
	derived d, &r = d;
	r.print(cout);
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_15_14

#include "15_03.h"
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	base bobj; 
	base *bp1 = &bobj; 
	base &br1 = bobj;
	
	derived dobj; 
	base *bp2 = &dobj; 
	base &br2 = dobj;
	
	bobj.print(cout); // (a)
	dobj.print(cout); // (b)
	
	// Run-time.
	bp1->name(); // (c)
	bp2->name(); // (d)
	br1.print(cout); // (e)
	br2.print(cout); // (f)

	return 0;
}
#endif


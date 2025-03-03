#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i = 0;
	int *const p1 = &i; //																																											we can’t change the value of p1; const is top-level
	const int ci = 42; //																																											we cannot change ci; const is top-level
	const int *p2 = &ci; //																																											we can change p2; const is low-level
	const int *const p3 = p2; //																																									right-most const is top-level, left-most is not
	const int &r = ci; //																																											const in reference types is always low-level

	i = ci; //																																														ok: copying the value of ci; top-level const in ci is ignored
	//TEST! p2 = p3; //																																												ok: pointed-to type matches; top-level const in p3 is ignored
	
	//TEST int *p = p3; //																																											error: p3 has a low-level const but p doesn’t
	p2 = p3; //																																														ok: p2 has the same low-level const qualification as p3
	p2 = &i; //																																														ok: we can convert int* to const int*
	//TEST int &r = ci; //																																											error: can’t bind an ordinary int& to a const int object
	//TEST! const int &r2 = i; //																																									ok: can bind const int& to plain int
	
	return 0;
}
#endif

#undef EX_02_30
#ifdef EX_02_30

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const int v2 = 0;
	int v1 = v2;
	v1 = 0; //MINE
	//TEST int *p1 = &v1, &r1 = v1; 
	int i{}; //MINE
	//TEST const int *p2 = &v2, *const p3 = &i, &r2 = v2; 

#undef EX_02_31
#ifdef EX_02_31
	//TEST r1 = v2; 
	//TEST p1 = p2;
	//TEST p2 = p1; 
	//TEST p1 = p3; 
	//TEST p2 = p3; 
#endif
}
#endif
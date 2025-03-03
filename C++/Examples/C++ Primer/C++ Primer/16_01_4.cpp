#ifdef ON

#include <iostream>
#include <functional>
#include <list>
#include <array>
#include "../../stdafx.h"
#include "16_01_4_1.h"
#include "16_01_4_2.h"
using namespace std;

void Member_Templates_of_Ordianary_Nontemplate_Classes_() { //ORIG Member Templates of Ordianary (Nontemplate) Classes
#ifdef OFF
	double *p = new double;
	DebugDelete d; // an object that can act like a delete expression
	d(p); // calls DebugDelete::operator()(double*), which deletes p

	int *ip = new int;
	DebugDelete()(ip); //TEST! //																																calls operator()(int*) on a temporary DebugDelete object
#endif

	//ERR unique_ptr<int, DebugDelete> p(new int, DebugDelete()); //																							destroying the the object to which p points // instantiates DebugDelete::operator()<int>(int *)
	unique_ptr<string, DebugDelete> sp(new string, DebugDelete()); //TEST! //																					destroying the the object to which sp points	// instantiates DebugDelete::operator()<string>(string*)
}

#ifdef MINE
template <typename T>
const auto DebugDeleteLambda = [](T *p) {
	cout << "deleting unique_ptr in DebugDeleteLambda\n";
	delete p;
	};

template <typename T>
void DebugDeleteFnc(T *p) {
	cout << "deleting unique_ptr in DebugDeleteFnc\n";
	delete p;
};

void mine1() {
	auto p1 = unique_ptr<int, decltype(DebugDeleteLambda<int>)>(new int(10), DebugDeleteLambda<int>);
	auto ps = unique_ptr<int, function<void(int *)>>(new int(10), DebugDeleteFnc<int>);
}
#endif

void mine2() {
	using namespace std;
	auto out = ostream_iterator<int>(cout, " ");

	vector<int> v1 = {1,2,3,4,5};
	cout << "v1: ";
	ranges::copy(v1, out);

	vector<int> v2(v1.begin() + 1, v1.end() - 1);
	cout << "\nv2: ";
	ranges::copy(v2, out);
	cout << '\n';
}

void Instantiation_and_Member_Templates_() {
	array<int, 10> ia = {0,1,2,3,4,5,6,7,8,9}; //ORIG int ia[] = {0,1,2,3,4,5,6,7,8,9};
	vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
	list<const char *> w = {"now", "is", "the", "time"};

	Blob<int> a1(begin(ia), end(ia)); //TEST //																														// instantiates the Blob<int> class and the Blob<int>	// constructor that has two int* parameters // instantiates the Blob<int> class	// and the Blob<int> constructor that has two int* parameters
	Blob<int> a2(vi.begin(), vi.end()); // 																															instantiates the Blob<int> constructor that has // two vector<long>::iterator parameters
	Blob<string> a3(w.begin(), w.end()); // 																														instantiates the Blob<string> class and the Blob<string>	// constructor that has two (list<const char*>::iterator parameters

	//MINE
	cout << "a1: " << a1 << '\n';
	cout << "a2: " << a2 << '\n';
	cout << "a3: " << a3 << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();

	//Member_Templates_of_Ordianary_Nontemplate_Classes_();
	//mine1();
	//mine2();
	Instantiation_and_Member_Templates_();

	return 0;
}
#endif

#ifdef EX_16_22
#include <iostream>
#include <fstream>
//OFF #include <vld.h>
#include "../../stdafx.h"
#include "16_01_4_3.h" // Keep the headers sequence.
#include "12_03_2_4.h"
#include "12_03_2_3.h"
using namespace std;

int main(int, char *argv[]) {
	using namespace std;
	print_file_line();

	ifstream in(argv[1]);
	runQueries(in);

	return 0;
}
#endif

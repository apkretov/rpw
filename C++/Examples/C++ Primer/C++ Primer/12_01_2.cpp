#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void Using_new_to_Dynamically_Allocate_and_Initialize_Objects() {
	int *pi = new int; //TEST!! //																																									pi points to a dynamically allocated, unnamed, uninitialized int

	{
		string *ps = new string; // initialized to empty string
		int *pi = new int; // pi points to an uninitialized int
	}

	{
		int *pi = new int(1024); //TEST!! //																																						object to which pi points has value 1024
		string *ps = new string(10, '9'); //TEST!! //																																				*ps is "9999999999"
		vector<int> *pv = new vector<int>{0,1,2,3,4,5,6,7,8,9}; //TEST!! //																															vector with ten elements with values from 0 to 9
	}

	string *ps1 = new string; //TEST!! //																																							default initialized to the empty string
	string *ps = new string(); //TEST!! //																																							value initialized to the empty string
	string *ps2 = new string{}; //TEST! //MINE
	int *pi1 = new int; //TEST!! //																																									default initialized; *pi1 is undefined
	int *pi2 = new int(); //TEST!! //																																								value initialized to 0; *pi2 is 0
	int *pi3 = new int{}; //TEST!! //MINE

	auto obj{0}; //MINE
	auto p1 = new auto(obj); //																																										p points to an object of the type of obj // that object is initialized from obj
	auto a{0}, b{0}, c{0};
	//TEST!! auto p2 = new auto{a,b,c}; //																																							error: must use parentheses for the initializer
	auto p3 = new auto(1); //TEST!! //MINE
	auto *p = new auto(*ps1); //TEST!! //MINE
}

void Dynamically_Allocated_const_Objects() {
	const int *pci = new const int(1024); //TEST!! //																																				allocate and initialize a const int
	const string *pcs = new const string; //TEST!! //																																				allocate a default-initialized const empty string
}

void Memory_Exhaustion() {
	int *p1 = new int; // if allocation fails, new throws std::bad_alloc
	int *p2 = new (nothrow) int; //TEST!! //																																						if allocation fails, new returns a null pointer
}

void Freeing_Dynamic_Memory() {
	void *p{nullptr}; //MINE
	delete p;
}

void Pointer_Values_and_delete() {
	int i, *pi1 = &i, *pi2 = nullptr;
	double *pd = new double(33), *pd2 = pd;
	//TEST delete i; //																																												error: i is not a pointer
	delete pi1; //TEST!! //																																											undefined: pi1 refers to a local
	delete pd; //TEST // 																																											ok
	delete pd2; //TEST!! // 																																										undefined: the memory pointed to by pd2 was already freed
	delete pi2; //TEST! // 																																											ok: it is always ok to delete a null pointer

	const int *pci = new const int(1024);
	delete pci; //TEST //																																											ok: deletes a const object
}

#ifndef Dynamically_Allocated_Objects_Exist_until_They_Are_Freed

using Foo = int; //MINE

template <typename T> //MINE
Foo *factory(T arg) { // factory returns a pointer to a dynamically allocated object
	// process arg as appropriate
	return new Foo(arg); //TEST! //																																									caller is responsible for deleting this memory
}

#ifdef _1
template <typename T> //MINE
void use_factory(T arg) {
	Foo *p = factory(arg);
	//TEST! // use p but do not delete it
} //																																																p goes out of scope, but the memory to which p points is not freed!

#elif _2
template <class T> //MINE
void use_factory(T arg) {
	Foo *p = factory(arg);
	// use p
	delete p; // remember to free the memory now that we no longer need it
}

#elif! _3
template <typename T> //MINE
Foo *use_factory(T arg) {
	Foo *p = factory(arg);
	// use p
	return p; // caller must delete the memory
}
#endif
#endif

void  Provides_Only_Limited_Protection() {
	int *p(new int(42)); // p points to dynamic memory
	auto q = p; // p and q point to the same memory
	delete p; // invalidates both p and q
	p = nullptr; //TEST1 //																																												indicates that p is no longer bound to an object
	cout << *q << '\n'; //TEST! //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Provides_Only_Limited_Protection();

	return 0;
}
#endif

#ifdef EX_12_06 
#include <iostream>
#include <vector>
using namespace std;

vector<int> *factory() {	
	return new vector<int>;
}

void fill(vector<int> *pv) {
	int i;
	while (cin >> i)
		pv->push_back(i);

	istream_iterator<int> in (cin);
}

int main(int argc, char *agrv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto pv = factory();
	delete pv;

	return 0;
}
#endif

#ifdef EX_12_07

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

using pv = shared_ptr<vector<int>>;

pv getvec() {
	return make_shared<vector<int>>();
}

pv input(pv p) {
	int i;
	
	while (cin >> i)
		p->push_back(i);
	
	return p;
}

void print(pv p) {
	copy(p->cbegin(), p->cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto p = getvec();
	p = input(p);
	print(p);

	return 0;
}
#endif

#ifdef EX_12_08

#include <iostream>
using namespace std;

bool b() {
	int *p = new int;
	// ...
	return p;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto b = b();

	return 0;
}
#endif

#ifdef EX_12_09

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int *q = new int(42), *r = new int(100);
	r = q;
	auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
	r2 = q2;

	return 0;
}
#endif

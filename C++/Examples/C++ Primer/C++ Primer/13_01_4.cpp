#ifdef ON

#ifndef EX_13_05

#include <iostream>
using namespace std;

class HasPtr {
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {
		cout << "HasPtr constructor: *ps = " << *ps << '\n';
	}

	HasPtr(const HasPtr &);
	~HasPtr();
#ifndef Classes_That_Need_Destructors_Need_Copy_and_Assignment
	//TEST!																																														// WRONG: HasPtr needs a copy constructor and copy-assignment operator
	// other members as before
#endif
private:
	string *ps;
	int i;
};

HasPtr::HasPtr(const HasPtr &hp) : ps(new string(*hp.ps)), i(hp.i) { // ch13/ex13_05.h @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch13/ex13_05.h // ch13/13.5.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.5.cpp
	cout << "HasPtr copy-constructor: *ps = " << *ps << '\n';
}

HasPtr::~HasPtr() {
	cout << "HasPtr destructor: *ps = " << *ps << '\n';
	delete ps;
}
#endif

#ifndef Classes_That_Need_Destructors_Need_Copy_and_Assignment {
HasPtr f(HasPtr hp) { //																																										HasPtr passed by value, so it is copied
	HasPtr ret = hp; //																																											copies the given HasPtr
	// process ret
	return ret; //																																												ret and hp are destroyed
}

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	HasPtr p("some values");
	f(p); //																																													when f completes, the memory to which p.ps points is freed
	HasPtr q(p); //TEST!! //																																									now both p and q point to invalid memory!

	return 0;
}
#endif
#endif

#ifdef EX_13_14

#include <iostream>
using namespace std;

struct numbered {
	numbered() : mysn(sn++) {
		cout << "Constructor\n";
	}

	numbered(const numbered &n) : mysn(n.mysn) {
		cout << "Copy constructor\n";
	}

	static size_t sn;
	size_t mysn;
};

size_t numbered::sn{111};

void f(numbered s) {
	cout << s.mysn << endl;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);

	return 0;
}
#endif
#ifdef MINE

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct base {
	void foo() const {
		cout << "Base\n";
	}
};

struct derived : base {
	void foo() const { //TEST
		cout << "Derived\n";
	}
};

int main() {
	PRINT_FILE_LINE();

	base b;
	derived d;
	b.foo();
	d.foo();
}
#endif //MINE
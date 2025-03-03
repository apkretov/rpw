#ifdef MINE

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct base {
	explicit base(string_view s) : str(s) {}
	const string str; //TEST!
};

struct derived : base {
	using base::base;
};

int main() {
	PRINT_FILE_LINE();

	base b{"base"};
	derived d{"derived"};
	cout << b.str << '\n';
	cout << d.str << '\n';
#ifdef ERR
	b.str = "new";
	d.str = "new";
#endif //ERR
}
#endif //MINE
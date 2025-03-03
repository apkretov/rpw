#undef EX_04_13
#ifdef EX_04_13

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i; double d;

	d = i = 3.5; // (a) //TEST
	cout << d << '\t' << i << '\n';

	i = d = 3.5; // (b) //TEST
	cout << d << '\t' << i << '\n';

	return 0;
}
#endif

#undef EX_04_14
#ifdef EX_04_14

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i{};

	//TEST if (42 = i) ;
	if (i = 42) //TEST
		cout << "true\n";
	else
		cout << "false\n";

	return 0;
}
#endif

#undef EX_04_15
#ifdef EX_04_15

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	double dval; int ival; int *pi;
	
	//TEST dval = ival = pi = 0;

	return 0;
}
#endif

#undef EX_04_16
#ifdef EX_04_16

#include <iostream>
using namespace std;

decltype(nullptr) *getPtr() {
	return nullptr;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	decltype(nullptr) *p;
	int i{1024};

	if ((p = getPtr()) != 0) // (a)
		cout << "true\n";
	else
		cout << "false\n";
	
	if (i == 1024) // (b)
		cout << "true\n";
	else
		cout << "false\n";

	return 0;
}
#endif

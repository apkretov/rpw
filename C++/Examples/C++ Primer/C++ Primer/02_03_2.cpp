#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	double obj = 3.14, *pd = &obj;
	// ok:	void* can hold the address value of any data pointer type
	void* pv = &obj; //	obj can be an object of any type
	pv = pd; //	pv can hold a pointer to any type

	cout << pv << '\n';
	//ERR cout << *pv << '\n';
	cout << *static_cast<double*>(pv) << '\n';

	return 0;
}
#endif

#undef EX_02_18
#ifdef EX_02_18

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int* pi{nullptr};
	double* pd{nullptr};
	cout << pi << '\t' << pd << '\n';

	++pi;
	++pd;
	cout << pi << '\t' << pd << '\n';

	return 0;
}
#endif

#undef EX_02_21
#ifdef EX_02_21

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i = 0;
	//ERR double* dp = &i; // (a) 
	//ERR int* ip = i; // (b) 
	int* p = &i; //(c) 

	cout << *p << '\n';

	return 0;
}
#endif
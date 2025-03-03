#undef ON
#ifdef ON

#include <iostream>
#include <string>
using namespace std;

void Remember_That_Operands_Can_Be_Evaluated_in_Any_Order() {
	string s{"test"};

	for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
		*it = toupper(*it); // capitalize the current character
	cout << s << '\n'; 

	decltype(s.end()) beg;
	// the behavior of the following loop is undefined!
	while (beg != s.end() && !isspace(*beg))
		*beg = toupper(*beg++); // error: this assignment is undefined
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Remember_That_Operands_Can_Be_Evaluated_in_Any_Order();

	return 0;
}
#endif

#undef EX_04_18
#ifdef EX_04_18

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const vector<int> v{0, 1, -2};
	auto pbeg = v.begin();
	
	while (pbeg != v.end() && *pbeg >= 0) // print elements up to the first negative value
		cout << *pbeg++ << endl; // print the current value and advance pbeg

	pbeg = v.begin();
	cout << '\n';
	while (pbeg != v.end() && *pbeg >= 0) // print elements up to the first negative value
		cout << *++pbeg << endl; // print the current value and advance pbeg

	return 0;
}
#endif

#undef EX_04_19
#ifdef EX_04_19

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int ival{}, *ptr{&ival};
	vector<int> vec(3);

	//TEST cout << boolalpha << (ptr != 0 && *ptr++) << '\n'; // (a) 
	//TEST cout << boolalpha << (ival++ && ival) << '\n'; // (b)
	//TEST cout << boolalpha << (vec[ival++] <= vec[ival]) << '\n'; // (c)

	return 0;
}
#endif

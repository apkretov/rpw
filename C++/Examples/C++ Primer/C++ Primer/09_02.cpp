#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifdef Constraints_on_Types_That_a_Container_Can_Hold
	// assume noDefault is a type without a default constructor
	vector<noDefault> v1(10, init); // ok: element initializer supplied
	//TEST! vector<noDefault> v2(10); //																																							error: must supply an element initializer
#endif

	return 0;
}
#endif

#ifdef EX_09_04

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

using it = vector<int>::const_iterator;

bool findint(it beg, it end, int i) {
	while (beg != end) {
		if (*beg++ == i)
			return true;
	}
	return false;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr int n{5};
	vector<int> v = {0, 1, 2, 3, 4, 5};

	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
	auto found = findint(v.cbegin(), v.cend(), n);
	cout << '\n' << boolalpha << found << '\n';
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_09_05

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

using it = vector<int>::const_iterator;

it findint(it beg, it end, int i) {
	while (beg != end) {
		if (*beg == i)
			return beg;
		++beg;
	}
	return beg;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr int n{5};
	vector<int> v = {0, 1, 2, 3, 4, 5};
	
	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
	auto found = findint(v.cbegin(), v.cend(), n);
	if (found != v.cend())
		cout << '\n' << *found << '\n';
	else
		cout << "\nNot found.\n";

	return 0;
}
#endif

#ifdef EX_09_06

#include <iostream>
#include <list>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	list<int> l = {0, 1, 2, 3, 4, 5};
	auto beg = l.cbegin(), end = l.cend();

	//TEST! while (beg < end) 
	while (beg != end)
		cout << *beg++ << ' ';
	cout << '\n';

	return 0;
}
#endif

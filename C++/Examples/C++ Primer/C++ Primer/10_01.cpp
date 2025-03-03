#ifdef ON

#include <iostream>
#include <vector>
#include <list>
using namespace std;

void Overview() {
	vector<int> vec; //MINE
	int val = 42; // value we’ll look for
	auto result = find(vec.cbegin(), vec.cend(), val); // result will denote the element we want if it’s in vec, or vec.cend() if not
	cout << "The value " << val	<< (result == vec.cend() ? " is not present" : " is present") << endl; // report the result

	{
		list<string> lst;
		string val = "a value"; // value we’ll look for
		auto result = find(lst.cbegin(), lst.cend(), val); // this call to find looks through string elements in a list
	}

	int a[] = {0, 1, 2, 3, 4, 5};
	auto res = find(cbegin(a), cend(a), 3);
	//MINE
	if (res != cend(a))
		cout << "res = " << *res << '\n';		
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Overview();

	return 0;
}
#endif

#ifdef EX_10_01

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const vector<int> v = {1, 2, 3, 2, 3, 3};
	constexpr int n{3};

	//TEST! auto c = count(v.begin(), v.end(), n); 	cout << c << '\n';

	return 0;
}
#endif

#ifdef EX_10_02

#include <iostream>
#include <list>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const list<string> l = {"1, 2, 3, 2, 3, 3", "aaa", "bbb", "aaa"};
	const string s{"aaa"};

	auto c = count(l.begin(), l.end(), s);
	cout << c << '\n';

	return 0;
}
#endif

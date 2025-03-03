#undef ON
#ifdef ON

#include <iostream>
using std::cout;
#include <vector>
using std::vector;


int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v2; // empty vector
	for (int i = 0; i != 100; ++i)
		v2.push_back(i); // append sequential integers to v2
	// at end of loop v2 has 100 elements, values 0 ... 99

	return 0;
}
#endif

#undef EX_03_14
#ifdef EX_03_14

#include <iostream>
using std::cout;
using std::cin;
#include <vector>
using std::vector;


int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v;
	int i;

	while (cin >> i)
		v.push_back(i);
	
	for (int i : v) 
		cout << i << " ";
	cout << '\n';

	return 0;
}
#endif

#undef EX_03_15
#ifdef EX_03_15

#include <iostream>
using std::cout;
using std::cin;
#include <vector>
using std::vector;
#include <string>
using std::string;


int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> v;
	string text;

	while (cin >> text)
		v.push_back(text);

	for (string text : v)
		cout << text << " ";
	cout << '\n';

	return 0;
}
#endif
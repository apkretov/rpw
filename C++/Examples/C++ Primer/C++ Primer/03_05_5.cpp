#undef ON
#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void Mixing_Library_strings_and_C_Style_Strings() {
	string s("Hello World"); //	s holds	Hello World
	//ERR char *str = s; // error: can’t initialize a char* from a string
	const char *str = s.c_str(); // ok
}

void Using_an_Array_to_Initialize_a_vector() {
	int v[]{1, 2, 3};
	vector<int> v(begin(v), end(v));
	
	for (auto i : v)
		cout << i << " ";
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Mixing_Library_strings_and_C_Style_Strings();
	Using_an_Array_to_Initialize_a_vector();

	return 0;
}
#endif

#undef EX_03_42
#ifdef EX_03_42

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const vector<int> v{0, 1, 2, 3};
	int v[4]{};

	for (size_t i = 0; i < v.size(); ++i)
		v[i] = v.at(i);

	for (auto n : v)
		cout << n << ' ';
	cout << '\n';

	return 0;
}
#endif

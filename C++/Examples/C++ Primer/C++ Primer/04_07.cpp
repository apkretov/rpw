#undef ON
#ifdef ON

#include <iostream>
using namespace std;

void Using_a_Conditional_Operator_in_an_Output_Expression() {
	const int grade{61};
	
	//TEST cout << ((grade < 60) ? "fail" : "pass") << '\n'; // prints pass or fail
	//TEST cout << (grade < 60) ? "fail" : "pass"; // prints 1 or 0!
	//ERR cout << grade < 60 ? "fail" : "pass"; // error: compares cout to 60
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Using_a_Conditional_Operator_in_an_Output_Expression();

	return 0;
}
#endif

#undef EX_04_21
#ifdef EX_04_21

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v{1, 2, 3};

	for (int &i : v) {
		i = i % 2 ? i *= 2 : i;
		cout << i << ' ';
	}
	cout << '\n';
	
	return 0;
}
#endif

#undef EX_04_23
#ifdef EX_04_23

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string s = "word";
	string pl = s + (s[s.size() - 1] == 's' ? "" : "s");

	cout << pl << '\n';

	return 0;
}
#endif
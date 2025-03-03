#undef ON
#ifdef ON

#include <iostream>
using namespace std;

void Precedence_and_Associativity() {
	cout << 6 + 3 * 4 / 2 + 2 << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Precedence_and_Associativity();

	return 0;
}
#endif

#undef EX_04_02
#ifdef EX_04_02

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> vec{0, 1, 2};

	cout << *vec.begin() << '\n'; // (a)
	cout << *(vec.begin()) << '\n';

	cout << *vec.begin() + 1 << '\n'; // (b)
	cout << (*(vec.begin())) + 1 << '\n';

	return 0;
}
#endif
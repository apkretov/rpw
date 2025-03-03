#undef EX_06_25
#ifdef EX_06_25

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string arg;

	for (size_t i = 1; i < argc; ++i) {
		cout << *argv[i] << '\n';
		arg += *argv[i];
	}
	cout << arg << '\n';

	return 0;
}
#endif
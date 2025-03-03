#if 0

#include <istream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void Print(const vector<string> &names, const vector<double> values, int width) {
	for (const auto &n : names)
		cout << setw(width) << n;
	cout << '\n';

	cout << fixed << setprecision(2);
	for (const auto &v : values)
		cout << setw(width) << v;
}

int main() {
	PRINT_FILE_LINE();

	vector<string> names = {"a", "b", "c"};
	vector<double> values = {5, 0.01, 0.0000005};

	cout << left;
	cout << setfill('.'); //TEST!
	Print(names, values, 10);
	cout << '\n';
}
#endif
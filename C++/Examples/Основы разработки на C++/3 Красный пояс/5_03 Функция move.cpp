#if 0

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

vector<string> ReadStrings(istream &stream) {
	vector<string> strings;
	string s;
	while (stream >> s) {
		cout << AS_KV(s) << '\n';
		strings.push_back(move(s));
		cout << AS_KV(s) << ", " << AS_KV(strings.back()) << '\n';
	}
	return strings;
}

int main() {
	PRINT_FILE_LINE();

	for (const string &s : ReadStrings(cin))
		cout << s << '\n';

	return 0;
}
#endif //1
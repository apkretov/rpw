#include <iostream>
using namespace std;

bool isShorter(const string &s1, const string &s2) { // compare the length of two strings
	return s1.size() < s2.size();
}

#ifdef ON

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
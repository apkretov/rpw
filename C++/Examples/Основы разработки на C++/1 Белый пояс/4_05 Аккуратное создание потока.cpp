#if 1

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	fstream input("4_05 - hello.txt");
	string line;

	if (input) {
		while (getline(input, line))
			cout << line << '\n';
		cout << "Done!\n";
	} else
		cout << "Error!\n";
}
#endif
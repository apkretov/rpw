#if 0

#include <array>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	int x = 111111;
	array<int, 10> numbers;
	numbers.fill(8);
	int y = 222222;

	for (int *p = &y; p <= &x; ++p)
		cout << *p << ' '; // This does not work on my system.
	cout << '\n';

	return 0;
}
#endif //1
#ifdef EX_18_07

#include <algorithm>
#include <iostream>
#include <ranges>
#include "18_01_3_2.h"
#include "18_01_3_3.h"
using namespace std;

int main() {
	print_file_line();

	Blob<string> vs{"Hello", ",", "world", "!"};
	cout << vs << '\n';

	return 0;
}
#endif

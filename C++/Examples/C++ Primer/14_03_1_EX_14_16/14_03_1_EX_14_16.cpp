#include <iostream>
#include "../../stdafx.h"
#include "14_03_1_2.h"
#include "14_07.h"
using namespace std;

int main(int argc, char* argv[]) {
    print_file_line();

	StrBlob b1 = {"aaa", "bbb"};
	StrBlob b2 = {"ccc"};
	StrBlob b3 = {"aaa", "bbb"};
	
	cout << "b1:\t";
	print(b1);
	cout << "b2:\t";
	print(b2);
	cout << "b3:\t";
	print(b3);

	cout << "\n(b1 == b2) = " << boolalpha << (b1 == b2) << '\n';
	cout << "(b1 == b3) = " << boolalpha << (b1 == b3) << '\n';

	cout << "\nb1.begin().deref() = " << b1.begin().deref() << '\n';
	auto b = b1.begin(), e = b1.end();
	cout << *b << ' ' << *--e << '\n';

    return 0;
}
#ifdef MINE

#include <iostream>
#include "../../stdafx.h"
#include "StrBlob.h"
#include "StrBlobPtr.h"

int main(int argc, char* argv[]) {
	print_file_line();

	StrBlob b1 = {"aaa", "bbb"};
	StrBlob b2 = {"ccc"};
	StrBlob b3 = {"aaa", "bbb"};

	std::cout << AS_KV(b1) << '\n';
	std::cout << AS_KV(b2) << '\n';
	std::cout << AS_KV(b3) << '\n';

	std::cout << "\n(b1 == b2) = " << std::boolalpha << (b1 == b2) << '\n';
	std::cout << "(b1 == b3) = " << std::boolalpha << (b1 == b3) << '\n';

	std::cout << "\n*b1.begin() = " << *b1.begin() << '\n';
	auto b = b1.begin(), e = b1.end();
	std::cout << *b << ' ' << *--e << '\n';

	return 0;
}
#endif // MINE

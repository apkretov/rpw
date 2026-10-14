#if 0

#include <iostream>
#include "../05/05.h"
//OFF #include "vld.h"
#include "../../stdafx.h"

Generator my_coroutine() { co_yield 42; }

int main(int argc, char* arg[]) {
	print_file_line();

	auto ro = my_coroutine();
	if (ro.next())
		std::cout << AS_KV(ro.value()) << '\n';

	return 0;
}
#endif // 1

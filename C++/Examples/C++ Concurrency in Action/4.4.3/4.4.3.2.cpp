#ifndef MINE

#include "Listing 4.17.h"
#include <iostream>
#include "../../stdafx.h"

int main() {
	print_file_line();

	auto lambda = [] { return 42; };
	auto f = spawn_async(lambda);
	std::cout << AS_KV(f.get());
}
#endif //MINE
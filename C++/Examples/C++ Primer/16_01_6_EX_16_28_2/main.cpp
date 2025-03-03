#include <iostream> // ch16/ex16.28 @ https://github.com/Mooophy/Cpp-Primer/tree/master/ch16/ex16.28
#include <string>
#include "shared_pointer.hpp"
#include "unique_pointer.h"
#include "../../stdafx.h" //MINE

int main() {
	print_file_line(); //MINE

	auto foo = cp5::SharedPointer<int>{new int(42)};
	auto bar(foo);
	std::cout << *foo << std::endl;
	std::cout << foo.use_count() << std::endl;

	auto string_ptr = cp5::SharedPointer<std::string>{new std::string{ "Yue" }};
	std::cout << *string_ptr << std::endl;
	std::cout << string_ptr->size() << std::endl;

	//MINE
	auto string_ptr2 = unique_pointer<std::string>{new std::string{ "aaa" }};
	std::cout << *string_ptr2 << std::endl;
	std::cout << string_ptr2->size() << std::endl;

	return 0;
}
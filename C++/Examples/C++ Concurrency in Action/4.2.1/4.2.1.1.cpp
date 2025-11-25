#ifndef MINE

#include <future>
#include "listing_4.7.h"
#include "../../stdafx.h"

int main() { 
	print_file_line();

	X x;
	auto f1 = std::async(&X::foo, &x, 42, "hello"); // Calls p->foo(42,"hello") where p is& x
	auto f2 = std::async(&X::bar, x, "goodbye"); // Calls tmpx.bar("goodbye") where tmpx is a copy of x
	auto f2_2 = std::async(X{}); //MINE

	Y y;
	auto f3 = std::async(Y(), 3.141); // Calls tmpy(3.141) where tmpy is move - constructed from Y()
	auto f4 = std::async(std::ref(y), 2.718); // Calls y(2.718)
	auto f6 = std::async(baz, std::ref(x)); // Calls baz(x)

	auto f5 = std::async(move_only()); // Calls tmp() where tmp is constructed from std::move(move_only())
}
#endif //MINE
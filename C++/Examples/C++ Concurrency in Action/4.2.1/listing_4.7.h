#pragma once

#include <iostream>
#include <string>
#include <future>

struct X {
	void foo(int, std::string const&) {}
	std::string bar(std::string const&) { return std::string{}; }
	void operator()() { std::cout << "X::operator()\n"; } //MINE
};

#ifdef OFF
X x;
auto f1 = std::async(&X::foo, &x, 42, "hello");
auto f2 = std::async(&X::bar, x, "goodbye");
#endif //OFF

struct Y {
	double operator()(double) { return 0; }
};

#ifdef OFF
Y y;
auto f3 = std::async(Y(), 3.141);
auto f4 = std::async(std::ref(y), 2.718);
#endif //OFF

X baz(X&) { return X{}; }

//OFF auto f6 = std::async(baz, std::ref(x));

class move_only {
public:
	move_only() = default;
	move_only(move_only&&) = default;
	move_only(move_only const&) = delete;
	move_only& operator=(move_only&&) = default;
	move_only& operator=(move_only const&) = delete;

	void operator()() {
		std::cout << "move_only::operator()\n"; //MINE
	}
};

//OFF auto f5 = std::async(move_only());

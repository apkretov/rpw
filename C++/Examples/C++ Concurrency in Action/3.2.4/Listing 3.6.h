#pragma once

#include <iostream>
#include <mutex>

#ifdef ORIG
class some_big_object {};
void swap(some_big_object& lhs, some_big_object& rhs);

class X {
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd) :some_detail(sd) {}

	friend void swap(X& lhs, X& rhs) {
		if (&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		swap(lhs.some_detail, rhs.some_detail);
	}
};
#endif //ORIG

#ifndef MINE
class some_big_object {
public:
	int value = 0;

	void swap(some_big_object& other) noexcept {
		std::swap(value, other.value);
		std::cout << "Swapped: " << value << " <-> " << other.value << std::endl; // This swap function cannot be noexcept due to the std::cout statement, as stream operations can throw exceptions, but this is purely for educational demonstration of console output and would be omitted in production code.
	}
};

class X {
private:
	some_big_object some_detail;
	std::mutex m;
public:
	explicit X(int v = 0) : some_detail{v} {}
	X(const X&) = delete;
	X& operator=(const X&) = delete;

	int get_value() const { return some_detail.value; }

	friend void swap(X& lhs, X& rhs) noexcept { // Original Listing 3.6 (C++11)
		if (&lhs == &rhs) // ❶ Check self-swap
			return;  

		std::lock(lhs.m, rhs.m);   // ❷ Lock both atomically

		std::lock_guard lock_a(lhs.m, std::adopt_lock);  // ❸ Adopt locks
		std::lock_guard lock_b(rhs.m, std::adopt_lock);

		lhs.some_detail.swap(rhs.some_detail);
	}

	friend void swap_scoped(X& lhs, X& rhs) noexcept { // C++17 scoped_lock version (simpler)
		if (&lhs == &rhs) 
			return;
		std::scoped_lock guard(lhs.m, rhs.m);  // Locks both, RAII unlocks
		lhs.some_detail.swap(rhs.some_detail);
	}
};
#endif //MINE
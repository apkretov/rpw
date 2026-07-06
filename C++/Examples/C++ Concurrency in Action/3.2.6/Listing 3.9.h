#pragma once

#ifdef ORIG
#include <mutex>

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
#ifndef ORIG
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
		std::lock(lock_a, lock_b);
#else //SCOPED_LOCK
		std::scoped_lock lock(lhs.m, rhs.m);
#endif //SCOPED_LOCK
		swap(lhs.some_detail, rhs.some_detail);
	}
};
#endif // ORIG

#ifndef MINE

#include <iostream>
#include <mutex>

class some_big_object {
public:
	int value = 0;

	void swap(some_big_object& other) noexcept {
		std::swap(value, other.value);
		std::cout << "Swapped: " << value << " <-> " << other.value << std::endl; // Note: std::cout can throw, so not truly noexcept - demo only
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

	friend void swap(X& lhs, X& rhs) noexcept { // Listing 3.9 equivalent (unique_lock + defer_lock)
		if (&lhs == &rhs) 
			return;
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);  // ❶ defer_lock
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);  // ❶ defer_lock
		std::lock(lock_a, lock_b);  // ❷ locks both atomically

		lhs.some_detail.swap(rhs.some_detail);
	}

	friend void swap_scoped(X& lhs, X& rhs) noexcept { // C++17 scoped_lock (simplest)
		if (&lhs == &rhs) 
			return;
		std::scoped_lock guard(lhs.m, rhs.m);
		lhs.some_detail.swap(rhs.some_detail);
	}
};
#endif //MINE
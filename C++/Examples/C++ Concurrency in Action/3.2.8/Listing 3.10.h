#pragma once

#ifdef ORIG
#include <mutex>

class Y {
private:
	int some_detail;
	mutable std::mutex m;

	int get_detail() const {
		std::lock_guard<std::mutex> lock_a(m);
		return some_detail;
	}
public:
	Y(int sd) : some_detail(sd) {}

	friend bool operator==(Y const& lhs, Y const& rhs) {
		if (&lhs == &rhs)
			return true;
		int const lhs_value = lhs.get_detail();
		int const rhs_value = rhs.get_detail();
		return lhs_value == rhs_value;
	}
};
#endif // ORIG

#ifndef MINE
#include <mutex>

class Y {
private:
	int some_detail;
	mutable std::mutex m;

	int get_detail() const {
		std::lock_guard<std::mutex> lock_a(m);
		return some_detail;
	}
public:
	explicit Y(int sd) : some_detail(sd) {}
	int get_value() const { return some_detail; }

	friend bool operator==(Y const& lhs, Y const& rhs) {
		if (&lhs == &rhs)
			return true;
		int const lhs_value = lhs.get_detail();
		int const rhs_value = rhs.get_detail();
		return lhs_value == rhs_value;
	}
};
#endif // MINE

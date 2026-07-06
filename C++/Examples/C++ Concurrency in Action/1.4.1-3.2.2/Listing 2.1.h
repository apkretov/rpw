#pragma once

struct func {
	int& i;
	func(int& i_) : i(i_) {}
	void do_something(int& i_) const { ++i_; } //MINE

	void operator()() {
		for (unsigned j = 0; j < 1000000; ++j) {
			do_something(i);
		}
	}
};
#pragma once

#ifndef EX_14_42

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

class Rnd {
public:
	Rnd(int min = 0, int max = 9) : gen(rnd_dev()), distr(min, max) {}
	Rnd(const Rnd &s) : gen(s.gen), distr(s.distr.min(), s.distr.max()) {} // std::generate requires the callable object to be copyable.
	
	int operator()() {
		return distr(gen);
	}
private:
	random_device rnd_dev;
	mt19937 gen;
	uniform_int_distribution<> distr;
};
#endif
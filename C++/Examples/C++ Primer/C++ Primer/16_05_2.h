#pragma once

#ifndef EX_16_63

#include <vector>
#include <algorithm>
using std::vector;

template <typename T>
inline size_t count(const vector<T> &v, const T &t) {
	return std::ranges::count_if(v, [&](const T &i) { return i == t; });
}

template <typename T>
inline size_t count(const vector<T> &v, const char *const &p) {
	return std::ranges::count_if(v, [&](const T &i) { return i == p; });
}
#endif

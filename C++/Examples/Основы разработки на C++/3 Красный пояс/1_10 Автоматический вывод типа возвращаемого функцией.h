#pragma once

#include <algorithm>
#include <iterator>

template <typename Iterator>
class IteratorRange {
	Iterator first;
	Iterator last;
public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l) {}
	Iterator begin() const { return first; }
	Iterator end() const { return last; }
};

#ifdef _1
template <typename Container>
IteratorRange<typename Container::iterator> Head(Container &c, size_t top) { //TEST!
	return {c.begin(), std::next(c.begin(), std::min(top, c.size()))};
}
#else //_2
template <typename Container>
auto Head(Container &c, size_t top) { //TEST!
	return IteratorRange{c.begin(), std::next(c.begin(), std::min(top, c.size()))};
}
#endif //_2
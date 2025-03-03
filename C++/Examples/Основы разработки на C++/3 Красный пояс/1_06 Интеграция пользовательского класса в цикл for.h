#pragma once

#include <vector>

template <typename Iterator>
struct IteratorRange {
	Iterator first;
	Iterator last;

	Iterator begin() const { //TEST!
		return first;
	}

	Iterator end() const { //TEST!
		return last;
	}
};

template <typename T>
IteratorRange<typename std::vector<T>::iterator> Head(std::vector<T> &v, size_t top) { //TEST!
	return {v.begin(), std::next(v.begin(), std::min(top, v.size()))};
}

#pragma region MINE
template <typename T>
IteratorRange<typename std::vector<T>::const_iterator> HeadMine(const std::vector<T> &v, size_t top) { //TEST!
	return {v.begin(), std::next(v.begin(), std::min(top, v.size()))};
}
#pragma endregion //MINE

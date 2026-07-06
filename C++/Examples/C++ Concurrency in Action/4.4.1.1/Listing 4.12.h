#pragma once

#include <algorithm>
#include <list>
#include <utility>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
	if (input.empty()) {
		return input;
	}
	std::list<T> result;
	result.splice(result.begin(), input, input.begin()); // 1: Slice first element off the input to use as the pivot
	T const& pivot = *result.begin(); // 2: Take a reference to the pivot to avoid an expensive copy

	auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; }); // 3: Partition list in-place around pivot via a lambda capture
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(), divide_point); // 4: Move elements up to divide_point into the lower_part list
	auto new_lower(sequential_quick_sort(std::move(lower_part))); // 5: Recursively sort lower part (moved to avoid copying)
	auto new_higher(sequential_quick_sort(std::move(input))); // 6: Recursively sort remaining higher part in input
	result.splice(result.end(), new_higher); // 7: Splice sorted higher values to the end (after pivot)
	result.splice(result.begin(), new_lower); // 8: Splice sorted lower values to the front (before pivot)
	return result;
}
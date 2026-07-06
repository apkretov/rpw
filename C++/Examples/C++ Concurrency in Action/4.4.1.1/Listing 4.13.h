#pragma once

#include <algorithm>
#include <future>
#include <list>
#include <utility>

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
	if (input.empty()) {
		return input;
	}
	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();
	auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
	std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part))); // 1: Rather than sorting the lower portion on the current thread, you sort it on another thread using std::async().
	auto new_higher(parallel_quick_sort(std::move(input))); // 2: The upper portion of the list is sorted with direct recursion as before.
	result.splice(result.end(), new_higher); // 3: Because you just used direct recursion to get new_higher, you can splice it into place as before.
	result.splice(result.begin(), new_lower.get()); // 4: Because new_lower is a std::future, you need to call get() to wait for the background task to complete and retrieve the value.
	return result;
}
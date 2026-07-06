#if 0

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>
#include <thread>
#include <vector>
#include "../../stdafx.h"
using namespace std;

template<typename Iterator, typename T>
struct accumulate_block {
	void operator()(Iterator first, Iterator last, T& result) {
		result = std::accumulate(first, last, result);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
	unsigned long const length = std::distance(first, last);
	if (!length) 
		return init;

	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	cout << "\nHardware threads: " << hardware_threads; //MINE
	unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads;

	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1);

	Iterator block_start = first;

	for (unsigned long i = 0; i < (num_threads - 1); ++i) {
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
		block_start = block_end;
	}

	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

	for (auto& entry : threads) 
		entry.join();

	return std::accumulate(results.begin(), results.end(), init);
}

int main() {
	print_file_line();

	//MINE
	vector<int> vec(1000000);
	ranges::iota(vec, 0);

	cout << "The first 10 elements: ";
	ranges::copy(vec | views::take(10), ostream_iterator<int>(cout, " ")); 
	cout << "\nThe last 10 elements: ";
	ranges::copy(vec | views::drop(vec.size() - 10), ostream_iterator<int>(cout, " ")); 

	int init = 0;
	int result = parallel_accumulate(vec.begin(), vec.end(), init);
	cout << "\nThe sum: " << format_num(result) << "\n";

	return 0;
}
#endif //1
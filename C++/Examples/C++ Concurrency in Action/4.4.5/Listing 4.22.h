#pragma once

#include <algorithm>
#include <future>
#include <vector>
#include "4.4.5.h" // MyData, ChunkResult, FinalResult, whatever, process_chunk, gather_results

std::future<FinalResult> process_data(std::vector<MyData>& vec) { // Gathering results from futures using std::async
	size_t const chunk_size = whatever;
	std::vector<std::future<ChunkResult>> results;
	for (auto begin = vec.begin(), end = vec.end(); begin != end;) {
		size_t const remaining_size = end - begin;
		size_t const this_chunk_size = std::min(remaining_size, chunk_size);
		results.push_back(std::async(process_chunk, begin, begin + this_chunk_size));
		begin += this_chunk_size;
	}
	return std::async([all_results = std::move(results)]() mutable { //MINE // mutable: f.get() needs a non-const future
		std::vector<ChunkResult> v;
		v.reserve(all_results.size());
		for (auto& f : all_results) {
			v.push_back(f.get()); // 1
		}
		return gather_results(v);
	});
}
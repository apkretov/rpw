#pragma once

#define MINE_5_15
#undef ORIG_5_15

#include <future>
#include <vector>
#ifdef MINE_5_15
#include "1_EX_09 Шаблон Paginator.h"
#endif //MINE_5_15
using namespace std;

template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result, size_t first_row, size_t column_size) {
	for (auto &row : result) {
		row.reserve(column_size);
		for (size_t column = 0; column < column_size; ++column)
			row.push_back(first_row ^ column);
		++first_row;
	}
}

vector<vector<int>> GenerateSingleThread(size_t size) {
	vector<vector<int>> result(size);
	GenerateSingleThread(result, 0, size);
	return result;
}

#ifdef ORIG_5_15
template <typename C>
struct Subrange {
	C &collection;
	size_t first_index, last_index;
	auto begin() const { return collection.begin() + first_index; }
	auto end() const { return collection.begin() + last_index; }
	size_t size() const { return last_index - first_index; }
};

template <typename Container>
class Paginator {
	vector<Subrange<Container>> pages;
public:
	Paginator(Container &c, size_t page_size) {
		for (size_t i = 0; i < c.size(); i += page_size)
			pages.push_back({c, i, min(i + page_size, c.size())});
	}

	auto begin() const { return pages.begin(); }
	auto end() const { return pages.end(); }
	size_t size() const { return pages.size(); }
};

template <typename C>
Paginator<C> Paginate(C &c, size_t page_size) {
	return Paginator<C>(c, page_size);
}
#endif //ORIG_5_15

vector<vector<int>> GenerateMultiThread(size_t size, size_t page_size) {
	vector<vector<int>> result(size);
	vector<future<void>> futures;
	size_t first_row = 0;
	for (auto page : Paginate(result, page_size)) {
		futures.push_back(async(launch::async, //ORIG: futures.push_back(async(
			[page, first_row, size] { GenerateSingleThread(page, first_row, size); })); //TO DO: Is the page a container?
		first_row += page_size;
	}
	return result;
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors &matrix) {
	int64_t sum = 0;
	for (const auto &row : matrix)
		for (auto item : row)
			sum += item;
	return sum;
}

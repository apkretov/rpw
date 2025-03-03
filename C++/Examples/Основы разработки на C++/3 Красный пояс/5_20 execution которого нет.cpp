#if 0

#include <execution>
#include <future>
#include <iostream>
#include <vector>
#include "../../stdafx.h"

using namespace std;

template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result, size_t first_row, size_t column_size) {
	for_each(execution::par, //TEST!
		result.begin(), result.end(),
		[&first_row, column_size](vector<int> &row) {
			row.reserve(column_size);
			for (size_t column = 0; column < column_size; ++column)
				row.push_back(first_row ^ column);
			++first_row;
		}
	);
}

vector<vector<int>> GenerateSingleThread(size_t size) {
	vector<vector<int>> result(size);
	GenerateSingleThread(result, 0, size);
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

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	LOG_DURATION("Total");
	const size_t matrix_size = 7000;
	vector<vector<int>> matrix;
	{
		LOG_DURATION("Single thread generation");
		matrix = GenerateSingleThread(matrix_size);
	}
	{
		LOG_DURATION("Single thread sum");
		cout << AS_KV(SumSingleThread(matrix)) << endl;
	}

	return 0;
}
#endif //1
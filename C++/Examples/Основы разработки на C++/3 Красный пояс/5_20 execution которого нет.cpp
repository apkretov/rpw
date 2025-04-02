#if 1

#include <execution>
#include <future>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifdef ORIG // Wrong.
template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result, size_t first_row, size_t column_size) {
	for_each(
		execution::par, //TEST!
		result.begin(), result.end(),
		[&first_row, column_size](vector<int> &row) {
			row.reserve(column_size);
			for (size_t column = 0; column < column_size; ++column)
				row.push_back(first_row ^ column);
			++first_row;
		}
	);
}
#else //TRAE
template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result, size_t first_row, size_t column_size) {
	for (auto &row : result) //TEST //																														Pre-allocate all vectors to avoid allocation during parallel execution
		row.resize(column_size);

	for_each(
		execution::par, //TEST! 
		result.begin(), result.end(),
		[&first_row, column_size](vector<int> &row) {
			for (size_t column = 0; column < column_size; ++column)
				row[column] = first_row ^ column;  // Using [] instead of push_back
			++first_row;
		}
	);
}
/* Output: Single thread generation: execution time (seconds)
size:		7 000
single:		.481, .465
par:		.184, .181
par_unseq:	.175, .179

size:		70 000
single:		56, 70, 53
par:		15, 16, 16
par_unseq:	33, 15, 15
*/
#endif //TRAE

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
	const size_t matrix_size = 7'000; //MINE: 70'000;
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
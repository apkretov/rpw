#if 0

#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

vector<int> BuildVector(int i) {
	return {i, i + 1, i + 2, i + 3, i + 4};
}

tuple<int, int, int, int, int> BuildTuple(int i) {
	return make_tuple(i, i + 1, i + 2, i + 3, i + 4);
}

array<int, 5> BuildArray(int i) {
	return {i, i + 1, i + 2, i + 3, i + 4};
}

const int COUNT = 1'000'000;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	{
		LOG_DURATION("vector");
		for (int i = 0; i < COUNT; ++i)
			auto numbers = BuildVector(i);
	}
	{
		LOG_DURATION("tuple");
		for (int i = 0; i < COUNT; ++i)
			auto numbers = BuildTuple(i);
	}
	{
		LOG_DURATION("array");
		for (int i = 0; i < COUNT; ++i)
			auto numbers = BuildArray(i);
	}

	return 0;
}
#endif //1
#if 0

#include <future>
#include <iostream>
#include <numeric>
#include <vector>
#include "../../stdafx.h"
using namespace std;

int SumTwoVectors(const vector<int> &one, const vector<int> &two) {
	future<int> f = async([&one] { return accumulate(begin(one), end(one), 0); }); //TEST!
	int result = accumulate(begin(two), end(two), 0);
	return result + f.get(); //TEST!
}

int main() {
	PRINT_FILE_LINE();
	cout << AS_KV(SumTwoVectors({1, 1, 1, 1}, {3, 3, 3})) << '\n';
}
#endif
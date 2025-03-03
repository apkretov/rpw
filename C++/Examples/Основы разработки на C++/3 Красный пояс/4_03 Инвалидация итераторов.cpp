#if 0

#include <iostream>
#include <deque>
#include <vector>
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

#ifdef VECTOR
	vector<int> numbers = {1};
#else //DEQUE
	deque<int> numbers = {1};
#endif //DEQUE

	auto it = begin(numbers);
	const int &ref = numbers[0]; //MINE
	cout << AS_KV(*it) << '\n';

	for (int i = 0; i < 2000; ++i)
		numbers.push_back(i);
	//TEST! cout << *it << '\n'; //																																		// This is an error on my system with dequek, too.
	cout << AS_KV(ref) << '\n'; //MINE //TEST!

	return 0;
}
#endif //1
#if 0

#include <iostream>
#include <list>
#include "../../stdafx.h"
using namespace std;

class NumbersOnList {
public:
	void Add(int x) {
		data.push_back(x);
	}

	template <typename Predicate>
	auto FindLast(Predicate predicate) {
		return find_if(rbegin(data), rend(data), predicate);
	}

	template <typename Predicate>
	void Remove(Predicate predicate) {
		data.remove_if(predicate);
	}
private:
	list<int> data;
};

const int SIZE = 10'000;
const int REMOVAL_COUNT = 1'000;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	LOG_DURATION("list");
	NumbersOnList numbers;

	for (int i = 0; i < SIZE; ++i)
		numbers.Add(i);
	
	auto it = numbers.FindLast([](int x) { return x % REMOVAL_COUNT == 0; });

	for (int i = 1; i < REMOVAL_COUNT; ++i)
		numbers.Remove([i](int x) { return x % REMOVAL_COUNT == i; });
	//ERR (on my system) cout << *it << '\n'; //TEST!

	return 0;
}
#endif //1
#if 0 

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void orig() {
	const int SIZE = 1'000'000;

	vector<int> v;
	{
		LOG_DURATION("vector push_back");
		for (int i = 0; i < SIZE; ++i)
			v.push_back(i);
	}
	deque<int> d;
	{
		LOG_DURATION("deque push_back");
		for (int i = 0; i < SIZE; ++i)
			d.push_back(i);
	}
	{
		LOG_DURATION("vector sort");
		sort(rbegin(v), rend(v));
	}
	{
		LOG_DURATION("deque sort");
		sort(rbegin(d), rend(d));
	}
}

void mine() {
	const int SIZE = 100'000;

	vector<int> v;
	{
		LOG_DURATION("vector");
		for (int i = 0; i < SIZE; ++i)
			v.insert(v.begin(), i);
	}
	deque<int> d;
	{
		LOG_DURATION("deque");
		for (int i = 0; i < SIZE; ++i)
			d.push_front(i);
	}
}

int main() {
	PRINT_FILE_LINE();

	orig();
	//mine();

	return 0;
}
#endif //1
#if 0

#include <iostream>
#include <list>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void mine() {
	const int SIZE = 100'000;
	const int REMOVAL_COUNT = 10;

	{
		LOG_DURATION("vector");
		vector<int> v;
		for (int i = 0; i < SIZE; ++i)
			//v.push_back(i);
			v.insert(v.begin(), i);
	}
	{
		LOG_DURATION("list");
		list<int> l;
		for (int i = 0; i < SIZE; ++i)
			//l.push_back(i);
			l.insert(l.begin(), i); //TEST
	}
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	mine();

	return 0;
}
#endif //1
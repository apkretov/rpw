#if 0 

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void LogVectorParams(const vector<int> &v) {
	cout << "Length = " << v.size() << ", capacity = " << v.capacity() << '\n';
	const int *data = v.data(); //TEST!
	for (size_t i = 0; i < v.capacity(); ++i)
		cout << *(data + i) << ' ';
	cout << '\n';
}

void data() {
	vector<int> v = {1, 2, 3};
	LogVectorParams(v);
	v.push_back(4);
	LogVectorParams(v);

	for (auto i = v.capacity() + 1; i < 10; ++i) { //MINE
		v.push_back(i);
		LogVectorParams(v);
	}
}

void reserve() {
#ifdef ORIG
	int size;
	cin >> size;
#else //MINE
	constexpr int size = 10'000'000;
#endif
	{
		LOG_DURATION("push_back unreserved");
		vector<int> v;
		for (int i = 0; i < size; ++i)
			v.push_back(i);

	}
	{
		LOG_DURATION("push_back reserved");
		vector<int> v;
		v.reserve(size); //TEST! //MINE: This does not matter on my system.
		for (int i = 0; i < size; ++i)
			v.push_back(i);

	}
}

int main() {
	PRINT_FILE_LINE();

	//data();
	reserve();

	return 0;
}
#endif //1
#if 0 

#include <algorithm>
#include <iostream>
#include <vector>;
#include "../../stdafx.h"
using namespace std;

void mine() {
	vector<int> v = {3, 0, 4, -5, 1, -9, 4};

	cout << "vector<int> v:";
	ranges::copy(v, ostream_iterator<int>(cout, " "));
	
	auto cnt = ranges::count_if(v, [](int i) { return i == 4; });
	cout << "\nranges::count_if(v, [](int i) { return i == 4; }) = " << cnt << '\n';
}

int main() {
	PRINT_FILE_LINE();

	mine();
}
#endif
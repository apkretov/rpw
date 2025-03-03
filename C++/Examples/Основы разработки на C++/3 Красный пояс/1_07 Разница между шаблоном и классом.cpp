#if 0 

#include <iostream>
#include "../../stdafx.h"
#include "1_06 »нтеграци€ пользовательского класса в цикл for.h"
using namespace std;

template <typename T>
size_t RangeSize(IteratorRange<T> r) { //TEST
	return r.end() - r.begin();
}

int main() {
	PRINT_FILE_LINE();

	vector<int> v{1, 2, 3, 4, 5};

	for (int x : Head(v, 3))
		cout << x << ' ';
	cout << '\n';

	cout << RangeSize(Head(v, 3)) << '\n';
}
#endif //1
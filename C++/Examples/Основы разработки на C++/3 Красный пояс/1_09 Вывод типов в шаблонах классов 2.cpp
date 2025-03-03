#if 0

#include <vector>
#include "../../stdafx.h"
using namespace std;

template <typename Iterator>
class PageRange {
	Iterator first;
	Iterator last;
public:
	PageRange(Iterator f, Iterator l) : first(f), last(l) {}

	Iterator begin() const {
		return first;
	}

	Iterator end() const {
		return last;
	}
};

template <typename T>
PageRange<typename vector<T>::iterator> Head(vector<T> &v, size_t top) {
	return {v.begin(), next(v.begin(), min(top, v.size()))};
}

void mine() {
	vector vi{0, 1, 2}; //TEST!
	vector vd{0.0, 1.1, 2.2};
	vector vc{'a', 'b', 'c'};
	vector vs{"aaa", "bbb", "ccc"};
}

int main() {
	PRINT_FILE_LINE();

	vector<int> v{1, 2, 3, 4, 5};

	PageRange second_half{v.begin() + v.size() / 2, v.end()}; //TEST!
	for (int x : second_half)
		cout << x << ' ';
	cout << '\n';
}
#endif //1

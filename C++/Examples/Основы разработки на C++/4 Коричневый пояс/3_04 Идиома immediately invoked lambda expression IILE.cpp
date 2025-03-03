#if 0

#include "3_03 Использование const для поддержания инвариантов в классах и объектах.h"
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	const vector<int> sorted_numbers = [] { 
		LOG_DURATION("Sorted numbers build");
		vector<int> data = Sorted({5, 4, 2, 1, 5, 1, 3, 4, 5, 6, 8});
		auto it = unique(data.begin(), data.end());
		data.erase(it, data.end());
		return data;
	}();

	for (int n : sorted_numbers)
		cout << n << ' ';
	cout << '\n';
}
#endif //1

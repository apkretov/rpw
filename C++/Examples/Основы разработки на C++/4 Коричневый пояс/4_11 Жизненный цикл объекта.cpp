#if 0

#include <memory>
#include "../../stdafx.h"
#include "vld.h"
using namespace std;

struct C {
	vector<int> vals;

	C(const vector<int> init) : vals(init) {
		if (any_of(begin(vals), end(vals), [](int val) { return (val < 0); }))
			throw runtime_error("negative values!"); //TEST! //																							vals гарантированно будет уничтожено
	}

	~C() { /*если объект был создан, то vals уничтожится здесь */ }
};

int main() {
	PRINT_FILE_LINE();

#pragma region MINE
	try {
		C с1({0, 1, 2, 3});
		C с2({0, 1, 2, -1});
	}
	catch (const runtime_error &e) {
		cerr << e.what() << '\n';
	}
#pragma endregion MINE

	return 0;
}
#endif //1
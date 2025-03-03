#if 0
#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
class SimpleVector { //VER1
public:
	explicit SimpleVector(size_t size) {
		data = new T[size];
		end_ = data + size;
	}

	~SimpleVector() {
		delete[] data;
	}

	T &operator[](size_t index) const {
		return data[index]; // *(data + index)
	}

#pragma region TEST!
	const T *begin() const {
		return data;
	}

	const T *end() const {
		return end_;
	}

	T *begin() {
		return data;
	}

	T *end() {
		return end_;
	}
#pragma endregion //TEST!
private:
	T *data;
	T *end_;
};

template <typename T>
void Print(const SimpleVector<T> &v) {
	for (auto i = v.begin(); i != v.end(); ++i) {
		cout << *i << ' ';
		//TEST! *i = 42; //																																	GPT: While you cannot modify the SimpleVector object itself, you can still modify the contents of the vector if the elements themselves are not const. This is allowed if the T type is not const-qualified in "T *begin() const" vs "const T *begin() const".
	}
}

int main(int argc, char *arg[]) {
	PRINT_FILE_LINE();

	SimpleVector<int> v(4);
	v[0] = 5;
	v[1] = 3;
	v[2] = 4;
	v[3] = -1;
	Print(v); 
	cout << '\n';

	sort(v.begin(), v.end());
	Print(v);
	cout << '\n';

	return 0;
}
#endif //1

#ifdef PERPLEXITY

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class IntegerArray {
private:
	int *data;
	size_t size;
public:
	explicit IntegerArray(size_t s) : size(s) {
		data = new int[s];
		for (int i = 0; i < size; ++i)
			data[i] = i; // Initialize with some values
	}

	~IntegerArray() { delete[] data; }

	class Iterator { // Iterator class definition
	private:
		int *ptr;
	public:
		explicit Iterator(int *p) : ptr(p) {}
		int &operator*() { return *ptr; } // Dereference operator

		Iterator &operator++() { // Pre-increment operator
			++ptr;
			return *this;
		}

		Iterator operator++(int) { // Post-increment operator
			Iterator temp = *this;
			++ptr;
			return temp;
		}

		bool operator==(const Iterator &other) const { return ptr == other.ptr; } // Equality operator
		bool operator!=(const Iterator &other) const { return ptr != other.ptr;	} // Inequality operator
	};

	Iterator begin() { return Iterator(data); } // Begin and end functions to return iterators
	Iterator end() { return Iterator(data + size); }
};

int main() {
	PRINT_FILE_LINE();

	IntegerArray arr(5);

	for (auto it = arr.begin(); it != arr.end(); ++it) { // Using the custom iterator
		cout << *it << " "; // Output the values
	}
	cout << endl;

	return 0;
}
#endif //PERPLEXITY

#pragma once

#include "Iterator.h"
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;

#pragma region Trae
template <typename T>
class VectorIterator : public Iterator<T> {
	vector<shared_ptr<T>> &items;
	int position = 0;
public:
	VectorIterator(vector<shared_ptr<T>> &items) : items(items) {}

	T &next() override {
		if (hasNext())
			return *items[position++];
		throw std::runtime_error("No more items");
	}

	bool hasNext() noexcept override { return position < items.size(); }
};
#pragma endregion //Trae

#pragma once

#include "Iterator.h"
#include <vector>
#include <memory>

#pragma region Trae
template <typename T>
class VectorIterator : public Iterator<T> {
	using VectorPtr = std::vector<std::shared_ptr<T>>;
	VectorPtr &items;
	int position = 0;
public:
	VectorIterator(VectorPtr &items) : items(items) {}

	T &next() override {
		if (hasNext())
			return *items[position++];
		throw std::runtime_error("No more items");
	}

	bool hasNext() const noexcept override { return position < items.size(); }
};
#pragma endregion //Trae

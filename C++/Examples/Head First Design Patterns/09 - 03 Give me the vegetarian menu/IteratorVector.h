#pragma once

#include <memory>
#include <vector>
#include "Iterator.h"

#pragma region Trae
template <typename T>
class VectorIterator : public Iterator<T> {
	using VectorPtr = std::vector<std::shared_ptr<T>>;
	VectorPtr &items;
	size_t position = 0;
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

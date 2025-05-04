#pragma once

#include <memory>
#include <vector>
#include "Iterator.h"

#pragma region Trae
template <typename T>
class VectorIterator : public Iterator<T> {
	using VecPtrT = std::vector<std::shared_ptr<T>>;
	VecPtrT &items;
	size_t position = 0;
public:
	VectorIterator(VecPtrT &items) : items(items) {
		//std::cout << "111 " << items[position]->getName() << '\n'; //MINE
		std::cout << "111 " << current().getName() << '\n'; //MINE
	}

	T &current() const override { //MINE
		if (position < items.size())
			return *items[position];
		throw std::runtime_error("No more items");
	}

	T &next() override {
		if (hasNext())
			return *items[position++];
		throw std::runtime_error("No more items");
	}

	bool hasNext() const override { 
		return position < items.size(); 
	}
};
#pragma endregion //Trae

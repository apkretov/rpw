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
#ifdef DEBUG
		std::clog << "030 " << typeid(current()).name() << ": " << current().getName() << '\n'; //MINE
#endif //DEBUG
	}

	T &current() const override { //MINE
		if (position < items.size())
			return *items[position];
		throw std::runtime_error("No more items");
	}

	T &next() override {
		if (hasNext()) {
#ifdef DEBUG
			std::clog << "080 " << typeid(current()).name() << ": " << current().getName() << '\n'; //MINE
#endif //DEBUG
			return *items[position++];
		}
		throw std::runtime_error("No more items");
	}

	bool hasNext() const override { 
		return position < items.size(); 
	}
};
#pragma endregion //Trae

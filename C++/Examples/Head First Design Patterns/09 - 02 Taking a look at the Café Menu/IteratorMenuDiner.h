#pragma once

#include <array>
#include "ItemMenu.h"
#include "Iterator.h"

#pragma region Trae
class DinerMenuIterator : public Iterator<MenuItem> {
private:
	const std::array<MenuItem, 6> &items;
	int position = 0;

public:
	DinerMenuIterator(const std::array<MenuItem, 6> &items) : items(items) {}

	bool hasNext() override {
		return position < items.size();
	}

	MenuItem &next() override {
		return const_cast<MenuItem &>(items[position++]);
	}
};
#pragma endregion //Trae
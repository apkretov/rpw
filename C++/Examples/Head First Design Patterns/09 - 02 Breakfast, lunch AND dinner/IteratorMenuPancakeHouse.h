#pragma once

#include <vector>
#include "ItemMenu.h"
#include "Iterator.h"

#pragma region Trae
class PancakeHouseMenuIterator : public Iterator<MenuItem> {
private:
	const std::vector<MenuItem> &items;
	int position = 0;

public:
	PancakeHouseMenuIterator(const std::vector<MenuItem> &items) : items(items) {}

	bool hasNext() override {
		return position < items.size();
	}

	MenuItem &next() override {
		return const_cast<MenuItem &>(items[position++]);
	}
};
#pragma endregion //Trae

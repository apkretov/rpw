#pragma once

#include <vector>
#include "ItemMenu.h"
#include "Iterator.h"

#pragma region Trae
class PancakeHouseMenuIterator : public Iterator<MenuItem> {
	using VecMenuItem = std::vector<MenuItem>;
	const VecMenuItem &items;
	size_t position = 0;
public:
	PancakeHouseMenuIterator(const VecMenuItem &items) : items(items) {}
	bool hasNext() override { return position < items.size(); }
	MenuItem &next() override { return const_cast<MenuItem &>(items[position++]); }
};
#pragma endregion //Trae

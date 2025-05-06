#pragma once

#include <array>
#include "ItemMenu.h"
#include "Iterator.h"

#pragma region Trae
class DinerMenuIterator : public Iterator<MenuItem> {
public:
	static constexpr size_t MAX_ITEMS = 6;
	DinerMenuIterator(const std::array<MenuItem, MAX_ITEMS> &items) : items(items) {}
	bool hasNext() override { return position < items.size(); }
	MenuItem &next() override { return const_cast<MenuItem &>(items[position++]); }
private:
	const std::array<MenuItem, MAX_ITEMS> &items;
	size_t position = 0;
};
#pragma endregion //Trae
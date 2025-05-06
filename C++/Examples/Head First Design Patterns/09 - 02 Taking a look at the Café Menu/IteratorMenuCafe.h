#pragma once

#include <vector>
#include <unordered_map>
#include "Iterator.h"
#include "ItemMenu.h"

#pragma region Trae
class CafeMenuIterator : public Iterator<MenuItem> {
private:
	std::vector<MenuItem> items;
	size_t position = 0;

public:
	CafeMenuIterator(const std::unordered_map<std::string, MenuItem> &menuItems) {
		for (const auto &pair : menuItems) {
			items.push_back(pair.second);
		}
	}

	bool hasNext() override {
		return position < items.size();
	}

	MenuItem &next() override {
		return items[position++];
	}
};
#pragma endregion //Trae
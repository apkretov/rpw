#pragma once

#include <array>
#include <ctime>
#include "Iterator.h"
#include "ItemMenu.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
package headfirst.designpatterns.iterator.dinermergercafe;

import java.util.Iterator;
import java.util.Calendar;

public class AlternatingDinerMenuIterator implements Iterator<MenuItem> {
	MenuItem[] items;
	int position;

	public AlternatingDinerMenuIterator(MenuItem[] items) {
		this.items = items;
		position = Calendar.DAY_OF_WEEK % 2;
	}
	public MenuItem next() {
		MenuItem menuItem = items[position];
		position = position + 2;
		return menuItem;
	}
	public boolean hasNext() {
		if (position >= items.length || items[position] == null) {
			return false;
		} else {
			return true;
		}
	}
}
*/
class AlternatingDinerMenuIterator : public Iterator<MenuItem> {
	const std::array<MenuItem, 6> &items;
	int position;
public:
	AlternatingDinerMenuIterator(const std::array<MenuItem, 6> &items) : items(items) {
		// Get current time to determine odd/even day
		std::time_t t = std::time(nullptr);
		std::tm *now = std::localtime(&t);
		// tm_wday is 0-6 (0 = Sunday), similar to Calendar.DAY_OF_WEEK % 2
		position = now->tm_wday % 2;
	}

	MenuItem &next() override {
		MenuItem &menuItem = const_cast<MenuItem &>(items[position]);
		position = position + 2;
		return menuItem;
	}

	bool hasNext() override {
		if (position >= items.size() || items[position] = MenuItem()) {
			return false;
		}
		return true;
	}
};
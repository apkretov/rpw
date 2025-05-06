#pragma once

#include <array>
#include <iostream>
#include <string_view>
#include "IteratorMenuDiner.h"
#include "Menu.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
public class DinerMenu implements Menu {
	static final int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem[] menuItems;

	public DinerMenu() {
		menuItems = new MenuItem[MAX_ITEMS];

		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.05);
	}
}
*/
class DinerMenu : public Menu {
    using string_view = std::string_view;
    static constexpr int MAX_ITEMS = DinerMenuIterator::MAX_ITEMS;
    int numberOfItems = 0;
    std::array<MenuItem, MAX_ITEMS> menuItems;
public:
	DinerMenu() {
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.05);
	}

	void addItem(string_view name, string_view description, bool vegetarian, double price) {
		if (numberOfItems >= MAX_ITEMS) {
			std::cerr << "Sorry, menu is full! Can't add item to menu\n";
			return;
		}
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems[numberOfItems] = menuItem;
		numberOfItems++;
	}

    PtrIterMenuitem createIterator() override { return std::make_shared<DinerMenuIterator>(menuItems); }
};
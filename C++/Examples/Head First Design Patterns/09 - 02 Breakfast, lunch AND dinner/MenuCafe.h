#pragma once

#include <unordered_map>
#include "IteratorMenuCafe.h"
#include "Menu.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
public class CafeMenu implements Menu {
	HashMap<String, MenuItem> menuItems = new HashMap<String, MenuItem>();

	public CafeMenu() {
		addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
		addItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69);
		addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
	}
}
*/
class CafeMenu : public Menu {
	std::unordered_map<std::string, MenuItem> menuItems;
public:
	CafeMenu() {
		addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
		addItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69);
		addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
	}

	void addItem(const std::string &name, const std::string &description, bool vegetarian, double price) {
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems[name] = menuItem;
	}

	std::shared_ptr<Iterator<MenuItem>> createIterator() override { return std::make_shared<CafeMenuIterator>(menuItems); }
};
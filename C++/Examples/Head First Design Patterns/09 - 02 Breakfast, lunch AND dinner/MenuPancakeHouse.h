#pragma once

#include "Menu.h"
#include <vector>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
public class PancakeHouseMenu implements Menu {
	ArrayList<MenuItem> menuItems;

	public PancakeHouseMenu() {
		menuItems = new ArrayList<MenuItem>();

		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.59);
	}
}
*/
class PancakeHouseMenu : public Menu {
	std::vector<MenuItem> menuItems;
public:
	PancakeHouseMenu() {
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.59);
	}

	void addItem(const std::string &name, const std::string &description, bool vegetarian, double price) {
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}

	std::shared_ptr<Iterator<MenuItem>> createIterator() override;
};
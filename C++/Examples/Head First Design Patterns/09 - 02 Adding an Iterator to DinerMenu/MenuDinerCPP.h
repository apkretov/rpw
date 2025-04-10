#pragma once

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "DinerMenuIterator.h"
#include "MenuItem.h"
using std::cout;
using std::string;
using std::array;
using std::unique_ptr;
using std::make_unique;

#pragma region Reworking the Diner Menu with Iterator
/* Java
public class DinerMenu {
	static final int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem[] menuItems;
	// constructor here
	// addItem here
	//OFF public MenuItem[] getMenuItems() { return menuItems; }
	public Iterator createIterator() { return new DinerMenuIterator(menuItems); } // Here's the createIterator() method. It creates a DinerMenuIterator from the menuItems array and returns it to the client.
	// other menu methods here
}
*/
template <typename T> // A more idiomatic C++ solution using modern C++ practices. The main changes include using std::array for fixed-size array, proper memory management, and RAII principles.
class DinerMenu {
	static const int MAX_ITEMS = 6;
	int numberOfItems = 0;
	array<T, MAX_ITEMS> menuItems;

public:
	DinerMenu() {
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
	}

	void addItem(string name, string description, bool vegetarian, double price) {
		if (numberOfItems >= MAX_ITEMS)
			cout << "Sorry, menu is full! Can't add item to menu\n";
		else {
			menuItems[numberOfItems] = T(name, description, vegetarian, price);
			numberOfItems++;
		}
	}

	unique_ptr<Iterator<T>> createIterator() {
		return make_unique<DinerMenuIterator<T>>(menuItems.data(), MAX_ITEMS);
	}
};
#pragma endregion //Reworking the Diner Menu with Iterator
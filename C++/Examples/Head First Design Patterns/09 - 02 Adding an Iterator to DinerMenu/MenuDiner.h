#pragma once
#include <iostream>
#include <string>
#include "DinerMenuIterator.h"
#include "MenuItem.h"
using std::cout;
using std::string;

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
template <typename T>
class DinerMenu {
public:
	static const int MAX_ITEMS = 6;
private:
	int numberOfItems = 0;
	T menuItems[MAX_ITEMS];
public:
	DinerMenu() {                
		menuItems = new MenuItem[MAX_ITEMS];

		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
	}

	~DinerMenu() { delete[] menuItems; }

	void addItem(string name, string description, bool vegetarian, double price) {                           
		MenuItem menuItem(name, description, vegetarian, price);
		if (numberOfItems >= MAX_ITEMS)
			cout << "Sorry, menu is full! Can't add item to menu\n";                      
		else {
			menuItems[numberOfItems] = menuItem;
			numberOfItems = numberOfItems + 1;
		}
	}

	//OFF MenuItem *getMenuItems() const { return menuItems; }
	Iterator<T> *createIterator() { // Here's the createIterator() method. It creates a DinerMenuIterator from the menuItems array and returns it to the client.
		return new DinerMenuIterator<T>(menuItems, MAX_ITEMS); // We're returning the Iterator interface. The client doesn't need to know how the menuItems are maintained in the DinerMenu, nor does it need to know how the DinerMenuIterator is implemented. It just needs to use the iterators to step through the items in the menu.
	}
};
#pragma endregion //Reworking the Diner Menu with Iterator

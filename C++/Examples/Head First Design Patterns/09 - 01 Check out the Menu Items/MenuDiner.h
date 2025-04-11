#pragma once
#include <iostream>
#include <span>
#include <string>
#include "MenuItem.h"
using std::cout;
using std::span;
using std::string;

#pragma region Lou and Mels Menu implementations // Lou and Mel's Menu implementations
/* Java
public class DinerMenu {
    static final int MAX_ITEMS = 6;
    int numberOfItems = 0;
    MenuItem[] menuItems;

    public DinerMenu() {
        menuItems = new MenuItem[MAX_ITEMS];

        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
        // a couple of other Diner Menu items added here
    }

    public void addItem(String name, String description, boolean vegetarian, double price) {
        MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
        if (numberOfItems >= MAX_ITEMS)
            System.err.println("Sorry, menu is full! Can't add item to menu");
        else {
            menuItems[numberOfItems] = menuItem;
            numberOfItems = numberOfItems + 1;
        }
    }

    public MenuItem[] getMenuItems() { return menuItems; }

    // other menu methods here
}
*/
class DinerMenu {
    static const int MAX_ITEMS = 6; // Mel takes a different approach; he's using an Array so he can control the max size of the menu and retrieve menu items out without having to cast his objects.
    int numberOfItems = 0;
    MenuItem* menuItems;
public:
    DinerMenu() { // Like Lou, Mel creates his menu items in the constructor, using the addItem() helper method
        menuItems = new MenuItem[MAX_ITEMS];

        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
        // a couple of other Diner Menu items added here
    }

    ~DinerMenu() { delete[] menuItems; }

    void addItem(string name, string description, bool vegetarian, double price) { // addItem() takes all the parameters necessary to create a MenuItem and instantiates one. It also checks to make sure we haven't hit the menu size limit
        MenuItem menuItem(name, description, vegetarian, price);
        if (numberOfItems >= MAX_ITEMS)
            cout << "Sorry, menu is full! Can't add item to menu\n"; // Mel specifically wants to keep his menu under a certain size (presumably so he doesn't have to remember too many recipes).
        else {
            menuItems[numberOfItems] = menuItem;
            numberOfItems = numberOfItems + 1;
        }
    }

    span<const MenuItem> getMenuItems() const { return span<const MenuItem>(menuItems, numberOfItems); } // getMenuItems() returns the array of menu items.
    // other menu methods here // Like Lou, Mel has a bunch of code that depends on the implementation of his menu being an Array. He's too busy cooking to rewrite all of this.
};
#pragma endregion //Lou and Mels Menu implementations
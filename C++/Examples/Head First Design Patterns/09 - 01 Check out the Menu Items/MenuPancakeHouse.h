#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"
using std::string;
using std::vector;

#pragma region Lou and Mels Menu implementations //Lou and Mel's Menu implementations
/* Java
public class PancakeHouseMenu {
    ArrayList menuItems; // Lou's using an ArrayList to store his menu items

    public PancakeHouseMenu() {
        menuItems = new ArrayList();
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99); // Each menu item is added to the ArrayList here, in the constructor
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99); // Each MenuItem has a name, a description, whether or not it's a vegetarian item, and the price
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
    }

    public void addItem(String name, String description, boolean vegetarian, double price) { // To add a menu item, Lou creates a new MenuItem object, passing in each argument, and then adds it to the ArrayList
        MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
        menuItems.add(menuItem);
    }

    public ArrayList getMenuItems() { return menuItems; } // The getMenuItems() method returns the list of menu items

    // other menu methods here // Lou has a bunch of other menu code that depends on the ArrayList implementation. He doesn't want to have to rewrite all that code!
}
*/
class PancakeHouseMenu {
    vector<MenuItem> menuItems; // Lou's using an ArrayList to store his menu items
public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99); // Each menu item is added to the ArrayList here, in the constructor
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99); // Each MenuItem has a name, a description, whether or not it's a vegetarian item, and the price
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
    }

    void addItem(string name, string description, bool vegetarian, double price) { // To add a menu item, Lou creates a new MenuItem object, passing in each argument, and then adds it to the ArrayList
        MenuItem menuItem(name, description, vegetarian, price);
        menuItems.push_back(menuItem);
    }

    const vector<MenuItem> &getMenuItems() const { return menuItems; } // The getMenuItems() method returns the list of menu items
    // other menu methods here // Lou has a bunch of other menu code that depends on the ArrayList implementation. He doesn't want to have to rewrite all that code!
};
#pragma endregion //Lou and Mels Menu implementations
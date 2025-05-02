#pragma once
#include <string>

#pragma region Check out the Menu Items
/* Java
public class MenuItem {
    String name; // A MenuItem consists of a name, a description, a flag to indicate if the item is vegetarian, and a price. You pass all these values into the constructor to initialize the MenuItem.
    String description;
    boolean vegetarian;
    double price;

    public MenuItem(String name, String description, boolean vegetarian, double price) { 
        this.name = name;
        this.description = description;
        this.vegetarian = vegetarian;
        this.price = price;
    }

    public String getName() { return name; } // These getter methods let you access the fields of the menu item.
    public String getDescription() { return description; }
    public double getPrice() { return price; }
    public boolean isVegetarian() { return vegetarian; }
}
*/
class MenuItem {
	using string = std::string;
    string name; // A MenuItem consists of a name, a description, a flag to indicate if the item is vegetarian, and a price. You pass all these values into the constructor to initialize the MenuItem.
    string description;
    bool vegetarian;
    double price;
public:
	MenuItem() : name(""), description(""), vegetarian(false), price(0.0) {} // Default constructor
    MenuItem(string name, string description, bool vegetarian, double price) : name(name), description(description), vegetarian(vegetarian), price(price) {}

    string getName() { return name; } // These getter methods let you access the fields of the menu item.
    string getDescription() { return description; }
    double getPrice() { return price; }
    bool isVegetarian() { return vegetarian; }
};
#pragma endregion //Check out the Menu Items
#pragma once

#include <string>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
public class MenuItem {
	String name;
	String description;
	boolean vegetarian;
	double price;

	public MenuItem(String name, String description, boolean vegetarian, double price) {
		this.name = name;
		this.description = description;
		this.vegetarian = vegetarian;
		this.price = price;
	}
}
*/
class MenuItem {
	using string = std::string;
	string name;
	string description;
	bool vegetarian;
	double price;
public:
	MenuItem() : name(""), description(""), vegetarian(false), price(0.0) {}
	MenuItem(const string &name, const string &description, bool vegetarian, double price) : name(name), description(description), vegetarian(vegetarian), price(price) {}
	string getName() const { return name; }
	string getDescription() const { return description; }
	double getPrice() const { return price; }
	bool isVegetarian() const { return vegetarian; }
};
#pragma once

#include <memory>
#include "IteratorNull.h"
#include "MenuComponent.h"

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
public class MenuItem extends MenuComponent {
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
  
    public String getName() { return name; }
    public String getDescription() { return description; }
    public double getPrice() { return price; }
    public boolean isVegetarian() { return vegetarian; }
  
    public Iterator<MenuComponent> createIterator() { return new NullIterator(); }
 
    public void print() {
        System.out.print("  " + getName());
        if (isVegetarian()) System.out.print("(v)");
        System.out.println(", " + getPrice());
        System.out.println("     -- " + getDescription());
    }
}
*/
class MenuItem : public MenuComponent {
	using string = std::string;
    string name;
    string description;
    bool vegetarian;
    double price;
public:
    MenuItem(string name, string description, bool vegetarian, double price) : name(name), description(description), vegetarian(vegetarian), price(price) {}

    string getName() override { return name; }
    string getDescription() override { return description; }
    double getPrice() override { return price; }
    bool isVegetarian() override { return vegetarian; }
	
	PtrIterMenucompont createIterator() override { return std::make_shared<NullIterator>(); }

    void print() override {
        std::cout << "  " << getName();
        if (isVegetarian()) 
			std::cout << "(v)";
        std::cout << ", " << getPrice() << "\n";
        std::cout << "     -- " << getDescription() << "\n";
    }
};

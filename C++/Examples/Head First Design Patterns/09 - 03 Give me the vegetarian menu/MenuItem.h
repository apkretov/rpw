#pragma once

#include "MenuComponent.h"
#include "NullIterator.h"
#include <memory>
using std::string;

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
    string name;
    string description;
    bool vegetarian;
    double price;

public:
    MenuItem(string name, string description, bool vegetarian, double price) : 
        name(name), description(description), vegetarian(vegetarian), price(price) {}

    string getName() override { return name; }
    string getDescription() override { return description; }
    double getPrice() override { return price; }
    bool isVegetarian() override { return vegetarian; }
    shared_ptr<Iterator<MenuComponent>> createIterator() override { 
        return std::make_shared<NullIterator>(); 
    }

    void print() override {
        cout << "  " << getName();
        if (isVegetarian()) cout << "(v)";
        cout << ", " << getPrice() << "\n";
        cout << "     -- " << getDescription() << "\n";
    }
};

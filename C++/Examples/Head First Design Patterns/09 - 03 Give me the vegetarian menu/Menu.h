#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "MenuComponent.h"
#include "IteratorComposite.h"
#include "IteratorVector.h"

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
public class Menu extends MenuComponent {
    ArrayList<MenuComponent> menuComponents = new ArrayList<MenuComponent>();
    String name;
    String description;
  
    public Menu(String name, String description) {
        this.name = name;
        this.description = description;
    }
 
    public void add(MenuComponent menuComponent) {
        menuComponents.add(menuComponent);
    }
 
    public void remove(MenuComponent menuComponent) {
        menuComponents.remove(menuComponent);
    }
 
    public MenuComponent getChild(int i) {
        return menuComponents.get(i);
    }
 
    public String getName() { return name; }
    public String getDescription() { return description; }
 
    public Iterator<MenuComponent> createIterator() {
        return new CompositeIterator(menuComponents.iterator());
    }
 
    public void print() {
        System.out.print("\n" + getName());
        System.out.println(", " + getDescription());
        System.out.println("---------------------");
  
        Iterator<MenuComponent> iterator = menuComponents.iterator();
        while (iterator.hasNext()) {
            MenuComponent menuComponent = iterator.next();
            menuComponent.print();
        }
    }
}
*/
class Menu : public MenuComponent {
	using string = std::string;
	std::vector<MenueComponentPtr> menuComponents;
    string name;
    string description;
public:
    Menu(string name, string description) : name(name), description(description) {}

    void add(MenueComponentPtr menuComponent) override { menuComponents.push_back(menuComponent); }

    void remove(MenueComponentPtr menuComponent) override {
        for (auto it = menuComponents.begin(); it != menuComponents.end(); ++it)
            if (*it == menuComponent) { //TO DO: Perhaps the source raw pointer should be checked out.
                menuComponents.erase(it);
                break;
            }
    }

    MenueComponentPtr getChild(size_t i) override { return menuComponents.at(i); } //TO DO: I'm not sure about this solution...
    string getName() override { return name; }
    string getDescription() override { return description; }
    MenuComponentIterPtr createIterator() override { return make_shared<CompositeIterator>(make_shared<VectorIterator<MenuComponent>>(menuComponents)); }

    void print() override {
        std::cout << "\n" << getName();
        std::cout << ", " << getDescription() << "\n";
        std::cout << "---------------------\n";
        for (const auto& menuComponent : menuComponents)
            menuComponent->print();
    }
};

#pragma once

#include <iostream>
#include <vector>
#include "MenuComponent.h"
#include "CompositeIterator.h"
#include "VectorIterator.h"
using std::cout;
using std::vector;

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
    vector<MenuComponent*> menuComponents;
    string name;
    string description;
public:
    Menu(string name, string description) : name(name), description(description) {}
    void add(MenuComponent* menuComponent) override { menuComponents.push_back(menuComponent); }

	void remove(MenuComponent* menuComponent) override {
        for (auto it = menuComponents.begin(); it != menuComponents.end(); ++it)
            if (*it == menuComponent) {
                menuComponents.erase(it);
                break;
            }
    }

    MenuComponent* getChild(int i) override { return menuComponents[i]; }
    string getName() override { return name; }
    string getDescription() override { return description; }
    Iterator<MenuComponent>* createIterator() override { return new CompositeIterator(new VectorIterator<MenuComponent>(menuComponents)); }

    void print() override {
        cout << "\n" << getName();
        cout << ", " << getDescription() << "\n";
        cout << "---------------------\n";
        for (auto menuComponent : menuComponents)
            menuComponent->print();
    }
};

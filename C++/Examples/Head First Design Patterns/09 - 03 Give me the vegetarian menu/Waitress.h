#pragma once
#include <iostream>
#include <memory>
#include "MenuComponent.h"
using std::cout;

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
package headfirst.designpatterns.composite.menuiterator;

import java.util.Iterator;
  
public class Waitress {
	MenuComponent allMenus;
 
	public Waitress(MenuComponent allMenus) {
		this.allMenus = allMenus;
	}
 
	public void printMenu() {
		allMenus.print();
	}
  
	public void printVegetarianMenu() {
		Iterator<MenuComponent> iterator = allMenus.createIterator();

		System.out.println("\nVEGETARIAN MENU\n----");
		while (iterator.hasNext()) {
			MenuComponent menuComponent = iterator.next();
			try {
				if (menuComponent.isVegetarian()) {
					menuComponent.print();
				}
			} catch (UnsupportedOperationException e) {}
		}
	}
}
*/
class Waitress {
    MenueComponentPtr allMenus;
public:
    Waitress(MenueComponentPtr allMenus) : allMenus(allMenus) {}
    void printMenu() { allMenus->print(); }

    void printVegetarianMenu() {
        MenuComponentIterPtr iterator = allMenus->createIterator();

        cout << "\nVEGETARIAN MENU\n----\n";
        while (iterator->hasNext()) {
            MenuComponent& menuComponent = iterator->next();
            if (menuComponent.isVegetarian())
                menuComponent.print();
        }
    }
};
#pragma once
#include <iostream>
#include <memory>
#include "MenuComponent.h"

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
    PtrMenucompont allMenus;
public:
    Waitress(PtrMenucompont allMenus) : allMenus(allMenus) {}
    void printMenu() { allMenus->print(); }

    void printVegetarianMenu() {
        std::cout << "\nVEGETARIAN MENU\n----\n";
#ifdef DEBUG
		std::clog << "010 " << typeid(*allMenus).name() << ": " << allMenus->getName() << '\n'; //MINE  
#endif //DEBUG
		PtrIterMenucompont iterator = allMenus->createIterator();
#ifdef DEBUG
		std::clog << "050 " << typeid(iterator->current()).name() << ": " << iterator->current().getName() << '\n'; //MINE
#endif //DEBUG
        while (iterator->hasNext()) {
			MenuComponent &menuComponent = iterator->next();
#ifdef DEBUG
			std::clog << "100 " << typeid(menuComponent).name() << ": " << menuComponent.getName() << '\n'; //MINE
#endif //DEBUG
            if (menuComponent.isVegetarian())
                menuComponent.print();
		}
    }
};
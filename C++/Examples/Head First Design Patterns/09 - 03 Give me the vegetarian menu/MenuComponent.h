#pragma once

#include <string>
#include <memory>
#include "Iterator.h"
using std::string;
using std::shared_ptr;

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
package headfirst.designpatterns.composite.menuiterator;

import java.util.*;

public abstract class MenuComponent {
   
	public void add(MenuComponent menuComponent) {
		throw new UnsupportedOperationException();
	}
	public void remove(MenuComponent menuComponent) {
		throw new UnsupportedOperationException();
	}
	public MenuComponent getChild(int i) {
		throw new UnsupportedOperationException();
	}
  
	public String getName() {
		throw new UnsupportedOperationException();
	}
	public String getDescription() {
		throw new UnsupportedOperationException();
	}
	public double getPrice() {
		throw new UnsupportedOperationException();
	}
	public boolean isVegetarian() {
		throw new UnsupportedOperationException();
	}

	public abstract Iterator<MenuComponent> createIterator();
 
	public void print() {
		throw new UnsupportedOperationException();
	}
}
*/
class MenuComponent {
public:
    virtual ~MenuComponent() {}
    virtual void add(shared_ptr<MenuComponent> menuComponent) {}
    virtual void remove(shared_ptr<MenuComponent> menuComponent) {}
    virtual shared_ptr<MenuComponent> getChild(int i) { return nullptr; }
    virtual string getName() { return ""; }
    virtual string getDescription() { return ""; }
    virtual double getPrice() { return 0.0; }
    virtual bool isVegetarian() { return false; }
    virtual shared_ptr<Iterator<MenuComponent>> createIterator() = 0;
    virtual void print() {}
};
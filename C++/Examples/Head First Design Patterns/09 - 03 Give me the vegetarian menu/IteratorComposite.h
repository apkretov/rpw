#pragma once

#include <stack>
#include "MenuComponent.h"

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
package headfirst.designpatterns.composite.menuiterator;

import java.util.*;
  
public class CompositeIterator implements Iterator<MenuComponent> {
	Stack<Iterator<MenuComponent>> stack = new Stack<Iterator<MenuComponent>>();
   
	public CompositeIterator(Iterator<MenuComponent> iterator) {
		stack.push(iterator);
	}
   
	public MenuComponent next() {
		if (hasNext()) {
			Iterator<MenuComponent> iterator = stack.peek();
			MenuComponent component = iterator.next();
			stack.push(component.createIterator());
			return component;
		} else {
			return null;
		}
	}
  
	public boolean hasNext() {
		if (stack.empty()) {
			return false;
		} else {
			Iterator<MenuComponent> iterator = stack.peek();
			if (!iterator.hasNext()) {
				stack.pop();
				return hasNext();
			} else {
				return true;
			}
		}
	}
}
*/
class CompositeIterator : public Iterator<MenuComponent> {
    mutable std::stack<PtrIterMenucompont> stack;
public:
    CompositeIterator(PtrIterMenucompont iterator) { 
#ifdef DEBUG
		std::clog << "040 " << typeid(iterator->current()).name() << ": " << iterator->current().getName() << '\n';
#endif //DEBUG
		stack.push(iterator); 
	}

	MenuComponent &current() const override { //MINE
		if (stack.empty())
			throw std::runtime_error("No more items in composite");
		PtrIterMenucompont iterator = stack.top();
		return iterator->current();
	}

	MenuComponent &next() override {
        if (hasNext()) {
            PtrIterMenucompont iterator = stack.top();
#ifdef DEBUG
			std::clog << "070 " << typeid(iterator->current()).name() << ": " << iterator->current().getName() << '\n'; //MINE
#endif //DEBUG
			MenuComponent &component = iterator->next();
#ifdef DEBUG
			std::clog << "090 " << typeid(component).name() << ": " << component.getName() << '\n'; //MINE
#endif //DEBUG
			stack.push(component.createIterator());
            return component;
        }
        throw std::runtime_error("No more items in composite");
    }

    bool hasNext() const override {
        if (stack.empty())
            return false;
		PtrIterMenucompont iterator = stack.top();
#ifdef DEBUG //MINE
		try {
			std::clog << "060 " << typeid(iterator->current()).name() << ": " << iterator->current().getName() << '\n';
		}
		catch (const std::runtime_error &e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
#endif //DEBUG
		if (!iterator->hasNext()) {
            stack.pop();
            return hasNext();
        }
        return true;
    }
};

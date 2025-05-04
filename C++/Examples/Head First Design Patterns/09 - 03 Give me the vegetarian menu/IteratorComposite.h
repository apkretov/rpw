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
		std::cout << "222 " << iterator.get()->get().getName() << '\n';
		stack.push(iterator); 
	}

	MenuComponent &get() const override { //MINE
		if (stack.empty())
			throw std::runtime_error("No more items in composite");
		PtrIterMenucompont iterator = stack.top();
		return iterator->get();
	}

	MenuComponent &next() override {
        if (hasNext()) {
            PtrIterMenucompont iterator = stack.top();
			MenuComponent &component = iterator->next();
            stack.push(component.createIterator());
            return component;
        }
        throw std::runtime_error("No more items in composite");
    }

    bool hasNext() const override {
        if (stack.empty())
            return false;
		PtrIterMenucompont iterator = stack.top();
        if (!iterator->hasNext()) {
            stack.pop();
            return hasNext();
        }
        return true;
    }
};

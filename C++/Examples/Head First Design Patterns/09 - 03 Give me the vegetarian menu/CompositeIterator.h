#pragma once

#include <stack>
#include "MenuComponent.h"
using std::stack;

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
	stack<Iterator<MenuComponent> *> stack;

public:
	CompositeIterator(Iterator<MenuComponent> *iterator) { stack.push(iterator); }

	MenuComponent *next() override {
		if (hasNext()) {
			Iterator<MenuComponent> *iterator = stack.top();
			MenuComponent *component = iterator->next();
			stack.push(component->createIterator());
			return component;
		}
		return nullptr;
	}

	bool hasNext() override {
		if (stack.empty())
			return false;

		Iterator<MenuComponent> *iterator = stack.top();
		if (!iterator->hasNext()) {
			stack.pop();
			return hasNext();
		}
		return true;
	}
};

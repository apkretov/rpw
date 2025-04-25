#pragma once

#include "Iterator.h"
#include "MenuComponent.h"

/* Java @https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/composite/menuiterator
public class NullIterator implements Iterator<MenuComponent> {
    public MenuComponent next() { return null; }
    public boolean hasNext() { return false; }
}
*/

class NullIterator : public Iterator<MenuComponent> {
public:
    MenuComponent& next() override { 
        throw std::runtime_error("No elements in NullIterator"); 
    }
    bool hasNext() noexcept override { return false; }
};

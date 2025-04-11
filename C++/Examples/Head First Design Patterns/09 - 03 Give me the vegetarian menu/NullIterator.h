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
    MenuComponent* next() override { return nullptr; }
    bool hasNext() override { return false; }
};

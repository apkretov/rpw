#pragma once
#include "Iterator.h"
#include "ItemMenu.h"
#include <memory>

using PtrIterMenuitem = std::shared_ptr<Iterator<MenuItem>>;

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
public interface Menu {
	Iterator<MenuItem> createIterator();
}
*/
class Menu {
public:
	virtual ~Menu() = default;
	virtual PtrIterMenuitem createIterator() = 0;
};


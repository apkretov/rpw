#pragma once
#include "Iterator.h"
#include "MenuItem.h"

#pragma region Adding an Iterator to DinerMenu
/* Java
public class DinerMenuIterator implements Iterator {
    MenuItem[] items;
    int position = 0; // position maintains the current position of the iteration over the array

    public DinerMenuIterator(MenuItem[] items) { // The constructor takes the array of menu items we are going to iterate over.
        this.items = items;
    }

    public Object next() { // The next() method returns the next item in the array and increments the position.
        MenuItem menuItem = items[position];
        position = position + 1;
        return menuItem;
    }

    public boolean hasNext() { // The hasNext() method checks to see if we've seen all the elements of the array and returns true if there are more to iterate through.
        if (position >= items.length || items[position] == null) { // Because the diner chef went ahead and allocated a max sized array, we need to check not only if we are at the end of the array, but also if the next item is null, which indicates there are no more items.
            return false;
        } else {
            return true;
        }
    }
}
*/
template <typename T>
class DinerMenuIterator : public Iterator<T> {
    T* items;
    int position = 0; // position maintains the current position of the iteration over the array
    int maxItems;
public:
    DinerMenuIterator(T* items, int maxItems) : items(items), maxItems(maxItems) {} // The constructor takes the array of menu items we are going to iterate over.

    T* next() override { // The next() method returns the next item in the array and increments the position.
        T* menuItem = &items[position];
        position = position + 1;
        return menuItem;
    }

    bool hasNext() override { // The hasNext() method checks to see if we've seen all the elements of the array and returns true if there are more to iterate through.
        if (position >= maxItems || items[position].getName().empty()) // Because the diner chef went ahead and allocated a max sized array, we need to check not only if we are at the end of the array, but also if the next item is null, which indicates there are no more items.
            return false;
        return true;
    }
};
#pragma endregion //Adding an Iterator to DinerMenu
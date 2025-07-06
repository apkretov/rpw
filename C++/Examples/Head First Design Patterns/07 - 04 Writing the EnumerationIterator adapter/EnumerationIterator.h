#pragma once

#include <stdexcept>
#include "Enumeration.h"
#include "Iterator.h"
using std::runtime_error;

/* Java
public class EnumerationIterator implements Iterator { // Since we're adapting Enumeration to Iterator, our Adapter implements the Iterator interface... it has to look like an Iterator.
	Enumeration enum;
	public EnumerationIterator(Enumeration enum) { this.enum = enum; } // The Enumeration we're adapting. We're using composition so we stash it in an instance variable.
	public boolean hasNext() { return enum.hasMoreElements(); } // The Iterator's hasNext() method is delegated to the Enumeration's hasMoreElements() method...
	public Object next() { return enum.nextElement(); } // ... and the Iterator's next() method is delegated to the Enumerations's nextElement() method.
	public void remove() { throw new UnsupportedOperationException(); } //TEST //																			Unfortunately, we can't support Iterator's remove() method, so we have to punt(in other words, we give up!).Here we just throw an exception.
}
*/
class EnumerationIterator : public Iterator { // Since we're adapting Enumeration to Iterator, our Adapter implements the Iterator interface... it has to look like an Iterator.
    Enumeration &enum_;  // The Enumeration we're adapting. We're using composition so we stash it in an instance variable.
public:
    EnumerationIterator(Enumeration &enum_) : enum_(enum_) {} // Constructor using member initializer list
    bool hasNext() override { return enum_.hasMoreElements(); } // The Iterator's hasNext() method is delegated to the Enumeration's hasMoreElements() method...
    void* next() override { return enum_.nextElement(); } // ... and the Iterator's next() method is delegated to the Enumerations's nextElement() method.
    void remove() override { throw runtime_error("Operation not supported"); } //TEST //															Unfortunately, we can't support Iterator's remove() method, so we have to punt(in other words, we give up!).Here we just throw an exception.
};

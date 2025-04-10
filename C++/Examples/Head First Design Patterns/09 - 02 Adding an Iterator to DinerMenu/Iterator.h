#pragma once

#pragma region Adding an Iterator to DinerMenu
/* Java
public interface Iterator {
    boolean hasNext(); // The hasNext() method returns a boolean indicating whether or not there are more elements to iterate over...
    Object next(); // ...and the next() method returns the next element.
}
*/
template <typename T>
class Iterator {
public:
	virtual ~Iterator() = default;
    virtual bool hasNext() = 0; // The hasNext() method returns a boolean indicating whether or not there are more elements to iterate over...
    virtual T *next() = 0; // ...and the next() method returns the next element.
};
#pragma endregion //Adding an Iterator to DinerMenu
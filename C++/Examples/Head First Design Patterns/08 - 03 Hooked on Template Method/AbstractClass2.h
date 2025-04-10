#pragma once

#include <iostream>
using std::cout;

#pragma region Code Way Up Close
/* Java
abstract class AbstractClass {
    final void templateMethod() { // We've changed the templateMethod() to include a new method call.
        primitiveOperation1();
        primitiveOperation2();
        concreteOperation(); // We still have our primitive methods; these are abstract and implemented by concrete subclasses.
        hook();
    }

    abstract void primitiveOperation1();

    abstract void primitiveOperation2();

    final void concreteOperation() { // A concrete operation is defined in the abstract class. This one is declared final so that subclasses can't override it. It may be used in the template method directly, or used by subclasses.
        // implementation here
    }

    void hook() {} // A concrete method, but it does nothing! // We can also have concrete methods that do nothing by default; we call these "hooks." Subclasses are free to override these but don't have to. We're going to see how these are useful on the next page.
}
*/
class AbstractClass {
public:
    virtual ~AbstractClass() = default;

    void templateMethod() { // We've changed the templateMethod() to include a new method call.
        primitiveOperation1();
        primitiveOperation2();
        concreteOperation(); // We still have our primitive methods; these are abstract and implemented by concrete subclasses.
        hook();
    }

    virtual void primitiveOperation1() = 0;
    virtual void primitiveOperation2() = 0;
    void concreteOperation() { /* implementation here */ } // A concrete operation is defined in the abstract class. This one is declared final so that subclasses can't override it. It may be used in the template method directly, or used by subclasses.
    virtual void hook() {} // A concrete method, but it does nothing! // We can also have concrete methods that do nothing by default; we call these "hooks." Subclasses are free to override these but don't have to. We're going to see how these are useful on the next page.
};
#pragma endregion //Code Way Up Close

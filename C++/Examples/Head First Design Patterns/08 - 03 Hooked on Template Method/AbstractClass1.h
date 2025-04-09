#pragma once

#pragma region Code Up Close
/* Java
abstract class AbstractClass { // Here we have our abstract class; it is declared abstract and meant to be subclassed by classes that provide implementations of the operations.
	final void templateMethod() { // Here's the template method. It's declared final to prevent subclasses from reworking the sequence of steps in the algorithm.
		primitiveOperation1(); // The template method defines the sequence of steps, each represented by a method.
		primitiveOperation2();
		concreteOperation();
	}
	abstract void primitiveOperation1(); // In this example, two of the primitive operations must be implemented by concrete subclasses.
	abstract void primitiveOperation2();
	void concreteOperation() { // We also have a concrete operation defined in the abstract class. More about these kinds of methods in a bit...
		// implementation here
	}
} */
class AbstractClass { // Here we have our abstract class; it is declared abstract and meant to be subclassed by classes that provide implementations of the operations.
public:
	virtual ~AbstractClass() = default;

	void templateMethod() { // Here's the template method. It's declared final to prevent subclasses from reworking the sequence of steps in the algorithm.
		primitiveOperation1(); // The template method defines the sequence of steps, each represented by a method.
		primitiveOperation2();
		concreteOperation();
	}

	virtual void primitiveOperation1() = 0; // In this example, two of the primitive operations must be implemented by concrete subclasses.
	virtual void primitiveOperation2() = 0;
	void concreteOperation() { /*implementation here*/ } // We also have a concrete operation defined in the abstract class. More about these kinds of methods in a bit...
};
#pragma endregion //Code Up Close

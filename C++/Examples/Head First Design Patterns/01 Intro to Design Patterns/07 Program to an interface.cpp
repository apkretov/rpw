#if 0

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

/* Java
// Programming to an implementation would be:
Dog d = new Dog(); // Declaring the variable “d” as type Dog (a concrete implementation of Animal) forces us to code to a concrete implementation.
d.bark();

// But programming to an interface/supertype would be:
Animal animal = new Dog(); // We know it's a Dog, but we can now use the animal reference polymorphically.
animal.makeSound();

// Even better, rather than hard-coding the instantiation of the subtype (like new Dog()) into the code, assign the concrete implementation object at runtime:
a = getAnimal(); // We don't know WHAT the actual animal subtype is... all we care about is that it knows how to respond to makeSound().
a.makeSound();
*/

struct Animal {
	virtual ~Animal() = default;
	virtual void makeSound() const = 0;
};

struct Dog : Animal {
	void makeSound() const override { bark(); }
	void bark() const { cout << "Make a bark sound.\n"; }
};

struct Cat : Animal {
	void makeSound() const override { meow(); }
	void meow() const { cout << "Make a meow sound.\n"; }
};

void programming_to_implementation() { // Programming to an implementation would be:
	Dog d;
	d.bark();
}

void programming_to_interface_supertype() { // But programming to an interface/supertype would be:
	auto animal = make_unique<Dog>(); // We know it's a Dog, but we can now use the animal reference polymorphically.
	animal->makeSound();
}

unique_ptr<Animal> getAnimal(string_view animal_type) {
	if (animal_type == "dog")
		return make_unique<Dog>();
	else if (animal_type == "cat")
		return make_unique<Cat>();
	else
		throw runtime_error("No animal type specified.");
}

void assign_implementation_at_runtime() { // Even better, rather than hard-coding the instantiation of the subtype (like new Dog()) into the code, assign the concrete implementation object at runtime:
	auto a = getAnimal("cat"); // We don't know WHAT the actual animal subtype is... all we care about is that it knows how to respond to makeSound().
	a->makeSound();
	
	a = getAnimal("dog"); 
	a->makeSound();
}

int main(int argc, char *argv[]) {
	print_file_line();

	programming_to_implementation();
	cout << '\n';
	programming_to_interface_supertype();
	cout << '\n';
	assign_implementation_at_runtime();
	
	return 0;
}
#endif //1
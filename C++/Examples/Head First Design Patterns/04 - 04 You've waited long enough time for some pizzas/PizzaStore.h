#pragma once

#include <string_view>
#include "Pizza.h"

#pragma region A framework for the pizza store
/* Java
public abstract class PizzaStore { // PizzaStore is now abstract.
	public Pizza orderPizza(String type) {
		Pizza pizza;
		pizza = createPizza(type); // Now createPizza is back to being a call to a method in the PizzaStore rather than on a factory object.
		pizza.prepare(); // All this looks just the same...
		pizza.bake();
		pizza.cut();
		pizza.box();
		return pizza;
	}
	abstract Pizza createPizza(String type); // Our "factory method" is now abstract in PizzaStore. // Now we've moved our factory object to this method.
}
*/
class PizzaStore { // PizzaStore is now abstract
public:
	virtual ~PizzaStore() = default;

	PizzaPtr orderPizza(string_view type) {
		PizzaPtr pizza = createPizza(type); // Now createPizza is back to being a call to a method in the PizzaStore rather than on a factory object
		pizza->prepare(); // All this looks just the same...
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}

	virtual PizzaPtr createPizza(string_view type) = 0; // Our "factory method" is now abstract in PizzaStore. // Now we've moved our factory object to this method
};
#pragma endregion //A framework for the pizza store

using PizzaStorePtr = unique_ptr<PizzaStore>; //MINE

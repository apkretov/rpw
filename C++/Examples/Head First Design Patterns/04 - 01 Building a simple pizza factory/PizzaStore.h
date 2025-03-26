#pragma once

#include "SimplePizzaFactory.h"

#pragma region Reworking the PizzaStore class
/* Java
public class PizzaStore {
	SimplePizzaFactory factory; // Now we give PizzaStore a reference to a SimplePizzaFactory.
	public PizzaStore(SimplePizzaFactory factory) { // PizzaStore gets the factory passed to it in the constructor.
		this.factory = factory;
	}
	public Pizza orderPizza(String type) {
		Pizza pizza;
		pizza = factory.createPizza(type); // And the orderPizza() method uses the factory to create its pizzas by simply passing on the type of the order. // Notice that we�ve replaced the new operator with a create method on the factory object.No more concrete instantiations here!
		pizza.prepare();
		pizza.bake();
		pizza.cut();
		pizza.box();
		return pizza;
	}
}
*/
class PizzaStore {
	SimplePizzaFactory factory_; // Now we give PizzaStore a reference to a SimplePizzaFactory.
public:
	explicit PizzaStore(SimplePizzaFactory factory) : factory_(std::move(factory)) {} // PizzaStore gets the factory passed to it in the constructor.

	PizzaPtr orderPizza(const string &type) {
		PizzaPtr pizza = factory_.createPizza(type); // And the orderPizza() method uses the factory to create its pizzas by simply passing on the type of the order. // Notice that we've replaced the new operator with a create method on the factory object.No more concrete instantiations here!
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}
};
#pragma endregion //Reworking the PizzaStore class

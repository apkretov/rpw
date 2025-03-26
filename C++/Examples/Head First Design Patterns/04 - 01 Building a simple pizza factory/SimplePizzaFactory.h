#pragma once

#include "Pizza.h"

#pragma region Building a simple pizza factory
/* Java
public class SimplePizzaFactory { // Here's our new class, the SimplePizzaFactory. It has one job in life : creating pizzas for its clients.
	public Pizza createPizza(String type) { // First we define a createPizza() method in the factory.This is the method all clients will use to instantiate new objects.
		Pizza pizza = null;
		if (type.equals("cheese")) // Here's the code we plucked out of the orderPizza() method.
			pizza = new CheesePizza();
		else if (type.equals("pepperoni"))
			pizza = new PepperoniPizza();
		else if (type.equals("clam"))
			pizza = new ClamPizza();
		else if (type.equals("veggie"))
			pizza = new VeggiePizza();
		return pizza;
	}
}
*/
class SimplePizzaFactory {
public:
	PizzaPtr createPizza(string_view type) {
		PizzaPtr pizza;
		if (type == "cheese")
			pizza = make_unique<CheesePizza>();
		else if (type == "pepperoni")
			pizza = make_unique<PepperoniPizza>();
		else if (type == "clam")
			pizza = make_unique<ClamPizza>();
		else if (type == "veggie")
			pizza = make_unique<VeggiePizza>();
		return pizza;
	}
};
#pragma endregion //Building a simple pizza factory
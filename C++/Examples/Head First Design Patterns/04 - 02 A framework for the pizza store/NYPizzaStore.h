#pragma once

#include "PizzaStore.h"

#pragma region Lets make a PizzaStore //Let's make a PizzaStore
/* Java
public class NYPizzaStore extends PizzaStore { // The NYPizzaStore extends PizzaStore, so it inherits the orderPizza() method(among others).
	Pizza createPizza(String item) { // createPizza() returns a Pizza, and the subclass is fully responsible for which concrete Pizza it instantiates. // We've got to implement createPizza(), since it is abstract in PizzaStore.
		if (item.equals(“cheese”)) { // Here's where we create our concrete classes.For each type of Pizza we create the NY style.
			return new NYStyleCheesePizza();
		} else if (item.equals(“veggie”)) {
			return new NYStyleVeggiePizza();
		} else if (item.equals(“clam”)) {
			return new NYStyleClamPizza();
		} else if (item.equals(“pepperoni”)) {
			return new NYStylePepperoniPizza();
		} else return null;
	}
} // * Note that the orderPizza() method in the superclass has no clue which Pizza we are creating; it just knows it can prepare, bake, cut, and box it!
*/
class NYPizzaStore final : public PizzaStore { // The NYPizzaStore extends PizzaStore, so it inherits the orderPizza() method(among others).
public:
	PizzaPtr createPizza(string_view item) override { // createPizza() returns a Pizza, and the subclass is fully responsible for which concrete Pizza it instantiates. // We've got to implement createPizza(), since it is abstract in PizzaStore.
		if (item == "cheese") // Here's where we create our concrete classes.For each type of Pizza we create the NY style.
			return make_unique<NYStyleCheesePizza>();
		else if (item == "veggie")
			return make_unique<NYStyleVeggiePizza>();
		else if (item == "clam")
			return make_unique<NYStyleClamPizza>();
		else if (item == "pepperoni")
			return make_unique<NYStylePepperoniPizza>();
		else 
			return nullptr;
	}
}; // * Note that the orderPizza() method in the superclass has no clue which Pizza we are creating; it just knows it can prepare, bake, cut, and box it!
#pragma endregion //Lets make a PizzaStore

#pragma once

#include <memory>
#include <string_view>
using std::make_unique;
using std::string_view;
using std::unique_ptr;

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

	unique_ptr<Pizza> orderPizza(string_view type) {
		unique_ptr<Pizza> pizza;
		pizza = createPizza(type); // Now createPizza is back to being a call to a method in the PizzaStore rather than on a factory object
		pizza->prepare(); // All this looks just the same...
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}

	virtual unique_ptr<Pizza> createPizza(string_view type) = 0; // Our "factory method" is now abstract in PizzaStore. // Now we've moved our factory object to this method
};
#pragma endregion //A framework for the pizza store

using PizzaStorePtr = unique_ptr<PizzaStore>; //MINE

#pragma region Lets make a PizzaStore //Let's make a PizzaStore
/* Java
public class NYPizzaStore extends PizzaStore { // The NYPizzaStore extends PizzaStore, so it inherits the orderPizza() method(among others).
	Pizza createPizza(String item) { // createPizza() returns a Pizza, and the subclass is fully responsible for which concrete Pizza it instantiates. // We’ve got to implement createPizza(), since it is abstract in PizzaStore.
		if (item.equals(“cheese”)) { // Here’s where we create our concrete classes.For each type of Pizza we create the NY style.
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
	unique_ptr<Pizza> createPizza(string_view item) override { // createPizza() returns a Pizza, and the subclass is fully responsible for which concrete Pizza it instantiates. // We've got to implement createPizza(), since it is abstract in PizzaStore.
		if (item == "cheese") // Here's where we create our concrete classes.For each type of Pizza we create the NY style.
			return make_unique<NYStyleCheesePizza>();
		else if (item == "veggie")
			return make_unique<NYStyleVeggiePizza>();
		else if (item == "clam")
			return make_unique<NYStyleClamPizza>();
		else if (item == "pepperoni")
			return make_unique<NYStylePepperoniPizza>();
		else return nullptr;
	}
}; // * Note that the orderPizza() method in the superclass has no clue which Pizza we are creating; it just knows it can prepare, bake, cut, and box it!
#pragma endregion //Lets make a PizzaStore

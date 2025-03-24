#if 1

#include <memory>
#include "../../stdafx.h"
#include "01 Building a simple pizza factory.h"
using namespace std;

#pragma region MINE
class NYStyleCheesePizza : public CheesePizza {};
class NYStylePepperoniPizza : public PepperoniPizza {};
class NYStyleClamPizza : public ClamPizza {};
class NYStyleVeggiePizza : public VeggiePizza {};
#pragma endregion //MINE

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
		PizzaPtr pizza;
		pizza = createPizza(type); // Now createPizza is back to being a call to a method in the PizzaStore rather than on a factory object
		pizza->prepare(); // All this looks just the same...
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}

	virtual PizzaPtr createPizza(string_view type) = 0; // Our "factory method" is now abstract in PizzaStore. // Now we've moved our factory object to this method
};
#pragma endregion //A framework for the pizza store

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

class NYPizzaStore : public PizzaStore { // The NYPizzaStore extends PizzaStore, so it inherits the orderPizza() method(among others).
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
		else return nullptr;
	}
}; // * Note that the orderPizza() method in the superclass has no clue which Pizza we are creating; it just knows it can prepare, bake, cut, and box it!
#pragma endregion //Lets make a PizzaStore

int main(int argc, char *argv[]) {
	print_file_line();

	NYPizzaStore ny_store;
	auto cheese_pizza = ny_store.createPizza("cheese");
	cheese_pizza->prepare();
	cheese_pizza->bake();
	cheese_pizza->cut();
	cheese_pizza->box();

	return 0;
}
#endif //1
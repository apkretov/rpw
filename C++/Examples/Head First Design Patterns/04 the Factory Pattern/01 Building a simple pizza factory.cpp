#if 1 

#include <memory>
#include "../../stdafx.h"
#include "01 Building a simple pizza factory.h"
using namespace std;

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

int main(int argc, char *argv[]) {
	print_file_line();

	SimplePizzaFactory factory;
	PizzaStore store{factory};
	auto cheese_pizza = factory.createPizza("cheese");
	cheese_pizza->prepare();
	cheese_pizza->bake();
	cheese_pizza->cut();
	cheese_pizza->box();

	return 0;
}
#endif //1
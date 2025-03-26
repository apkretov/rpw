#if 0

#include <memory>
#include "06 Building the ingredient factories.h"
#include "../../stdafx.h"
using namespace std;

#pragma region Reworking the pizzas
/* Java
public abstract class Pizza {
	String name; // Each pizza holds a set of ingredients that are used in its preparation.
	Dough dough;
	Sauce sauce;
	Veggies veggies[];
	Cheese cheese;
	Pepperoni pepperoni;
	Clams clam;
	abstract void prepare(); // We've now made the prepare method abstract. This is where we are going to collect the ingredients needed for the pizza, which of course will come from the ingredient factory.
	void bake() { System.out.println("Bake for 25 minutes at 350");	} // Our other methods remain the same, with the exception of the prepare method.
	void cut() { System.out.println("Cutting the pizza into diagonal slices"); }
	void box() { System.out.println("Place pizza in official PizzaStore box"); }
	void setName(String name) { this.name = name; }
	String getName() { return name; }
	public String toString() {
		//code to print pizza here
	}
}
*/
class Pizza {
protected:
	string name; // Each pizza holds a set of ingredients that are used in its preparation.
	unique_ptr<Dough> dough;
	unique_ptr<Sauce> sauce;
	vector<unique_ptr<Veggies>> veggies;
	unique_ptr<Cheese> cheese;
	unique_ptr<Pepperoni> pepperoni;
	unique_ptr<Clams> clam;
public:
	virtual ~Pizza() = default;
	virtual void prepare() = 0; // We've now made the prepare method abstract. This is where we are going to collect the ingredients needed for the pizza, which of course will come from the ingredient factory.
	virtual void bake() { cout << "Bake for 25 minutes at 350\n"; } // Our other methods remain the same, with the exception of the prepare method.
	virtual void cut() { cout << "Cutting the pizza into diagonal slices\n"; }
	virtual void box() { cout << "Place pizza in official PizzaStore box\n"; }
	void setName(const string &name) { this->name = name; }
	string getName() const { return name; }

	virtual string toString() const {
		//code to print pizza here
		return "";
	}
};
#pragma endregion //Reworking the pizzas

using PizzaPtr = unique_ptr<Pizza>; //MINE

#pragma region Reworking the pizzas, continued...
/* Java
public class CheesePizza extends Pizza {
	PizzaIngredientFactory ingredientFactory;
	public CheesePizza(PizzaIngredientFactory ingredientFactory) { this.ingredientFactory = ingredientFactory; } // To make a pizza now, we need a factory to provide the ingredients.So each Pizza class gets a factory passed into its constructor, and it's stored in an instance variable.

	void prepare() { // The prepare() method steps through creating a cheese pizza, and each time it needs an ingredient, it asks the factory to produce it.
		System.out.println("Preparing " + name);
		dough = ingredientFactory.createDough(); // Here's where the magic happens!
		sauce = ingredientFactory.createSauce();
		cheese = ingredientFactory.createCheese();
	}
}
*/
class CheesePizza : public Pizza {
	PizzaIngredientFactory &ingredientFactory;
public:
	CheesePizza(PizzaIngredientFactory &ingredientFactory) : ingredientFactory(ingredientFactory) {} // To make a pizza now, we need a factory to provide the ingredients. So each Pizza class gets a factory passed into its constructor, and it's stored in an instance variable.

	void prepare() override { // The prepare() method steps through creating a cheese pizza, and each time it needs an ingredient, it asks the factory to produce it.
		cout << "Preparing " << name << "\n";
		dough = ingredientFactory.createDough(); // Here's where the magic happens!
		sauce = ingredientFactory.createSauce();
		cheese = ingredientFactory.createCheese();
	}
};
#pragma endregion //Reworking the pizzas, continued...

#pragma region Code Up Close
/* Java
public class ClamPizza extends Pizza {
	PizzaIngredientFactory ingredientFactory;
	public ClamPizza(PizzaIngredientFactory ingredientFactory) { this.ingredientFactory = ingredientFactory;} // ClamPizza also stashes an ingredient factory.

	void prepare() {
		System.out.println(“Preparing “ + name);
		dough = ingredientFactory.createDough(); // To make a clam pizza, the prepare method collects the right ingredients from its local factory.
		sauce = ingredientFactory.createSauce();
		cheese = ingredientFactory.createCheese();
		clam = ingredientFactory.createClam(); // If it's a New York factory, the clams will be fresh; if it's Chicago, they'll be frozen.
	}
}
*/
class ClamPizza : public Pizza {
	PizzaIngredientFactory &ingredientFactory;
public:
	ClamPizza(PizzaIngredientFactory &ingredientFactory) : ingredientFactory(ingredientFactory) {} // ClamPizza also stashes an ingredient factory.

	void prepare() override {
		cout << "Preparing " << name << "\n";
		dough = ingredientFactory.createDough(); // To make a clam pizza, the prepare method collects the right ingredients from its local factory.
		sauce = ingredientFactory.createSauce();
		cheese = ingredientFactory.createCheese();
		clam = ingredientFactory.createClam(); // If it's a New York factory, the clams will be fresh; if it's Chicago, they'll be frozen.
	}
};
#pragma endregion //Code Up Close

#pragma region Revisiting our pizza stores
/* Java
public class NYPizzaStore extends PizzaStore {
	protected Pizza createPizza(String item) {
		Pizza pizza = null;
		PizzaIngredientFactory ingredientFactory = new NYPizzaIngredientFactory(); // The NY Store is composed with a NY pizza ingredient factory.This will be used to produce the ingredients for all NY style pizzas.
		if (item.equals(“cheese”)) { // For each type of Pizza, we instantiate a new Pizza and give it the factory it needs to get its ingredients.
			pizza = new CheesePizza(ingredientFactory); // We now pass each pizza the factory that should be used to produce its ingredients. // Look back one page and make sure you understand how the pizza and the factory work together!
			pizza.setName(“New York Style Cheese Pizza”);
		} else if (item.equals(“veggie”)) {
			pizza = new VeggiePizza(ingredientFactory);
			pizza.setName(“New York Style Veggie Pizza”);
		} else if (item.equals(“clam”)) {
			pizza = new ClamPizza(ingredientFactory);
			pizza.setName(“New York Style Clam Pizza”);
		} else if (item.equals(“pepperoni”)) {
			pizza = new PepperoniPizza(ingredientFactory);
			pizza.setName(“New York Style Pepperoni Pizza”);
		}
		return pizza;
	}
}
*/
class NYPizzaStore : public PizzaStore {
protected:
    PizzaPtr createPizza(const string &item) override {
        PizzaPtr pizza = nullptr;
        auto ingredientFactory = make_unique<NYPizzaIngredientFactory>(); // The NY Store is composed with a NY pizza ingredient factory. This will be used to produce the ingredients for all NY style pizzas.
        
        if (item == "cheese") { // For each type of Pizza, we instantiate a new Pizza and give it the factory it needs to get its ingredients.
            pizza = make_unique<CheesePizza>(*ingredientFactory); // We now pass each pizza the factory that should be used to produce its ingredients.
            pizza->setName("New York Style Cheese Pizza");
        } else if (item == "veggie") {
            pizza = make_unique<VeggiePizza>(*ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");
        } else if (item == "clam") {
            pizza = make_unique<ClamPizza>(*ingredientFactory);
            pizza->setName("New York Style Clam Pizza");
        } else if (item == "pepperoni") {
            pizza = make_unique<PepperoniPizza>(*ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");
        }
        return pizza;
    }
};
#pragma endregion //Revisiting our pizza stores

int main() {
	print_file_line();
	return 0;
}
#endif //1
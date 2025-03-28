#pragma once

#include "Pizza.h"
#include "PizzaIngredientFactory.h"

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

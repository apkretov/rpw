#pragma once

#include "Pizza.h"
#include "PizzaIngredientFactory.h"

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

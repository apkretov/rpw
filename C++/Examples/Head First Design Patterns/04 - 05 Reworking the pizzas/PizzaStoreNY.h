#pragma once

#include "PizzaStore.h"
#include "PizzaIngredientFactoryNY.h"
#include "PizzaCheese.h"

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
	PizzaPtr createPizza(string_view item) override {
		PizzaPtr pizza = nullptr;
		auto ingredientFactory = make_unique<NYPizzaIngredientFactory>(); // The NY Store is composed with a NY pizza ingredient factory. This will be used to produce the ingredients for all NY style pizzas.

		if (item == "cheese") { // For each type of Pizza, we instantiate a new Pizza and give it the factory it needs to get its ingredients.
			pizza = make_unique<CheesePizza>(*ingredientFactory); // We now pass each pizza the factory that should be used to produce its ingredients.
			pizza->setName("New York Style Cheese Pizza");
#if 0
		} else if (item == "veggie") {
			pizza = make_unique<VeggiePizza>(*ingredientFactory);
			pizza->setName("New York Style Veggie Pizza");
		} else if (item == "clam") {
			pizza = make_unique<ClamPizza>(*ingredientFactory);
			pizza->setName("New York Style Clam Pizza");
		} else if (item == "pepperoni") {
			pizza = make_unique<PepperoniPizza>(*ingredientFactory);
			pizza->setName("New York Style Pepperoni Pizza");
#endif //0
		}
		return pizza;
	}
};
#pragma endregion //Revisiting our pizza stores
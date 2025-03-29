#pragma once

#include "PizzaStore.h"
#include "PizzaIngredientFactoryChicago.h"
#include "PizzaCheese.h"
#include "PizzaClam.h"

#pragma region Sharpen your pencil
class ChicagoPizzaStore : public PizzaStore {
protected:
	ChicagoPizzaIngredientFactory ingredientFactory;

	PizzaPtr createPizza(string_view item) override {
		PizzaPtr pizza = nullptr;

		if (item == "cheese") { 
			pizza = make_unique<CheesePizza>(ingredientFactory);
			pizza->setName("Chicago Style Cheese Pizza");
		} else if (item == "clam") {
			pizza = make_unique<ClamPizza>(ingredientFactory);
			pizza->setName("Chicago Style Clam Pizza");
		}
		return pizza;
	}
};
#pragma endregion //Sharpen your pencil
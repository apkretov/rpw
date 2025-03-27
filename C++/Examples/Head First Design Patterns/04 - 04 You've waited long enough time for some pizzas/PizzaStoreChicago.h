#pragma once

#include "PizzaStore.h"

#pragma region MINE
class ChicagoPizzaStore final : public PizzaStore {
public:
	PizzaPtr createPizza(string_view item) override {
		if (item == "cheese")
			return make_unique<ChicagoStyleCheesePizza>();
		else if (item == "veggie")
			return make_unique<ChicagoStyleVeggiePizza>();
		else if (item == "clam")
			return make_unique<ChicagoStyleClamPizza>();
		else if (item == "pepperoni")
			return make_unique<ChicagoStylePepperoniPizza>();
		else 
			return nullptr;
	}
};
#pragma endregion //MINE

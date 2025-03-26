#pragma once

#include "PizzaStore.h"

class CaliforniaPizzaStore : public PizzaStore {
public:
	PizzaPtr createPizza(string_view item) override {
		if (item == "cheese")
			return make_unique<CaliforniaStyleCheesePizza>();
		else if (item == "veggie")
			return make_unique<CaliforniaStyleVeggiePizza>();
		else if (item == "clam")
			return make_unique<CaliforniaStyleClamPizza>();
		else if (item == "pepperoni")
			return make_unique<CaliforniaStylePepperoniPizza>();
		else return nullptr;
	}
};

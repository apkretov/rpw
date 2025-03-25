#pragma once

#pragma region MINE
#ifndef YOU_VE_WAITED_LONG_ENOUGH_TIME_FOR_SOME_PIZZAS
class ChicagoStyleCheesePizza final : public Pizza {};
#endif //YOU_VE_WAITED_LONG_ENOUGH_TIME_FOR_SOME_PIZZAS
class ChicagoStylePepperoniPizza final : public Pizza {};
class ChicagoStyleClamPizza final : public Pizza {};
class ChicagoStyleVeggiePizza final : public Pizza {};

class CaliforniaStyleCheesePizza final : public Pizza {};
class CaliforniaStylePepperoniPizza final : public Pizza {};
class CaliforniaStyleClamPizza final : public Pizza {};
class CaliforniaStyleVeggiePizza final : public Pizza {};

class ChicagoPizzaStore : public PizzaStore {
public:
	unique_ptr<Pizza> createPizza(string_view item) override {
		if (item == "cheese")
			return make_unique<ChicagoStyleCheesePizza>();
		else if (item == "veggie")
			return make_unique<ChicagoStyleVeggiePizza>();
		else if (item == "clam")
			return make_unique<ChicagoStyleClamPizza>();
		else if (item == "pepperoni")
			return make_unique<ChicagoStylePepperoniPizza>();
		else return nullptr;
	}
};

class CaliforniaPizzaStore : public PizzaStore {
public:
	unique_ptr<Pizza> createPizza(string_view item) override {
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
#pragma endregion //MINE

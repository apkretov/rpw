#if 1

#include <array>
#include <memory>
#include "../../stdafx.h"
#include "02 A framework for the pizza store.h"
using namespace std;

#pragma region MINE
class ChicagoStyleCheesePizza final : public CheesePizza {};
class ChicagoStylePepperoniPizza final : public PepperoniPizza {};
class ChicagoStyleClamPizza final : public ClamPizza {};
class ChicagoStyleVeggiePizza final : public VeggiePizza {};

class CaliforniaStyleCheesePizza final : public CheesePizza {};
class CaliforniaStylePepperoniPizza final : public PepperoniPizza {};
class CaliforniaStyleClamPizza final : public ClamPizza {};
class CaliforniaStyleVeggiePizza final : public VeggiePizza {};

class ChicagoPizzaStore : public PizzaStore { 
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
		else return nullptr;
	}
}; 

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
#pragma endregion //MINE

int main(int argc, char *argv[]) {
	print_file_line();

	array<unique_ptr<PizzaStore>, 2> stores = {make_unique<ChicagoPizzaStore>(), make_unique<CaliforniaPizzaStore>()};
	for (const auto& store : stores) {
		auto cheese_pizza = store->createPizza("cheese");
		cheese_pizza->prepare();
		cheese_pizza->bake();
		cheese_pizza->cut();
		cheese_pizza->box();
		cout << '\n';
	}

	return 0;
}
#endif //1
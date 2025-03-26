
#include <array>
#include "../../stdafx.h"
#include "NYPizzaStore.h"
#include "ChicagoPizzaStore.h"
#include "CaliforniaPizzaStore.h"

int main(int argc, char *argv[]) {
	print_file_line();

	array<PizzaStorePtr, 2> stores = {make_unique<ChicagoPizzaStore>(), make_unique<CaliforniaPizzaStore>()};
	for (const auto &store : stores) {
		auto cheese_pizza = store->createPizza("cheese");
		cheese_pizza->prepare();
		cheese_pizza->bake();
		cheese_pizza->cut();
		cheese_pizza->box();
		cout << '\n';
	}

	return 0;
}

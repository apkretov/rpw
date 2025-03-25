#if 0

#include <array>
#include <memory>
#include "../../stdafx.h"
#include "02 A framework for the pizza store 1.h"
#include "03 Sharpen your pencil.h"
using namespace std;

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
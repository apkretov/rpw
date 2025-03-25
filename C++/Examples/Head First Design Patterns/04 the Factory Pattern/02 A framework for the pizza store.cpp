#if 0

#include <memory>
#include "../../stdafx.h"
#include "02 A framework for the pizza store 1.h"

int main(int argc, char *argv[]) {
	print_file_line();

	NYPizzaStore ny_store;
	auto cheese_pizza = ny_store.createPizza("cheese");
	cheese_pizza->prepare();
	cheese_pizza->bake();
	cheese_pizza->cut();
	cheese_pizza->box();

	return 0;
}
#endif //1
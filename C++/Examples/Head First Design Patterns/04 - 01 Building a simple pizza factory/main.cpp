#include <memory>
#include "../../stdafx.h"
#include "PizzaStore.h"

int main(int argc, char *argv[]) {
	print_file_line();

	SimplePizzaFactory factory;
	PizzaStore store{factory};
	auto cheese_pizza = factory.createPizza("cheese");
	cheese_pizza->prepare();
	cheese_pizza->bake();
	cheese_pizza->cut();
	cheese_pizza->box();

	return 0;
}

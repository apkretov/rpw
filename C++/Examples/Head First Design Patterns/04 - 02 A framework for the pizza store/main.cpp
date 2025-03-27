#include "../../stdafx.h"
#include "NYPizzaStore.h"

int main(int argc, char *argv[]) {
	print_file_line();

	NYPizzaStore ny_store;
	PizzaPtr cheese_pizza = ny_store.createPizza("cheese");
	cheese_pizza->prepare();
	cheese_pizza->bake();
	cheese_pizza->cut();
	cheese_pizza->box();

	return 0;
}

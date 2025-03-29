#include "../../stdafx.h"
#include "PizzaStoreChicago.h"
#include "PizzaStoreNY.h"
using namespace std;

int main() {
	print_file_line();

#pragma region MINE
	PizzaStorePtr nyStore = make_unique<NYPizzaStore>();
	PizzaPtr pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << "\n\n";
	pizza = nyStore->orderPizza("clam");
	cout << "Ethan ordered a " << pizza->getName() << "\n\n";

	PizzaStorePtr chicagoStore = make_unique<ChicagoPizzaStore>();
	pizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " << pizza->getName() << "\n\n";
	pizza = chicagoStore->orderPizza("clam");
	cout << "Joel ordered a " << pizza->getName() << '\n';
#pragma endregion //MINE  

	return 0;
}

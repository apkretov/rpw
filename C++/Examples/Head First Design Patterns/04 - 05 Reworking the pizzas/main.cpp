#include "../../stdafx.h"
#include "PizzaStoreNY.h"
using namespace std;

int main() {
	print_file_line();

#pragma region MINE
	PizzaStorePtr nyStore = make_unique<NYPizzaStore>();
	PizzaPtr pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << '\n';
#pragma endregion //MINE  

	return 0;
}

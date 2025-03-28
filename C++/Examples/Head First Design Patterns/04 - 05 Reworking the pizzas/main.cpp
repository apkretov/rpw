#include "../../stdafx.h"
#include "PizzaStoreNY.h"
using namespace std;

int main() {
	print_file_line();

#ifdef MINE
	PizzaStorePtr nyStore = make_unique<NYPizzaStore>();
	PizzaPtr pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << '\n';
#endif //MINE

	return 0;
}

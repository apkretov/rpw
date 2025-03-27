#include <memory>
#include "../../stdafx.h"
#include "PizzaStyleChicagoCheese.h"
#include "PizzaStyleNYCheese.h"
#include "PizzaStyleOthers.h"
#include "PizzaStoreCalifornia.h"
#include "PizzaStoreChicago.h"
#include "PizzaStoreNY.h"
using namespace std;

#pragma region Youve waited long enough, time for some pizzas! //You've waited long enough, time for some pizzas!
/* Java
public class PizzaTestDrive {
	public static void main(String[] args) {
		PizzaStore nyStore = new NYPizzaStore(); // First we create two different stores.
		PizzaStore chicagoStore = new ChicagoPizzaStore();
		Pizza pizza = nyStore.orderPizza("cheese"); // Then use one one store to make Ethan's order.
		System.out.println("Ethan ordered a " + pizza.getName() + "\n");
		pizza = chicagoStore.orderPizza("cheese"); // And the other for Joel's.
		System.out.println("Joel ordered a " + pizza.getName() + "\n");
	}
}
*/
int main(int argc, char *argv[]) {
	print_file_line();

	PizzaStorePtr nyStore = make_unique<NYPizzaStore>(); // First we create two different stores.
	PizzaStorePtr chicagoStore = make_unique<ChicagoPizzaStore>();

	PizzaPtr pizza = nyStore->orderPizza("cheese"); // Then use one store to make Ethan's order.
	cout << "Ethan ordered a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->orderPizza("cheese"); // And the other for Joel's.
	cout << "Joel ordered a " << pizza->getName() << "\n\n";

	return 0;
}
#pragma endregion //Youve waited long enough, time for some pizzas!

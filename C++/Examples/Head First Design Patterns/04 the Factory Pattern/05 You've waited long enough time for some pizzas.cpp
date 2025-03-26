#if 1

#define YOU_VE_WAITED_LONG_ENOUGH_TIME_FOR_SOME_PIZZAS // For 03 Sharpen your pencil.h

#include <memory>
#include "../../stdafx.h"
#include "04 We're just missing one thing PIZZA.h"
#include "03 Sharpen your pencil.h"
using namespace std;

#pragma region You’ve waited long enough, time for some pizzas!
/* Java
public class PizzaTestDrive {
	public static void main(String[] args) {
		PizzaStore nyStore = new NYPizzaStore(); // First we create two different stores.
		PizzaStore chicagoStore = new ChicagoPizzaStore();
		Pizza pizza = nyStore.orderPizza("cheese"); // Then use one one store to make Ethan’s order.
		System.out.println("Ethan ordered a " + pizza.getName() + "\n");
		pizza = chicagoStore.orderPizza("cheese"); // And the other for Joel’s.
		System.out.println("Joel ordered a " + pizza.getName() + "\n");
	}
}
*/
int main(int argc, char *argv[]) {
	print_file_line();

	unique_ptr<PizzaStore> nyStore = make_unique<NYPizzaStore>(); // First we create two different stores.
	unique_ptr<PizzaStore> chicagoStore = make_unique<ChicagoPizzaStore>();

	PizzaPtr pizza = nyStore->orderPizza("cheese"); // Then use one store to make Ethan's order.
	cout << "Ethan ordered a " << pizza->getName() << "\n" << endl;

	pizza = chicagoStore->orderPizza("cheese"); // And the other for Joel's.
	cout << "Joel ordered a " << pizza->getName() << "\n" << endl;

	return 0;
}
#pragma endregion //You’ve waited long enough, time for some pizzas!
#endif //1
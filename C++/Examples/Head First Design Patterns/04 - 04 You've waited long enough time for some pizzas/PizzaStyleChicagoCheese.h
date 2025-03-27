#pragma once

#include "Pizza.h"

#pragma region Now we just need some concrete subclasses...
/* Java
public class ChicagoStyleCheesePizza extends Pizza {
	public ChicagoStyleCheesePizza() { // The Chicago Pizza uses plum tomatoes as a sauce along with extra thick crust.
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";
		toppings.add("Shredded Mozzarella Cheese"); // The Chicago style deep dish pizza has lots of mozzarella cheese!
	}

	void cut() { System.out.println("Cutting the pizza into square slices"); } // The Chicago style pizza also overrides the cut() method so that the pieces are cut into squares.
}
*/
class ChicagoStyleCheesePizza final : public Pizza {
public:
	ChicagoStyleCheesePizza() { // The Chicago Pizza uses plum tomatoes as a sauce along with extra thick crust.
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";
		toppings.push_back("Shredded Mozzarella Cheese"); // The Chicago style deep dish pizza has lots of mozzarella cheese!
	}

	void cut() override { cout << "Cutting the pizza into square slices\n"; } // The Chicago style pizza also overrides the cut() method so that the pieces are cut into squares.
};
#pragma endregion //Now we just need some concrete subclasses...


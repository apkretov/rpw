#pragma once

#include "Pizza.h"

#pragma region Now we just need some concrete subclasses...
/* Java
public class NYStyleCheesePizza extends Pizza {
	public NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza"; // The NY Pizza has its own marinara style sauce and thin crust.
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		toppings.add("Grated Reggiano Cheese"); // And one topping, reggiano cheese!
	}
}
*/
class NYStyleCheesePizza final : public Pizza {
public:
	NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza"; // The NY Pizza has its own marinara style sauce and thin crust.
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		toppings.push_back("Grated Reggiano Cheese"); // And one topping, reggiano cheese!
	}
};
#pragma endregion //Now we just need some concrete subclasses...

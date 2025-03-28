#pragma once

#include "Ingredients.h"

#pragma region Building the ingredient factories
/* Java
public interface PizzaIngredientFactory{
	public Dough createDough(); // For each ingredient we define a create method in our interface.
	public Sauce createSauce();
	public Cheese createCheese();
	public Veggies[] createVeggies();
	public Pepperoni createPepperoni();
	public Clams createClam();
}
*/
class PizzaIngredientFactory {
public:
	virtual ~PizzaIngredientFactory() = default;
	virtual unique_ptr<Dough> createDough() = 0; // For each ingredient we define a create method in our interface.
	virtual unique_ptr<Sauce> createSauce() = 0;
	virtual unique_ptr<Cheese> createCheese() = 0;
	virtual vector<unique_ptr<Veggies>> createVeggies() = 0;
	virtual unique_ptr<Pepperoni> createPepperoni() = 0;
	virtual unique_ptr<Clams> createClam() = 0;
};
#pragma endregion //Building the ingredient factories

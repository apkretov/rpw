#pragma once

#include "PizzaIngredientFactory.h"

#pragma region Building the New York ingredient factory
/* Java
public class NYPizzaIngredientFactory implements PizzaIngredientFactory {
	public Dough createDough() { return new ThinCrustDough(); } // For each ingredient in the ingredient family, we create the New York version.
	public Sauce createSauce() { return new MarinaraSauce(); }
	public Cheese createCheese() { return new ReggianoCheese(); }

	public Veggies[] createVeggies() {
		Veggies veggies[] = {new Garlic(), new Onion(), new Mushroom(), new RedPepper()};
		return veggies;
	}

	public Pepperoni createPepperoni() { return new SlicedPepperoni(); }
	public Clams createClam() { return new FreshClams(); }
}
*/
class NYPizzaIngredientFactory final : public PizzaIngredientFactory {
public:
	unique_ptr<Dough> createDough() override { return make_unique<ThinCrustDough>(); } // For each ingredient in the ingredient family, we create the New York version.
	unique_ptr<Sauce> createSauce() override { return make_unique<MarinaraSauce>(); }
	unique_ptr<Cheese> createCheese() override { return make_unique<ReggianoCheese>(); }
	VeggiesVec createVeggies() override { return {make_unique<Garlic>(), make_unique<Onion>(), make_unique<Mushroom>(), make_unique<RedPepper>()}; }
	unique_ptr<Pepperoni> createPepperoni() override { return make_unique<SlicedPepperoni>(); }
	unique_ptr<Clams> createClam() override { return make_unique<FreshClams>(); }
};
#pragma endregion //Building the New York ingredient factory#pragma once

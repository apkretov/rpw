#pragma once

#include "PizzaIngredientFactory.h"

#pragma region Sharpen your pencil
class ChicagoPizzaIngredientFactory final : public PizzaIngredientFactory {
public:
	unique_ptr<Dough> createDough() override { return make_unique<ThickCrustDough>(); } // For each ingredient in the ingredient family, we create the Chicago version.
	unique_ptr<Sauce> createSauce() override { return make_unique<PlumTomatoSauce>(); }
	unique_ptr<Cheese> createCheese() override { return make_unique<MozzarellaCheese>(); }

	VeggiesVec createVeggies() override {
		VeggiesVec veggies;
		veggies.push_back(make_unique<BlackOlives>());
		veggies.push_back(make_unique<Spinach>());
		veggies.push_back(make_unique<EggPlant>());
		return veggies;
	}

	unique_ptr<Pepperoni> createPepperoni() override { return make_unique<SlicedPepperoni>(); }
	unique_ptr<Clams> createClam() override { return make_unique<FrozenClams>(); }
};
#pragma endregion //Sharpen your pencil

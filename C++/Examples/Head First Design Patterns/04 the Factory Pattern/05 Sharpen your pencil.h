#pragma once

#include "04 Building the ingredient factories.h"

class ThickCrustDough : public Dough {}; // The Chicago ingredients.
class PlumTomatoSauce : public Sauce {};
class MozzarellaCheese : public Cheese {};
class SlicedPepperoni : public Pepperoni {};
class FrozenClams : public Clams {};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
	unique_ptr<Dough> createDough() override { return make_unique<ThickCrustDough>(); }
	unique_ptr<Sauce> createSauce() override { return make_unique<PlumTomatoSauce>(); }
	unique_ptr<Cheese> createCheese() override { return make_unique<MozzarellaCheese>(); }

	VeggiesVec createVeggies() override {
		VeggiesVec veggies;
		veggies.push_back(make_unique<Garlic>());
		veggies.push_back(make_unique<Onion>());
		veggies.push_back(make_unique<Mushroom>());
		veggies.push_back(make_unique<RedPepper>());
		return veggies;
	}

	unique_ptr<Pepperoni> createPepperoni() override { return make_unique<SlicedPepperoni>(); }
	unique_ptr<Clams> createClam() override { return make_unique<FrozenClams>(); }
};

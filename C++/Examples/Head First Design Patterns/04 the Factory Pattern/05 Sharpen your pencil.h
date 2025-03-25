#pragma once

#include "04 Building the ingredient factories.h"

class ThickCrustDough final : public Dough {}; // The Chicago ingredients.
class PlumTomatoSauce final : public Sauce {};
class MozzarellaCheese final : public Cheese {};
class SlicedPepperoni final : public Pepperoni {};
class FrozenClams final : public Clams {};

class ChicagoPizzaIngredientFactory final : public PizzaIngredientFactory {
public:
	unique_ptr<Dough> createDough() override { return make_unique<ThickCrustDough>(); }
	unique_ptr<Sauce> createSauce() override { return make_unique<PlumTomatoSauce>(); }
	unique_ptr<Cheese> createCheese() override { return make_unique<MozzarellaCheese>(); }
	VeggiesVec createVeggies() override { return {make_unique<Garlic>(), make_unique<Onion>(), make_unique<Mushroom>(), make_unique<RedPepper>()}; }
	unique_ptr<Pepperoni> createPepperoni() override { return make_unique<SlicedPepperoni>(); }
	unique_ptr<Clams> createClam() override { return make_unique<FrozenClams>(); }
};

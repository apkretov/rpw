#pragma once

#include <memory>
#include <vector>
using std::vector;
using std::make_unique;
using std::unique_ptr;

#pragma region MINE
class Veggies {};
class Garlic final : public Veggies {};
class Onion final : public Veggies {};
class Mushroom final : public Veggies {};
class RedPepper final : public Veggies {};
using VeggiesVec = vector<unique_ptr<Veggies>>;

class Dough {};
class Sauce {};
class Cheese {};
class Pepperoni {};
class Clams {};

class ThinCrustDough final : public Dough {}; // The NY ingredients.
class MarinaraSauce final : public Sauce {};
class ReggianoCheese final : public Cheese {};
class SlicedPepperoni final : public Pepperoni {};
class FreshClams final : public Clams {};
#pragma endregion //MINE

#pragma region Building the ingredient factories
class PizzaIngredientFactory {
public:
	virtual ~PizzaIngredientFactory() = default;
	virtual unique_ptr<Dough> createDough() = 0;
	virtual unique_ptr<Sauce> createSauce() = 0;
	virtual unique_ptr<Cheese> createCheese() = 0;
	virtual vector<unique_ptr<Veggies>> createVeggies() = 0;
	virtual unique_ptr<Pepperoni> createPepperoni() = 0;
	virtual unique_ptr<Clams> createClam() = 0;
};
#pragma endregion //Building the ingredient factories

#pragma region Building the New York ingredient factory
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

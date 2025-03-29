#pragma once

#include <memory>
#include <vector>
using namespace std;

#pragma region MINE
class Veggies {};
class Garlic final : public Veggies {};
class Onion final : public Veggies {};
class Mushroom final : public Veggies {};
class RedPepper final : public Veggies {};
class Spinach final : public Veggies {};
class BlackOlives final : public Veggies {};
class EggPlant final : public Veggies {};
using VeggiesVec = vector<unique_ptr<Veggies>>;

class Dough {};
class Sauce {};
class Cheese {};
class Pepperoni {};
class Clams {};

class ThinCrustDough final : public Dough {}; // The NY ingredients.
class MarinaraSauce final : public Sauce {};
class ReggianoCheese final : public Cheese {};
class SlicedPepperoni final : public Pepperoni {}; // Chicago's too.
class FreshClams final : public Clams {};

class ThickCrustDough final : public Dough {}; // The Chicago ingredients.
class PlumTomatoSauce final : public Sauce {};
class MozzarellaCheese final : public Cheese {};
class FrozenClams final : public Clams {};
#pragma endregion //MINE

#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::unique_ptr;

#pragma region MINE
class Pizza {
public:
	virtual ~Pizza() = default;
	void prepare() { cout << "Preparing " << typeid(*this).name() << '\n'; }
	void bake() { cout << "Baking " << typeid(*this).name() << '\n'; }
	void cut() { cout << "Cutting " << typeid(*this).name() << '\n'; }
	void box() { cout << "Boxing " << typeid(*this).name() << '\n'; }
};

using PizzaPtr = unique_ptr<Pizza>;

class CheesePizza : public Pizza {};
class PepperoniPizza : public Pizza {};
class ClamPizza : public Pizza {};
class VeggiePizza : public Pizza {};
#pragma endregion //MINE
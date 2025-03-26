#pragma once

#include <iostream>
#include <memory>
using namespace std;

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

class NYStyleCheesePizza final : public Pizza {};
class NYStylePepperoniPizza final : public Pizza {};
class NYStyleClamPizza final : public Pizza {};
class NYStyleVeggiePizza final : public Pizza {};
#pragma endregion //MINE

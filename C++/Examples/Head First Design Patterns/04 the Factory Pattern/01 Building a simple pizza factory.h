#pragma once

#include <iostream>
using std::cout;

#pragma region MINE
class Pizza {
public:
	virtual ~Pizza() = default;
	void prepare() { cout << "Preparing " << typeid(*this).name() << '\n'; }
	void bake() { cout << "Baking " << typeid(*this).name() << '\n'; }
	void cut() { cout << "Cutting " << typeid(*this).name() << '\n'; }
	void box() { cout << "Boxing " << typeid(*this).name() << '\n'; }
};
#pragma endregion //MINE
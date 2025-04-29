#pragma once

#include <iostream>
#include "Honkable.h"

#pragma region Sharpen your pencil
class Goose : public Honkable {
public:
	void honk() const override { std::cout << "Honk\n"; }
};
#pragma endregion //Sharpen your pencil
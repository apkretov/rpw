#pragma once

#include <iostream>
#include "GooseAbstract.h"

#pragma region Sharpen your pencil
class Goose : public AbstractGoose {
public:
	void honk() const { std::cout << "Honk\n"; }
};
#pragma endregion //Sharpen your pencil
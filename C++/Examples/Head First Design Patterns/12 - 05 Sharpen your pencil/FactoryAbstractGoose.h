#pragma once

#include "Quackable.h"

#pragma region Sharpen your pencil
class AbstractGooseFactory {
public:
	virtual ~AbstractGooseFactory() = default;
	virtual QuackablePtr createGoose() = 0;
};
#pragma endregion //Sharpen your pencil
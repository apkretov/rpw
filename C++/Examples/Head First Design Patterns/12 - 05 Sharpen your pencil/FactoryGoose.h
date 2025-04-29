#pragma once

#include "FactoryAbstractGoose.h"
#include "Goose.h"
#include "GooseAdapter.h"

#pragma region Sharpen your pencil
class GooseFactory : public AbstractGooseFactory {
public:
	QuackablePtr createGoose() override { return std::make_unique<GooseAdapter>(Goose{}); }
};
#pragma endregion //Sharpen your pencil

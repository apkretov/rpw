#pragma once

#include "FactoryAbstractGoose.h"
#include "Goose.h"

#pragma region Sharpen your pencil
class GooseFactory : public AbstractGooseFactory {
public:
	//HonkablePtr createGoose() override { return std::make_unique<Goose>(); }
};
#pragma endregion //Sharpen your pencil
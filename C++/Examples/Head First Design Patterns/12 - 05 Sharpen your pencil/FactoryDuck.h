#pragma once

#include "FactoryAbstractDuck.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "GooseAdapter.h"

#pragma region Sharpen your pencil
class DuckFactory : public AbstractDuckFactory {
public:
	QuackablePtr createMallardDuck() override { return std::make_unique<MallardDuck>(); }
	QuackablePtr createRedheadDuck() override { return std::make_unique<RedheadDuck>(); }
	QuackablePtr createDuckCall()	 override { return std::make_unique<DuckCall>(); }
	QuackablePtr createRubberDuck()	 override { return std::make_unique<RubberDuck>(); }
	QuackablePtr createGooseDuck()	 override { return std::make_unique<GooseAdapter>(Goose{}); }
};
#pragma endregion //Sharpen your pencil
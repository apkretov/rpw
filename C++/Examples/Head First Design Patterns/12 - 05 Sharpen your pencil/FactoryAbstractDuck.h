#pragma once

#include "Quackable.h"

#pragma region Sharpen your pencil
class AbstractDuckFactory {
public:
	virtual ~AbstractDuckFactory() = default;
	virtual QuackablePtr createMallardDuck() = 0;
	virtual QuackablePtr createRedheadDuck() = 0;
	virtual QuackablePtr createDuckCall() = 0;
	virtual QuackablePtr createRubberDuck() = 0;
	virtual QuackablePtr createGooseDuck() = 0; //TEST!
};
#pragma endregion //Sharpen your pencil
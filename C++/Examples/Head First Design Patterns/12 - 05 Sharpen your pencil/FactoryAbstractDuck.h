#pragma once

#include "Quackable.h"

#pragma region Sharpen your pencil
class AbstractDuckFactory {
public:
	virtual ~AbstractDuckFactory() = default;
	virtual PtrQuackable createMallardDuck() = 0;
	virtual PtrQuackable createRedheadDuck() = 0;
	virtual PtrQuackable createDuckCall() = 0;
	virtual PtrQuackable createRubberDuck() = 0;
	virtual PtrQuackable createGooseDuck() = 0; //TEST!
};
#pragma endregion //Sharpen your pencil
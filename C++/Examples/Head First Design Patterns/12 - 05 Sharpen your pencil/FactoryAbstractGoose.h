#pragma once

#pragma region Sharpen your pencil
class AbstractGooseFactory {
public:
	virtual ~AbstractGooseFactory() = default;
	virtual QuackablePtr createMallardDuck() = 0;
	virtual QuackablePtr createRedheadDuck() = 0;
	virtual QuackablePtr createDuckCall() = 0;
	virtual QuackablePtr createRubberDuck() = 0;
};
#pragma endregion //Sharpen your pencil
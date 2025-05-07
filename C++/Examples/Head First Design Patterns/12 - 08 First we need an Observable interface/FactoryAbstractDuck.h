#pragma once

#include "Quackable.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/factory
package headfirst.designpatterns.combining.factory;

public abstract class AbstractDuckFactory {
 
	public abstract Quackable createMallardDuck();
	public abstract Quackable createRedheadDuck();
	public abstract Quackable createDuckCall();
	public abstract Quackable createRubberDuck();
}
*/
#pragma region We need a factory to produce ducks
class AbstractDuckFactory {
public:
	virtual ~AbstractDuckFactory() = default;
	virtual PtrQuackable createMallardDuck() = 0;
	virtual PtrQuackable createRedheadDuck() = 0;
	virtual PtrQuackable createDuckCall() = 0;
	virtual PtrQuackable createRubberDuck() = 0;
};
#pragma endregion //We need a factory to produce ducks
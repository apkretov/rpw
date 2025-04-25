#pragma once

#include <memory>
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
	virtual std::unique_ptr<Quackable> createMallardDuck() = 0;
	virtual std::unique_ptr<Quackable> createRedheadDuck() = 0;
	virtual std::unique_ptr<Quackable> createDuckCall() = 0;
	virtual std::unique_ptr<Quackable> createRubberDuck() = 0;
};
#pragma endregion //We need a factory to produce ducks
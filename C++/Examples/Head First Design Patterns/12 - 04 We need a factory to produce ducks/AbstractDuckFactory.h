#pragma once

#pragma region We need a factory to produce ducks
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/factory
package headfirst.designpatterns.combining.factory;

public abstract class AbstractDuckFactory {
 
	public abstract Quackable createMallardDuck();
	public abstract Quackable createRedheadDuck();
	public abstract Quackable createDuckCall();
	public abstract Quackable createRubberDuck();
}
*/
class Quackable;

class AbstractDuckFactory {
public:
	virtual Quackable* createMallardDuck() = 0;
	virtual Quackable* createRedheadDuck() = 0;
	virtual Quackable* createDuckCall() = 0;
	virtual Quackable* createRubberDuck() = 0;
	virtual ~AbstractDuckFactory() = default;
};
#pragma endregion //We need a factory to produce ducks
#pragma once

#include "AbstractDuckFactory.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DuckCall.h"
#include "RubberDuck.h"

#pragma region We need a factory to produce ducks
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/factory
package headfirst.designpatterns.combining.factory;

public class DuckFactory extends AbstractDuckFactory {
  
	public Quackable createMallardDuck() {
		return new MallardDuck();
	}
  
	public Quackable createRedheadDuck() {
		return new RedheadDuck();
	}
  
	public Quackable createDuckCall() {
		return new DuckCall();
	}
   
	public Quackable createRubberDuck() {
		return new RubberDuck();
	}
}
*/
class DuckFactory : public AbstractDuckFactory {
public:
	Quackable* createMallardDuck() override { return new MallardDuck(); }
	Quackable* createRedheadDuck() override { return new RedheadDuck(); }
	Quackable* createDuckCall() override { return new DuckCall(); }
	Quackable* createRubberDuck() override { return new RubberDuck(); }
};
#pragma endregion //We need a factory to produce ducks
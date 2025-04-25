#pragma once

#include "AbstractDuckFactory.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DuckCall.h"
#include "RubberDuck.h"

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
#pragma region We need a factory to produce ducks
class DuckFactory : public AbstractDuckFactory {
public:
	std::unique_ptr<Quackable> createMallardDuck() override { return std::make_unique<MallardDuck>(); }
	std::unique_ptr<Quackable> createRedheadDuck() override { return std::make_unique<RedheadDuck>(); }
	std::unique_ptr<Quackable> createDuckCall() override { return std::make_unique<DuckCall>(); }
	std::unique_ptr<Quackable> createRubberDuck() override { return std::make_unique<RubberDuck>(); }
};
#pragma endregion //We need a factory to produce ducks
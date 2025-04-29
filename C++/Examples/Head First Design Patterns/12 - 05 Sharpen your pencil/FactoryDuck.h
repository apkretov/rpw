#pragma once

#include "FactoryAbstractDuck.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "Goose.h"
#include "GooseAdapter.h"

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
	QuackablePtr createMallardDuck() override { return std::make_unique<MallardDuck>(); }
	QuackablePtr createRedheadDuck() override { return std::make_unique<RedheadDuck>(); }
	QuackablePtr createDuckCall()	 override { return std::make_unique<DuckCall>(); }
	QuackablePtr createRubberDuck()	 override { return std::make_unique<RubberDuck>(); }
	QuackablePtr createGooseDuck()	 override { return std::make_unique<GooseAdapter>(Goose{}); }
};
#pragma endregion //We need a factory to produce ducks
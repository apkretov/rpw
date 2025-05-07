#pragma once

#include "FactoryAbstractDuck.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"

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
	PtrQuackable createMallardDuck() override { return std::make_unique<MallardDuck>(); }
	PtrQuackable createRedheadDuck() override { return std::make_unique<RedheadDuck>(); }
	PtrQuackable createDuckCall()	 override { return std::make_unique<DuckCall>(); }
	PtrQuackable createRubberDuck()	 override { return std::make_unique<RubberDuck>(); }
};
#pragma endregion //We need a factory to produce ducks
#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class DuckSimulator {
	public static void main(String[] args) {
		DuckSimulator simulator = new DuckSimulator();
		simulator.simulate();
	}
  
	void simulate() {
		Quackable mallardDuck = new MallardDuck();
		Quackable redheadDuck = new RedheadDuck();
		Quackable duckCall = new DuckCall();
		Quackable rubberDuck = new RubberDuck();
 
		System.out.println("\nDuck Simulator");
 
		simulate(mallardDuck);
		simulate(redheadDuck);
		simulate(duckCall);
		simulate(rubberDuck);
	}
   
	void simulate(Quackable duck) {
		duck.quack();
	}
}
*/

#ifndef DUCK_SIMULATOR_H
#define DUCK_SIMULATOR_H

#include "Quackable.h"

class DuckSimulator {
public:
    void simulate();
    void simulate(Quackable* duck);
};

#endif // DUCK_SIMULATOR_H
#pragma endregion //Duck reunion
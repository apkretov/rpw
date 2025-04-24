#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DuckCall.h"
#include "RubberDuck.h"
#include "GooseAdapter.h"
#include <memory>

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

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
		Quackable gooseDuck = new GooseAdapter(new Goose());
 
		System.out.println("\nDuck Simulator: With Goose Adapter");
 
		simulate(mallardDuck);
		simulate(redheadDuck);
		simulate(duckCall);
		simulate(rubberDuck);
		simulate(gooseDuck);
	}
 
	void simulate(Quackable duck) {
		duck.quack();
	}
}
*/
class DuckSimulator {
public:
	void simulate(Quackable* duck) { duck->quack(); }

	void simulate() {
		std::unique_ptr<Quackable> mallardDuck = std::make_unique<MallardDuck>();
		std::unique_ptr<Quackable> redheadDuck = std::make_unique<RedheadDuck>();
		std::unique_ptr<Quackable> duckCall = std::make_unique<DuckCall>();
		std::unique_ptr<Quackable> rubberDuck = std::make_unique<RubberDuck>();
		std::unique_ptr<Quackable> gooseDuck = std::make_unique<GooseAdapter>(Goose());

		cout << "\nDuck Simulator: With Goose Adapter\n";

		simulate(mallardDuck.get());
		simulate(redheadDuck.get());
		simulate(duckCall.get());
		simulate(rubberDuck.get());
		simulate(gooseDuck.get());
	}
};

int main() {
	DuckSimulator simulator;
	simulator.simulate();
	return 0;
}
#pragma endregion //We need a goose adapter
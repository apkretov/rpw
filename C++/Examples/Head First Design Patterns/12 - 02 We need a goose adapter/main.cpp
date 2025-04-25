#include <memory>
#include "../../stdafx.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "GooseAdapter.h"

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
	void simulate(const Quackable &duck) { duck.quack(); }

	void simulate() {
		using QuackablePtr = std::unique_ptr<Quackable>;

		QuackablePtr mallardDuck = std::make_unique<MallardDuck>();
		QuackablePtr redheadDuck = std::make_unique<RedheadDuck>();
		QuackablePtr duckCall = std::make_unique<DuckCall>();
		QuackablePtr rubberDuck = std::make_unique<RubberDuck>();
		QuackablePtr gooseDuck = std::make_unique<GooseAdapter>(Goose());

		cout << "\nDuck Simulator: With Goose Adapter\n";

		simulate(*mallardDuck);
		simulate(*redheadDuck);
		simulate(*duckCall);
		simulate(*rubberDuck);
		simulate(*gooseDuck);
	}
};

int main() {
	print_file_line();

	DuckSimulator simulator;
	simulator.simulate();
	return 0;
}
#pragma endregion //We need a goose adapter
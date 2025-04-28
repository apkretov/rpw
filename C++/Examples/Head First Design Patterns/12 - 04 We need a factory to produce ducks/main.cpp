#include <memory>
#include "../../stdafx.h"
#include "vld.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "FactoryAbstractDuck.h"
#include "FactoryCountingDuck.h"
#include "GooseAdapter.h"
#include "QuackCounter.h"
using std::make_unique;

#pragma region Lets set up the simulator to use the factory //Let's set up the simulator to use the factory
/* Java 
public class DuckSimulator {
	public static void main(String[] args) {
		DuckSimulator simulator = new DuckSimulator();
		AbstractDuckFactory duckFactory = new CountingDuckFactory();
		simulator.simulate(duckFactory);
	}
	void simulate(AbstractDuckFactory duckFactory) {
		Quackable mallardDuck = duckFactory.createMallardDuck();
		Quackable redheadDuck = duckFactory.createRedheadDuck();
		Quackable duckCall = duckFactory.createDuckCall();
		Quackable rubberDuck = duckFactory.createRubberDuck();
		Quackable gooseDuck = new GooseAdapter(new Goose());
		System.out.println("\nDuck Simulator : With Abstract Factory");
		simulate(mallardDuck);
		simulate(redheadDuck);
		simulate(duckCall);
		simulate(rubberDuck);
		simulate(gooseDuck);
		System.out.println("The ducks quacked " + QuackCounter.getQuacks() + " times");
	}
	void simulate(Quackable duck) {
		duck.quack();
	}
}
*/

class DuckSimulator {
public:
	void simulate(Quackable &duck) { duck.quack(); }

	void simulate(AbstractDuckFactory &duckFactory) {
		auto mallardDuck = duckFactory.createMallardDuck();
		auto redheadDuck = duckFactory.createRedheadDuck();
		auto duckCall = duckFactory.createDuckCall();
		auto rubberDuck = duckFactory.createRubberDuck();
		auto gooseDuck = std::make_unique<GooseAdapter>(Goose{});

		cout << "\nDuck Simulator: With Abstract Factory\n";

		simulate(*mallardDuck);
		simulate(*redheadDuck);
		simulate(*duckCall);
		simulate(*rubberDuck);
		simulate(*gooseDuck);

		cout << "The ducks quacked " << QuackCounter::getQuacks() << " times\n";
	}
};

int main() {
	print_file_line();

	DuckSimulator simulator;
	CountingDuckFactory duckFactory;
	simulator.simulate(duckFactory);

	cout << '\n';
	return 0;
}
#pragma endregion //Lets set up the simulator to use the factory
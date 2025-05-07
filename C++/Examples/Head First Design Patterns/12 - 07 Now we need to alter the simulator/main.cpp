#include <memory>
#include "../../stdafx.h"
#include "FactoryCountingDuck.h"
#include "Flock.h"
#include "GooseAdapter.h"
using std::make_unique;

#pragma region Now we need to alter the simulator
/* Java
public class DuckSimulator {
	void simulate(AbstractDuckFactory duckFactory) {
		Quackable redheadDuck = duckFactory.createRedheadDuck(); // Create all the Quackables, just like before
		Quackable duckCall = duckFactory.createDuckCall();
		Quackable rubberDuck = duckFactory.createRubberDuck();
		Quackable gooseDuck = new GooseAdapter(new Goose());
		System.out.println("\nDuck Simulator: With Composite - Flocks");

		Flock flockOfDucks = new Flock(); // First we create a Flock, and load it up with Quackables
		flockOfDucks.add(redheadDuck);
		flockOfDucks.add(duckCall);
		flockOfDucks.add(rubberDuck);
		flockOfDucks.add(gooseDuck);

		Flock flockOfMallards = new Flock(); // Then we create a new Flock of Mallards

		Quackable mallardOne = duckFactory.createMallardDuck(); // Here we're creating a little family of mallards
		Quackable mallardTwo = duckFactory.createMallardDuck();
		Quackable mallardThree = duckFactory.createMallardDuck();
		Quackable mallardFour = duckFactory.createMallardDuck();

		flockOfMallards.add(mallardOne); // ...and adding them to the Flock of mallards
		flockOfMallards.add(mallardTwo);
		flockOfMallards.add(mallardThree);
		flockOfMallards.add(mallardFour);

		flockOfDucks.add(flockOfMallards); // Then we add the Flock of mallards to the main flock

		System.out.println("\nDuck Simulator: Whole Flock Simulation");
		simulate(flockOfDucks); // Let's test out the entire Flock!

		System.out.println("\nDuck Simulator: Mallard Flock Simulation");
		simulate(flockOfMallards); // Then let's just test out the mallard's Flock

		System.out.println("\nThe ducks quacked " + // Finally, let's give the Quackologist the data
				QuackCounter.getQuacks() +
				" times");
	}

	void simulate(Quackable duck) { // Nothing needs to change here, a Flock is a Quackable!
		duck.quack();
	}
}
*/
class DuckSimulator {
public:
	void simulate(Quackable &duck) { duck.quack(); } // Nothing needs to change here, a Flock is a Quackable!

	void simulate(AbstractDuckFactory &duckFactory) {
		auto redheadDuck = duckFactory.createRedheadDuck(); // Create all the Quackables, just like before
		auto duckCall = duckFactory.createDuckCall();
		auto rubberDuck = duckFactory.createRubberDuck();
		auto gooseDuck = make_unique<GooseAdapter>(Goose{});
		cout << "\nDuck Simulator: With Composite - Flocks\n";

		Flock flockOfDucks; // First we create a Flock, and load it up with Quackables
		flockOfDucks.add(std::move(redheadDuck));
		flockOfDucks.add(std::move(duckCall));
		flockOfDucks.add(std::move(rubberDuck));
		flockOfDucks.add(std::move(gooseDuck));

		Flock flockOfMallards; // Then we create a new Flock of Mallards

		auto mallardOne = duckFactory.createMallardDuck(); // Here we're creating a little family of mallards
		auto mallardTwo = duckFactory.createMallardDuck();
		auto mallardThree = duckFactory.createMallardDuck();
		auto mallardFour = duckFactory.createMallardDuck();

		flockOfMallards.add(std::move(mallardOne)); // ...and adding them to the Flock of mallards
		flockOfMallards.add(std::move(mallardTwo));
		flockOfMallards.add(std::move(mallardThree));
		flockOfMallards.add(std::move(mallardFour));

#ifndef TRAE // If we really need to simulate both flocks separately, create the mallard flock simulation before moving it :
		cout << "\nDuck Simulator: Mallard Flock Simulation\n";
		simulate(flockOfMallards); // Then let's just test out the mallard's Flock
#endif //TRAE

		cout << "\nDuck Simulator: Whole Flock Simulation\n";
		flockOfDucks.add(make_unique<Flock>(std::move(flockOfMallards))); // Then we add the Flock of mallards to the main flock
		simulate(flockOfDucks); // Let's test out the entire Flock!

#ifdef ORIG
		cout << "\nDuck Simulator: Mallard Flock Simulation\n";
		simulate(flockOfMallards); // Then let's just test out the mallard's Flock
#endif //ORIG

		cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times\n"; // Finally, let's give the Quackologist the data
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
#pragma endregion //Now we need to alter the simulator

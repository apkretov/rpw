#define OFF

#include <iostream>
#include <memory>
#include "../../stdafx.h"
#include "FactoryCountingDuck.h"
#include "Flock.h"
#include "GooseAdapter.h"
#include "Quackologist.h"
using std::cout;
using std::make_unique;

#pragma region Were ready to observe. Lets update the simulator and give it try //We're ready to observe. Let's update the simulator and give it try:
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

		System.out.println("\nDuck Simulator: With Observer");
		Quackologist quackologist = new Quackologist(); // All we do here is create a Quackologist and set him as an observer of the flock.
		flockOfDucks.registerObserver(quackologist);

		simulate(flockOfDucks); // This time we'll we just simulate the entire flock.

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
#ifdef OFF
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

		flockOfDucks.add(make_unique<Flock>(std::move(flockOfMallards))); // Then we add the Flock of mallards to the main flock
		
		cout << "\nDuck Simulator: With Observer\n";
		auto quackologist = std::make_shared<Quackologist>(); // All we do here is create a Quackologist and set him as an observer of the flock.
		flockOfDucks.registerObserver(quackologist);

		simulate(flockOfDucks); // This time we'll we just simulate the entire flock.

		cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times\n"; // Finally, let's give the Quackologist the data
#endif //OFF
	}
};

int main() {
	print_file_line();

#ifdef OFF
	DuckSimulator simulator;
	CountingDuckFactory duckFactory;
	simulator.simulate(duckFactory);
#endif //OFF

	cout << '\n';
	return 0;
}
#pragma endregion //Were ready to observe. Lets update the simulator and give it try

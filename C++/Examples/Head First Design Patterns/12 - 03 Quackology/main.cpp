#include <memory>
#include "../../stdafx.h"
#include "vld.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "GooseAdapter.h"
#include "QuackCounter.h"
using std::make_unique;
using QuackablePtr = std::unique_ptr<Quackable>;

#pragma region We need to update the simulator to create decorated ducks
/* Java 
public class DuckSimulator {
	public static void main(String[] args) {
		DuckSimulator simulator = new DuckSimulator();
		simulator.simulate();
	}
	void simulate() {
		Quackable mallardDuck = new QuackCounter(new MallardDuck());
		Quackable redheadDuck = new QuackCounter(new RedheadDuck());
		Quackable duckCall = new QuackCounter(new DuckCall());
		Quackable rubberDuck = new QuackCounter(new RubberDuck());
		Quackable gooseDuck = new GooseAdapter(new Goose());
		System.out.println("\nDuck Simulator : With Decorator”);
		simulate(mallardDuck);
		simulate(redheadDuck);
		simulate(duckCall);
		simulate(rubberDuck);
		simulate(gooseDuck);
		System.out.println("The ducks quacked " +
			QuackCounter.getQuacks() + " times”);
	}
	void simulate(Quackable duck) {
		duck.quack();
	}
}
*/
class DuckSimulator {
public:
	void simulate(Quackable &duck) { duck.quack(); }

	void simulate() {
		auto mallardDuck =	make_unique<QuackCounter>(MallardDuck{}); //TEST!
		auto redheadDuck =	make_unique<QuackCounter>(RedheadDuck{});
		auto duckCall =		make_unique<QuackCounter>(DuckCall{});
		auto rubberDuck =	make_unique<QuackCounter>(RubberDuck{});
		auto gooseDuck =	make_unique<GooseAdapter>(Goose{});

		cout << "\nDuck Simulator: With Goose Adapter\n";

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
	simulator.simulate();

#ifdef MINE
	simulator.simulate();

	DuckSimulator simulator2;
	simulator2.simulate();
#endif //MINE
	cout << '\n';
	return 0;
}
#pragma endregion //We need to update the simulator to create decorated ducks
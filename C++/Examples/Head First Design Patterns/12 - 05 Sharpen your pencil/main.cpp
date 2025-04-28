#include <memory>
#include "../../stdafx.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "FactoryAbstractDuck.h"
#include "FactoryCountingDuck.h"
#include "GooseAdapter.h"
#include "QuackCounter.h"
using std::make_unique;

#pragma region Sharpen your pencil
class DuckSimulator {
public:
	void simulate(Quackable &duck) { duck.quack(); }

	void simulate(AbstractDuckFactory &duckFactory) {
		auto mallardDuck = duckFactory.createMallardDuck();
		auto redheadDuck = duckFactory.createRedheadDuck();
		auto duckCall	 = duckFactory.createDuckCall();
		auto rubberDuck	 = duckFactory.createRubberDuck();
		auto gooseDuck   = make_unique<GooseAdapter>(Goose{});

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
#pragma endregion //Sharpen your pencil
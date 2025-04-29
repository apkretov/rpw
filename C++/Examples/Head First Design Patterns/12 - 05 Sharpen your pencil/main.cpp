#include <memory>
#include "../../stdafx.h"
//#include "DuckMallard.h" //TO DO Remove this from the source project too.
//#include "DuckRedhead.h"
//#include "DuckCall.h"
//#include "DuckRubber.h"
//#include "FactoryAbstractDuck.h"
#include "FactoryCountingDuck.h"
//#include "GooseAdapter.h"
//#include "QuackCounter.h"
#include "FactoryGoose.h"
using std::make_unique;

#pragma region Sharpen your pencil
class DuckSimulator {
public:
	void simulate(Quackable &duck) { duck.quack(); }

	void simulate(AbstractDuckFactory &duckFactory, AbstractGooseFactory &gooseFactory) {
		auto mallardDuck = duckFactory.createMallardDuck();
		auto redheadDuck = duckFactory.createRedheadDuck();
		auto duckCall	 = duckFactory.createDuckCall();
		auto rubberDuck	 = duckFactory.createRubberDuck();
		auto gooseDuck	 = gooseFactory.createGoose();

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
	GooseFactory gooseFactory;
	simulator.simulate(duckFactory, gooseFactory);

	cout << '\n';
	return 0;
}
#pragma endregion //Sharpen your pencil
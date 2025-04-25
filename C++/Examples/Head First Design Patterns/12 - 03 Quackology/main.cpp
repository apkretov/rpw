//#include <array>
//#include <memory>
#include <vector>
#include "../../stdafx.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"
#include "GooseAdapter.h"
#include "QuackCounter.h"

#pragma region MINE
class DuckSimulator {
public:
	void simulate(QuackCounter &duck) { duck.quack(); }

	void simulate() {
		MallardDuck mallardDuck;
		GooseAdapter gooseDuck(Goose{});
		std::vector<QuackCounter> arr;
		arr.emplace_back(mallardDuck);
		arr.emplace_back(gooseDuck);

		for (auto &item : arr)
			simulate(item);
		std::cout << AS_KV(arr.at(0).getQuacks()) << '\n';
	}
};

int main() {
	print_file_line();

	DuckSimulator simulator;
	simulator.simulate();
	return 0;
}
#pragma endregion //MINE
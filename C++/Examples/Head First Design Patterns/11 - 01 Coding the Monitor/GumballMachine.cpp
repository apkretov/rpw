#include "GumballMachine.h"
#include "StateHasQuarter.h"
#include "StateNoQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include "StateWinner.h"
#include <memory>
using std::make_shared;

#pragma region Coding the Monitor
GumballMachine::GumballMachine(string_view location, int count) : location(location), count(count) {}

shared_ptr<GumballMachine> GumballMachine::create(string_view location, int count) {
	auto machine = shared_ptr<GumballMachine>(new GumballMachine(location, count));
	machine->initialize();
	return machine;
}

void GumballMachine::initialize() {
	soldOutState = make_shared<SoldOutState>(shared_from_this());
	noQuarterState = make_shared<NoQuarterState>(shared_from_this());
	hasQuarterState = make_shared<HasQuarterState>(shared_from_this());
	soldState = make_shared<SoldState>(shared_from_this());
	winnerState = make_shared<WinnerState>(shared_from_this());
	state = (count > 0) ? noQuarterState : soldOutState;
}
#pragma endregion //Coding the Monitor
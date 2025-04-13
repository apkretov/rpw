#include "GumballMachine.h"
#include "StateHasQuarter.h"
#include "StateNoQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include "StateWinner.h"
#include <memory>
using std::make_shared;

#pragma region We still need to finish the Gumball 1 in 10 game
shared_ptr<GumballMachine> GumballMachine::create(int numberGumballs) {
    auto machine = shared_ptr<GumballMachine>(new GumballMachine(numberGumballs));
    machine->initialize();
    return machine;
}

GumballMachine::GumballMachine(int numberGumballs) : count(numberGumballs) {}

void GumballMachine::initialize() {
    soldOutState = make_shared<SoldOutState>(shared_from_this());
    noQuarterState = make_shared<NoQuarterState>(shared_from_this());
    hasQuarterState = make_shared<HasQuarterState>(shared_from_this());
    soldState = make_shared<SoldState>(shared_from_this());
    winnerState = make_shared<WinnerState>(shared_from_this());
    state = (count > 0) ? noQuarterState : soldOutState;
}
#pragma endregion //We still need to finish the Gumball 1 in 10 game
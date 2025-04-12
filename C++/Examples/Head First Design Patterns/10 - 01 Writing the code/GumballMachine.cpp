#include "GumballMachine.h"
#include "StateHasQuarter.h"
#include "StateNoQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include <memory>
using std::make_shared;

GumballMachine::GumballMachine(int numberGumballs) : count(numberGumballs) { // We need to construct the object first before using shared_from_this()
	soldOutState = make_shared<SoldOutState>(shared_from_this());
	noQuarterState = make_shared<NoQuarterState>(shared_from_this());
	hasQuarterState = make_shared<HasQuarterState>(shared_from_this());
    soldState = make_shared<SoldState>(shared_from_this());
    state = (numberGumballs > 0) ? noQuarterState : soldOutState;
}

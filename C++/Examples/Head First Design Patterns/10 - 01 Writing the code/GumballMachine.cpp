#include "GumballMachine.h"
#include "StateHasQuarter.h"
#ifdef OFF
#include "StateNoQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include <memory>
#endif //OFF
using std::make_shared;

GumballMachine::GumballMachine(int numberGumballs) { // We need to construct the object first before using shared_from_this()
#ifdef OFF
	soldOutState = make_shared<SoldOutState>(shared_from_this());
	noQuarterState = make_shared<NoQuarterState>(shared_from_this());
#endif //OFF
	hasQuarterState = make_shared<HasQuarterState>(shared_from_this());
#ifdef OFF
    soldState = make_shared<SoldState>(shared_from_this());
#endif //OFF
    count = numberGumballs;
#ifdef OFF
    state = (numberGumballs > 0) ? noQuarterState : soldOutState;
#endif //OFF
}

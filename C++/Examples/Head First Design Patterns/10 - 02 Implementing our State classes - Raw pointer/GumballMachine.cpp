#include "GumballMachine.h"
#include "StateNoQuarter.h"
#include "StateHasQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"

GumballMachine::GumballMachine(int numberGumballs) {
    soldOutState = std::make_unique<SoldOutState>(this);
    noQuarterState = std::make_unique<NoQuarterState>(this);
    hasQuarterState = std::make_unique<HasQuarterState>(this);
    soldState = std::make_unique<SoldState>(this);
    count = numberGumballs;
    if (numberGumballs > 0) {
        state = noQuarterState.get();
    }
    else {
        state = soldOutState.get();
    }
}

#include "GumballMachine.h"
#include "StateNoQuarter.h"
#include "StateHasQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"

GumballMachine::GumballMachine(int numberGumballs) {
    soldOutState = new SoldOutState(this);
    noQuarterState = new NoQuarterState(this);
    hasQuarterState = new HasQuarterState(this);
    soldState = new SoldState(this);
    count = numberGumballs;
    if (numberGumballs > 0) state = noQuarterState;
    else state = soldOutState;
}

GumballMachine::~GumballMachine() {
    delete soldOutState;
    delete noQuarterState;
    delete hasQuarterState;
    delete soldState;
}
#include "GumballMachine.h"
#include "StateNoQuarter.h"
#include "StateHasQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include <memory>
using std::make_shared;

GumballMachine::GumballMachine(int numberGumballs) 
    : soldOutState(make_shared<SoldOutState>(this))
    , noQuarterState(make_shared<NoQuarterState>(this))
    , hasQuarterState(make_shared<HasQuarterState>(this))
    , soldState(make_shared<SoldState>(this))
    , count(numberGumballs)
    , state(numberGumballs > 0 ? noQuarterState : soldOutState)
{}

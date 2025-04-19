#include "GumballMachine.h"
#include "StateNoQuarter.h"
#include "StateHasQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
using std::make_unique;

GumballMachine::GumballMachine(int count) {
    soldOutState = make_unique<SoldOutState>(this);
    noQuarterState = make_unique<NoQuarterState>(this);
    hasQuarterState = make_unique<HasQuarterState>(this);
    soldState = make_unique<SoldState>(this);
    count = count;
    if (count > 0)
        state = noQuarterState.get();
    else 
        state = soldOutState.get();
}

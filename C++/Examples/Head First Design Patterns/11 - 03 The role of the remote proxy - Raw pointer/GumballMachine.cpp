#include "GumballMachine.h"
#include "StateHasQuarter.h"
#include "StateNoQuarter.h"
#include "StateSold.h"
#include "StateSoldOut.h"
#include "StateWinner.h"
#include <memory>

#pragma region Trae
GumballMachine::GumballMachine(std::string_view location, int count) : location(location), count(count) {
    soldOutState = std::make_unique<SoldOutState>(this);
    noQuarterState = std::make_unique<NoQuarterState>(this);
    hasQuarterState = std::make_unique<HasQuarterState>(this);
    soldState = std::make_unique<SoldState>(this);
    winnerState = std::make_unique<WinnerState>(this);
    state = (count > 0) ? noQuarterState.get() : soldOutState.get();
}
#pragma endregion //Trae
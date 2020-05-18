#include "StdAfx.h"
#include <iostream>
using std::cout;
using std::cin;
#include "ticks.h"
#include "constants.h"

ticks::ticks(double p): Price(p) {} //initialise with an initial Price

void ticks::EnterPrice() { //enter a Price
	cout << "\nEnter a Price: ";
	cin >> Price;
}

void ticks::Generate(account& Account, double& Bid, double& Ask, void(*start)()) { // Generate a tick
	EnterPrice(); //enter a Price
	while (Price != 0) { //open any number of trades until 0 entered
		Bid = Price;
		Ask = Price + Spread * Point;
		Account.Refresh(Bid, Ask); // Refresh the account on a tick
		(*start)(); //trigger the start function
		Account.Display(); //display all the orders, balance & equity
		EnterPrice(); //enter a Price
	}
}
#include "StdAfx.h"
#include "Order.h"
#include "constants.h"
#include <iomanip>
using std::setw; // enables program to set a field width
using std::setprecision;

unsigned int order::Count = 0; //initialise the static data member

ostream &operator<<(ostream& output, const order& Order) { // overloaded stream insertion operator; cannot be a member function if we would like to invoke it with cout << someOrder;
	const int PrecnGBP = 4; //GBP precision
	output << setw(6) << Order.Ticket << setw(6) << Order.GetTypeOrderStr() << setw(6) << setprecision(Precn2) << Order.Lots << setw(8) << fixed << setprecision(PrecnGBP) << Order.PriceOpen << setw(12) << Order.SL << setw(8) << Order.TP << setw(8) << Order.PriceLast << setw(12) << setprecision(Precn2) << Order.Profit << endl;
	return output; // enables cout << a << b << c;
}

order::order(int intTypeOrder, double dblLots, double dlbPriceOpen, double dblStoploss, double dblTakeprofit): //increment the orders' Count //the current Count is the order's Ticket
Ticket(++order::Count), TypeOrder(intTypeOrder), Lots(dblLots), PriceOpen(dlbPriceOpen), SL(dblStoploss), TP(dblTakeprofit), PriceLast(0), Profit(0), CloseTime(0) {}

inline void order::CompProfit(double PriceFrom, double PriceTo) { //compute the profit from one price to another
	const int Leverage = 10; //the leverage
	Profit = (PriceFrom - PriceTo) / Point * Lots * Leverage;
}

void order::ProfitBuy(double PriceLast) { //compute the Profit of a Buy order
	this->PriceLast = PriceLast;
	CompProfit(PriceLast, PriceOpen); //compute the profit
} 

void order::ProfitSell(double PriceLast) { //compute the Profit of a Sell order
	this->PriceLast = PriceLast;
	CompProfit(PriceOpen, PriceLast); //compute the profit
}

string order::GetTypeOrderStr() const { //string representation of an order's type
	switch (TypeOrder) {
	case OP_BUY:
		return "Buy";
	case OP_SELL:
		return "Sell";
	case OP_BUYLIMIT:
		return "Buy limit";
	case OP_SELLLIMIT:
		return "Sell limit";
	case OP_BUYSTOP:
		return "Buy stop";
	case OP_SELLSTOP:
		return "Sell stop";
	}
}

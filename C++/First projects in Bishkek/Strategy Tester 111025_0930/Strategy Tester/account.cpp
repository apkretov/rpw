#include "StdAfx.h"
#include "Account.h"
#include "constants.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
#include <iomanip>
using std::setw; // enables program to set a field width
using std::setprecision;
#include <math.h>
using std::floor;

account::account(double Balance): Balance(Balance), Equity(0) {}

void account::OrderAdd(const order& Order, double Bid, double Ask) { //Add a created order
	Orders.push_back(Order);
	size_t IdxOrders = Order.GetTicket() - 1;
	OrdersOpnPnd.push_back(IdxOrders);
	order* OrderPtr = &Orders.at(IdxOrders); //the pointer to the added order
	switch (Order.GetTypeOrder()) {
	case OP_BUY:
		OrderPtr->ProfitBuy(Bid); //compute the current order's profit
		break;
	case OP_SELL:
		OrderPtr->ProfitSell(Ask); //compute the current order's profit
	}
	Equity += OrderPtr->GetProfit();
}

inline void account::CloseBS(order& Order, void(order::*ProfitBS)(double), double PriceLast, const size_t& Idx) { // close the specified order by removing it from the open orders' array
	(Order.*ProfitBS)(PriceLast); //compute the current order's profit
	Order.SetCloseTime(); //set any value different from 0 & to be developed later if necessary
	Equity -= Order.GetProfit();
	Balance += Order.GetProfit();
	OrdersOpnPnd.erase(OrdersOpnPnd.begin() + Idx); //close the current order by deleting its index from an open orders' indexes array & reposition the calling function's loop's iterator (Idx) by decrementing it
}

void account::CloseOrd(const size_t& Ticket, double Bid, double Ask) { //close the order with the specified ticket
	size_t Idx = 0;
	while (Orders.at(OrdersOpnPnd.at(Idx)).GetTicket() != Ticket) Idx++; //find the market order's index in the OrdersOpnPnd array to be deleted
	order *Order = &Orders.at(Ticket - 1); //the pointer to the specified order
	switch (Order->GetTypeOrder()) {
	case OP_BUY:
		CloseBS(*Order, &order::ProfitBuy, Bid, Idx);
		break;
	case OP_SELL:
		CloseBS(*Order, &order::ProfitSell, Ask, Idx);
	}
}

void account::RefreshBS(double Price, bool(account::*TriggerSL)(double, double) const, bool(account::*TriggerTP)(double, double) const, void(order::*ProfitBS)(double), size_t& Idx) { // Refresh Buy/Sell orders on a tick
	order *Order = &Orders.at(OrdersOpnPnd.at(Idx)); //the pointer to a current order
	double SL = Order->GetSL(); //the current order's stop loss & take profit
	double TP = Order->GetTP();
	if ((this->*TriggerSL)(SL, Price)) //the stop loss triggered?
		CloseBS(*Order, ProfitBS, SL, Idx--); //close the current order by deleting its index from an open orders' indexes array & reposition the calling function's loop's iterator (Idx) by decrementing it
	else if ((this->*TriggerTP)(TP, Price)) //the take profit triggered?
		CloseBS(*Order, ProfitBS, TP, Idx--); //close the current order by deleting its index from an open orders' indexes array & reposition the calling function's loop's iterator (Idx) by decrementing it
	else { //Refresh the pfofit
		(*Order.*ProfitBS)(Price); //compute the current order's profit
		Equity += Order->GetProfit();
	}
}

void account::RefreshPending(double PriceOpen, bool(account::*TriggerPending)(double, double) const, void(order::*ProfitBS)(double), size_t& Idx) { // refresh pending orders on a tick
	order *Order = &Orders.at(OrdersOpnPnd.at(Idx)); //the pointer to a current order
	if ((this->*TriggerPending)(Order->GetPriceOpen(), PriceOpen)) (Order->*ProfitBS)(PriceOpen); //the opening trigger hit? //compute the current order's profit
}

void account::Refresh(double Bid, double Ask) { // Refresh the orders on a tick.
	size_t OrdersOpnPndSize = OrdersOpnPnd.size();
	Equity = 0; //set equity to 0 to recompute it again
	for (size_t i = 0; i < OrdersOpnPndSize; i++) { //refresh market & pending orders on a tick
		switch (Orders.at(OrdersOpnPnd.at(i)).GetTypeOrder()) {
		case OP_BUY:
			RefreshBS(Bid, &account::TriggerSLBuy, &account::TriggerTPBuy, &order::ProfitBuy, i); // Refresh Buy orders on a tick
			break;
		case OP_SELL:
			RefreshBS(Ask, &account::TriggerSLSell, &account::TriggerTPSell, &order::ProfitSell, i); // Refresh Sell orders on a tick
			break;
		case OP_BUYLIMIT:
			RefreshPending(Ask, &account::TriggerBuyLimit, &order::ProfitBuy, i); // refresh Buy Limit orders on a tick
			break;
		case OP_SELLLIMIT:
			RefreshPending(Bid, &account::TriggerSellLimit, &order::ProfitSell, i); // refresh Sell Limit orders on a tick
			break;
		case OP_BUYSTOP:
			RefreshPending(Ask, &account::TriggerBuyStop, &order::ProfitBuy, i); // refresh Buy Stop orders on a tick
			break;
		case OP_SELLSTOP:
			RefreshPending(Bid, &account::TriggerSellStop, &order::ProfitSell, i); // refresh Sell Stop orders on a tick
		}
		OrdersOpnPndSize = OrdersOpnPnd.size();
	}
}

void account::Display() const { //display all the orders, balance & equity
	cout << endl << "Ticket" << setw(6) << "Type" << setw(6) << "Size" << setw(12) << "Open price" << setw(4) << "SL" << setw(8) << "TP" << setw(16) << "Last price" << setw(9) << "Profit" << endl; // display the headers
	for (size_t i = 0; i < OrdersOpnPnd.size(); i++) cout << Orders.at(OrdersOpnPnd.at(i));
	cout << "Balance: " << setprecision(Precn2) << Balance << "   Equity: " << Equity << "   % equity: " << setprecision(2) << floor(Equity / Balance * 10000 + 0.5) / 100 << endl;
}

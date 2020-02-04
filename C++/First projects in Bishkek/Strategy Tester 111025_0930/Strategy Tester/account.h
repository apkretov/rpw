#ifndef ACCOUNT_H
#define ACCOUNT_H
#pragma once
#include "Order.h"
#include <vector>
using std::vector;

//#ifndef ACCOUNT_H
//#define ACCOUNT_H
class account {
private:
	vector<order> Orders; //all orders
	vector<size_t> OrdersOpnPnd; //market & pending orders' indexes
	order* SelectedOrd; //the current order
	double Balance, Equity;

	bool TriggerBuyLimit(double Price, double Ask) const {return Ask <= Price;}; //Buy Limit triggered?
	bool TriggerSellLimit(double Price, double Bid) const {return Bid >= Price;}; //Sell Limit triggered?
	bool TriggerBuyStop(double Price, double Ask) const {return Ask >= Price;}; //Buy Stop triggered?
	bool TriggerSellStop(double Price, double Bid) const {return Bid <= Price;}; //Sell Stop triggered?

	bool TriggerSLBuy(double SL, double Bid) const {return SL != 0 && TriggerSellStop(SL, Bid);}; //buy stop loss triggered?
	bool TriggerSLSell(double SL, double Ask) const {return SL != 0 && TriggerBuyStop(SL, Ask);}; //sell stop loss triggered?
	bool TriggerTPBuy(double TP, double Bid) const {return TP != 0 && TriggerSellLimit(TP, Bid);}; //buy take profit triggered?
	bool TriggerTPSell(double TP, double Ask) const {return TP != 0 && TriggerBuyLimit(TP, Ask);}; //sell take profit triggered?
	
	void CloseBS(order&, void(order::*)(double), double, const size_t&);
	void RefreshBS(double, bool(account::*)(double, double) const, bool(account::*)(double, double) const, void(order::*)(double), size_t&);
	void RefreshPending(double, bool(account::*)(double, double) const, void(order::*)(double), size_t&);
	void DisplayOrd(const vector<size_t>&) const;
	
public:
	explicit account(double);
	size_t GetCount() const {return OrdersOpnPnd.size();} //Returns open and pending orders Count
	void OrderAdd(const order&, double, double);
	void SelectOrdByPos(const unsigned int Idx) {SelectedOrd = &Orders.at(OrdersOpnPnd.at(Idx));}; //select an order by position 
	void SelectOrdByTkt(const unsigned int Ticket) {SelectedOrd = &Orders.at(Ticket - 1);}; //select an order by position 
	order* GetSelectedOrd() const {return SelectedOrd;}; //get the current order
	void CloseOrd(const size_t&, double, double);
	void Refresh(double, double);
	void Display() const;
};
#endif
#ifndef ORDER_H
#define ORDER_H
#pragma once
#include <string>
using std::string;
#include <iostream>
using std::ostream;
using std::fixed;
using std::endl;

class orderPM {
	friend ostream &operator<<(ostream&, const orderPM&);
protected: //private:
	static unsigned int Count;
	const unsigned int Ticket;
	int TypeOrder;
	const double Lots, PriceOpen;
	double SL, TP;
 	double PriceLast, Profit; //PM SUSPENDED
	int CloseTime; //the member name might need changing to correspond to MetaTrader's counterpart //PM
	void CompProfit(double, double); //PM
public:
	orderPM(int, double, double, double, double);
	unsigned int GetTicket() const {return Ticket;}; // get ticket
	int GetTypeOrder() const {return TypeOrder;}; // get order type
	virtual string GetTypeOrderStr() const; //PM
	double GetLots() const {return Lots;}; 
	double GetPriceOpen() const {return PriceOpen;}; 
	double GetSL() const {return SL;};
	double GetTP() const {return TP;};
	//double GetPriceLast() const {return PriceLast;}; //PM
	virtual double GetPriceLast() const = 0; //PM
	double GetProfit() const {return Profit;}; //PM
	int GetCloseTime() const {return CloseTime;}; //PM
	void SetCloseTime() {CloseTime = 1;}; //set any value different from 0 & to be developed later, if necessary //PM
	void ProfitBuy(double); //compute the Profit of a Buy order //PM
	void ProfitSell(double); //compute the Profit of a Sell order //PM
};
#endif

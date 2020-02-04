// Strategy Tester.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <fstream>
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <math.h>
using std::floor;
#include "symbol.h"
#include "Account.h"
#include "globals.h"
#include "ticks.h"
#include "constants.h"

//*************************************************************************************************
/*extern*/ double mdblBalance = 6000; //the initial balance
/*extern*/ int TP = 30;
/*extern*/ int SL = 30;
///*extern*/ double LotsAccelerator = 1; //The Volume Accelerating coefficient. - Given opposite positions allowed at a time this logic needs developing.
/*extern*/ extern bool GlobalsInitialise = true; //Initialising the global variables.
/*extern*/ extern bool GlobalsDelete = false; //Delete the global variables.

double mdblLots = 1 /*0.01*/;
string mstrLots = "MartingaleBB_Lots";
string mstrLastOrder = "MartingaleBB_LastOrder";
string mstrClosePositions = "MartingaleBB_ClosePositions";
int mintTrue = 1;
int mintFalse = -1;
int mintType; 
int mintShift = 1; //The indicator shift relative to the chart.
int mintBBPeriod = 24; //Bollinger bands' period.
int mintSlippage = 10;
//*************************************************************************************************

account Account(mdblBalance); // market and pending orders
globals Globals; //global variables kept in MetaTrader as GlobalVariables
double Bid = 0, Ask = 0;

inline int OrdersTotal() {return Account.GetCount();} //Returns market and pending orders Count.

bool OrderSelect(unsigned int index, int select, int pool = MODE_TRADES) { //Selects an order. The pool parameter has been ignored so far.
	switch (select) {
	case SELECT_BY_POS: //select by position from among open & pending orders
		Account.SelectOrdByPos(index);
		break;
	case SELECT_BY_TICKET: //select by ticket from among all available orders
		Account.SelectOrdByTkt(index);
		break;
	}
	return true;
}

inline string OrderSymbol() {return "";} //Returns the order symbol value for selected Order. Should be string OrderSymbol() but simplified to bool.

int OrderSend(string symbol, int cmd, double volume, double Price, int slippage, double stoploss, double takeprofit, string comment = NULL_, int magic = 0, int expiration = 0, int arrow_color = 0) { //The main function used to open a position or place a pending Order. Returns number of the ticket assigned to the order by the trade server.
	order Order(cmd, volume, Price, stoploss, takeprofit);
	Account.OrderAdd(Order, Bid, Ask);  //Add a created order
	return Order.GetTicket();
}

bool OrderModify(unsigned int ticket, double price, double stoploss, double takeprofit, int expiration, int arrow_color = CLR_NONE) {
//bool OrderModify(unsigned int ticket, double price, double stoploss, double takeprofit, int expiration, color arrow_color = CLR_NONE) {
	return true; //The function needs programming.
}

bool OrderClose(unsigned int ticket, double lots, double price, int slippage, color Color = CLR_NONE) { //Closes opened order. If the function succeeds, the return value is true. If the function fails, the return value is false. The parameters other than ticket are omitted for simplicity for the time being.
	Account.CloseOrd(ticket, Bid, Ask); //close the order with the specified ticket
	return true;
}
 
inline string Symbol() {return "";} //Returns a text string with the name of the current financial instrument.

inline int OrderTicket() {return Account.GetSelectedOrd()->GetTicket();} //Returns ticket number for the currently selected order.
 
inline int OrderType() {return Account.GetSelectedOrd()->GetTypeOrder();} //Returns the current order's type.

inline double OrderLots() {return Account.GetSelectedOrd()->GetLots();} //Returns amount of lots for the selected order.

inline double OrderOpenPrice() {return Account.GetSelectedOrd()->GetPriceOpen();} //Returns the current order's open price.

inline double OrderClosePrice() {return Account.GetSelectedOrd()->GetPriceLast();} //Returns the current order's close price.

inline double OrderProfit() {return Account.GetSelectedOrd()->GetProfit();}

inline unsigned int OrderCloseTime() {return Account.GetSelectedOrd()->GetCloseTime();} //Returns close time for the currently selected order. If order close time is not 0 then the order selected and has been closed and retrieved from the account history. Open and pending orders close time is equal to 0.

inline int OrderMagicNumber() {return MAGICMA;} //Returns an identifying (magic) number for the currently selected Order.

double MarketInfo(string symbol, int type) { //Returns various data about securities listed in the Market Watch window. 
	switch (type) {
	case MODE_SPREAD:
		return Spread;
	}
}

double GlobalVariableGet(const string& name) {
	if (name == mstrLots) 
		return Globals.LastLots;
	else if (name == mstrLastOrder)
		return Globals.LastOrder;
	else if (name == mstrClosePositions)
		return Globals.ClosePositions;
	//switch (name) {
	//case mstrLots:
	//	return Globals.LastLots;
	//case mstrLastOrder:
	//	return Globals.LastOrder;
	//case mstrClosePositions:
	//	return 0;
	//}
}

void GlobalVariableSet(const string& name, double value) { //Sets a new value of the global variable. If it does not exist, the system creates (to be done later) a new gloabl variable.
	if (name == mstrLots) 
		Globals.LastLots = value;
	else if (name == mstrLastOrder)
		Globals.LastOrder = value;
	else if (name == mstrClosePositions)
		Globals.ClosePositions = value;
}

inline void GlobalVariableDel(const string& name) {} //Deletes the global variable. The original version simplified: bool GlobalVariableDel(string name)

inline double MathRound(double value) { //Returns value rounded to the nearest integer of the specified numeric value.
	return floor(value + 0.5);
}

inline int Hour() {return 0;} //Returns the hour (0,1,2,..23) of the last known server time by the moment of the program start.

/*inline*/ double iBands(string symbol, int timeframe, int period, int deviation, int bands_shift, int applied_price, int mode, int shift) { // Calculates the Bollinger bands indicator and returns its value.
	double dblBBUpper = 1.7964, dblBBLower = 1.7925;
	switch (mode) {
		case MODE_UPPER:
			return dblBBUpper;
		case MODE_LOWER:
			return dblBBLower;
	}
}

inline double iMA(string symbol, int timeframe, int period, int ma_shift, int ma_method, int applied_price, int shift) {return 0;} //Calculates the Moving average indicator and returns its value.

inline double iClose(string symbol, int timeframe, int shift) {return 0;} //Returns Close value for the bar of indicated symbol with timeframe and shift.

//*************************************************************************************************
bool SelectPosition(int intType) { // Select a Buy/Sell (intType) position, if the expert has opened one.
	bool blnSelectPosition = false;
	for(int i = 0; i < OrdersTotal(); i ++) {
		if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
		if(OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
			if (OrderType() == intType) { //Specified type?
				blnSelectPosition = true; //The position selected.
				break;
			}
		}
	}
	return(blnSelectPosition);
}

//*************************************************************************************************
double Lots() { // Raise the number of lots, if the last trade has been unprofitable. - Given opposite positions allowed at a time this logic needs developing.
   double dblLots;
   //int intLastPt;
   //int intOrder = GlobalVariableGet(mstrLastOrder);
   //if (intOrder == mintFalse) {
      dblLots = mdblLots; //No previous orders. Start from the initial lots.
   //}else if (OrderSelect(intOrder, SELECT_BY_TICKET, MODE_HISTORY)) { //A previous order selected?
   //   if (OrderType() == OP_SELL) 
		 // intLastPt = DistancePts(OrderOpenPrice(), OrderClosePrice()); //The last order's profit.
   //   else 
		 // intLastPt = DistancePts(OrderClosePrice(), OrderOpenPrice());
   //   if (intLastPt > TP / 2) { //Compare the last profit with 1/2 TP instead of > 0 due to slippare & spread deviations.
   //      dblLots = mdblLots; //The last trade has been profitable. Reset the lots.
   //      GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
   //   }else if (intLastPt < 0) {
   //      dblLots = MathRound(GlobalVariableGet(mstrLots) * LotsAccelerator * 100) / 100; //Raise the lots after a loss. Round the lots.
   //      GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
   //   }else{
   //      dblLots = GlobalVariableGet(mstrLots); //Leave the lots unchanged.
   //   }
   //}
   return (dblLots);
}

//*************************************************************************************************
double BB(int intMode) { // The Bollinger bands.
	double BBDev = 3; //Bollinger bands' deviation.
	return(iBands(NULL_, PERIOD_M15, mintBBPeriod, BBDev, mintShift, PRICE_CLOSE, intMode, 0));
}

//*************************************************************************************************
void PlaceOrder(int intType, double dblPrice, double dblSL, double dblTP) { // Place a Buy/Sell Limit position.
	string strSetup = "Martingale BB";
	//OrderSend(Symbol(), intType, Lots(), dblPrice, mintSlippage, dblSL, dblTP, strSetup, MAGICMA, 0, Blue); //Remember the order number.
	OrderSend(Symbol(), intType, Lots(), dblPrice, mintSlippage, dblSL, dblTP, strSetup, MAGICMA, 0, CLR_NONE); //Remember the order number.
}

//*************************************************************************************************
void MoveOrder(double dblPrice, double dblSL, double dblTP) { // Move a pending order.
	//OrderModify(OrderTicket(), dblPrice, dblSL, dblTP, 0, Blue);
	OrderModify(OrderTicket(), dblPrice, dblSL, dblTP, 0, CLR_NONE);
}

//*************************************************************************************************
void OpenPosition() { // Open a position.
	string strSymbol = "GBPUSD";
	double dblBBUpper, dblBBLower;
	dblBBUpper = BB(MODE_UPPER); // The upper Bollinger bands.
	dblBBLower = BB(MODE_LOWER); // The lower Bollinger bands.
	if (Bid < dblBBUpper && Bid > dblBBLower) { //Inside BB?
		double dblSpread = MarketInfo(strSymbol, MODE_SPREAD) * Point;
		if (SelectPosition(OP_SELLLIMIT)) { //A Sell-limit set?
			if (OrderOpenPrice() != dblBBUpper) //Is the Sell-limit open price wrong? 
				MoveOrder(dblBBUpper, dblBBUpper + dblSpread + SL * Point, dblBBUpper - TP * Point); // Move the pending order.
		}else if (!SelectPosition(OP_SELL)) //No open Sell position?
			PlaceOrder(OP_SELLLIMIT, dblBBUpper, dblBBUpper + dblSpread + SL * Point, dblBBUpper - TP * Point); // Select a Sell position, if the expert has opened one. // Place a Sell-limit position.
		if (SelectPosition(OP_BUYLIMIT)) { //A Buy-limit set?
			if (OrderOpenPrice() != (dblBBLower + dblSpread)) //Is the Buy-limit open price wrong? 
				MoveOrder(dblBBLower + dblSpread, dblBBLower - SL * Point, dblBBLower + dblSpread + TP * Point); // Move the pending order.
		}else if (!SelectPosition(OP_BUY)) //No open Sell position?
			PlaceOrder(OP_BUYLIMIT, dblBBLower + dblSpread, dblBBLower - SL * Point, dblBBLower + dblSpread + TP * Point); // Select a Buy position, if the expert has opened one. // Place a Buy-limit position.
	}
}

//*************************************************************************************************
void ClosePositions() { // Close all positions.
	for(int i = 0; i < OrdersTotal(); i ++) {
		if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
		if(OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
			if (OrderType() == OP_SELL)
				OrderClose(OrderTicket(), OrderLots(), Ask, mintSlippage);
			else if (OrderType() == OP_BUY)
				OrderClose(OrderTicket(), OrderLots(), Bid, mintSlippage);
		}
	}
}

//*************************************************************************************************
void start() { // Start function
	if (GlobalVariableGet(mstrClosePositions) == mintTrue) {
		ClosePositions(); // Close all positions.
		GlobalVariableSet(mstrClosePositions, mintFalse); //Reset the ClosePositions flag.
	}else
		OpenPosition(); // Open a position.
}

//*************************************************************************************************
void init() {
   if (GlobalsInitialise) { //Reset the global variables?
      GlobalVariableSet(mstrLots, mdblLots); //The initial volume.
      GlobalVariableSet(mstrLastOrder, mintFalse); //Remember the order number.
	  GlobalVariableSet(mstrClosePositions, mintFalse); //Reset the ClosePositions flag.
   }
}

//*************************************************************************************************
void deinit() { // Delete the setup's all globals.
   if (GlobalsDelete) {
      GlobalVariableDel(mstrLots);
      GlobalVariableDel(mstrLastOrder);
	  GlobalVariableDel(mstrClosePositions);
   }
}

int _tmain(int argc, _TCHAR* argv[]) {
	const double initPrice = 1.5; //initial Price
	cout << "The Martingale Floating Equity Setup" << endl;
	cout << "Start from buying (1) or selling (0): ";
	cin >> mintType;
	cout << /*endl <<*/ "The initial lots: ";
	cin >> mdblLots;
	cout << endl;
	ticks Ticks(initPrice);
	init();
	Ticks.Generate(Account, Bid, Ask, start); // Generate symbol ticks.
	deinit(); // Delete the setup's all globals.
	return 0;
}

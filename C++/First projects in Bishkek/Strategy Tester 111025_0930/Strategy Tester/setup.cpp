#include "stdafx.h"
#include <fstream>
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include "symbol.h"
#include "orders.h"
#include "ticks.h"
#include "setup.h"
#include "globals.h"

bool SelectPosition() { // Select the position, if the expert has opened one.
	bool blnSelectPosition = false;
	for(int i = 0; i < OrdersTotal(); i ++) {
		if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) {
			if(OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
				blnSelectPosition = true; //The position selected.
				break;
			}
		}
   }
   return(blnSelectPosition);
}

//*************************************************************************************************
void DefineType() { // Revert the previous position type (Buy/Sell).
   switch (mintType) {
      case OP_BUY:
         mintType = OP_SELL;
         break;
      case OP_SELL:
         mintType = OP_BUY;
   }
}

//*************************************************************************************************
double Lots() { // Raise the number of lots, if the last trade has been unprofitable.
	double dblLots;
	int intLastPt;
	int intOrder = GlobalVariableGet(mstrLastOrder);
	if (intOrder == mintFalse) {
		dblLots = mdblLots; //No previous orders. Start from the initial lots.
 	}else if (OrderSelect(intOrder, SELECT_BY_TICKET, MODE_HISTORY)) { //A previous order selected?
	//	if (OrderType() == OP_SELL) intLastPt = DistancePts(OrderOpenPrice(), OrderClosePrice()); //The last order's profit.
	//	else intLastPt = DistancePts(OrderClosePrice(), OrderOpenPrice());
	//	if (intLastPt > TP / 2) { //Compare the last profit with 1/2 TP instead of > 0 due to slippare & spread deviations.
	//		dblLots = mdblLots; //The last trade has been profitable. Reset the lots.
	//		GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
	//	}else if (intLastPt < 0) {
	//		dblLots = MathRound(GlobalVariableGet(mstrLots) * LotsAccelerator * 100) / 100; //Raise the lots after a loss. Round the lots.
	//		GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
	//	}else{
	//		dblLots = GlobalVariableGet(mstrLots); //Leave the lots unchanged.
	//	}
	}
	return (dblLots);
}

//*************************************************************************************************
void OpenPosition() { // Open a position.
	string strSetup = "Martingale Floating Equity";
	int intOrderSend;
	if (mintType == OP_SELL) { 
		intOrderSend = OrderSend(Symbol(), mintType, Lots(), Bid, 3, 0, Bid - TP * Point, strSetup, MAGICMA, 0, Blue);
		if (intOrderSend != mintFalse) GlobalVariableSet(mstrLastOrder, intOrderSend); //Remember the order number.
	}else{
		intOrderSend = OrderSend(Symbol(), mintType, Lots(), Ask, 3, 0, Ask + TP * Point, strSetup, MAGICMA, 0, Blue);
		if (intOrderSend != mintFalse) GlobalVariableSet(mstrLastOrder, intOrderSend); //Remember the order number.
	}
}

//*************************************************************************************************
void start() { // Start function
   int intSlippage = 10;
   double dblPrice;
   int intPt;
   if(!SelectPosition()) {
      DefineType(); // Define the position type (Buy/Sell).
      OpenPosition(); //Open a position, if there's a signal & no position has been opened.
   }else{
   //   if (OrderType() == OP_SELL) intPt = DistancePts(OrderOpenPrice(), Ask); //The current profit.
   //   else intPt = DistancePts(Bid, OrderOpenPrice()); //The current profit.
   //   if (intPt >= TP) OrderClose(OrderTicket(), GlobalVariableGet(mstrLots), dblPrice, intSlippage);
   }
}

//*************************************************************************************************
void init() {
	mintType = OP_BUY; //Start from buying.
    GlobalVariableSet(mstrLots, mdblLots); //The initial volume.
    GlobalVariableSet(mstrLastOrder, mintFalse); //Remember the order number.
}

//*************************************************************************************************
void deinit() { // Delete the setup's all globals.
	GlobalVariableDel(mstrLots);
	GlobalVariableDel(mstrLastOrder);
}


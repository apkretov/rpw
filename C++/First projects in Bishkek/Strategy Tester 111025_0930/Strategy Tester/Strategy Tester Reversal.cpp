#include "StdAfx.h"

//	//ADD C++ CODE HERE
//
////*************************************************************************************************
///*extern*/ int TP = 30; //the initial take profit
///*extern*/ double mdblBalance = 6000; //the initial balance
///*extern*/ int mintType = OP_BUY; //Start from buying;
///*extern*/ double mdblLots = 0.01;
//
//string mstrSymbol = "GBPUSD";
////double mdblLots = 0.01;
//string mstrLots = "Coin_Lots";
//string mstrLastOrder = "Coin_LastOrder";
//int mintTrue = 1, mintFalse = -1;
//int /*mintType, */mintSpread;
////*************************************************************************************************
//
////ADD C++ CODE HERE
//
////*************************************************************************************************
//bool SelectPosition() { // Select the position, if the expert has opened one.
//	bool blnSelectPosition = false;
//	//for(int i = 0; i < OrdersTotal(); i ++) {
//	//	if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) {
//	//		if(OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
//	//			blnSelectPosition = true; //The position selected.
//	//			break;
//	//		}
//	//	}
//	//}
//	int intOrder = GlobalVariableGet(mstrLastOrder);
//	if (intOrder != mintFalse) { //Have there been any orders before?
//		if (OrderSelect(intOrder, SELECT_BY_TICKET)) { //The previous order selected?
//			if (OrderCloseTime() == 0) 
//				blnSelectPosition = true; //Open and pending orders close time is equal to 0.
//		}
//	}
//	return(blnSelectPosition);
//}
//
////*************************************************************************************************
//void DefineType() { // Revert the previous position type (Buy/Sell).
//   switch (mintType) {
//      case OP_BUY:
//         mintType = OP_SELL;
//         break;
//      case OP_SELL:
//         mintType = OP_BUY;
//   }
//}
//
////*************************************************************************************************
//int DistancePts(double dblPrice1, double dblPrice2) { // Return the distance in points betwenn the specified prices.
//    return(MathRound((dblPrice1 - dblPrice2) / Point));
//}
//
////*************************************************************************************************
//int Profit() { // The recently selected order's profit in points.
//	//return OrderProfit() / Point;
//	switch (OrderType()) {
//	case OP_BUY:
//		return DistancePts(OrderClosePrice(), OrderOpenPrice());
//	case OP_SELL:
//		return DistancePts(OrderOpenPrice(), OrderClosePrice());
//	}
//
//}
//
////*************************************************************************************************
//double Lots() { // Raise the number of lots, if the last trade has been unprofitable.
// 	//int LotsAccelerator = 2; //The number of lots accelerator.
//	double dblLots = 0;
//	int intLastPt;
//	int intOrder = GlobalVariableGet(mstrLastOrder);
//	if (intOrder == mintFalse)
//		dblLots = mdblLots; //No previous orders. Start from the initial lots.
// 	else if (OrderSelect(intOrder, SELECT_BY_TICKET, MODE_HISTORY)) { //The previous order selected?
//		////if (OrderType() == OP_SELL) 
//		////	intLastPt = DistancePts(OrderOpenPrice(), OrderClosePrice()); //The last order's profit.
//		////else 
//		////	intLastPt = DistancePts(OrderClosePrice(), OrderOpenPrice());
//		//switch (OrderType()) {
//		//case OP_BUY:
//		//	intLastPt = DistancePts(OrderClosePrice(), OrderOpenPrice());
//		//case OP_SELL:
//		//	intLastPt = DistancePts(OrderOpenPrice(), OrderClosePrice()); //The last order's profit.
//		//}
//		intLastPt = Profit(); //The last order's profit in points.
//		if (intLastPt > TP / 2) { //Compare the last profit with 1/2 TP instead of > 0 due to slippare & spread deviations.
//			dblLots = mdblLots; //The last trade has been profitable. Reset the lots.
//			GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
//		}else if (intLastPt < 0) {
//			//dblLots = MathRound(GlobalVariableGet(mstrLots) * LotsAccelerator * 100) / 100; //Raise the lots after a loss. Round the lots.
//			dblLots = GlobalVariableGet(mstrLots) * 2; //Double the lots after a loss.
//			GlobalVariableSet(mstrLots, dblLots); //Remember the volume raised.
//		}else{
//			dblLots = GlobalVariableGet(mstrLots); //Leave the lots unchanged.
//		}
//	}
//	return (dblLots);
//}
//
////*************************************************************************************************
//void OpenPosition() { // Open a position.
//	string strSetup = "Martingale Floating Equity";
//	int intOrderSend;
//	DefineType(); // Define the position type (Buy/Sell).
//	if (mintType == OP_SELL) { 
//		//intOrderSend = OrderSend(Symbol(), mintType, Lots(), Bid, 3, 0, Bid - TP * Point, strSetup, MAGICMA, 0, Blue);
//		intOrderSend = OrderSend(Symbol(), mintType, Lots(), Bid, 3, 0, 0, strSetup, MAGICMA, 0, Blue);
//		if (intOrderSend != mintFalse) GlobalVariableSet(mstrLastOrder, intOrderSend); //Remember the order number.
//	}else{
//		//intOrderSend = OrderSend(Symbol(), mintType, Lots(), Ask, 3, 0, Ask + TP * Point, strSetup, MAGICMA, 0, Blue);
//		intOrderSend = OrderSend(Symbol(), mintType, Lots(), Ask, 3, 0, 0, strSetup, MAGICMA, 0, Blue);
//		if (intOrderSend != mintFalse) GlobalVariableSet(mstrLastOrder, intOrderSend); //Remember the order number.
//	}
//}
//
////*************************************************************************************************
//void CloseOrders() { // Close all open orders.
//	int intSlippage = 10;
//	double dblPrice;
//	int intOrdersTotal = OrdersTotal(); //Assign to this variable the orders' total count due to that OrdersTotal() is going to change as the initially available orders will close.
//	for(int i = 0; i < intOrdersTotal; i ++) { //Loop through all open orders.
//		if(OrderSelect(0, SELECT_BY_POS, MODE_TRADES)) { //Always select the 1st order (indexed 0) because the end of the orders' array approached the beginning as the orders close in the cycle.
//			if(OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
//				switch (OrderType()) { //Distinguish between Bid/Ask to close at.
//				case OP_BUY:
//					dblPrice = Bid;
//					break;
//				case OP_SELL:
//					dblPrice = Ask;
//				}
//				OrderClose(OrderTicket(), OrderLots(), dblPrice, intSlippage);
//			}
//		}
//	}
//	GlobalVariableSet(mstrLots, mdblLots); //Reinitialise volume.
//	GlobalVariableSet(mstrLastOrder, mintFalse); //Reset the last order number.
//}
//
////*************************************************************************************************
//void CloseReverse() { // Close the position(s).
//	int intPt = Profit(); // The recently selected order's profit in points.
//	if (intPt <= TP * (-1)) //Is the current loss equivalent to TP?
//		OpenPosition(); //Open a position, if there's a signal & no position has been opened.
//	else if (intPt >= TP) //The target TP triggered?
//		CloseOrders(); // Close all open orders.
//}
//
////*************************************************************************************************
//void start() { // Start function
//	if(!SelectPosition())
//		OpenPosition(); //Open a position, if there's a signal & no position has been opened.
//	else
//		CloseReverse(); // Close the position(s).
//}
//
////*************************************************************************************************
//void init() {
//	//mintType = OP_SELL; //Start from selling.
//	//mintType = OP_BUY; //Start from buying.
//	mintSpread = MarketInfo(mstrSymbol, MODE_SPREAD);
//    GlobalVariableSet(mstrLots, mdblLots); //The initial volume.
//    GlobalVariableSet(mstrLastOrder, mintFalse); //Remember the order number.
//}
//
////*************************************************************************************************
//void deinit() { // Delete the setup's all globals.
//	GlobalVariableDel(mstrLots);
//	GlobalVariableDel(mstrLastOrder);
//}
//
//	//ADD C++ CODE HERE
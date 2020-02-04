#include "trade.h"

using std::string;

using namespace mtqc;
#include "algEA.h"
using namespace mtqc::algEA;

#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

trade::trade() {
	cintSlippage = 10;
	cstrTicket = "Ticket";
	cintTicket = -1;
	cintType = -1;
}

//convert direction to cintType and bid/ask
void trade::direc_to_type_bid_ask(enmDirec intDirec, int& intType, double& dblPrice) { 
	switch (intDirec) {
	case enmDirec::direc_up:
		intType = OP_BUY;
		dblPrice = Ask;
		break;
	case enmDirec::direc_down:
		intType = OP_SELL;
		dblPrice = Bid;
	}	
}

//convert cintType  to dirction and bid/ask
void trade::type_to_direc_bid_ask(int intType, enmDirec& intDirec, double& dblPrice) {
	switch (intType) {
	case OP_BUY:
		intDirec = enmDirec::direc_up;
		dblPrice = Ask;
		break;
	case OP_SELL:
		intDirec = enmDirec::direc_down;
		dblPrice = Bid;
	}	
}

bool trade::open(int intType, double dblPrice, double dblLots, double dblStopLoss, double dblTakeProfit) {
	const int intFailureFlag = -1;
	const string strComment = "Expert advisor";
	
	/*KTB
	//Returns number of the cintTicket assigned to the order by the trade server or -1 if it fails.
	cintTicket = OrderSend(
		Symbol(), 
		intType, 
		intLots, 
		dblPrice, 
		cintSlippage, 
		dblStopLoss, 
		dblTakeProfit, 
		strComment
	); 
	if (cintTicket == intFailureFlag)
		return false;
	else {*/
		cintType = intType;
		/*KTB 
		cdtmTimeOpen = TimeCurrent();
		//develop to retrieve an exact open price and time from the history pool
		cdblPriceOpen = dblPrice; 
		cintLots = intLots;
		*/
		return true;
	/*KTB}*/
}

	/*inline*/ int trade::getType() const	{ 
		return cintType; 
	}

	/*inline*/ void trade::setType(int intType) { 
		cintType = intType; 
	}

	/*inline*/ void trade::setPriceOpen(double dblPriceOpen) { 
		cdblPriceOpen = dblPriceOpen; 
	}

	/*inline*/ void trade::setLots(int intLots) { 
		cintLots = intLots; 
	}

	/*inline*/ bool trade::getBEReached() const { 
		return cblnBEReached; 
	}
   
	/*inline*/ void trade::setBEReached(bool blnBEReached) { 
		cblnBEReached = cblnBEReached; 
	}

bool trade::open_bid_ask(enmDirec intDirec, double dblLots, double dblStopLoss, double dblTakeProfit) {
	int intType;
	double dblPrice;
	direc_to_type_bid_ask(intDirec, intType, dblPrice);
	return open(intType, dblPrice, dblLots, dblStopLoss, dblTakeProfit);
}

//for open orders, it is the current unrealized profit; for closed orders, it is the fixed profit +
double trade::getProfit() { 
	enmDirec intDirec;
	double dblPrice;
	type_to_direc_bid_ask(cintType, intDirec, dblPrice);
	return distance(cdblPriceOpen, dblPrice, intDirec);
}

bool trade::close(double dblPrice) {
	/*KTB 
	if (!OrderClose(cintTicket, cintLots, dblPrice, cintSlippage)) 
		return false;
	else {
		//develop to retrieve the profit, close price, and close time from the history pool
		cdtmTimeClose = TimeCurrent();
	*/ 
		return true;
	/*}*/
}

bool trade::close_bid_ask(enmDirec intDirec) {
	int intType;
	double dblPrice;
	direc_to_type_bid_ask(intDirec, intType, dblPrice);
	return close(dblPrice);
}

//MT4 version void trade::copy(const trade &objTrade) {
void trade::copy(const trade* objTrade) {
	cintTicket = objTrade->cintTicket;
	cintType = objTrade->cintType;
	cdtmTimeOpen = objTrade->cdtmTimeOpen;
	cdtmTimeClose = objTrade->cdtmTimeClose;
	cdblPriceOpen = objTrade->cdblPriceOpen;
	cdblStopLoss = objTrade->cdblStopLoss;
	cdblTakeProfit = objTrade->cdblTakeProfit;
	cintLots = objTrade->cintLots;
}

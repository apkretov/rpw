#include "trade.h"
using std::string;
//#include "functionsMT4.h"
using namespace mtqc;
#include "algEA.h"
using namespace mtqc::algEA;
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

//constexpr int OP_BUY = 0, OP_SELL = 1, OP_BUYLIMIT = 2, OP_SELLLIMIT = 3, OP_BUYSTOP = 4, OP_SELLSTOP = 5; //Copy/pasted for MT4 compatability to make the switch operator work.
//constexpr int OP_BUY = 0, OP_SELL = 1; //Copied/pasted for MT4 compatability to make the switch operator work.
//extern double Bid, Ask;

//double distance(double dblFrom, double dblTo, enmDirec intDirec);

trade::trade() {
	cintSlippage = 10;
	cstrTicket = "Ticket";
	cintTicket = -1;
	cintType = -1;
}

void trade::direc_to_type_bid_ask(enmDirec intDirec, int& intType, double& dblPrice) { //convert direction to cintType and bid/ask +
	switch (intDirec) {
	case enmDirec::direc_up:
		intType = OP_BUY;
		dblPrice = Ask;
		break;
	case enmDirec::direc_down:
		intType = OP_SELL;
		dblPrice = Bid;
}	}

void trade::type_to_direc_bid_ask(int intType, enmDirec& intDirec, double& dblPrice) { //convert cintType  to dirction and bid/ask +
	switch (intType) {
	case OP_BUY:
	//case int(enmOperations::OP_BUY):
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
	/*KTB cintTicket = OrderSend(Symbol(), intType, intLots, dblPrice, cintSlippage, dblStopLoss, dblTakeProfit, strComment); //Returns number of the cintTicket assigned to the order by the trade server or -1 if it fails.
	if (cintTicket == intFailureFlag)
		return false;
	else {*/
		cintType = intType;
		/*KTB cdtmTimeOpen = TimeCurrent();
		cdblPriceOpen = dblPrice; //develop to retrieve an exact open price and time from the history pool
		cintLots = intLots;*/
		return true;
	/*KTB}*/
}

	/*inline*/ int trade::getType() const	{ return cintType; }
	/*inline*/ void trade::setType(int intType) { cintType = intType; }
	/*inline*/ void trade::setPriceOpen(double dblPriceOpen) { cdblPriceOpen = dblPriceOpen; }
	/*inline*/ void trade::setLots(int intLots) { cintLots = intLots; }
   /*inline*/ bool trade::getBEReached() const { return cblnBEReached; }
   /*inline*/ void trade::setBEReached(bool blnBEReached) { cblnBEReached = cblnBEReached; }

bool trade::open_bid_ask(enmDirec intDirec, double dblLots, double dblStopLoss, double dblTakeProfit) {
	int intType;
	double dblPrice;
	direc_to_type_bid_ask(intDirec, intType, dblPrice);
	return open(intType, dblPrice, dblLots, dblStopLoss, dblTakeProfit);
}

double trade::getProfit() { //for open orders, it is the current unrealized profit; for closed orders, it is the fixed profit +
	enmDirec intDirec;
	double dblPrice;
	type_to_direc_bid_ask(cintType, intDirec, dblPrice);
	return distance(cdblPriceOpen, dblPrice, intDirec);
}

bool trade::close(double dblPrice) {
	/*KTB if (!OrderClose(cintTicket, cintLots, dblPrice, cintSlippage)) return false;
	else {
		cdtmTimeClose = TimeCurrent();*/ //develop to retrieve the profit, close price, and close time from the history pool
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

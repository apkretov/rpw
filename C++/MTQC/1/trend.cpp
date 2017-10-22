#include "trend.h"
#include "enumerators.h"
//#include "functionsMT4.h"
using namespace mtqc;
#include "algEA.h"
using namespace mtqc::algEA;
//#include "constantsAlg.h"
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

//extern const int gintIdx0; //constantsAlg
//extern double Bid, Ask;
//extern int JawsReverseRange;

//ENUM_POINTER_TYPE CheckPointer(const trade* const ptrTrade);
//ENUM_POINTER_TYPE CheckPointer(const alg* const ptrAlg);
//int distance_pts(double dblFrom, double dblTo, enmDirec intDirec); //functionsAlg

trend::trend(double dblPeak) : cdblPeak(dblPeak) {
	cintTimeFrames[0] = ENUM_TIMEFRAMES::PERIOD_M5;
	cintTimeFrames[1] = ENUM_TIMEFRAMES::PERIOD_M30;
	cintTimeFrames[2] = ENUM_TIMEFRAMES::PERIOD_H1;
	cintTimeFrames[3] = ENUM_TIMEFRAMES::PERIOD_H4;
	cintIdxTFActive = gintIdx0;
	initialise(cintTimeFrames[cintIdxTFActive]);
	//cdblPeak = dblPeak;
}

/*MT4 version 
trend::~trend() { //delete the parent and child trends, if created +
	if (CheckPointer(cobjTradeActive.get()) == POINTER_DYNAMIC) { cobjTradeActive.reset(); }
	if (CheckPointer(cobjTradePrior.get()) == POINTER_DYNAMIC) { cobjTradePrior.reset(); }
	if (CheckPointer(cobjAlg.get()) == POINTER_DYNAMIC) { cobjAlg.reset(); } //check for POINTER_DYNAMIC just in case for more robustness despite it is unnecessary at the current stage
}*/

/*inline*/ double trend::alg_GetSave(int intIdx) { return cobjAlg->getSave(intIdx); }
/*inline*/ bool trend::alg_SignalGet() { return cobjAlg->signalGet(); }
/*inline*/ bool trend::alg_SignalTeethFarGetSave(int intSignalTeethFarness) { return cobjAlg->signalTeethFarGetSave(intSignalTeethFarness); }
/*inline*/ datetime trend::alg_GetSignalTime() const { return cobjAlg->getSignalTime(); }
//tradeSP trend::getTradeActive() const { return cobjTradeActive; }
/*inline*/ int trend::tradeActive_GetType() const { return cobjTradeActive->getType(); }
/*inline*/ void trend::tradeActive_SetType(int intType) { cobjTradeActive->setType(intType); }
/*inline*/ void trend::tradeActive_SetPriceOpen(double dblPriceOpen) { cobjTradeActive->setPriceOpen(dblPriceOpen); }
/*inline*/ void trend::tradeActive_SetLots(int intLots) { cobjTradeActive->setLots(intLots); }
/*inline*/ bool trend::tradeActive_GetBEReached() const { return cobjTradeActive->getBEReached(); }
/*inline*/ void trend::tradeActive_SetBEReached(bool blnBEReached) { cobjTradeActive->setBEReached(blnBEReached); }
/*inline*/ double trend::tradeActive_GetProfit() { return cobjTradeActive->getProfit(); }


void trend::initialise(ENUM_TIMEFRAMES intTimeFrame) {
	cintTimeFrame = intTimeFrame;
	cobjAlg = boost::movelib::make_unique<alg>(intTimeFrame, gintIdx0);
	cintDirec = cobjAlg->getDirec();
	cintPhase = enmPhases::phase_beginning;
}

/*inline*/ enmPhases trend::getPhase() const { return cintPhase; }
/*inline*/ void trend::setPhase(enmPhases intPhase) { cintPhase = intPhase; }	
inline enmDirec trend::setGetDirec(int intIdx) const { return cobjAlg->setGetDirec(intIdx); }

enmDirec trend::getSetSaveDirec(int intIdx) {
	cintDirec = cobjAlg->getSetSaveDirec(intIdx);
	return cintDirec;
}

bool trend::direc_reversed() { return distance_pts(cintDirec == enmDirec::direc_up ? cobjAlg->low() : cobjAlg->high(), Bid, cintDirec) < (JawsReverseRange * -1); } //return true, if direction reversed

/*inline*/ void trend::update_peak(double dblPrice) { if (distance_pts(cdblPeak, dblPrice, cintDirec) > 0) cdblPeak = dblPrice; } //update the current trend peak with the specified price //is a new price behind the current peak (taking into account the trend direction)?

void trend::trade_open() {
	if (cobjAlg->signalOvercome()) { //Has the signal been overcome?
		cobjTradeActive = boost::make_shared<trade>(); //Top 10 dumb mistakes to avoid with C++ 11 smart pointers - Mistake # 4 : Not using make_shared to initialize a shared_ptr ! @ http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/ //Resume
		if (cobjTradeActive->open_bid_ask(cintDirec, /*KTB Lots*/0)) {
			cintPhase = enmPhases::phase_signal_triggered;
}	}	} 

/*KTB
bool time_frame_shift() {
	if (cintIdxTFActive < ArraySize(cintTimeFrames) - 1) { //Isn't the active time frame the biggest one already?
		if (getTradeActive()->getProfit() >= 0) { //a profit trade in the old time frame?
			alg objAlg(cintTimeFrames[cintIdxTFActive + 1], gintIdx0); //watch an appearance of an opposite direction
			if (objAlg.getDirec() == cintDirec) { //is the new time frame direction the same?
				if (objAlg.signalGet()) { //has a signaled appeared in the new time frame?
					if (objAlg.signalOvercome()) { //can trade in the new time frame, i.g. signal triggered?
						datetime dtmSignalTimePrior = cobjAlg->getSignalTime(); //remember the prior signal to use it the shifted time frame //develop: trend_child/parent will contain the prior direction
						double dblSignalPricePrior = cobjAlg->cdblSignalPrice;
						cobjAlg.reset();
						initialise(cintTimeFrames[++cintIdxTFActive]); //Shift the active time frame index and initialise the trend.
						cobjAlg->setSignalTime(dtmSignalTimePrior); //restore the original signal generated in the prior time frame //develop: trend_child/parent will contain the prior and new time frame signals; it's more robust to remember the new time frame signal in a way
						cobjAlg->cdblSignalPrice = dblSignalPricePrior;
						cintPhase = phase_signal_triggered;
						return true;
	}	}	}	}	}
	return false;
}*/

bool trend::trade_close() { //close a buy/sell position +
	if (!cobjTradeActive->close_bid_ask(cintDirec)) return false; //din't the currently active trade close?
	else {
		//MT4 version if (CheckPointer(cobjTradePrior.get()) == POINTER_DYNAMIC) cobjTradePrior.reset(); //delete the previously prior object, if it has been created before and not deleted yet //Unlike the MT4 version this resetting isn't necessary because another resetting follows up right below. It's kept for MT4 compatability.
		//MT4 version cobjTradePrior = new trade; //for more robustness develop to use a prior trade retrieved from the history pool rather than my cobjTradePrior
		//MT4 version cobjTradePrior->copy(cobjTradeActive); //the current trade gets prior and cleared (next line)
		cobjTradePrior = std::move(cobjTradeActive);
		cintPhase = enmPhases::phase_end; //flag the end of the trend
		return true;
}	}

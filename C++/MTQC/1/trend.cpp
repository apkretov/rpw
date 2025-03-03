#include "trend.h"
#include "enumerators.h"

using namespace mtqc;
#include "algEA.h"
using namespace mtqc::algEA;

#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

trend::trend(double dblPeak) 
	: cdblPeak(dblPeak) 
{
	cintTimeFrames[0] = ENUM_TIMEFRAMES::PERIOD_M5;
	cintTimeFrames[1] = ENUM_TIMEFRAMES::PERIOD_M30;
	cintTimeFrames[2] = ENUM_TIMEFRAMES::PERIOD_H1;
	cintTimeFrames[3] = ENUM_TIMEFRAMES::PERIOD_H4;
	cintIdxTFActive = gintIdx0;
	initialise(cintTimeFrames[cintIdxTFActive]);
}

/*MT4 version
//delete the parent and child trends, if created +
trend::~trend() { 
	if (CheckPointer(cobjTradeActive.get()) == POINTER_DYNAMIC) 
		cobjTradeActive.reset(); 
	if (CheckPointer(cobjTradePrior.get()) == POINTER_DYNAMIC) 
		cobjTradePrior.reset(); 
	//check for POINTER_DYNAMIC just in case for more robustness despite it is unnecessary at the current stage
	if (CheckPointer(cobjAlg.get()) == POINTER_DYNAMIC) 
		cobjAlg.reset(); 
}*/

/*inline*/ double trend::alg_GetSave(int intIdx) { 
	return cobjAlg->getSave(intIdx); 
}

/*inline*/ bool trend::alg_SignalGet() { 
	return cobjAlg->signalGet(); 
}

/*inline*/ bool trend::alg_SignalTeethFarGetSave(int intSignalTeethFarness) { 
	return cobjAlg->signalTeethFarGetSave(intSignalTeethFarness); 
}

/*inline*/ datetime trend::alg_GetSignalTime() const { 
	return cobjAlg->getSignalTime(); 
}

/*inline*/ int trend::tradeActive_GetType() const { 
	return cobjTradeActive->getType(); 
}

/*inline*/ void trend::tradeActive_SetType(int intType) { 
	cobjTradeActive->setType(intType); 
}

/*inline*/ void trend::tradeActive_SetPriceOpen(double dblPriceOpen) { 
	cobjTradeActive->setPriceOpen(dblPriceOpen); 
}

/*inline*/ void trend::tradeActive_SetLots(int intLots) { 
	cobjTradeActive->setLots(intLots); 
}

/*inline*/ bool trend::tradeActive_GetBEReached() const { 
	return cobjTradeActive->getBEReached(); 
}

/*inline*/ void trend::tradeActive_SetBEReached(bool blnBEReached) { 
	cobjTradeActive->setBEReached(blnBEReached); 
}

/*inline*/ double trend::tradeActive_GetProfit() { 
	return cobjTradeActive->getProfit();
}


void trend::initialise(ENUM_TIMEFRAMES intTimeFrame) {
	cintTimeFrame = intTimeFrame;
	cobjAlg = boost::movelib::make_unique<alg>(intTimeFrame, gintIdx0);
	cintDirec = cobjAlg->getDirec();
	cintPhase = enmPhases::phase_beginning;
}

/*inline*/ enmPhases trend::getPhase() const { 
	return cintPhase; 
}

/*inline*/ void trend::setPhase(enmPhases intPhase) { 
	cintPhase = intPhase; 
}	

inline enmDirec trend::setGetDirec(int intIdx) const { 
	return cobjAlg->setGetDirec(intIdx); 
}

enmDirec trend::getSetSaveDirec(int intIdx) {
	cintDirec = cobjAlg->getSetSaveDirec(intIdx);
	return cintDirec;
}

//return true, if direction reversed
bool trend::direc_reversed() { 
	return distance_pts(cintDirec == enmDirec::direc_up 
		? cobjAlg->low() 
		: cobjAlg->high(), Bid, cintDirec) < (JawsReverseRange * -1); 
} 

//update the current trend peak with the specified price //is a new price behind the current peak (taking into account the trend direction)?
/*inline*/ void trend::update_peak(double dblPrice) { 
	if (distance_pts(cdblPeak, dblPrice, cintDirec) > 0) 
		cdblPeak = dblPrice; 
} 

void trend::trade_open() {
	//Has the signal been overcome?
	if (cobjAlg->signalOvercome()) { 
		//Top 10 dumb mistakes to avoid with C++ 11 smart pointers - Mistake # 4 : Not using make_shared to initialize a shared_ptr ! 
		//@ http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/ //Resume
		cobjTradeActive = boost::make_shared<trade>(); 
		if (cobjTradeActive->open_bid_ask(cintDirec, /*KTB Lots*/0)) {
			cintPhase = enmPhases::phase_signal_triggered;
		}
	}
}

/*KTB
bool time_frame_shift() {
	//Isn't the active time frame the biggest one already?
	if (cintIdxTFActive < ArraySize(cintTimeFrames) - 1) { 
		//a profit trade in the old time frame?
		if (getTradeActive()->getProfit() >= 0) { 
			//watch an appearance of an opposite direction
			alg objAlg(cintTimeFrames[cintIdxTFActive + 1], gintIdx0); 
			//is the new time frame direction the same?
			if (objAlg.getDirec() == cintDirec) { 
				//has a signaled appeared in the new time frame?
				if (objAlg.signalGet()) { 
					//can trade in the new time frame, i.g. signal triggered?
					if (objAlg.signalOvercome()) { 
						//remember the prior signal to use it the shifted time frame 
						//develop: trend_child/parent will contain the prior direction
						datetime dtmSignalTimePrior = cobjAlg->getSignalTime(); 
						double dblSignalPricePrior = cobjAlg->cdblSignalPrice;
						cobjAlg.reset();

						//Shift the active time frame index and initialise the trend.
						initialise(cintTimeFrames[++cintIdxTFActive]); 
						//restore the original signal generated in the prior time frame 
						//develop: trend_child/parent will contain the prior and new time frame signals; it's more robust to remember the new time frame signal in a way
						cobjAlg->setSignalTime(dtmSignalTimePrior); 
						cobjAlg->cdblSignalPrice = dblSignalPricePrior;
						cintPhase = phase_signal_triggered;
						
						return true;
					}
				}
			}
		}
	}
	return false;
}
*/

//close a buy/sell position
bool trend::trade_close() { 
	//din't the currently active trade close?
	if (!cobjTradeActive->close_bid_ask(cintDirec)) 
		return false; 
	else {
		/*MT4 version 
		//delete the previously prior object, if it has been created before and not deleted yet //Unlike the MT4 version this resetting isn't necessary because another resetting follows up right below. It's kept for MT4 compatability.
		if (CheckPointer(cobjTradePrior.get()) == POINTER_DYNAMIC) 
			cobjTradePrior.reset(); 
		*/
		
		/*MT4 version 
		//for more robustness develop to use a prior trade retrieved from the history pool rather than my cobjTradePrior
		cobjTradePrior = new trade; 
		*/
		
		/*MT4 version 
		//the current trade gets prior and cleared (next line)
		cobjTradePrior->copy(cobjTradeActive); 
		*/
		
		cobjTradePrior = std::move(cobjTradeActive);
		
		//flag the end of the trend
		cintPhase = enmPhases::phase_end; 
		
		return true;
	}	
}

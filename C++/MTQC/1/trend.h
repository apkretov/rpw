#pragma once
#include <boost\move\unique_ptr.hpp> //unique_ptr boost equivalent? @ http://stackoverflow.com/questions/2953530/unique-ptr-boost-equivalent
#include <boost\move\make_unique.hpp>
#define unique_ptr_t boost::movelib::unique_ptr 
#include <boost\make_shared.hpp>
#include "chartProperties.h"
#include "alg.h"
#include "trade.h"

namespace mtqc {
	typedef boost::shared_ptr<trade> tradeSP;
	
	class trend : public chartProperties {
	private:
		enmPhases cintPhase;
		double cdblPeak; //the highest/lowest price over the trend
		ENUM_TIMEFRAMES cintTimeFrames[4]; //the four time frames involved
		unique_ptr_t<alg> cobjAlg;
		int cintIdxTFActive; //the current time frame
		tradeSP cobjTradeActive; //TO DO: Add const to the new classes.
		tradeSP cobjTradePrior;
		void initialise(ENUM_TIMEFRAMES intTimeFrame);
	public:
		trend(double dblPeak);
		enmPhases getPhase() const;
		void setPhase(enmPhases intPhase);
		double alg_GetSave(int intIdx);
		bool alg_SignalGet();
		bool alg_SignalTeethFarGetSave(int intSignalTeethFarness);
		datetime alg_GetSignalTime() const;
		int tradeActive_GetType() const;
		void tradeActive_SetType(int intType);
		void tradeActive_SetPriceOpen(double dblPriceOpen);
		void tradeActive_SetLots(int intLots);
		bool tradeActive_GetBEReached() const;
		void tradeActive_SetBEReached(bool blnBEReached);
		double tradeActive_GetProfit();
		enmDirec setGetDirec(int intIdx) const override final; //#4 — override è final @ https://habrahabr.ru/post/182920/
		enmDirec getSetSaveDirec(int intIdx) override final; //#4 — override è final @ https://habrahabr.ru/post/182920/
		bool direc_reversed();
		void update_peak(double dblPrice);
		void trade_open();
	
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
	
		bool trade_close(); //close a buy/sell position +
	};
}
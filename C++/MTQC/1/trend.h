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

		//TO DO: Refactor the code here to get rid of repeating the alg class's functions.
		double alg_GetSave(int intIdx);
		bool alg_SignalGet();
		bool alg_SignalTeethFarGetSave(int intSignalTeethFarness);
		datetime alg_GetSignalTime() const;

		//TO DO: Refactor the code here to get rid of repeating the trade class's functions.
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
		bool trade_close(); //close a buy/sell position +
	};
}
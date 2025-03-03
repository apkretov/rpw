#pragma once
#include "enumerators.h"
#include "datetime.h"
#include "indicator.h"

namespace mtqc {
	class datetime;

	class alg : public indicator {
		double cdblLips, cdblTeeth, cdblJaws;
		datetime cdtmSignalTime;
		double cdblSignalPrice;
		bool cblnSignalTeethFar;
		
		void initialise(ENUM_TIMEFRAMES intTimeFrame, int intIdx);

	public:
		alg(ENUM_TIMEFRAMES intTimeFrame, int intIdx);
		datetime getSignalTime() const;
		void setSignalTime(const datetime& dtmSignalTime);
		double getSignalPrice() const;
		void setSignalPrice(double dblSignalPrice);
		
		enmDirec setGetDirec(int intIdx) const override final; //#4 — override è final @ https://habrahabr.ru/post/182920/
		enmDirec getSetSaveDirec(int intIdx) override final; //#4 — override è final @ https://habrahabr.ru/post/182920/
		
		double lips_get(int intIdx) const; //TO DO: Rename it into setLips. 
													  //TO DO: Make these three functions private. 
													  //TO DO: Remove these functions and use cobjCandlesByIndexLips->getClose(intShift) directly to boost performance.
		
		double teeth_get(int intIdx) const;
		double jaws_get(int intIdx) const;

		double getSave(int intIdx) override final; //TO DO: Rename it into setAlligator. //#4 — override è final @ https://habrahabr.ru/post/182920/

		double high() const;
		double high(int intIdx) const;
		double low() const;
		double low(int intIdx) const;

		/*
		KTB Switched off because shifting the time frame needs arranging a new chrTag for another time frame. 
		bool time_frame_shift(ENUM_TIMEFRAMES intTimeFrame) override final; 
		*/

		bool signalGet();
		bool signalOvercome() const;
		bool signalTeethFarGetSave(int intSignalTeethFarness);
	};
}
#include "stdafx.h"
#include "terminalMT4.h"
using std::string;
//#include "functionsMT4.h"
#include "enumerators.h"
#include "alg.h"
#include "candlesByIndex.h"
#include "datetime.h"
#include "messages.h"
#include "algEA.h"
using namespace mtqc::algEA;
//#include "constantsAlg.h"
using boost::shared_ptr;

#define make_unique_t boost::movelib::make_unique
//#define unique_ptr_t boost::movelib::unique_ptr 

namespace mtqc {
	namespace terminalMT4 {
		static struct { // using new_type_name = existing_type; "Type aliases (typedef / using)" @ http://www.cplusplus.com/doc/tutorial/other_data_types/
			boost::shared_ptr<candlesByIndex> bars;
			unique_ptr_t<candlesByIndex> lips;
			unique_ptr_t<candlesByIndex> teeth;
			unique_ptr_t<candlesByIndex> jaws;
		} msttCandlesByIndex;

		//extern const int OP_BUY = 0; //operations.cpp.
		//extern const int OP_SELL = 1;
		//extern const int OP_BUYLIMIT = 2;
		//extern const int OP_SELLLIMIT = 3;
		//extern const int OP_BUYSTOP = 4;
		//extern const int OP_SELLSTOP = 5;
		//enum enmOperations : int { OP_BUY, OP_SELL };

		extern const int gintIdx0 = 0; //constantsAlg.cpp.
		//extern const int MODE_GATORLIPS = 0; 
		//extern const int MODE_GATORTEETH = 2;
		//extern const int MODE_GATORJAW = 1;

		double Bid{}, Ask{}; //functionsMT4.cpp
		time Time(msttCandlesByIndex.bars);

		#include "display.h"
		template <typename T> 
		static ENUM_POINTER_TYPE checkPointer_t(const T ptr) { return ptr == nullptr ? ENUM_POINTER_TYPE::POINTER_INVALID : ENUM_POINTER_TYPE::POINTER_DYNAMIC; }
		ENUM_POINTER_TYPE CheckPointer(const trade* const ptrTrade) { return checkPointer_t(ptrTrade); } //"So how do we check if a pointer is NULL pointer?" @ http://stackoverflow.com/questions/6185821/so-how-do-we-check-if-a-pointer-is-null-pointer +
		ENUM_POINTER_TYPE CheckPointer(const alg* const ptrAlg) { return checkPointer_t(ptrAlg); }
		ENUM_POINTER_TYPE CheckPointer(const trend* const ptrTrend) { return checkPointer_t(ptrTrend); }

		double MathRound(double dblValue) { return round(dblValue); }
		double MathMax(double a, double b) { return (a < b) ? b : a; } //Despite MQL4 compatibility, it's introduced because '#include <algorithm> using std::max;' works but 'using std:MathMin;' doesn't. //std::max @ http://en.cppreference.com/w/cpp/algorithm/max +
		double MathMin(double a, double b) { return (b < a) ? b : a; } //Despite MQL4 compatibility, it's introduced because '#include <algorithm> using std::max;' works but 'using std:min;' doesn't. //std::min @ http://en.cppreference.com/w/cpp/algorithm/min +

		double iHigh(int intShift) { return msttCandlesByIndex.bars->getHigh(intShift); }
		double iLow(int intShift) { return msttCandlesByIndex.bars->getLow(intShift); }
		double iClose(int intShift) { return msttCandlesByIndex.bars->getClose(intShift); }
		datetime iTime(int intShift) { return msttCandlesByIndex.bars->getDatetime(intShift); }
		int iBars() { return msttCandlesByIndex.bars->getN(); } // Introduced for MTQC compatability. +

		double iAlligator(int intMode, int intShift) {
			if (intMode == MODE_GATORLIPS) return msttCandlesByIndex.lips->getClose(intShift);
			else if (intMode == MODE_GATORTEETH) return msttCandlesByIndex.teeth->getClose(intShift);
			else if (intMode == MODE_GATORJAW) return msttCandlesByIndex.jaws->getClose(intShift);
			else return 0; //An unexpected argument.
		}
																	  
		void Alert(const string& strMessage) { messages::message(strMessage); } // Displays a message. +

		void setCandlesByIndex(lua_State* L, const string& strTagPrice, const string& strTagAlg, int intCount, int intOffset) { // Set the data source for the Alligator EA. +
			const int intLine1 = 0; //The index of line 1 on a chart used for the Qlua getCandlesByIndex function.
			msttCandlesByIndex.bars = boost::make_shared<candlesByIndex>(L, strTagPrice, intLine1, intCount, intOffset); //TO DO: Make a robust syncronisation based on fixing the 1st bar of the selected series for all the lines. //TO DO: Introduce a candlesByIndexArg struct.
			msttCandlesByIndex.lips = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORLIPS, intCount, intOffset);
			msttCandlesByIndex.teeth = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORTEETH, intCount, intOffset);
			msttCandlesByIndex.jaws = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORJAW, intCount, intOffset);
		}

		void refreshCandlesByIndex() { // Refresh the data source for the Alligator EA. +
			msttCandlesByIndex.bars->refresh();
			msttCandlesByIndex.lips->refresh();
			msttCandlesByIndex.teeth->refresh();
			msttCandlesByIndex.jaws->refresh();
		}

		void OnTick(double dblPrice) { // Simulate an MT4 OnTick event. +
			Ask = Bid = dblPrice;
			//Ask = dblPrice;
			//Bid = dblPrice;
			refreshCandlesByIndex(); //Refresh the data source for the Alligator EA.
			//OnTickAlg(); //Alligatort EA's OnTick function.
}	}	}

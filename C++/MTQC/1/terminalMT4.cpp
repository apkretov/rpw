#include "stdafx.h"
#include "terminalMT4.h"
using std::string;

#include "enumerators.h"
#include "alg.h"
#include "candlesByIndex.h"
#include "datetime.h"
#include "messages.h"

#include "algEA.h"
using namespace mtqc::algEA;

using boost::shared_ptr;

#define make_unique_t boost::movelib::make_unique

namespace mtqc {
	namespace terminalMT4 {

		// using new_type_name = existing_type; "Type aliases (typedef / using)" @ http://www.cplusplus.com/doc/tutorial/other_data_types/
		static struct { 
			boost::shared_ptr<candlesByIndex> bars;
			unique_ptr_t<candlesByIndex> lips;
			unique_ptr_t<candlesByIndex> teeth;
			unique_ptr_t<candlesByIndex> jaws;
		} msttCandlesByIndex;

		//constantsAlg.cpp.
		extern const int gintIdx0 = 0; 

		//functionsMT4.cpp
		double Bid{}, Ask{}; 
		time Time(msttCandlesByIndex.bars);

		/*KTB This is a working prior version before the decltype counterpart below. The latter needs testing.
		template <typename T> 
		static ENUM_POINTER_TYPE checkPointer_t(const T ptr) { 
			return ptr == nullptr ? ENUM_POINTER_TYPE::POINTER_INVALID : ENUM_POINTER_TYPE::POINTER_DYNAMIC; 
		}*/
		template<typename T> //RESUME: While redundant the decltype is used to practise. //The decltype Keyword: The Basics @ http://thbecker.net/articles/auto_and_decltype/section_05.html
		static auto checkPointer_t(T ptr) -> decltype(ptr == nullptr ? ENUM_POINTER_TYPE::POINTER_INVALID : ENUM_POINTER_TYPE::POINTER_DYNAMIC) {
			return ptr == nullptr ? ENUM_POINTER_TYPE::POINTER_INVALID : ENUM_POINTER_TYPE::POINTER_DYNAMIC; 
		}		

		//"So how do we check if a pointer is NULL pointer?" @ http://stackoverflow.com/questions/6185821/so-how-do-we-check-if-a-pointer-is-null-pointer +
		ENUM_POINTER_TYPE CheckPointer(const trade* const ptrTrade) { 
			return checkPointer_t(ptrTrade); 
		} 
		
		ENUM_POINTER_TYPE CheckPointer(const alg* const ptrAlg) { 
			return checkPointer_t(ptrAlg); 
		}
		
		ENUM_POINTER_TYPE CheckPointer(const trend* const ptrTrend) { 
			return checkPointer_t(ptrTrend); 
		}

		double MathRound(double dblValue) { 
			return round(dblValue); 
		}
		
		//Despite MQL4 compatibility, it's introduced because '#include <algorithm> using std::max;' works but 'using std:MathMin;' doesn't. 
		//std::max @ http://en.cppreference.com/w/cpp/algorithm/max +
		double MathMax(double a, double b) { 
			return (a < b) ? b : a; 
		} 
		
		//Despite MQL4 compatibility, it's introduced because '#include <algorithm> using std::max;' works but 'using std:min;' doesn't. 
		//std::min @ http://en.cppreference.com/w/cpp/algorithm/min +
		double MathMin(double a, double b) { 
			return (b < a) ? b : a; 
		} 

		double iHigh(int intShift) { 
			return msttCandlesByIndex.bars->getHigh(intShift); 
		}
		
		double iLow(int intShift) { 
			return msttCandlesByIndex.bars->getLow(intShift); 
		}
		
		double iClose(int intShift) { 
			return msttCandlesByIndex.bars->getClose(intShift); 
		}
		
		datetime iTime(int intShift) { 
			return msttCandlesByIndex.bars->getDatetime(intShift); 
		}
		
		// Introduced for MTQC compatability. +
		int iBars() { 
			return msttCandlesByIndex.bars->getN(); 
		} 

		double iAlligator(int intMode, int intShift) {
			if (intMode == MODE_GATORLIPS) 
				return msttCandlesByIndex.lips->getClose(intShift);
			else if (intMode == MODE_GATORTEETH) 
				return msttCandlesByIndex.teeth->getClose(intShift);
			else if (intMode == MODE_GATORJAW) 
				return msttCandlesByIndex.jaws->getClose(intShift);
			else //An unexpected argument.
				return 0; 
		}
																	  
		// Displays a message.
		void Alert(const string& strMessage) { 
			messages::message(strMessage); 
		}

		// Set the data source for the Alligator EA.
		void setCandlesByIndex(lua_State* L, const string& strTagPrice, const string& strTagAlg, int intCount, int intOffset) {
			//The index of line 1 on a chart used for the Qlua getCandlesByIndex function.
			const int intLine1 = 0; 
			//TO DO: Make a robust syncronisation based on fixing the 1st bar of the selected series for all the lines. 
			//TO DO: Introduce a candlesByIndexArg struct.
			msttCandlesByIndex.bars = boost::make_shared<candlesByIndex>(L, strTagPrice, intLine1, intCount, intOffset); 
			msttCandlesByIndex.lips = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORLIPS, intCount, intOffset);
			msttCandlesByIndex.teeth = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORTEETH, intCount, intOffset);
			msttCandlesByIndex.jaws = make_unique_t<candlesByIndex>(L, strTagAlg, MODE_GATORJAW, intCount, intOffset);
		}

		// Refresh the data source for the Alligator EA. +
		void refreshCandlesByIndex() { 
			msttCandlesByIndex.bars->refresh();
			msttCandlesByIndex.lips->refresh();
			msttCandlesByIndex.teeth->refresh();
			msttCandlesByIndex.jaws->refresh();
		}

		// Simulate an MT4 OnTick event.
		void OnTick(double dblPrice) { 
			Ask = Bid = dblPrice;
			//Refresh the data source for the Alligator EA.
			refreshCandlesByIndex(); 
		}	
	}	
}

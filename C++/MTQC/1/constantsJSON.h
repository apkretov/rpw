#pragma once
#include "enumerators.h"
#include "switch.h"

namespace mtqc {
	class constantsJSON {
		std::string cstrACCOUNT;
		std::string cstrCLIENT_CODE;

		int cintLengthPrice{};
		int cintLengthLots{};

		bool cblnFuturesFractional{};
		int cintContractSize{};

		#ifdef BLN_ALG
			int cintChartOffset{};
			int cintCandlesCount{};
		#endif

		ENUM_TIMEFRAMES cintPERIOD_CURRENT{};
		#ifdef BLN_TRADE_SR
			double cdblStockToFuturesAdjustment{};
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			double cdblPriceStock{};
		#endif 
	
	public:
		constantsJSON();
	};	
}

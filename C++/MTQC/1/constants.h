#pragma once
#include "enumerators.h"
#include "switch.h"
#include "constantsXML.h"

namespace mtqc {
	namespace constants {
		extern const std::string ACCOUNT;
		extern const std::string CLIENT_CODE;
		extern const std::string gstrMsgWrongOrder;
		extern const int gintOperationNull;
		extern const int gintLengthValueSeparator;
		extern const int gintLengthPrice;
		extern const int gintLengthLots;
		extern const int gintLengthOperation;
		extern const std::string gstrOperations[];
		extern const bool gblnFuturesFractional;
		extern const int gintContractSize;
		extern const std::string MagicNumber;
		#ifdef BLN_ALG
			extern const int gintChartOffset;
			extern const int gintCandlesCount;
		#endif
		extern const ENUM_TIMEFRAMES PERIOD_CURRENT;
		extern const std::string gstrMTQC;
		#ifdef BLN_TRADE_SR
			extern const double gdblStockToFuturesAdjustment;
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			extern const double gdblPriceStock;
		#endif 
		extern constantsXML gobjConstantsXML;
}	}

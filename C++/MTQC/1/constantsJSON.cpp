#include "stdafx.h"
#include "constantsJSON.h"
using namespace mtqc;
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>
using std::string;
#include "functions.h"
using mtqc::functions::stringToInt;
using mtqc::functions::stringToDouble;
#include <exception>
using std::exception;
#include "messages.h"

constantsJSON::constantsJSON() {
	try {
		using boost::property_tree::ptree;
		ptree ptreeConstants;
		boost::property_tree::read_json("MTQC - Constants.json", ptreeConstants);
		ptree ptreeRoot = ptreeConstants.get_child("Constants");

		ptree ptreeAccount = ptreeRoot.get_child("Account");
		cstrACCOUNT = ptreeAccount.get_value<string>("Account");
		cstrCLIENT_CODE = ptreeAccount.get_value<string>("Client code");

		ptree ptreeLengths = ptreeRoot.get_child("Lengths");
		cintLengthPrice = stringToInt(ptreeLengths.get_value<string>("Length of price"));
		cintLengthLots = stringToInt(ptreeLengths.get_value<string>("Length of lots"));

		ptree ptreeFutures = ptreeRoot.get_child("Futures");
		cblnFuturesFractional = ptreeFutures.get_value<bool>("Futures fractional");
		cintContractSize = stringToInt(ptreeFutures.get_value<string>("Contract size"));

		#ifdef BLN_ALG
			#ifdef BLN_ALG_SETTINGS_1
				const string strAlgSettings = "Alligator settings 1";
			#elif defined(BLN_ALG_SETTINGS_2)
				const string strAlgSettings = "Alligator settings 2";
			#endif
			ptree ptreeAlgSettings = ptreeRoot.get_child(strAlgSettings);
			cintChartOffset = stringToInt(ptreeAlgSettings.get_value<string>("Chart offset"));
			cintCandlesCount = stringToInt(ptreeAlgSettings.get_value<string>("Candles count"));
		#endif
	
		cintPERIOD_CURRENT = (ENUM_TIMEFRAMES)stringToInt(ptreeRoot.get_value<string>("Period.Current period"));
		#ifdef BLN_TRADE_SR
			cdblStockToFuturesAdjustment = stringToDouble(ptreeRoot.get_value<string>("Trade SR.Stock-to-futures adjustment"));
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			cdblPriceStock = stringToDouble(ptreeRoot.get_value<string>("Test without quotes.Stock price"));
		#endif
	}
	
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}
}

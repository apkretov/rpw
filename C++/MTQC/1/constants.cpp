using std::string;
#include "constants.h"

namespace mtqc {
	namespace constants {
		extern const string ACCOUNT = "SPBFUT00gg2"; /*MFC Account*/ //Торговый счет из таблицы "Таблица торговых счетов", колонка "Счет". @ http://robostroy.ru/community/article.aspx?id=773 //TO DO: Include this constant and other similar into MTQC – MFC.
		extern const string CLIENT_CODE = "162349"; /*MFC Account*/ //Код клиента из таблицы "Клиентский портфель", колонка "Код клиента". @ http ://robostroy.ru/community/article.aspx?id=773
		extern const string gstrMsgWrongOrder = "Wrong order type!";
		extern const int gintOperationNull = -1;
		extern const int gintLengthValueSeparator = 1;
		extern const int gintLengthPrice = 6; /*MFC Lengths*/
		extern const int gintLengthLots = 6; /*MFC Lengths*/
		extern const int gintLengthOperation = 1;
		extern const string gstrOperations[6] = { "B", "S", "bl", "sl", "bs", "ss" };
		extern const bool gblnFuturesFractional = false; /*MFC Futures*/ //The flag for a fractional part of the futures price.
		extern const int gintContractSize = 100; /*MFC Futures*/ //TO DO: Use the Quik paramenters table.
		extern const string MagicNumber = "1"; //The variable is w/o a scope/type prefix for MT4 compatibility.
		#ifdef BLN_ALG
			#ifdef BLN_ALG_SETTINGS_1
				extern const int gintChartOffset = 8; /*MFC Alligator*/ //The offset of the chart from the right edge.
				extern const int gintCandlesCount = 1000; /*MFC Alligator*/ //The count of bars/ticks selected by the Qlua getCandlesByIndex function.	
			#elif defined(BLN_ALG_SETTINGS_2)
				extern const int gintChartOffset = 144; /*MFC Alligator*/ //The offset of the chart from the right edge.
				extern const int gintCandlesCount = 50; /*MFC Alligator*/ //The count of bars/ticks selected by the Qlua getCandlesByIndex function.
			#endif
		#endif
		extern const ENUM_TIMEFRAMES PERIOD_CURRENT = ENUM_TIMEFRAMES::PERIOD_TICK; /*MFC Period*/ //The current period, that of the tagged chart.
		extern const string gstrMTQC = STR_PROJECT_NAME;
		#ifdef BLN_TRADE_SR
			extern const double gdblStockToFuturesAdjustment = -2.5; /*MFC Trade SR*/
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			extern const double gdblPriceStock = 157.14; /*MFC Test without quotes*/
		#endif 
		constantsXML gobjConstantsXML;
	}	
}
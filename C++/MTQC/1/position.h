#pragma once
#include "fileCSV.h"
#include "terminal.h"

namespace mtqc{
	class position { 
		//const std::string ACCOUNT = "SPBFUT00gg2"; //Торговый счет из таблицы "Таблица торговых счетов", колонка "Счет". @ http://robostroy.ru/community/article.aspx?id=773 //TO DO: Include this constant and other similar into MTQC – MFC.
		//const std::string CLIENT_CODE = "162349"; //Код клиента из таблицы "Клиентский портфель", колонка "Код клиента". @ http ://robostroy.ru/community/article.aspx?id=773
		const std::string cstrTradeNumsTxt = "TradeNums.log"; 
		const std::string cstrTotalnetTxt = "Totalnet.log";
		const std::string cstrFilePrefix;
		//const bool cblnTradeDisabled; //The trading disabled flag.
		bool cblnTradeDisabled; //The trading disabled flag.
		int cintLotsTraded; //The initial volume to trade. It can be changed from MT4.
		fileCSV cobjFileCSVOrders, cobjFileCSVTrades;
		std::vector<int> cintTradeNums;	// Массив для хранения номеров записанных в файл сделок (для предотвращения дублирования) @ http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/
		int cintTotalnet;
		//KTB bool sendTransaction_(lua_State* L, int intOperation, const std::string& strPriceDOM, double dblPriceStock, const std::string& strOpenClose, int intLots);
		bool sendTransaction_(int intOperation, const terminal& objTerminal, const std::string& strOpenClose, int intLots);
		int getOperation() const;
		bool open_(int intOperation, const terminal & objTerminal, int & intLotsOpened);
	public:
		const std::string strOpen = "Open";
		const std::string strClose = "Close";
		//position(bool blnTradeDisabled_, int intLotsTraded_);
		position();
		void initialise(bool blnTradeDisabled_, int intLotsTraded_);
		int getTotalnet() const;
		void setTotalnet(int intTotalnet);
		void checkOrCreate(const std::string& strFileName, const std::string& strInput = "");
		int checkBit(int intFlags, int intBit);
		void setLotsTraded(int intLotsTraded_);
		void recordTrade(int intTradeNum, int intFlags, const std::string& strPrice, const std::string& strQty);
		bool open(int intOperation, const terminal& objTerminal);
		bool open(int intOperation, const terminal& objTerminal, int& intLotsOpened);
		bool matchClosingToOpened(int intOperationClosing) const;
		bool close(const terminal & objTermninal, bool blnReverse);
	};	
}
#pragma once
#include "constantsXMLv.h"

namespace mtqc {
	class constantsXML : public constantsXMLv { // Use namepsace instead of numbering like this next time: Namespaces provide a method for preventing name conflicts in large projects. See Namespaces @ http://en.cppreference.com/w/cpp/language/namespace 
	
		const std::wstring cstrCLASSCODEName = L"CLASSCODE";
		const std::wstring cstrStockName = L"Stock";
		const std::wstring cstrFuturesName = L"Futures";
	
		const std::wstring cstrTradeSRName = L"TradeSR";
	
		const std::wstring cstrStockPointName = L"StockPoint";
		const std::wstring cstrStockTagPriceName = L"StockTagPrice";
		const std::wstring cstrStockTagAlgName = L"StockTagAlg";
	
		const std::wstring cstrFuturesPointName = L"FuturesPoint";
		const std::wstring cstrFuturesTagPriceName = L"FuturesTagPrice";
		const std::wstring cstrFuturesTagAlgName = L"FuturesTagAlg";

		const std::wstring cstrLotsTradedName = L"LotsTraded";
		const std::wstring cstrLotsMaxName = L"LotsMax";
	
		const std::wstring cstrResumeRangeName = L"ResumeRange";

		const std::wstring cstrTradeDisabledName = L"TradeDisabled";
		const std::wstring cstrAllMessagesName = L"AllMessages";

		std::wstring cstrCLASSCODE;
		std::wstring cstrStock;
		std::wstring cstrFutures;
	
		bool cblnTradeSR;
	
		double cdblStockPoint;
		std::wstring cstrStockTagPrice;
		std::wstring cstrStockTagAlg;
	
		int cintFuturesPoint;
		std::wstring cstrFuturesTagPrice;
		std::wstring cstrFuturesTagAlg;

		int cintLotsTraded;
		int cintLotsMax;
	
		bool cblnTradeDisabled;
		bool cblnAllMessages;
	
		int cintResumeRange;

		bool isEmpty(const std::wstring& strMember, const std::wstring& strMemberName) const;
		bool stringToBool(const std::wstring& str1true_0false) const;
		void writeNodesToXML();

	public:
		std::wstring getCLASSCODE() const override final;
		void setCLASSCODE(const std::wstring& strCLASSCODE) override final;

		std::wstring getStock() const override final;
		void setStock(const std::wstring& strStock) override final;

		std::wstring getFutures() const override final;
		void setFutures(const std::wstring& strFutures) override final;
	
		bool getTradeSR() const override final;
		void setTradeSR(bool blnTRADE_SR) override final;
		void setTradeSR(const std::wstring& strTRADE_SR) override final;

		double getStockPoint() const override final;
		void setStockPoint(double dblStockPoint) override final;
		void setStockPoint(const std::wstring& strStockPoint) override final;

		std::wstring getStockTagPrice() const override final;
		void setStockTagPrice(const std::wstring& strStockTagPrice) override final;
	
		std::wstring getStockTagAlg() const override final;
		void setStockTagAlg(const std::wstring& strStockTagAlg) override final;

		int getFuturesPoint() const override final;
		void setFuturesPoint(int intFuturesPoint) override final;
		void setFuturesPoint(const std::wstring& strFuturesPoint) override final;

		std::wstring getFuturesTagPrice() const override final;
		void setFuturesTagPrice(const std::wstring& strFuturesTagPrice) override final;
	
		std::wstring getFuturesTagAlg() const override final;
		void setFuturesTagAlg(const std::wstring& strFuturesTagAlg) override final;

		int getLotsTraded() const override final;
		void setLotsTraded(int intLotsTraded) override final;
		void setLotsTraded(const std::wstring& strLotsTraded) override final;

		int getLotsMax() const override final;
		void setLotsMax(int intLotsMax) override final;
		void setLotsMax(const std::wstring& strLotsMax) override final;

		bool getTradeDisabled() const override final;
		void setTradeDisabled(bool blnTradeDisabled) override final;
		void setTradeDisabled(const std::wstring& strTradeDisabled) override final;
		
		bool getAllMessages() const override final;
		void setAllMessages(bool blnAllMessages) override final;
		void setAllMessages(const std::wstring& strAllMessages) override final;

		int getResumeRange() const override final;
		void setResumeRange(int intResumeRange) override final;
		void setResumeRange(const std::wstring& strResumeRange) override final;

		void readXML() override final;
		void writeXML() override final;
		void destroy() override final;
	};	
}

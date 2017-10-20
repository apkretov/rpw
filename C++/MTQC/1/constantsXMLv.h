#pragma once //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/

namespace mtqc {
	class constantsXMLv {
	public:
		virtual std::wstring getCLASSCODE() const = 0;
		virtual void setCLASSCODE(const std::wstring& strCLASSCODE) = 0;

		virtual std::wstring getStock() const = 0;
		virtual void setStock(const std::wstring& strStock) = 0;

		virtual std::wstring getFutures() const = 0;
		virtual void  setFutures(const std::wstring& strFutures) = 0;
	
		virtual bool getTradeSR() const = 0;
		virtual void  setTradeSR(bool blnTRADE_SR) = 0;
		virtual void  setTradeSR(const std::wstring& strTRADE_SR) = 0;

		virtual double getStockPoint() const = 0;
		virtual void  setStockPoint(double dblStockPoint) = 0;
		virtual void  setStockPoint(const std::wstring& strStockPoint) = 0;

		virtual std::wstring getStockTagPrice() const = 0;
		virtual void  setStockTagPrice(const std::wstring& strStockTagPrice) = 0;
	
		virtual std::wstring getStockTagAlg() const = 0;
		virtual void  setStockTagAlg(const std::wstring& strStockTagAlg) = 0;

		virtual int getFuturesPoint() const = 0;
		virtual void  setFuturesPoint(int intFuturesPoint) = 0;
		virtual void  setFuturesPoint(const std::wstring& strFuturesPoint) = 0;

		virtual std::wstring getFuturesTagPrice() const = 0;
		virtual void  setFuturesTagPrice(const std::wstring& strFuturesTagPrice) = 0;
	
		virtual std::wstring getFuturesTagAlg() const = 0;
		virtual void  setFuturesTagAlg(const std::wstring& strFuturesTagAlg) = 0;

		virtual int getLotsTraded() const = 0;
		virtual void  setLotsTraded(int intLotsTraded) = 0;
		virtual void  setLotsTraded(const std::wstring& strLotsTraded) = 0;

		virtual int getLotsMax() const = 0;
		virtual void  setLotsMax(int intLotsMax) = 0;
		virtual void  setLotsMax(const std::wstring& strLotsMax) = 0;

		virtual bool getTradeDisabled() const = 0;
		virtual void setTradeDisabled(bool blnTradeDisabled) = 0;
		virtual void setTradeDisabled(const std::wstring& strTradeDisabled) = 0;
		
		virtual bool getAllMessages() const = 0;
		virtual void setAllMessages(bool blnAllMessages) = 0;
		virtual void setAllMessages(const std::wstring& strAllMessages) = 0;

		virtual int getResumeRange() const = 0;
		virtual void setResumeRange(int intResumeRange) = 0;
		virtual void setResumeRange(const std::wstring& strResumeRange) = 0;

		virtual void readXML() = 0;
		virtual void writeXML() = 0;
		virtual void destroy() = 0;
	};	
}
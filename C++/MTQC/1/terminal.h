#pragma once

namespace mtqc{
	class terminal { 
		lua_State* L;
		//KTB DEBUGGING lua_State* L_; 
		//KTB const int /*KTB intIcon_type_information,*/ intIcon_type_exclamation /*KTB , icon_type_critical*/;
		bool cblnRun;
		double cdblPriceStock;
		int cintOperationsTable;
		//KTB void destroyL();
		double cdblOfferBidPrice[2] = { 0, 0 };
		int cintOfferBidQuantity[2] = { 0, 0 };

		//bool incrmentCompare(int& i, int intTo);
		//bool decrmentCompare(int& i, int intTo);
		//bool incrmentCompareMessaging(int& i, int intTo, terminal* objTerminal);
		//static bool decrmentCompareMessaging(int& i, int intTo, terminal* objTerminal);

		void getOfferBidBest(int intFrom, int intTo, bool(*fncInDecrmentCompare)(int&, int), double& dblPrice, int& intQuantity);
		void getOfferBidBestMessaging(int intFrom, int intTo, bool(*fncInDecrmentCompare)(int&, int, terminal*), double& dblPrice, int& intQuantity);
		void message_(const std::string& strMessage, int intIcon_type = 1) const;
	public:
		explicit terminal(lua_State* L_ = nullptr);
		~terminal();
		double getOfferBidPrice(size_t intIx) const;
		lua_State* getL() const; //TO DO: Declare all constant functions.
		void setL(lua_State* L_);
		bool getRun() const;
		void setRun(bool blnRun);
		double getPriceStock() const;
		void setPriceStock(double dblPriceStock);
		bool getOfferBid(const std::string& strFutures);
		void createOperationsTable(int(*tableNotificationCallback)(lua_State *));
		void destroyOperationsTable();
		//KTB void message(const char* chrMessage) const;
		//KTB void message(const std::string& srtMessage) const;
		//KTB void messageNoPriceStock() const;
		void messageNoOfferBid() const;
	};
}

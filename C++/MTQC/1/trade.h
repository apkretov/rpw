#pragma once

#include "enumerators.h"
#include "datetime.h"

namespace mtqc {

	class trade {
		int cintTicket, cintType;
		std::string cstrTicket;
		
		//If order close time is not 0, then the order selected and has been closed and retrieved from the account history. Open and pending orders close time is equal to 0.
		datetime cdtmTimeOpen, cdtmTimeClose; 
		
		double cdblPriceOpen, cdblStopLoss, cdblTakeProfit;
		int cintLots;
		bool cblnBEReached;
		int cintSlippage;

		void direc_to_type_bid_ask(enmDirec intDirec, int& intType, double& dblPrice);
		void type_to_direc_bid_ask(int intType, enmDirec& intDirec, double& dblPrice);
		bool open(int intType, double dblPrice, double dblLots = 0, double dblStopLoss = 0, double dblTakeProfit = 0);

	public:
		trade();

		int getType() const;
		void setType(int intType);

		void setPriceOpen(double dblPriceOpen);
		void setLots(int intLots);

		bool getBEReached() const;
		void setBEReached(bool blnBEReached);

		bool open_bid_ask(enmDirec intDirec, double dblLots = 0, double dblStopLoss = 0, double dblTakeProfit = 0);

		double getProfit();

		bool close(double dblPrice);
		bool close_bid_ask(enmDirec intDirec);

		void copy(const trade* objTrade);
	};
}
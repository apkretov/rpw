#pragma once

namespace mtqc {

	class object {
		int cintOperation;
		double cdblPrice;
		std::string cstrDescription;
	
	public:
		object(int intOperation, double dblPrice, std::string strDescription);
		object::object(object&& objObject);
	
		int getOperation() const;
		double getPrice() const;
		
		std::string getDescription() const;
		void setDescription(const std::string& strDescription);
		
		int getOperationBuySell() const;
		
		bool isKept() const;
		bool isPending() const;
		bool isResuming() const;
		bool isReversing() const;
		bool isAlert() const;
		//KTB bool isTrade() const { return description == "t"; } 
	};	
}

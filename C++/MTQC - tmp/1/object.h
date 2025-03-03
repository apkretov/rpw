#pragma once

namespace mtqc {

	class object {
		int cintOperation;
		double cdblPrice;
		std::string cstrDescription;
		void KTB_setTrade(bool blnTrade);

		const unsigned char cchrFlagAlert = 1 << 0; // 0000 0001 // The bit positions of the flags. // 3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
		const unsigned char cchrFlagTrade = 1 << 1; // 0000 0010
		const unsigned char cchrFlagPending = 1 << 2; // 0000 0100
		const unsigned char cchrFlagKept = 1 << 3; // 0000 1000
		const unsigned char cchrFlagResuming = 1 << 4; // 0001 0000
		const unsigned char cchrFlagReversing = 1 << 5; // 0010 0000
		const unsigned char cchrFlagMoving = 1 << 6; // 0100 0000
		unsigned char cchrFlag = 0; //all flags/options turned off to start


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

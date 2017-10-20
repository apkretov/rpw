#pragma once

namespace mtqc {
	class mt4QuikConnector_ {
		const int cintPosition1stSymbol = 1; //The position of the 1st symbol within a string for the string.substr function.
		const int cintLengthCommand = 5; //The length of commands.
		const std::string cstrDisableOjects = "cmdDO"; //The Disable Ojects command.
		const std::string cstrClosePosition = "cmdCP"; //The Close Position command.
		//KTB const std::string cstrKeyPressedEsc = "keyES"); 
		const std::string cstrKeyPressedOperation = "cmdBS"; //The Buy/Sell operation command.
		const std::string cstrSetLots = "cmdSL"; //The Set Lots command.
		//const std::string cstrRefreshConstants = "C"; //The Refreshs Constants command. //TO DO: Unlike now, pass more than one character. See e.g: BUG: Imported DLL Functions Receive Only First Character of Strings Passed By Value (MQL Build 237) @ https://www.mql5.com/en/forum/348
		const std::string cstrRefreshConstants = "cmdRC"; //The Refreshs Constants command.
		std::string cstrMessage; //Introducing C++11 Brace-Initialization - string s{}; //same as: string s; @ http://www.informit.com/articles/article.aspx?p=1852519
		int getValue(int intLengthValue) const;
	public:
		void setMessage(std::string strMessage);
		bool pricesSent() const;
		bool disableObjects() const;
		bool closePosition() const;
		//KTB bool keyPressedEsc() const;
		int keyPressedOperation() const;
		int setLots() const;
		bool refreshConstants() const;
	};
}
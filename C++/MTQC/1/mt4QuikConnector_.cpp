#include "mt4QuikConnector_.h"
using std::string;
#include "functions.h"
using namespace mtqc;
using namespace mtqc::functions;

#include "constants.h"
using namespace mtqc::constants;

/*inline*/ void mt4QuikConnector_::setMessage(string strMessage) { cstrMessage = strMessage; } 

int mt4QuikConnector_::getValue(int intLengthValue) const { // Get the value (price, lots, etc.) after the command prefix. 
	int intPositionValue = cintPosition1stSymbol + cintLengthCommand + gintLengthValueSeparator; // The position of the value (price, lots, etc.) after the command prefix.
	return stringToInt( cstrMessage.substr(intPositionValue - 1, intLengthValue) ); //Lua->C++: string.sub(strString, intPosition1, intPosition2) -> strString.substr(intPosition1 - 1, intPosition2 - intPosition1)
}

bool mt4QuikConnector_::pricesSent() const { return stringToInt(cstrMessage.substr(cintPosition1stSymbol - 1, 1)) != 0; } // Is it a prices message (with a number of orders in front)? //Lua: return cintType(tonumber(string.substr(self.message, cintPosition1stSymbol, 1))) == "number";  

/*inline*/ bool mt4QuikConnector_::disableObjects() const { return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrDisableOjects; } 

bool mt4QuikConnector_::closePosition() const { return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrClosePosition; }

int mt4QuikConnector_::keyPressedOperation() const { // An operation key is pressed. 
	if (cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrKeyPressedOperation) 
		return getValue(gintLengthOperation);
	else 
		return gintOperationNull;
}

int mt4QuikConnector_::setLots() const { // A Set Lots command ir received. Get the number of lots from it. 
	if (cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrSetLots) return getValue(gintLengthLots);
	else return 0;
}

//bool mt4QuikConnector_::refreshConstants() const { // Refresh the constants. 
//	const int intLengthRefreshConstants = 1; //Unlike messages from MT4 only one symbol is passed from WinAPIInterface.exe by some reason. TO DO: Solve that error.
//	return cstrMessage.substr(cintPosition1stSymbol - 1, intLengthRefreshConstants) == cstrRefreshConstants;
//}

bool mt4QuikConnector_::refreshConstants() const { return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrRefreshConstants; } // Refresh the constants. 


#include "mt4QuikConnector_.h"
using std::string;
#include "functions.h"
using namespace mtqc;
using namespace mtqc::functions;
#include "constants.h"
using namespace mtqc::constants;

/*inline*/ void mt4QuikConnector_::setMessage(string strMessage) { 
	cstrMessage = strMessage; 
} 

// Get the value (price, lots, etc.) after the command prefix. 
int mt4QuikConnector_::getValue(int intLengthValue) const { 
	// The position of the value (price, lots, etc.) after the command prefix.
	int intPositionValue = cintPosition1stSymbol + cintLengthCommand + gintLengthValueSeparator; 
	//Lua->C++: string.sub(strString, intPosition1, intPosition2) -> strString.substr(intPosition1 - 1, intPosition2 - intPosition1)
	return stringToInt( cstrMessage.substr(intPositionValue - 1, intLengthValue) ); 
}

bool mt4QuikConnector_::pricesSent() const { 
	// Is it a prices message (with a number of orders in front)? 
	//Lua: return cintType(tonumber(string.substr(self.message, cintPosition1stSymbol, 1))) == "number";  
	return stringToInt(cstrMessage.substr(cintPosition1stSymbol - 1, 1)) != 0; 
} 

/*inline*/ bool mt4QuikConnector_::disableObjects() const { 
	return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrDisableOjects; 
} 

bool mt4QuikConnector_::closePosition() const { 
	return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrClosePosition; 
}

// An operation key is pressed. 
int mt4QuikConnector_::keyPressedOperation() const { 
	if (cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrKeyPressedOperation) 
		return getValue(gintLengthOperation);
	else 
		return gintOperationNull;
}

// A Set Lots command ir received. Get the number of lots from it. 
int mt4QuikConnector_::setLots() const { 
	if (cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrSetLots) 
		return getValue(gintLengthLots);
	else 
		return 0;
}

// Refresh the constants. 
bool mt4QuikConnector_::refreshConstants() const { 
	return cstrMessage.substr(cintPosition1stSymbol - 1, cintLengthCommand) == cstrRefreshConstants; 
} 

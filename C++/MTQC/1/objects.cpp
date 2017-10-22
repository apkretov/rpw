#include "objects.h"
using std::string;
using std::to_string;
using std::remove_if;
#include <iterator>
#include "messages.h"
#include "functions.h"
//#include "constantsXML.h"
using namespace mtqc;
using namespace mtqc::functions;
#include "switch.h"
#include "constants.h"
using namespace mtqc::constants;
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

//extern const string gstrMsgWrongOrder; //variousConsts
//extern const int gintLengthValueSeparator; 
//extern const string gstrOperations[6];
//extern const int gintLengthPrice;
//extern const int gintLengthOperation;
//extern const double Point; //expertProperties 
//extern const int ResumeRange;
//extern const bool	gblnAllMessages;
//extern constantsXML gobjConstantsXML;
//constexpr int OP_BUY = 0, OP_SELL = 1, OP_BUYLIMIT = 2, OP_SELLLIMIT = 3, OP_BUYSTOP = 4, OP_SELLSTOP = 5; //Copy/pasted for MT4 compatability to make the switch operator work.

objects::objects() : cobjObjectTriggered(nullptr), cstrPricesToDisplay(""), cdblPriceScanned(0)/*KTB , count(0), intCountPending(0)*/ {}

object_SP objects::getObjectTriggered() const { return cobjObjectTriggered; }

void objects::deleteAll() { // Delete all the dynamically created trading objects +
	cobjObjects.clear();
	cobjObjectsActive.clear();
	cobjObjectsPending.clear();
}

//static mtqc::object getObject(int intOperation, double dblPrice, const string& strDescription) { //Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. //#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/ +
mtqc::object objects::getObject(int intOperation, double dblPrice, const string& strDescription) const { //Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. //#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/ +
	mtqc::object objObject(intOperation, dblPrice, strDescription);
	return objObject;
} 

#include /*<type_traits>*/ <boost\type_traits.hpp>	//Boost for Visual C++ Developers @ https://msdn.microsoft.com/en-us/library/aa288739(v=vs.71).aspx //C++11 Standard library equivalent is <type_traits>. //Standard library header <type_traits> @ http://en.cppreference.com/w/cpp/header/type_traits //<type_traits> @ http://www.cplusplus.com/reference/type_traits/ 
#include <cassert>
object_SP objects::add(int intOperation, double dblPrice, const string& strDescription) { //Add a new trading onbject into the collection. Return a pointer to it. +
	boost::shared_ptr<mtqc::object> objObjectSP(new mtqc::object(getObject(intOperation, dblPrice, strDescription))); //Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. //#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/
	static_assert(boost::is_object<mtqc::object>::value, "This must be an object."); //vs. compile-time error: static_assert(std::is_pointer<mtqc::object>::value, "This must be a pointer."); //#9 Ч static_assert и классы свойств @ https://habrahabr.ru/post/182920/ //What is the difference between assert and static_assert? @ http://stackoverflow.com/questions/18210270/what-is-the-difference-between-assert-and-static-assert
	assert(("objObjectSP should never be null!", objObjectSP)); //What is the difference between assert and static_assert? @ http://stackoverflow.com/questions/18210270/what-is-the-difference-between-assert-and-static-assert
	cobjObjects.insert(mapObj_t::value_type(intOperation, objObjectSP));
	if (!objObjectSP->isPending()) cobjObjectsActive.push_back(objObjectSP);
	else cobjObjectsPending.push_back(objObjectSP);
	return objObjectSP;
}

object_SP objects::item(int intOperation) const { // Returns a reference to the mapped value of the element identified with key intOperation. +
	auto ptrObjects = cobjObjects.find(intOperation); //Searches the container for an element with a key equivalent to intOperation and returns an iterator to it if found, otherwise it returns an iterator to map::end. //std::map::find @ http://www.cplusplus.com/reference/map/map/find/
	if (ptrObjects != std::end(cobjObjects)) return ptrObjects->second;
	else return nullptr;	
}

inline int objects::getCount(bool blnPendingInclusive) const { return blnPendingInclusive ? cobjObjects.size() : cobjObjectsActive.size(); } //Get the count of the trading objects inclusive/exclusive the pending once, if any.

void objects::setPricesToDisplay() { // Compile a string with the prices of the active object to be displayed. 
	if (gobjConstantsXML.getAllMessages()) { //Are all the messages shown ?
		cstrPricesToDisplay = "";
		int intCount{};
		//for (object_SP& objOperationActive : cobjObjectsActive) cstrPricesToDisplay = cstrPricesToDisplay + (++intCount > 1 ? ", " : " ") + gstrOperations[objOperationActive->getOperation()] + " " + fncConvert::numberToStringF(objOperationActive->getPrice());
		for (object_SP& objOperationActive : cobjObjectsActive) cstrPricesToDisplay = cstrPricesToDisplay + (++intCount > 1 ? ", " : " ") + gstrOperations[objOperationActive->getOperation()] + " " + numberToStringF(objOperationActive->getPrice());
	}	
}

void objects::set(const string& strPricesForQuik) { // Alternatively to boost performance this can be done with bitwise encoding using binary or hexadecimal numbers. 
	int intPositionCount = 1; //The position of the count in strPricesForQuik
	int intLengthDescription = 1; //The length of the description (e.g. kp, pn etc.).
	cobjObjectTriggered = nullptr;
	deleteAll();
	int intCount = stringToInt(strPricesForQuik.substr(intPositionCount - 1, 1)); //Get the numnber of orders
	if (intCount > 0) {
		int intLengthPricesForQuik = strPricesForQuik.length();
		int intLengthCount = to_string(intCount).length(); //The length of the count.
		int intPositionOpearation1 = intPositionCount + intLengthCount + 1; //The position of trade operation 1.
		for (int i = 1; i <= intCount; i++)	{
			int intPositionOpearation = intPositionOpearation1 + (i - 1) * ((gintLengthOperation + gintLengthValueSeparator) + (gintLengthPrice + gintLengthValueSeparator) + (intLengthDescription + gintLengthValueSeparator)); //The position of a trade operation.
			string strOperation = strPricesForQuik.substr(intPositionOpearation - 1, gintLengthOperation); 		
			int intOperation = stringToInt(static_cast<string&&>(strOperation)); //A trade operation //Practicing with moving rvalue unlike simple: int intOperation = stringToInt(strOperation); //static_cast conversion @ http://en.cppreference.com/w/cpp/language/static_cast //Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
			int intPositionPrice = intPositionOpearation + gintLengthOperation + gintLengthValueSeparator; //The position of the price of the above operation.
			string strPrice = strPricesForQuik.substr(intPositionPrice - 1, gintLengthPrice);
			//double dblPrice = fncConvert::stringToDouble(strPrice); //The price at the this position.
			double dblPrice = stringToDouble(strPrice); //The price at the this position.
			int intPositionDescription = intPositionPrice + gintLengthPrice + gintLengthValueSeparator; //The position of the description of the above operation.
			string strDescription = strPricesForQuik.substr(intPositionDescription - 1, intLengthDescription);
			if (strDescription == string(intLengthDescription, ' ')) strDescription = ""; //Trim a blank description. //Lua: string.rep(" ", intLengthDescription) // Create string with specified number of characters @ http://stackoverflow.com/questions/12483406/create-string-with-specified-number-of-characters
			add(intOperation, dblPrice, strDescription);
			int intPositionPricesToDisplay = intPositionDescription + intLengthDescription + gintLengthValueSeparator;
	}	}
	cdblPriceScanned = 0; //Reset the price last scanned for a trigger object.
	setPricesToDisplay(); // Compile a string with the prices of the active object to be displayed.
}

void objects::scanTriggered(double dblPrice) { //Alternatively the ojbects array can be always full but with dummy minimal or maximal prices instead of missing objects. Then distinguish buy/sell trades and scan only for a respective buy/sell object only 2 istead of all 4. 
	cobjObjectTriggered = nullptr;
	if (dblPrice != cdblPriceScanned) { //Scan for a triggered object, if the new price differs from that scanned before.
		cdblPriceScanned = dblPrice; //Remember the new price scanned.
		for (object_SP objObject : cobjObjectsActive) {
			switch (objObject->getOperation()) {
				case OP_BUYLIMIT:
					if (roundToPts(dblPrice - objObject->getPrice()) <= 0) {
						cobjObjectTriggered = objObject; 
						if (!objObject->isAlert()) return; //This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
					}
					break;
				case OP_SELLLIMIT:
					if (roundToPts(dblPrice - objObject->getPrice()) >= 0) {
						cobjObjectTriggered = objObject; 
						if (!objObject->isAlert()) return; //This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
					}
					break;
				case OP_BUYSTOP:
					if (roundToPts(dblPrice - objObject->getPrice()) > 0) {
						cobjObjectTriggered = objObject; 
						if (!objObject->isAlert()) return; //This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
					}
					break;
				case OP_SELLSTOP:
					if (roundToPts(dblPrice - objObject->getPrice()) < 0) {
						cobjObjectTriggered = objObject; 
						if (!objObject->isAlert()) return; //This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
					}
					break;
}	}	}	}

/*KTB The map active/pending objects container.
void objects::remove(int intOperation) { // Unlike Lua, remove an object from the collection instead of renaming it. The latter functionality is rejected at all. 
	if (!item(intOperation)->isPending()) cintOperationsActive.erase(intOperation); //Erase the pointer to the object deleted.
	else cintOperationsPending.erase(intOperation); //Erase the pointer to the object deleted.
	cobjObjects.erase(intOperation); //Erase the pointer to the object deleted.
}*/
/*KTB The vector active/pending objects container option 1.
void objects::remove(int intOperation) { // Unlike Lua, remove an object from the collection instead of renaming it. The latter functionality is rejected at all. 
	object_SP objObjec = item(intOperation); //Get the object.
	if (objObjec) { //Does it exist?
		if (!objObjec->isPending()) cintOperationsActive.erase( std::remove(cintOperationsActive.begin(), cintOperationsActive.end(), intOperation), cintOperationsActive.end() ); //Erase the pointer to the object deleted.
		else cintOperationsPending.erase( std::remove(cintOperationsPending.begin(), cintOperationsPending.end(), intOperation), cintOperationsPending.end() ); //Erase the pointer to the object deleted.
		cobjObjects.erase(intOperation); //Erase the pointer to the object deleted.
}	}*/
void objects::remove(int intOperation) { // Unlike Lua, remove an object from the collection instead of renaming it. The latter functionality is rejected at all. 
	object_SP objObjec = item(intOperation); //Get the object.
	if (objObjec) { //Does it exist?
		if (!objObjec->isPending()) cobjObjectsActive.erase( std::remove(cobjObjectsActive.begin(), cobjObjectsActive.end(), objObjec), cobjObjectsActive.end() ); //Erase the pointer to the object deleted.
		else cobjObjectsPending.erase( std::remove(cobjObjectsPending.begin(), cobjObjectsPending.end(), objObjec), cobjObjectsPending.end() ); //Erase the pointer to the object deleted.
		cobjObjects.erase(intOperation); //Erase the pointer to the object deleted.
}	}

/*KTB The initial version before cobjObjects/cobjObjectsActive/cobjObjectsPending.
void objects::renameAll(int intOperationSkip, bool blnDisableAll) { //Rename all trade objects except a skipped one to prevent their accidential wrong reuse, unless required. 
	if (blnDisableAll) deleteAll(); //Rename all in the blnDisableAll mode. This part resembles the deleteAll function but is kept distinct from it only for compatability with MT4.
	else { //All the active objects get cancelled.
		mapObj_t objObjectsActiveNew;
		for (auto ptr = cintOperationsActive.begin(); ptr != cintOperationsActive.end(); ptr++) {
			if ((ptr->second->getOperation() == intOperationSkip) || ptr->second->isKept()) objObjectsActiveNew.insert(mapObj_tVT(ptr->first, ptr->second)); //Is this a skipped or a kept object? //Save it in a separate container.
		}
		cintOperationsActive.clear(); //Clear the container off its prior active objects.
		cintOperationsActive.swap(objObjectsActiveNew); //Fill it with the skipped and kept ones.
		for (auto ptr = cintOperationsPending.begin(); ptr != cintOperationsPending.end(); ptr++) { //All the pending objects turn active instead of the prior active ones.
			ptr->second->description = ""; //Clear the pending flag to enable the trading object for a later use.
			cintOperationsActive.insert(mapObj_tVT(ptr->first, ptr->second)); //All the pending objects turn active instead of the prior active ones.
		}
		cintOperationsPending.clear(); //Clear the container because all the pending objects have got active.
}	}*/
/*KTB The version with cobjObjects/cobjObjectsActive/cobjObjectsPending.
void objects::renameAll(int intOperationSkip, bool blnDisableAll) { //Rename all trade objects except a skipped one to prevent their accidential wrong reuse, unless required. 
	if (blnDisableAll) deleteAll(); //Rename all in the blnDisableAll mode. This part resembles the deleteAll function but is kept distinct from it only for compatability with MT4.
	else { //All the active objects get cancelled.
		cobjObjects.clear(); //Clear the general map.
		for (auto& sttObjectActive : cintOperationsActive) { //Save skipped and kept objects in the general container.
			if ((sttObjectActive.second->getOperation() == intOperationSkip) || sttObjectActive.second->isKept()) cobjObjects.insert(sttObjectActive); 
		}
		cintOperationsActive.clear(); //Clear the container off its prior active objects.
		for (auto& sttObjectPending : cintOperationsPending) { //All the pending objects turn active instead of the prior active ones. Save them in the general container.
			sttObjectPending.second->description = ""; //Clear the pending flag to enable the trading object for a later use.
			cobjObjects.insert(sttObjectPending);
		}
		cintOperationsPending.clear(); //Clear the container because all the pending objects have got active.
		for (auto& sttObject : cobjObjects) cintOperationsActive.insert(sttObject); //Turn all the objects active.
}	}*/
void objects::renameAll(int intOperationSkip, bool blnDisableAll) { //Rename all trade objects except a skipped one to prevent their accidential wrong reuse, unless required. 
	if (blnDisableAll) deleteAll(); //Rename all in the blnDisableAll mode. This part resembles the deleteAll function but is kept distinct from it only for compatability with MT4.
	else { //All the active objects except skipped and kept get cancelled.
		cobjObjects.clear();
		cobjObjectsActive.erase( remove_if( cobjObjectsActive.begin(), cobjObjectsActive.end(), [&intOperationSkip](object_SP ptr){ return ptr->getOperation() != intOperationSkip && !ptr->isKept(); } ), cobjObjectsActive.end() ); //Save skipped and kept objects. //lambda function.
		if (!cobjObjectsPending.empty())	{ //Are there pending objects?
			std::for_each(cobjObjectsPending.begin(), cobjObjectsPending.end(), [](object_SP ptr) { ptr->setDescription(""); }); //lambda function.
			std::move(cobjObjectsPending.begin(), cobjObjectsPending.end(), std::back_inserter(cobjObjectsActive));
			cobjObjectsPending.clear(); //Clear the container because all the pending objects have got active.
		} 
		for (auto ptr : cobjObjectsActive) cobjObjects.insert(mapObj_t::value_type(ptr->getOperation(), ptr));
}	}

void objects::displayPrices(const string& strOpenClose, bool blnNoObjects) const { // Dispay the prices of all the trade objectes. If there is none don't display anyting. 
	if (getCount(false) > 0) { //Objects exclusive pending.
		if (gobjConstantsXML.getAllMessages()) messages::message(strOpenClose + ":" + cstrPricesToDisplay); //Are there active objects (non-pending)?
	}else if (blnNoObjects) messages::message("No objects.");
}

object_SP objects::createResuming() { //Create a resuming trade object on closing the triggered object with a resume flag. 
	object_SP objObjectResuming{}; //Introducing C++11 Brace-Initialization //int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519
	if (cobjObjectTriggered->getOperation() > OP_SELLLIMIT) messages::message(gstrMsgWrongOrder + " Only positions closed by limit orders can be resumed!"); //OP_SELLLIMIT=3. Is it OP_BUYSTOP=4 or OP_SELLSTOP=5?
	else {
		//int intOperationResuming = BUYtoSELL(fncConvert::LIMITSTOPtoBUYSELL(cobjObjectTriggered->getOperation())) + OP_BUYSTOP; //Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
		int intOperationResuming = BUYtoSELL(LIMITSTOPtoBUYSELL(cobjObjectTriggered->getOperation())) + OP_BUYSTOP; //Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
		////double dblPriceResuming = cobjObjectTriggered->getPrice() + ResumeRange * ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) * Point ); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
		//double dblPriceResuming = cobjObjectTriggered->getPrice() + gobjConstantsXML.getResumeRange() * ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) * Point ); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
#ifndef BLN_TRADE_SR
		double dblPriceResuming = cobjObjectTriggered->getPrice() + gobjConstantsXML.getResumeRange() * ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) * gobjConstantsXML.getFuturesPoint() ); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
#else
		double dblPriceResuming = cobjObjectTriggered->getPrice() + gobjConstantsXML.getResumeRange() * ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) * gobjConstantsXML.getFuturesPoint() ); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
#endif
		object_SP objObjectExisting = item(intOperationResuming); //Prevent name collision between an existing and newly created object.
		if (!objObjectExisting) objObjectResuming = add(intOperationResuming, dblPriceResuming, ""); //Does not an object with the same trade operation as a resuming one exist? Add one.
		else { //An object with the same trade operation as a resuming one exists.
			if (objObjectExisting->isPending()) objObjectExisting->setDescription(""); //Has it been pending? //The resuming object will not be pending.
			messages::message("Object " + to_string(objObjectExisting->getOperation()) + " renamed!");
			objObjectResuming = objObjectExisting;
		}
		cobjObjectTriggered->setDescription(""); //Clear the description of the triggered trade object to prevent its accidential wrong reuse.
	}
	return objObjectResuming;
}

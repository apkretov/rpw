#include "objects.h"

using std::string;
using std::to_string;
using std::remove_if;

#include <iterator>

#include "messages.h"

#include "functions.h"
using namespace mtqc;
using namespace mtqc::functions;

#include "switch.h"

#include "constants.h"
using namespace mtqc::constants;

#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

objects::objects() : cobjObjectTriggered(nullptr), cstrPricesToDisplay(""), cdblPriceScanned(0)/*KTB , count(0), intCountPending(0)*/ {}

object_SP objects::getObjectTriggered() const { return cobjObjectTriggered; }

void objects::deleteAll() { // Delete all the dynamically created trading objects +
	cobjObjects.clear();
	cobjObjectsActive.clear();
	cobjObjectsPending.clear();
}

//Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. 
//#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/
mtqc::object objects::getObject(int intOperation, double dblPrice, const string& strDescription) const { 
	mtqc::object objObject(intOperation, dblPrice, strDescription);
	return objObject;
} 

//Boost for Visual C++ Developers @ https://msdn.microsoft.com/en-us/library/aa288739(v=vs.71).aspx 
//C++11 Standard library equivalent is <type_traits>. //Standard library header <type_traits> @ http://en.cppreference.com/w/cpp/header/type_traits 
//<type_traits> @ http://www.cplusplus.com/reference/type_traits/ 
#include /*<type_traits>*/ <boost\type_traits.hpp>	
#include <cassert>

//Add a new trading onbject into the collection. Return a pointer to it. +
object_SP objects::add(int intOperation, double dblPrice, const string& strDescription) { 
	//Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. 
	//#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/
	boost::shared_ptr<mtqc::object> objObjectSP(new mtqc::object(getObject(intOperation, dblPrice, strDescription))); 
	
	//vs. compile-time error: static_assert(std::is_pointer<mtqc::object>::value, "This must be a pointer."); 
	//#9 Ч static_assert и классы свойств @ https://habrahabr.ru/post/182920/ 
	//What is the difference between assert and static_assert? @ http://stackoverflow.com/questions/18210270/what-is-the-difference-between-assert-and-static-assert
	static_assert(boost::is_object<mtqc::object>::value, "This must be an object."); 
	
	//What is the difference between assert and static_assert? @ http://stackoverflow.com/questions/18210270/what-is-the-difference-between-assert-and-static-assert
	assert(("objObjectSP should never be null!", objObjectSP)); 
	cobjObjects.insert(mapObj_t::value_type(intOperation, objObjectSP));
	
	if (!objObjectSP->isPending()) 
		cobjObjectsActive.push_back(objObjectSP);
	else 
		cobjObjectsPending.push_back(objObjectSP);
	
	return objObjectSP;
}

// Returns a reference to the mapped value of the element identified with key intOperation. +
object_SP objects::item(int intOperation) const { 
	//Searches the container for an element with a key equivalent to intOperation and returns an iterator to it if found, otherwise it returns an iterator to map::end. 
	//std::map::find @ http://www.cplusplus.com/reference/map/map/find/
	auto ptrObjects = cobjObjects.find(intOperation); 

	if (ptrObjects != std::end(cobjObjects)) 
		return ptrObjects->second;
	else 
		return nullptr;
}

//Get the count of the trading objects inclusive/exclusive the pending once, if any.
inline int objects::getCount(bool blnPendingInclusive) const { 
	return blnPendingInclusive ? cobjObjects.size() : cobjObjectsActive.size(); 
} 

// Compile a string with the prices of the active object to be displayed. 
void objects::setPricesToDisplay() { 
	if (gobjConstantsXML.getAllMessages()) { //Are all the messages shown ?
		cstrPricesToDisplay = "";
		int intCount{};
		for (object_SP& objOperationActive : cobjObjectsActive) 
			cstrPricesToDisplay = cstrPricesToDisplay 
				+ (++intCount > 1 ? ", " : " ") 
				+ gstrOperations[objOperationActive->getOperation()] + " " 
				+ numberToStringF(objOperationActive->getPrice());
	}
}

// Alternatively to boost performance this can be done with bitwise encoding using binary or hexadecimal numbers. 
void objects::set(const string& strPricesForQuik) { 
	//The position of the count in strPricesForQuik
	int intPositionCount = 1; 
	//The length of the description (e.g. kp, pn etc.).
	int intLengthDescription = 1; 
	
	cobjObjectTriggered = nullptr;
	deleteAll();

	//Get the numnber of orders
	int intCount = stringToInt(strPricesForQuik.substr(intPositionCount - 1, 1)); 
	
	if (intCount > 0) {
		int intLengthPricesForQuik = strPricesForQuik.length();
		int intLengthCount = to_string(intCount).length(); //The length of the count.
		int intPositionOpearation1 = intPositionCount + intLengthCount + 1; //The position of trade operation 1.
	
		for (int i = 1; i <= intCount; i++)	{
			//The position of a trade operation.
			int intPositionOpearation = intPositionOpearation1 
				+ (i - 1) 
				* ((gintLengthOperation + gintLengthValueSeparator) 
					+ (gintLengthPrice + gintLengthValueSeparator) 
					+ (intLengthDescription + gintLengthValueSeparator)
				); 

			string strOperation = strPricesForQuik.substr(intPositionOpearation - 1, gintLengthOperation); 		
			
			//A trade operation 
			//Practicing with moving rvalue unlike simple: int intOperation = stringToInt(strOperation); 
			//static_cast conversion @ http://en.cppreference.com/w/cpp/language/static_cast 
			//Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
			int intOperation = stringToInt(static_cast<string&&>(strOperation)); 
			
			//The position of the price of the above operation.
			int intPositionPrice = intPositionOpearation + gintLengthOperation + gintLengthValueSeparator; 
			string strPrice = strPricesForQuik.substr(intPositionPrice - 1, gintLengthPrice);
			//The price at the this position.
			double dblPrice = stringToDouble(strPrice); 
			
			//The position of the description of the above operation.
			int intPositionDescription = intPositionPrice + gintLengthPrice + gintLengthValueSeparator; 
			string strDescription = strPricesForQuik.substr(intPositionDescription - 1, intLengthDescription);
			
			//Trim a blank description. 
			//Lua: string.rep(" ", intLengthDescription) 
			// Create string with specified number of characters @ http://stackoverflow.com/questions/12483406/create-string-with-specified-number-of-characters
			if (strDescription == string(intLengthDescription, ' ')) 
				strDescription = ""; 
			
			add(intOperation, dblPrice, strDescription);
			int intPositionPricesToDisplay = intPositionDescription + intLengthDescription + gintLengthValueSeparator;
		}	
	}
	//Reset the price last scanned for a trigger object.
	cdblPriceScanned = 0; 
	// Compile a string with the prices of the active object to be displayed.
	setPricesToDisplay(); 
}

//Alternatively the ojbects array can be always full but with dummy minimal or maximal prices instead of missing objects. Then distinguish buy/sell trades and 
//scan only for a respective buy/sell object only 2 istead of all 4. 
void objects::scanTriggered(double dblPrice) { 
	cobjObjectTriggered = nullptr;
	//Scan for a triggered object, if the new price differs from that scanned before.
	if (dblPrice != cdblPriceScanned) { 
		//Remember the new price scanned.
		cdblPriceScanned = dblPrice; 
		for (object_SP objObject : cobjObjectsActive) {
			switch (objObject->getOperation()) {
				case OP_BUYLIMIT:
					if (roundToPts(dblPrice - objObject->getPrice()) <= 0) {
						cobjObjectTriggered = objObject; 
						//This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
						if (!objObject->isAlert()) 
							return; 
					}
					break;
				case OP_SELLLIMIT:
					if (roundToPts(dblPrice - objObject->getPrice()) >= 0) {
						cobjObjectTriggered = objObject; 
						//This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
						if (!objObject->isAlert()) 
							return; 
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

// Unlike Lua, remove an object from the collection instead of renaming it. The latter functionality is rejected at all. 
void objects::remove(int intOperation) { 
	//Get the object.
	object_SP objObjec = item(intOperation); 
	
	//Does it exist?
	if (objObjec) { 
		//Erase the pointer to the object deleted.
		if (!objObjec->isPending()) 
			cobjObjectsActive.erase( std::remove(cobjObjectsActive.begin(), cobjObjectsActive.end(), objObjec), cobjObjectsActive.end() ); 
		else //Erase the pointer to the object deleted.
			cobjObjectsPending.erase( std::remove(cobjObjectsPending.begin(), cobjObjectsPending.end(), objObjec), cobjObjectsPending.end() ); 
		//Erase the pointer to the object deleted.
		cobjObjects.erase(intOperation); 
	}	
}

//Rename all trade objects except a skipped one to prevent their accidential wrong reuse, unless required. 
void objects::renameAll(int intOperationSkip, bool blnDisableAll) { 
	//Rename all in the blnDisableAll mode. This part resembles the deleteAll function but is kept distinct from it only for compatability with MT4.
	if (blnDisableAll) deleteAll(); 
	else { //All the active objects except skipped and kept get cancelled.
		cobjObjects.clear();

		//Save skipped and kept objects. //lambda function.
		cobjObjectsActive.erase( 
			remove_if( cobjObjectsActive.begin(), 
				cobjObjectsActive.end(), 
				[&intOperationSkip](object_SP ptr){ return ptr->getOperation() != intOperationSkip && !ptr->isKept(); } 
			), 
			cobjObjectsActive.end() 
		); 
		
		//Are there pending objects?
		if (!cobjObjectsPending.empty())	{ 
			//lambda function.
			std::for_each( cobjObjectsPending.begin(), cobjObjectsPending.end(), [](object_SP ptr) { ptr->setDescription(""); } ); 
			std::move(cobjObjectsPending.begin(), cobjObjectsPending.end(), std::back_inserter(cobjObjectsActive));
			//Clear the container because all the pending objects have got active.
			cobjObjectsPending.clear(); 
		} 

		for (auto ptr : cobjObjectsActive) 
			cobjObjects.insert(mapObj_t::value_type(ptr->getOperation(), ptr));
	}
}

// Dispay the prices of all the trade objectes. If there is none don't display anyting. 
void objects::displayPrices(const string& strOpenClose, bool blnNoObjects) const { 
	//Objects exclusive pending.
	if (getCount(false) > 0) { 
		//Are there active objects (non-pending)?
		if (gobjConstantsXML.getAllMessages()) 
			messages::message(strOpenClose + ":" + cstrPricesToDisplay); 
	} 
	else if (blnNoObjects) 
		messages::message("No objects.");
}

//Create a resuming trade object on closing the triggered object with a resume flag. 
object_SP objects::createResuming() { 
	//Introducing C++11 Brace-Initialization 
	//int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519
	object_SP objObjectResuming{}; 
	
	//OP_SELLLIMIT=3. Is it OP_BUYSTOP=4 or OP_SELLSTOP=5?
	if (cobjObjectTriggered->getOperation() > OP_SELLLIMIT) 
		messages::message(gstrMsgWrongOrder + " Only positions closed by limit orders can be resumed!"); 
	else {
		//Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
		int intOperationResuming = BUYtoSELL(LIMITSTOPtoBUYSELL(cobjObjectTriggered->getOperation())) + OP_BUYSTOP; 

		#ifndef BLN_TRADE_SR
			//Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
			double dblPriceResuming = cobjObjectTriggered->getPrice() 
				+ gobjConstantsXML.getResumeRange() 
				* ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) 
					* gobjConstantsXML.getFuturesPoint() ); 
		#else 
			//Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
			double dblPriceResuming = cobjObjectTriggered->getPrice() 
				+ gobjConstantsXML.getResumeRange() 
				* ( (cobjObjectTriggered->getOperation() == OP_BUYLIMIT ? -1 : 1) 
					* gobjConstantsXML.getFuturesPoint() );
		#endif
		
		//Prevent name collision between an existing and newly created object.
		object_SP objObjectExisting = item(intOperationResuming); 
		
		//Does not an object with the same trade operation as a resuming one exist? Add one.
		if (!objObjectExisting) 
			objObjectResuming = add(intOperationResuming, dblPriceResuming, ""); 
		else { //An object with the same trade operation as a resuming one exists.
			//Has it been pending? 
			if (objObjectExisting->isPending()) 
				//The resuming object will not be pending.
				objObjectExisting->setDescription(""); 
			messages::message("Object " + to_string(objObjectExisting->getOperation()) + " renamed!");
			objObjectResuming = objObjectExisting;
		}
		
		//Clear the description of the triggered trade object to prevent its accidential wrong reuse.
		cobjObjectTriggered->setDescription(""); 
	}
	return objObjectResuming;
}
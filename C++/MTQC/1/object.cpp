#include "object.h"
using std::string;
#include "functions.h"
using namespace mtqc::functions;

namespace mtqc {
	object::object(int intOperation, double dblPrice, string strDescription) :
		cintOperation(intOperation),
		cdblPrice(dblPrice),
		cstrDescription(strDescription)
	{}

	//Move constructor. //Resume
	//Practicing with rvalue and move consturctor despite originally this operation was implemented more efficiently. 
	//#10 Ч семантика перемещени€ @ https://habrahabr.ru/post/182920/ 
	//Move constructors @ http://en.cppreference.com/w/cpp/language/move_constructor 
	object::object(object&& objObject) :
		cintOperation(objObject.getOperation()),
		cdblPrice(objObject.getPrice()),
		cstrDescription(std::move(objObject.getDescription()))
	{}

	void object::KTB_setTrade(bool blnTrade) { //Set the trade flag. //TO DO: Bitwise flagging is suspended due to a time constraint. Resume its development when necessary.
		if (blnTrade) { //Set to true is equvalent to prvevious decription clearing.
			setDescription(""); //Clear the decription according to the prior logic.
			cchrFlag |= cchrFlagTrade; //Set the trade flag. //RESUME //Turning individual bits on @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
		}
		else
			cchrFlag &= ~cchrFlagTrade; //Reset the trade flag. //Turning individual bits off @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
	}

	inline int object::getOperation() const {
		return cintOperation;
	}

	inline double object::getPrice() const {
		return cdblPrice;
	}

	inline string object::getDescription() const {
		return cstrDescription;
	}

	/*inline*/ void object::setDescription(const string& strDescription) {
		cstrDescription = strDescription;
	}

	int object::getOperationBuySell() const {
		return LIMITSTOPtoBUYSELL(getOperation());
	}

	bool object::isKept() const {
		return getDescription() == "k";
	}

	bool object::isPending() const {
		return getDescription() == "p";
	}

	bool object::isResuming() const {
		return getDescription() == "m";
	}

	bool object::isReversing() const {
		return getDescription() == "r";
	}

	bool object::isAlert() const {
		return getDescription() == "a";
	}
}

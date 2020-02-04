#pragma once
#include "object.h"
#include <map>

namespace mtqc {

	typedef boost::shared_ptr<mtqc::object> object_SP;
	typedef std::map<int, object_SP> mapObj_t;

	class objects {
		mapObj_t cobjObjects;
		std::vector<object_SP> cobjObjectsActive, cobjObjectsPending;
		object_SP cobjObjectTriggered;
		double cdblPriceScanned; //The price last scanned for a trigger object.
		std::string cstrPricesToDisplay;
		mtqc::object getObject(int intOperation, double dblPrice, const std::string& strDescription) const;
		void deleteAll();
		object_SP add(int intOperation, double dblPrice, const std::string& strDescription);
		object_SP item (int intOperation) const;

	public:
		objects();

		object_SP getObjectTriggered() const;
		int getCount(bool blnPendingInclusive) const;
		void setPricesToDisplay();
		void set(const std::string& strPricesForQuik);
		void scanTriggered(double dblPrice);
		void remove(int intOperation);
		void renameAll(int intOperationSkip, bool blnDisableAll);
		void displayPrices(const std::string& strOpenClose, bool blnNoObjects) const;
		object_SP createResuming();
	};
}
#pragma once

#include <boost\weak_ptr.hpp>
#include "datetime.h"
#include "candlesByIndex.h"

namespace mtqc {

	class time { //Consider using std::tm @ http://en.cppreference.com/w/cpp/chrono/c/tm
		//KTB datetime cobjDatetime;
		//KTB const candlesByIndex* const cptrCandlesByIndex;
		const boost::weak_ptr<candlesByIndex> cptrCandlesByIndex;

	public:
		//KTB time(const candlesByIndex* const ptrCandlesByIndex);
		time(boost::weak_ptr<candlesByIndex> ptrCandlesByIndex);
		//KTB void setTime(datetime& objDatetime) { cobjDatetime = objDatetime; }
		datetime operator[](int intShift) const; //Intorduced for MT4 compatability.
	};	
}
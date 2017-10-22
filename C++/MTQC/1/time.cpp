#include "time.h"

namespace mtqc {
	//KTB time::time(const candlesByIndex* const ptrCandlesByIndex) : cptrCandlesByIndex(ptrCandlesByIndex) {}
	time::time(boost::weak_ptr<candlesByIndex> ptrCandlesByIndex) 
		: cptrCandlesByIndex(ptrCandlesByIndex) 
	{}

	//KTB datetime time::operator[](int intShift) const { return cobjDatetime; } //Intorduced for MT4 compatability. +

	//Intorduced for MT4 compatability.
	datetime time::operator[](int intShift) const {
		//Make sure the outer pointer is currently valid.
		if (!cptrCandlesByIndex.expired()) 
			return cptrCandlesByIndex.lock()->getDatetime(intShift); 
		else 
			return datetime();
	} 
}
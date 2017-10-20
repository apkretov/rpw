#include "time.h"

namespace mtqc {
	//KTB time::time(const candlesByIndex* const ptrCandlesByIndex) : cptrCandlesByIndex(ptrCandlesByIndex) {}
	time::time(boost::weak_ptr<candlesByIndex> ptrCandlesByIndex) : cptrCandlesByIndex(ptrCandlesByIndex) { }

	//KTB datetime time::operator[](int intShift) const { return cobjDatetime; } //Intorduced for MT4 compatability. +

	datetime time::operator[](int intShift) const { //Intorduced for MT4 compatability. +
		if (!cptrCandlesByIndex.expired()) return cptrCandlesByIndex.lock()->getDatetime(intShift); //Make sure the outer pointer is currently valid.
		else return datetime();
	} 
}
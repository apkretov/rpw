#property strict

#ifndef BB_MQH
#define BB_MQH

#include "switch.mqh"

#ifdef REGRESSION

class BB {
	bool cblnNarrowed;
public:
	BB() : cblnNarrowed(false) {}
	
	bool getNarrowed() const {
		return cblnNarrowed;
	}
	
	void setNarrowed(bool blnNarrowed) {
		cblnNarrowed = blnNarrowed;
	}
};

#endif //REGRESSION

#endif //BB_MQH
#pragma once
#include "chartProperties.h"

namespace mtqc {
	class indicator : public chartProperties {
	public:
		virtual double getSave(int intIdx) = 0;
};	}
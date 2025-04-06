#pragma once

#include "Adaptee.h"
#include "Target.h"

class Adapter : public Target, Adaptee { 
public:
	void request() {}
};
#ifndef GLOBALS_H
#define GLOBALS_H
#include "stdafx.h"
#pragma once

class globals { //global variables kept in MetaTrader as GlobalVariables
public:
	globals(void);
	double LastLots; //The last values kept by MetaTrader's globals.
	int LastOrder;
	int ClosePositions; //The Close All Positions flag.
};
#endif
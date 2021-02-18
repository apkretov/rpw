#include "stdafx.h"
#include <string>

enum color {CLR_NONE = 0xFFFFFFFF};
const int OP_BUY = 0, OP_SELL = 1, OP_BUYLIMIT = 2, OP_SELLLIMIT = 3, OP_BUYSTOP = 4, OP_SELLSTOP = 5;
const int MODE_TRADES = 0, MODE_HISTORY = 1, SELECT_BY_POS = 0, SELECT_BY_TICKET = 1;
const int PERIOD_M15 = 15, PERIOD_H1 = 60, PERIOD_H4 = 240; //Timeframes of the charts.
const int PRICE_CLOSE = 0; //Applied price constants.
const int MODE_UPPER = 1, MODE_LOWER = 2; //BB Indicator line identifiers.
const int MODE_SMA = 0, MODE_EMA = 1, MODE_SMMA = 2, MODE_LWMA = 3; //Moving Average calculation methods.
const int Blue = 0, MAGICMA = 20100619;
const int MODE_SPREAD = 13; //Spread value in points.
const string /*int*/ NULL_ = ""/*0*/;
const double Point = 0.0001;
const double Spread = /*0.000*/3; //Spread
const int /*PrecnGBP = 4,*/ Precn2 = 2; //precisions
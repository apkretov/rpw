#pragma once
#include "trade.h"
#include "trend.h"
#include "time.h"

namespace mtqc {
	namespace terminalMT4 { //TO DO: By using iheritance/polimorphism try to unite this class with alg and alligatorEA. As such this namespace can be implemented as a class but made so for MT4 compatibilty.
		//void refreshCandlesByIndex();

		//extern const int OP_BUY; //operations.cpp.
		//extern const int OP_SELL;
		//extern const int OP_BUYLIMIT;
		//extern const int OP_SELLLIMIT;
		//extern const int OP_BUYSTOP;
		//extern const int OP_SELLSTOP;
		//enum enmOperations : int;
		//enum enmOperations : int { OP_BUY, OP_SELL };
		enum enmOperations : int { OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP }; //The enumarator is unscoped for MT4 compatibility.

		extern const int gintIdx0; //constantsAlg.cpp.
		//extern const int MODE_GATORLIPS; 
		//extern const int MODE_GATORTEETH;
		//extern const int MODE_GATORJAW;
		enum enmAlg : int { MODE_GATORLIPS, MODE_GATORTEETH = 2, MODE_GATORJAW = 1 }; //The enumarator is unscoped for MT4 compatibility.

		extern double Bid, Ask; //functionsMT4.cpp
		extern time Time;
	
		ENUM_POINTER_TYPE CheckPointer(const trade* const ptrTrade);
		ENUM_POINTER_TYPE CheckPointer(const alg* const ptrAlg);
		ENUM_POINTER_TYPE CheckPointer(const trend* const ptrTrend);

		double MathRound(double dblValue);
		double MathMax(double a, double b);
		double MathMin(double a, double b);

		double iHigh(int intShift);
		double iLow(int intShift);
		double iClose(int intShift);
		datetime iTime(int intShift);
		int iBars();

		double iAlligator(int intMode, int intShift);

		void Alert(const std::string& strMessage);

		void setCandlesByIndex(lua_State* L, const std::string& strTagPrice, const std::string& strTagAlg, int intCount, int intOffset);
		void OnTick(double dblPrice);
};	}
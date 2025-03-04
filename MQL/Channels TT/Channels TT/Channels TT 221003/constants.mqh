#property strict
#ifndef CONSTANTS_MQH
#define CONSTANTS_MQH

#include "enumerators.mqh"

input enmMagic MagicNumber = _1;
//TO DO: Get it from MTQC Win32Interface not to duplicate it.
input int LotsMax = 2;
input int ResumeRange = 2;
#ifdef TRADE_IN_SMARTX
	input bool SmartX_PresetOrderEntry = false;
	//KTB input bool SmartX_SberAbove = true; //TO DO: More than 4 parameters do not work. Combine blnPresetOrderEntry & blnSberAbove in a bitwise code.
#endif 

input enmActivate Activate = ActivateTimeFrame;
input ENUM_TIMEFRAMES TimeFrameMax = PERIOD_H4;
input string IndicatorSought = "Alligator(13,8,5)";
input bool Sound = true;
input enmTickSteps TickStep = pts50;

#ifdef SIMULATOR
	#define TIME_DELAY "2018.11.22 15:59"
	input string TimeDelay = TIME_DELAY;	
#endif 
#ifdef REGRESSION
		#ifdef SIMULATOR
			input string RegressBegTime = TIME_DELAY;
		#else 
			input string RegressBegTime = "";
		#endif 
	input bool UseClose = true;
	input double StdDevAdjust = 1;
	input int BBPeriod = 21;
#endif 

struct variousConsts { 
   const int idx_1; 
   const int idx0; 
   const int operationNull; 
   const int operationAll;
   const string msgWrongOrder; 
   string formatDecimals;
   const string priceSeparator;
   const int lengthPrice;
   const int lengthLots;   
   const int lengthHrMinSec;
   const string lots;
   const string safetyLock;
   const string flagAlert;
   const string flagRegress;
   const string activateMaximizeRestore;
   const string CtrlVsleep;
	#ifdef REGRESSION
		const string rsiPeakIndic;
		const string rsiPeakChart;
		const string rsiPeakGlobalTester;
	#endif 
	#ifdef SIMULATOR
		const string delay1BeforeSuspense;
		const string delay2AfterSuspense;
		const string timeDelay;
		const string timeActive; 
	#endif
   int KTB_Ticket;
}; 

variousConsts gsttVariousConsts = {
   -1, 
   0, 
   -1, 
   OP_SELLSTOP + 1,
   "Wrong order type!",    
   "",                           
   ",",
   6,
   6,
   2,
   "Lots",
   "SafetyLock",
   "a",
   /*"g"*/"lr",
   "ActivateMaximizeRestore",
   "CtrlVsleep",
	#ifdef REGRESSION
		"RSIPeakIndic",
		"RSIPeakChart",
		"RSIPeakGlobalTester",
	#endif 
	#ifdef SIMULATOR
		"Delay1BeforeSuspense",
		"Delay2AfterSuspense",
		"TimeDelay",
		"TimeActive"
	#endif   
}; 

int Lots = (int)GlobalVariableGet(gsttVariousConsts.lots); //Get the lots saved as a global variable unlike a member one to enable external manipulation.

string gstrOperations[4] = {"bl", "sl", "bs", "ss"};

#endif //CONSTANTS_MQH
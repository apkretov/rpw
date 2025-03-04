#property strict

#include "switch.mqh"

#include <WinUser32.mqh> //This is needed for MessageBox.
#import "MTQC.dll"
   void saveSizePicture(string strPictureName); //Save a picture and make its size actual in Windows Photo Viewer.
   #ifdef TRADE_IN_SMARTX
   	bool placeOrderSX(int intOperation, int intLots, double dblPrice, bool blnPresetOrderEntry/*, KTB bool blnSberAbove*/); // Place an order in SmartX. //TO DO: More than 4 parameters do not work. Combine blnPresetOrderEntry & blnSberAbove in a bitwise code.
		bool cancelOrdersSX(int intOperationsCanceled, bool blnPresetOrderEntry); //Cancel orders in SmartX: all, buys, or sells. Pre-set all the controls, if neceessary (blnPresetOrderEntry), usually the first time an order is sent. Then leave it open for a faster entry w/o the presetting.
   	bool keyPressedOperationSX(int intOperation); //Buy/sell in SmartX.
   #endif
   void altDown(int _); // Press and hold Alt.
   void altUp(int _); // Release Alt.
#import "user32.dll" //It is needed to unselect all selected objects.
   int GetLastActivePopup(int hWnd);
   int GetAncestor(int hWnd, int gaFlags);
   void keybd_event(int bVk, int bScan, int dwFlags, int dwExtraInfo); //http://www.forexfactory.com/showthread.php?t=468143        http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
#import

#include "enumerators.mqh"
#include "functions.mqh"
#include "constants.mqh"
#include "object.mqh"
#include "objects.mqh"
#include "position.mqh"

#ifdef TRADE_IN_QUIK
	#include "mt4QuikConnector.mqh"
#endif
#ifdef REGRESSION
	#include "regress.mqh"
	#include "trend.mqh"
	#include "bb.mqh"
#endif 

#ifdef TRADE_IN_QUIK
	mt4QuikConnector mobjMT4QuikConnector;
#endif 
objects mobjObjects;
position mobjPosition;
#ifdef REGRESSION
	regress* mptrRegress = NULL;
	trend mobjTrend;
	BB mobjBB;
#endif

void setDisplayPause() { 
   mobjObjects.set(); //Reset the objects after the operation.
   mobjObjects.displayPrices(mobjPosition.getTotalnet()); //Dispay the close prices of all the trade objects. If there is none don't display anyting.
   #ifdef TRADE_IN_QUIK
   	mobjMT4QuikConnector.setPaused(true); //After a trade, the price of the triggered object is being changed that triggers a change event. That's why before changing the price the connector is paused to prevent both possible ambiguity in Quik and an unnecessary OS overhead.
   #endif 
}

#ifdef TRADE_IN_SMARTX
	bool cancelUntriggeredOrdersSX(string strOperationSkip = "") { // Cancel all the remaining untriggered (on opening/closing a position) objects, if any.
	   if (mobjObjects.getCount() > 1) { //Are there any other objects apart from the triggered one?
	      for (int i = 0; i < mobjObjects.getCount(); i++) {
	         object* objObject = mobjObjects.each(i);
	         if (objObject != mobjObjects.getObjectTriggered()) { //Skip the triggered object.
	            if (objObject.name != strOperationSkip) { //Is it not a skipped object?
	               if (objObject.getTrade(true)) //Another trade object is available. Stop the loop and cancel all untriggered objects.
	                  return cancelOrdersSX(gsttVariousConsts.operationAll, SmartX_PresetOrderEntry);
	            }
	         }
	      }
	   }
	   return true;
	}
#endif //TRADE_IN_SMARTX

#ifdef REGRESSION
   double rsiGet() {
       const int intPeriod = 7;
       const int intShift = 0;
       return iRSI(NULL, PERIOD_CURRENT, intPeriod, PRICE_CLOSE, intShift);
   }

	bool rsiCloseTradeDo(enmDirec intDirec, double dblRsi, double dblRsiPeakChart, double dblRsiPeakIndic) {
		const double dblStdDevPart = /*1*//*0.5*/0.25; //The part of the StdDev that a bar lenght needs to exceed in order to trade.		
		if ( (Close[0] - dblRsiPeakChart) * intDirec > 0 && (dblRsiPeakIndic - dblRsi) * intDirec > 0 ) { //Is this a divergence? //The encoded logics: (Close[0] > dblRsiPeakChart && dblRsi < dblRsiPeakIndic); (Close[0] < dblRsiPeakChart && dblRsi > dblRsiPeakIndic).
		   if (MathAbs(Close[0] - Open[0]) > (mobjTrend.getBarLengthAvr() + mobjTrend.getBarLengthStdDev() * dblStdDevPart)) { //Trade on a culmination bar that deviates from the mean further longer than the StdDev.
		      keyPressedOperation(intDirec == direcUp ? OP_SELL : OP_BUY); //Sell.
		   	return true;
		   }
		}	
	return false;
	}

	bool rsiCloseTrade() { //Trade to close by RSI. Return true, if traded.
		const int intRsi70 = 70, intRsi30 = 30; //The overbought/oversold zones.
		double dblRsiPeakIndic = GlobalVariableGet(gsttVariousConsts.rsiPeakIndic);
		double dblRsiPeakChart = GlobalVariableGet(gsttVariousConsts.rsiPeakChart);
		if (GlobalVariableGet(gsttVariousConsts.rsiPeakGlobalTester) == 0 || dblRsiPeakIndic == 0 || dblRsiPeakChart == 0) //Has not RSI been set?
			return false; //Exit.
		double dblRsi = rsiGet();
		if (dblRsi > intRsi70) //Is this an up trend?
			return rsiCloseTradeDo(direcUp, dblRsi, dblRsiPeakChart, dblRsiPeakIndic);
		else if(dblRsi < intRsi30) //Is this an oversold zone?
			return rsiCloseTradeDo(direcDown, dblRsi, dblRsiPeakChart, dblRsiPeakIndic);
		return false;
	}
#endif //REGRESSION

void runOpen() { // The open procedure of the run fucntion. 
   mobjObjects.displayPrices(mobjPosition.getTotalnet());
   if (mobjObjects.getObjectTriggered() != NULL) { //Has any trading object triggered?
      if (mobjObjects.getObjectTriggered().getAlert()) {
         alert(mobjPosition.getLabelOpened(), mobjObjects); //Alert and skip opening while doing all the same operations as if it's opening.
         mobjPosition.getLabelOpened().setColourWhite();
         mobjPosition.getLabelClosed().setColourGray(); //Gray it out just in case it may be still displaying a prior close price.
         mobjObjects.getObjectTriggered().rename(); //Rename the trade object to prevent its accidential wrong reuse.
         setDisplayPause();
      } else {
         int intOperation = mobjObjects.getObjectTriggered().getOperationBuySell();
         if (mobjPosition.open(intOperation)) { //Fulfill an operation, unless it's just an alert.
            #ifdef TRADE_IN_SMARTX
               if (!cancelUntriggeredOrdersSX()) // Cancel all the remaining untriggered objects, if any.
                  return;
            #endif 
            mobjObjects.renameAll(false, mobjObjects.getObjectTriggered().name);
            /*if (!KTB_swap(i))*/ mobjObjects.getObjectTriggered().rename(NULL, mobjPosition.getTicket(), mobjPosition.getOpenTime(), mobjPosition.getOpenPrice());  //No swapping? //Rename the trade object to prevent its accidential wrong reuse. //CORRECT IT!
            setDisplayPause();
            #ifdef TRADE_IN_SMARTX
               syncSXOrders(gsttVariousConsts.operationAll); //Syncronise the SmartX orders with the trade objects that remain/appear after the openning.
            #endif 
         }  
      }
   }  
}

void run() { //Trade by managing objects and positions. Refresh objects, unless they've been refreshed right before the function call. 
	#ifdef REGRESSION
		if (rsiCloseTrade()) //No processing, after an RSI closing trade.
			return;
	#endif
   mobjPosition.refresh();
   mobjObjects.scanTriggered(); //Refresh objects.
   if (mobjPosition.getTotalnet() == 0) 
      runOpen(); //Is there no Channels position? Check to open one.
   else { //There is an open position. Check to close it.
      mobjObjects.displayPrices(mobjPosition.getTotalnet());
      if (mobjObjects.getObjectTriggered() != NULL) { //Check to close a Channels position.
         if ( !mobjPosition.matchClosingToOpened(mobjObjects.getObjectTriggered().getOperationBuySell()) ) //Does the closing operation match the open one?
            runOpen(); //This is an additionial opening.
         else { 
            if (mobjObjects.getObjectTriggered().getAlert()) {
               alert(mobjPosition.getLabelClosed(), mobjObjects); //Alert and skip closing while doing all the same operations as if it's closing.
               mobjPosition.getLabelClosed().setColourWhite();
               mobjPosition.getLabelOpened().setColourGray();
               mobjObjects.getObjectTriggered().rename(); //Rename the trade object to prevent its accidential wrong reuse.
               setDisplayPause();
            } else {
               if (mobjPosition.close(false, (mobjObjects.getObjectTriggered().getReversing() ? MathAbs(mobjPosition.getTotalnet()) : Lots))) { //A reversing object closes all the lots opened before.
                  string strOperationSkip = "";
                  if (mobjObjects.getObjectTriggered().getResuming()) { //Is resuming required? 
                     object* objObjectResuming = NULL;
                     objObjectResuming = mobjObjects.createResuming(); //Remember the trade operation index of the opened position.
                     strOperationSkip = objObjectResuming.name;
                  } else if (mobjObjects.getObjectTriggered().getReversing()) { //Is reversing required?
                     RefreshRates();
                     mobjPosition.open(mobjObjects.getObjectTriggered().getOperationBuySell()); //Reverse, i.e. open a position to the same direction as the closing one.
                  }
                  #ifdef TRADE_IN_SMARTX
                     if (!cancelUntriggeredOrdersSX(strOperationSkip)) // Cancel all the remaining untriggered objects, if any.
                        return;
                  #endif 
                  mobjObjects.getObjectTriggered().rename(NULL, mobjPosition.getTicket(), mobjPosition.getCloseTime(), mobjPosition.getClosePrice()); //Rename the trade object to prevent its accidential wrong reuse.
                  mobjObjects.renameAll(false, strOperationSkip); //Rename all trade objects except a skipped one to prevent their accidential wrong reuse.
                  setDisplayPause();
                  #ifdef TRADE_IN_SMARTX
                     syncSXOrders(gsttVariousConsts.operationAll); //Syncronise the SmartX orders with the trade objects that remain/appear after the openning.                  
						  #endif 
               }  
            }  
         }  
      }  
   }  
}

bool isAnyObjectSelected(string& strSingleObject) { // Return true if any object is selected. If there is only one selected return its name. 
   strSingleObject = "";
   int intCount = 0; //The selected objects count.
   for (int i = 0; i < ObjectsTotal(); i++) { //Find selected objects.
      string strObjectName = ObjectName(i);
      graphObject objGraphObject(strObjectName);
      if (objGraphObject.getSelected()) { //Is it selected?
         if (intCount++ == 0) 
            strSingleObject = strObjectName; //Remember the object selected.
         else {
            strSingleObject = "";
            break; //Stop, if more than one object are selected.
         }  
      }  
   }
   return intCount > 0;
}

#ifdef REGRESSION			
	double get_iBands(int intMode, int intShift) { // Calculate the Bollinger Bands indicator.
		const double dblDeviation = 2; //The BB standard deviations.
		const int intBandsShift = 1; //The indicator shift relative to the chart. 
		return iBands(NULL, PERIOD_CURRENT, BBPeriod, dblDeviation, intBandsShift, PRICE_MEDIAN, intMode, intShift);
	}
	
	bool BBSpreadNarrowed() { // Check the spread of the BB, whether it has narrowed down within its period.
		const double dblNarrowThreshold = 1.5; //The narrowing down threshold.
		double dblSpreadMin = 0xFFFFFFFF; //#define INF 0x6FFFFFFF // Not quite infinite, Jul 2029, or 1,879,048,191 // How to initialize a double to the max value ? double VarMax = ???; @ https://www.mql5.com/en/forum/140395
		double dblSpreadMax = 0;
		double dblSpread = 0;
		for (int i = 0; i < BBPeriod; i++) {
		   dblSpread = get_iBands(MODE_UPPER, i) - get_iBands(MODE_LOWER, i);
		   if (dblSpread > dblSpreadMax) //Find the maximum.
		   	dblSpreadMax = dblSpread;
		   if (dblSpread < dblSpreadMin) //Find the mininum.
		   	dblSpreadMin = dblSpread;
		}
		if (dblSpreadMax / dblSpreadMin > dblNarrowThreshold) //Narrowed down enough?
			return true;
		else
			return false;
	}

	double getBBFrac() {/*2*/ // Get the fractal that is the closest to the BB that has been crossed.
		/////////
		return 0;
	}
	
	void setBBObjects() { // Set BB objects to trade.
      if (!mobjBB.getNarrowed()) { //Continue, unless the BB narrowed down before.
	      if (BBSpreadNarrowed()) { messageV("111 The BB has narrowed down within its period!"); //Has the BB narrowed down within its period?			
	      	mobjBB.setNarrowed(true); // Register the BB narrowing.
				/*1*//*if (Close[0] >/< getBBFrac()) { // Has the BB been crossed?
				   ////////
				}*/
			}
		}
	}
	
	bool regressPrepareTrade(enmDirec& intDirec) { // Prepare a regression trade.
	   const string strRegress = "lr"; //The linear regression object name.
	   int intShiftPeak = 0, intShiftBeg = 0;
	   double dblCloseBeg = 0;
		datetime dtmRegressBegTime = 0;
	   	   	   
	   if (RegressBegTime == "") { //Check the regression begin time. Delete the regression object, if the time has been removed.
	      if (mptrRegress != NULL) { //Delete the regression object first, if any.
	         delete mptrRegress;
	         mptrRegress = NULL;
			}
			return false;
		} else {
			dtmRegressBegTime = StringToTime(RegressBegTime);
			if (Time[0] <= dtmRegressBegTime) //Exit, if the regression begin time has not come yet.
				return false;
		}
	   
	   intShiftBeg = iBarShift(NULL, PERIOD_CURRENT, dtmRegressBegTime); //The bar at the regression indicator's beginning. //Get the regression trend direction and the peak.
	   dblCloseBeg = Close[intShiftBeg]; //The close price at the regression indicator's beginning.
	   if (dblCloseBeg < Close[0]) { //Is this an up trend?
	   	intDirec = direcUp;
			intShiftPeak = iHighest(NULL, PERIOD_CURRENT, MODE_CLOSE, intShiftBeg + 1); //The bar of the highest close price.
	   } else { //This is a down trend.
	   	intDirec = direcDown;
			intShiftPeak = iLowest(NULL, PERIOD_CURRENT, MODE_CLOSE, intShiftBeg + 1); //The bar of the lowest close price.
	   }
	   
		if (mptrRegress == NULL) //Create a regression object. This is needed right after the regression begin time has got been set.
	      mptrRegress = new regress(strRegress, dtmRegressBegTime, Time[intShiftPeak]);
		else { //Extend the regression object to the peak.
			if (mptrRegress.getTime2() != Time[intShiftPeak]) //Move the regression object, only if its anchor point is not at the current time (prevent unnecessary computations).
				mptrRegress.setTime2(Time[intShiftPeak]);
		}
	   if (Close[0] < mptrRegress.getSup() || Close[0] > mptrRegress.getRes()) { //Exit, if the price is outside 1 StdDev. 
	   	return false;
	   } else
	   	return true;
	}
	
	void setRegressObjects() { // Place/move trade objects alongside a linear regression.	   
	   enmDirec intDirec = direcFlat;
	   double dblConfIntervShift = 0, dblPriceStop = 0;
	   int intOperation = -1;
	   if (!regressPrepareTrade(intDirec)) // Prepare a regression trade.
	   	return;
	   	
	   if (StdDevAdjust != 1) //The confidence interval shift. Omit its computing, unless necessary.
	   	dblConfIntervShift = (mptrRegress.getRes() - mptrRegress.getLR()) * (1 - StdDevAdjust); 
	   if (intDirec == direcUp) { //Place/move exit stop orders in the opposite direction to the regression trend.
	 	   dblPriceStop = mptrRegress.getSup() + dblConfIntervShift; //Invert the price for the confidence interval.
	      intOperation = OP_SELL + OP_BUYLIMIT;
	   } else {
	      dblPriceStop = mptrRegress.getRes() - dblConfIntervShift; //Invert the price for the confidence interval.
	      intOperation = OP_BUY + OP_BUYLIMIT;
	   }
	   
	   object* objObject = mobjObjects.item(gstrOperations[intOperation]); // Move or create a regression trade object.
	   if (objObject != NULL) { //Does an object with such a name exist? 
	      objObject.setPriceHLineArrow(dblPriceStop); //Move it.
	   } else { //There is no regression object yet. Create one.
	      graphObject objGraphObject(gstrOperations[intOperation], StringToTime(RegressBegTime), dblPriceStop);
	      //OFF objGraphObject.setDescription(gsttVariousConsts.flagAlert);
	   }
	}	
#endif //REGRESSION

void setMessageRun() { // Set an object, pass a message to Quik, and run the program. 
	#ifdef REGRESSION
   	if (mptrRegress != NULL)
   		mobjTrend.setBarLength(StringToTime(RegressBegTime), mptrRegress.getTime2());
   	setRegressObjects();
   #endif 
   mobjObjects.set();
   #ifdef TRADE_IN_QUIK
   	mobjMT4QuikConnector.passMessageV(mobjObjects.getPricesForQuik()); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may change the objects on closing by reversing/resuming.
   #endif 
   run();
}

#ifdef SIMULATOR
	void delay() {
	   const string strSuspend = "sus";
	   const int intMultiplicator = 250000;
	   long lngDelay = (long)GlobalVariableGet(gsttVariousConsts.delay1BeforeSuspense) * intMultiplicator;
	   if (ObjectFind(strSuspend) == 0) {
	      if (Time[0] >= ObjectGet(strSuspend, OBJPROP_TIME1)) 
	         lngDelay = (long)GlobalVariableGet(gsttVariousConsts.delay2AfterSuspense) * intMultiplicator;
	   } else if (Time[0] >= MathMin(StringToTime(TimeDelay), GlobalVariableGet(gsttVariousConsts.timeDelay))) 
	      lngDelay = (long)GlobalVariableGet(gsttVariousConsts.delay2AfterSuspense) * intMultiplicator;
	   for (long i = 0; i < lngDelay; ++i);	   
	}
	
	void simulatorOnTick() {
	   static datetime dtmM1priorTime;
	   datetime dtmTimeM1 = Time[0];
	   if (dtmTimeM1 > dtmM1priorTime) { //has a new bar opened? //This code seems similar to if (mobjObjects.getTimeSet() == Time[gsttVariousConsts.idx0]) in OnTick().
	      dtmM1priorTime = dtmTimeM1; //remember the current bar openning time for the future
	      GlobalVariableSet(gsttVariousConsts.timeActive, Time[0]);
	      //OFF Comment("Time[0]: ", Time[0], "   long: ", (long)GlobalVariableGet(gsttVariousConsts.timeActive));
	   }  
	   delay();
	}
	
	void simulatorOnInit() {
	   const int intDelay1BeforeSuspense = 0;
	   const int intDelay2AfterSuspense = /*1000*//*50*/10;
	   GlobalVariableTemp(gsttVariousConsts.delay1BeforeSuspense);
	   GlobalVariableSet(gsttVariousConsts.delay1BeforeSuspense, intDelay1BeforeSuspense);
	   GlobalVariableTemp(gsttVariousConsts.delay2AfterSuspense);
	   GlobalVariableSet(gsttVariousConsts.delay2AfterSuspense, intDelay2AfterSuspense);
	   GlobalVariableTemp(gsttVariousConsts.timeDelay);
	   GlobalVariableSet(gsttVariousConsts.timeDelay, StringToTime(TimeDelay));
	   GlobalVariableTemp(gsttVariousConsts.timeActive);
	}
#endif //SIMULATOR

void OnTick() {
	#ifdef SIMULATOR
		simulatorOnTick();
	#endif 
   if (mobjObjects.getTimeSet() == Time[gsttVariousConsts.idx0]) {
      #ifdef REGRESSION
      	setRegressObjects();
      #endif 
      run(); //Call only run() within each given bar.
   } else { //The time the setMessageRun() has been called before is less than the current bar's time.
      #ifdef REGRESSION
      	setBBObjects(); // Set BB objects to trade.
      #endif
      mobjObjects.setTimeSet(Time[gsttVariousConsts.idx0]); //Remember the time when setMessageRun() is being called.
      setMessageRun();
   }  
}

void enableObjectCreateDeleteEvents(ENUM_CHART_PROPERTY_INTEGER intCreateDelete) { // Enables the mode of sending messages concerning the event of a graphic object creation to all mql4 applications on the chart. 
   ResetLastError();
   if (!ChartSetInteger(0, intCreateDelete, true)) 
      Alert(__FUNCTION__ + ", Error Code = ", GetLastError()); // Enables the mode of sending messages concerning the event of a graphic object creation/deletion to all mql4 applications on the chart. 
}

void renameGraphObjects() { // Rename all the graph objects whose names are an operation. 
   for (int i = 0; i < ArraySize(gstrOperations); i++) {
      string strName = gstrOperations[i];
      if (ObjectFind(strName) == 0) { //Is there a graph object with an operation name?
         graphObject objGraphObject(strName);
         objGraphObject.rename_(StringConcatenate(strName, anticollisionAffix()));
      }  
   }  
}

#ifdef TRADE_IN_SMARTX
	bool closePositionSX() { // Close an open position in SmartX, if any.
	   if (mobjPosition.getTotalnet() > 0) //Is it a buy position? Close it by selling.
	      return keyPressedOperationSX(OP_SELL); //IMPORTANT: To generate a correct closing buy/sell operation keep the EA's total net syncronised with SmartX! TO DO: Program a function in SmartCOM similar to closePosition() in MT4QuikConnector.cpp.
	   else if(mobjPosition.getTotalnet() < 0) //Is it a sell position? Close it by buying.
	      return keyPressedOperationSX(OP_BUY); //IMPORTANT: To generate a correct closing buy/sell operation keep the EA's total net syncronised with SmartX! TO DO: Program a function in SmartCOM similar to closePosition() in MT4QuikConnector.cpp.      
	   else
	      return true;
	}
#endif //TRADE_IN_SMARTX

void reset() { // A full reset: reset the advisor and close a position, if any. 
      #ifdef TRADE_IN_QUIK
Print("111 reset: mobjMT4QuikConnector.disableObjects()");
      	mobjMT4QuikConnector.disableObjects(); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may call cause a CHARTEVENT_OBJECT_CHANGE evern or another one.      
      #endif 
      #ifdef TRADE_IN_SMARTX //Cancel all orders in SmartX.
         if (!cancelOrdersSX(gsttVariousConsts.operationAll, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
            return;
      #endif 
      mobjObjects.renameAll(true);
      mobjObjects.set(); //Reset the objects after the operation.
      mobjPosition.refresh();
      mobjPosition.getLabelOpened().setDescription("");
      mobjPosition.getLabelClosed().setDescription("");
      #ifdef TRADE_IN_QUIK
      	mobjMT4QuikConnector.closePosition(); //TO DO: Pass this command to Quik after a short pause unlike the two commands at a millisecond. The second command will not be executed in Quik. //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may call cause a CHARTEVENT_OBJECT_CHANGE evern or another one.      	
      #endif 
      #ifdef TRADE_IN_SMARTX
         if (!closePositionSX()) //Close an open position in SmartX, if any.
            return;
      #endif 
      if (mobjPosition.getTicket() >= 0) //Is there a Channels position in MT4 to be closed?
         mobjPosition.close(true, Lots); 
      renameGraphObjects(); //Rename all the graph objects whose names are trading.
      messageV(""); //Clear the comment line.
}

bool confirmOperation(string strMessage) { // Conffirm an operation with a message box, if the safety lock is enabled. 
   if (GlobalVariableGet(gsttVariousConsts.safetyLock) == 0) 
      return true; //The safety lock is off, no confirmation is needed.
   else 
      return MessageBox(strMessage, StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_YESNOCANCEL | MB_ICONQUESTION) == IDYES;
}

bool closePosition() { // Close an open position, if any.
   mobjPosition.refresh();
   if (mobjPosition.getTicket() < 0) //Is there no Channels position to be closed?
      return false;
   else { 
      if (confirmOperation("Close the open position?")) { //Close the open position?
         #ifdef TRADE_IN_QUIK
         	mobjMT4QuikConnector.closePosition(); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may call cause a CHARTEVENT_OBJECT_CHANGE evern or another one.
         #endif 
         #ifdef TRADE_IN_SMARTX
            if (!closePositionSX()) //Close an open position in SmartX, if any.
               return false;
         #endif 
         mobjPosition.close(true, MathAbs(mobjPosition.getTotalnet()));
         playSound();
      }
      return true;
   }  
}

void disableObjects() { // Disable all the objects and close a position, if any. The function is distinct just to keep the programme similar to the QLua counterpart. 
   #ifdef TRADE_IN_QUIK
   	mobjMT4QuikConnector.disableObjects(); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may call cause a CHARTEVENT_OBJECT_CHANGE evern or another one.
   #endif
   #ifdef TRADE_IN_SMARTX //Cancel all orders in SmartX.
      if (!cancelOrdersSX(gsttVariousConsts.operationAll, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
         return;
   #endif 
   mobjObjects.renameAll(true);
   mobjObjects.set(); //Reset the objects after the operation.
   messageV("Objects disabled");
}

#ifdef TRADE_IN_SMARTX
	double convertToSXPrice(int intOperation, double dblPrice) { //Convert an EA stop order price to SmartX's. Unlike MTQC, do it here because in MTQC double to char conversion does not work properly in this case.
	   switch(intOperation) {
	      case OP_BUYSTOP:
	        dblPrice += Point;
	        break;
	      case OP_SELLSTOP:
	          dblPrice -= Point;
	      break;
	   }
	   return dblPrice;
	}
	
	void messageSXOrderNotPlaced() {
	   MessageBox("The order has not been placed in SmartX!", StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_ICONWARNING);
	}
	
	bool placeOrderSXDo(object* objObject) { //Place an order in SmartX.
	   double dblPriceSX = convertToSXPrice(objObject.getOperationInt(), objObject.getPrice()); //Convert an EA stop order price to SmartX's.
	   if (!(objObject.getReversing())) { //Place a trade/resuming order in SmartX.
	      if (!placeOrderSX(objObject.getOperationInt(), Lots, dblPriceSX, SmartX_PresetOrderEntry/*KTB , SmartX_SberAbove*/)) {
	         messageSXOrderNotPlaced();
	         return false;
	      }
	   } 
	   if (objObject.getResuming()) { //Place a resuming order in SmartX.
	      int intOperationResuming = resumingOperation(objObject.getOperationInt()); //Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
	      double dblPriceResuming = resumingPrice(objObject.getOperationInt(), objObject.getPrice()); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
	      double dblPriceResumingSX = convertToSXPrice(intOperationResuming, dblPriceResuming); //Convert an EA stop order price to SmartX's.
	      if ( placeOrderSX(intOperationResuming, Lots, dblPriceResumingSX, SmartX_PresetOrderEntry/*KTB , SmartX_SberAbove*/) )
	         return true;      
	   } else if (objObject.getReversing()) { //Place a reversing order in SmartX.
	      if ( placeOrderSX(objObject.getOperationInt(), MathAbs(mobjPosition.getTotalnet()) + Lots, dblPriceSX, SmartX_PresetOrderEntry/*KTB, SmartX_SberAbove*/) ) // A reversing order closes all lots opened before and opens another one to a reversal direction.
	         return true;
	   } else
	      return true; 
	   messageSXOrderNotPlaced();
	   return false;   
	}
	
	bool syncSXOrders(int intOperationsCanceled) { //Syncronise the SmartX orders with the trade objects. intOperationsCanceled must be gsttVariousConsts.operationAll/OP_BUY/OP_SELL.
	   for (int i = 0; i < mobjObjects.getCount(); i++) { //Sincronise.
	      object* objObject = mobjObjects.each(i);
	      if (objObject.getTrade(true)) { //Only trade objects.
	         if (intOperationsCanceled != gsttVariousConsts.operationAll) { //Only buy/sell orders have been canceled before?
	            if ( LIMITSTOPtoBUYSELL(objObject.getOperationInt()) == intOperationsCanceled ) { //Place only buy/sell orders.
	               if (!placeOrderSXDo(objObject)) { //Place an order in SmartX.
	                  return false;
	               }
	            }
	         } else { //All orders have been canceled before. Place all.
	            if (!placeOrderSXDo(objObject)) //Place an order in SmartX.
	               return false;
	         }
	      }
	   }
	   return true;
	}
#endif //TRADE_IN_SMARTX

void keyPressedEsc() { // Esc pressed to unselect all objects / disable them / close position. 
   string strSingleObject;
   if (isAnyObjectSelected(strSingleObject)) {
      #ifdef TRADE_IN_SMARTX //If trading in SmartX and a single object is selected check to syncronise it with the orders in SmartX.
         if (strSingleObject != "") { //Contunue, if only one object is selected.
            object* objObject = mobjObjects.item(strSingleObject);
            if (objObject != NULL) { //Does an object with such a name exist?
               if (objObject.getMoving()) { //Is this a trade object that has been moved? 
                  objObject.setTrade(); //Unflag it moving.
                  int intOperationsCanceled = LIMITSTOPtoBUYSELL(objObject.getOperationInt());
                  if (!cancelOrdersSX(intOperationsCanceled, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
                     return;
                  if (!syncSXOrders(intOperationsCanceled)) //Syncronise the SmartX orders with the trade objects.
                     return; 
                  setMessageRun(); //And reset the objects.
               }
            }
         }
      #endif 
      postMessage(wmEsc); //Is any object selected to be unselected? //Графики -> Объекты -> Снять все выделения @ http://ruforum.mt5.com/threads/892-arhiv-mql4-besplatnoe-napisanie-programm?p=10823666&viewfull=1 and @ http://forum.mql4.com/ru/9807
   } else if (mobjObjects.getCount() > 0) { //Is there any object to be disabled?
      disableObjects();
   } else if (!closePosition()) //Close an open position, if any, or otherwise run a full reset.
      reset(); 
}

void restoreWindow() { // Restore an MDI-child widnow maximised by pressing Alt+NumMinus, Enter. +------------------------------------------------------------------+
   keybd_event(keyNumMinus, 0x9e, 0 , 0); //Press.
   keybd_event(keyEnter, 0, 0, 0);
}

bool containsIndicator(long lngChartID, string strIndicatorName) { // Does a chart contain an indicator on the main chart subwindow? 
   const int intSubWindow = 0; //Look up the indicarot on the main chart subwindow only.
   for (int i = 0; i < ChartIndicatorsTotal(lngChartID, intSubWindow); i++) { //Look up the indicarot on the main chart subwindow only sub_window of ChartIndicatorsTotal = 0.
      if (ChartIndicatorName(lngChartID, intSubWindow, i) == strIndicatorName) return true; //Is this the indicator sought?
   }
   return false;
}

bool activateIndicatorTF(int& intPeriodNext, long& lngChartNext) { // To activate indicator containing vs. maxiimal TF charts?  +------------------------------------------------------------------+
   static bool blnContainsIndicator = containsIndicator(ChartID(), IndicatorSought); //Does the current chart contain the indicator sought? 
   switch (Activate) {
      case ActivateIndicator:
         if (intPeriodNext <= TimeFrameMax) { //Is the timeframe smaller or equal to the maximal one needed?
            if (containsIndicator(lngChartNext, IndicatorSought) != blnContainsIndicator) 
               return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
         }
         break;
      case ActivateTimeFrame: {
         static int intDiffTarget = (TimeFrameMax - Period()) * (-1); //The difference between the current and the maximal period. //The target difference, i.e. the negative to the current.      
         if (TimeFrameMax - intPeriodNext < intDiffTarget) { //Is the timeframe smaller or equal to the maximal one needed?
            if (containsIndicator(lngChartNext, IndicatorSought) == blnContainsIndicator) 
               return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
         }  
      }  
   }
   return false; 
}

void activateCharts() { //Activate or switch the daily-intraday time frame windows or indicator containing windows back and forth. This is the ActivateCharts.mq4 sctrips built-in to the EA. The code is built-in because the scripts' short-cut (Alt+D/F) do not work due to overlapping the AutoIt automatic Alt holding.
   const int intLimit = 100;
   long lngChartNext; // variables for chart ID
   long lngChartPrior = ChartFirst();
   long lngChartCurrPeriod = 0; //The variable for a chart with the current chart's period.
   int intPeriodCurr = Period(); //Remember the period (time frame) of current chart.
   int i = 0;
   
   altDown(0); // Press and hold Alt to restore the windows' size to normal at the end.     
   while (i < intLimit) { // We have certainly not more than 100 open charts
      lngChartNext = ChartNext(lngChartPrior); // Get the new chart ID by using the previous chart ID
      if (lngChartNext < 0) 
         break; // Have reached the end of the chart list
      int intPeriodNext = ChartPeriod(lngChartNext); //The period of the next chart.
      if (activateIndicatorTF(intPeriodNext, lngChartNext)) { // To activate indicator containing vs. maxiimal TF charts?
         showWindow(lngChartNext, showMaximized); //Show that window.
         if (intPeriodNext == intPeriodCurr) lngChartCurrPeriod = lngChartNext; //Remember the chart with the initially current chart's period.
      }
      lngChartPrior = lngChartNext; // Let's save the current chart ID for the ChartNext()
      i++; // Do not forget to increase the counter
   }  
   showWindow(lngChartCurrPeriod, showNormal); //Show the chart with the initially current chart's period.
   restoreWindow(); // Restore an MDI-child widnow maximised by pressing Alt+NumMinus, Enter. 
   altUp(0); // Release Alt.
}

void refreshEA() { // F5 pressed to refresh. 
   if ( MessageBox("Refresh the expert advisor?\nCAUTION: An operation might get triggered in Quik!", StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_YESNOCANCEL | MB_ICONEXCLAMATION) == IDYES ) 
      setMessageRun();
}

void keyPressedOperationOpen(int intOperation) { // The open procedure of the keyPressedOperation fucntion. 
   if (confirmOperation("Open a position?")) { //Open a position?
      #ifdef TRADE_IN_QUIK
      	mobjMT4QuikConnector.keyPressedOperation(intOperation); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may change the objects on closing by reversing/resuming.
      #endif 
      #ifdef TRADE_IN_SMARTX
         if (!keyPressedOperationSX(intOperation)) //Buy/sell in SmartX.
            return;
      #endif 
      if (mobjPosition.open(intOperation)) { //Open a buy position.
         playSound();
         #ifdef TRADE_IN_SMARTX
            if (!cancelUntriggeredOrdersSX()) // Cancel all the remaining untriggered objects, if any.
               return;
         #endif 
         mobjObjects.renameAll(false);
         mobjObjects.set(); //Reset the objects after the operation.
         #ifdef TRADE_IN_SMARTX
            syncSXOrders(gsttVariousConsts.operationAll); //Syncronise the SmartX orders with the trade objects that remain/appear after the openning.         
         #endif 
      }
   }  
}

void keyPressedOperation(int intOperation) { // KeyArrowUp/KeyB/KeyArrowDown/KeyS pressed to buy or sell. 
   mobjPosition.refresh();
   if (mobjPosition.getTicket() < 0) //Is there no Channels position? 
      keyPressedOperationOpen(intOperation); 
   else { //Check to close a Channels position.
		#ifdef TRADE_IN_QUIK
      	mobjMT4QuikConnector.keyPressedOperation(intOperation); //Important: first pass object prices to Quik and then run the expert advisor in MT4 becuase the latter may change the objects on closing by reversing/resuming.      
      #endif 
      if (!mobjPosition.matchClosingToOpened(intOperation)) 
         keyPressedOperationOpen(intOperation); //The open procedure of the keyPressedOperation function.
      else { //Does the closing operation match the open one?
         if (confirmOperation("Close the open position?")) { //Close the open position?
            #ifdef TRADE_IN_SMARTX
               if (!keyPressedOperationSX(intOperation)) //Buy/sell in SmartX.
                  return;
            #endif 
            if (mobjPosition.close(false, Lots)) { //Has a position been closed?  //Reset the objects.
               mobjObjects.renameAll(false);
               playSound();
               mobjObjects.set(); //Reset the objects after the operation.
               #ifdef TRADE_IN_SMARTX
                  syncSXOrders(gsttVariousConsts.operationAll); //Syncronise the SmartX orders with the trade objects that remain/appear after the openning.
               #endif 
            }
         }  
      }  
   }  
}

bool cancelSelectedOrders(int& intOperationsSelected) { // Cancel all selected trade objects whose orders have been placed in SmartX. 
   bool blnBuysSelected = false; //The flags to press either Cancel All or Cansel Buys/Sells button on SmartX.
   bool blnSellsSelected = false;
   for (int i = 0; !(blnBuysSelected && blnSellsSelected) && i < mobjObjects.getCount(); i++) { //A for-each loop till the last object or until defining that there are bouth buy/sell selected trade objects (blnBuysSelected && blnSellsSelected).
      object* objObject = mobjObjects.each(i);
      if (objObject.getTrade() || objObject.getKept()) { //Is it a trade object?
         if (objObject.getSelected()) { //Is it selected?
            if (LIMITSTOPtoBUYSELL(objObject.getOperationInt()) == OP_BUY) //Remember its operation.
               blnBuysSelected = true;
            else
               blnSellsSelected = true;
         }
      }
   } 
   if (blnBuysSelected && blnSellsSelected) { //Cancel all orders.
      intOperationsSelected = gsttVariousConsts.operationAll;
      return true;
   } else if (blnBuysSelected) { //Cancel only buy orders.
      intOperationsSelected = OP_BUY;
      return true;
   } else if (blnSellsSelected) { //Cancel only sell orders.
      intOperationsSelected = OP_SELL;
      return true;
   } else 
      return true; //No action but return true to signal no failure in the procedure.
}

void deleteSelectedObjects() { //Delete selected objects by pressing the Del key. The Del key lets restore the objects deleted by pressing Ctrl+Z. IMPORTANT: The restored trade objects are not passed to SmartX.
   int intOperationsSelected = gsttVariousConsts.operationNull;
   #ifdef TRADE_IN_SMARTX //Trading in SmartX?
      if (cancelSelectedOrders(intOperationsSelected)) { //Cancel all selected trade objects whose orders have been placed in SmartX.
         keybd_event(keyDel, 0, 0, 0); //Delete first and then start syncronising.
         if (intOperationsSelected != gsttVariousConsts.operationNull) { //Are there any trade objects selected to syncronise the orders in SmartX?
            if (cancelOrdersSX(intOperationsSelected, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
               syncSXOrders(intOperationsSelected);
         }
      }
   #else 
      keybd_event(keyDel, 0, 0, 0);
   #endif 
}

bool moveObject(int intKeyNavigation) { // Move a selected object. If an existing operational object is being moved up/down reset the objects. //TO DO: Use ObjectMove @ https://docs.mql4.com/objects/objectmove
   string strObjectMoved;
   isAnyObjectSelected(strObjectMoved);
   if (strObjectMoved != "") { //Contunue, if only one object is selected.
      graphObject objGraphObjectMoved(strObjectMoved);
      if (objGraphObjectMoved.isMovable()) { //Conitnue, if the object movable.
         bool blnResetObjects = false;
         switch (intKeyNavigation) {
            case keyArrowUp: case keyArrowDown: //Move a selected object up/down.
               keybd_event(keyEnd, 0, 0, 0); //Return the chart back by simulating an End key stroke after pressing a navigation key.
            case keyR: case keyF: 
               if (objGraphObjectMoved.isOperational()) { //If an existing operational object is being moved up/down, flag to reset the objects.
                  object* objObject = mobjObjects.item(strObjectMoved);
                  if (objObject != NULL) { //Does such an object exist?                     
                     blnResetObjects = true;
                     #ifdef TRADE_IN_SMARTX //If trading in SmartX, flag a trade object moving to syncronise the orders in SmartX.
                        if (objObject.getTrade()) //Move a trade object being flagged moving.
                           objObject.setMoving();
                        else if( objObject.getTrade(true)) { //Move only an alert. For simplicity of the SmartX order sycronisation prevent moving all other flagged objects. //TO DO: Arragne syncronising flagged objects with SmartX orders.
                           MessageBox("A kept, resuming, or reversing object can not be moved because moving is not syncronised with SmartX!\n\nCancel it before moving.", StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_ICONINFORMATION); 
                           return false;
                        }
                     #endif 
                  }
               }
               if (intKeyNavigation == keyArrowUp || intKeyNavigation == keyR) //Move a selected object up.
                  objGraphObjectMoved.moveUp(); 
               else //Move a selected object down.
                  objGraphObjectMoved.moveDown(); 
               if (blnResetObjects)
                  setMessageRun(); //An existing operational object is being moved reset the objects.
               break;
            case keyArrowLeft: //Move a selected object to the left.
               keybd_event(keyEnd, 0, 0, 0); //Return the chart back by simulating an End key stroke after pressing a navigation key.
            case keyA:
               objGraphObjectMoved.moveLeft(); 
               break;
            case keyArrowRight: //Move a selected object to the right.
               keybd_event(keyEnd, 0, 0, 0); //Return the chart back by simulating an End key stroke after pressing a navigation key.
            case keyG:
               objGraphObjectMoved.moveRight(); 
               break;
         }  
      }
      return true;
   }
   return false;
}

int renamedSmartXOperation(const object& objObject) { //Return an operation being renamed that has been placed in SmartX.
   if (objObject.getTrade() || objObject.getKept() || objObject.getReversing()) //Remember the canceled operation to cancel it below.
      return LIMITSTOPtoBUYSELL(objObject.getOperationInt()); //Buy/sell orders are going to get canceled.
   else if (objObject.getResuming())
      return gsttVariousConsts.operationAll; //This is a resuming object. All orders are going to get canceled because a resuming object contributs to bouth buy and sell orders.
   else
      return gsttVariousConsts.operationNull;
   
}

int renameLimitStop(graphObject& objLimitStop, const string& strName) { // Rename a graph object into a buy/sell limit/stop preventing a name collision. If trading in SmartX and a trade object (alarm exclusive) is being renamed return its index.
   int intRenamedOperation = gsttVariousConsts.operationNull;
   object* objObject = mobjObjects.item(strName);
   if (objObject != NULL) { //Prevent name collision between an existing and newly created object.
      if (objObject.getSelected()) //Is the single selected object the target operation itself? No renaming.
         return intRenamedOperation;
      else {
         #ifdef TRADE_IN_SMARTX //Only for SmartX.
            intRenamedOperation = renamedSmartXOperation(objObject);
         #endif 
         objObject.rename(); //Rename it.
      }
   }
   objLimitStop.rename_(strName);
   objLimitStop.setDescription(gsttVariousConsts.flagAlert);
   return intRenamedOperation;
}

void setLimitStop(graphObject& objLimitStop, int intOperation) { // Set an object selected as a buy limit/stop. 
   int intRenamedOperation = gsttVariousConsts.operationNull;
   switch (intOperation) {
      case OP_BUY:
         if (objLimitStop.getPrice() < Bid) 
            intRenamedOperation = renameLimitStop(objLimitStop, gstrOperations[OP_BUYLIMIT - OP_BUYLIMIT]); //Buy limit.
         else 
            intRenamedOperation = renameLimitStop(objLimitStop, gstrOperations[OP_BUYSTOP - OP_BUYLIMIT]); //Buy stop.
         break;
      case OP_SELL:
         if (objLimitStop.getPrice() > Bid) 
            intRenamedOperation = renameLimitStop(objLimitStop, gstrOperations[OP_SELLLIMIT - OP_BUYLIMIT]); //Sell limit.
         else 
            intRenamedOperation = renameLimitStop(objLimitStop, gstrOperations[OP_SELLSTOP - OP_BUYLIMIT]); //Sell stop.
   }
   setMessageRun(); //Refresh the advisor.
   #ifdef TRADE_IN_SMARTX //Only for SmartX.
      if (intRenamedOperation != gsttVariousConsts.operationNull) { //Syncronise the SmartX orders with the trade objects, in required above.
         if (cancelOrdersSX(intRenamedOperation, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
            syncSXOrders(intRenamedOperation);
      }
   #endif 
}

void tradeOrOrder(int intOperation) { // Buy/sell or make a limit/stop order. 
   string strSelected;
   isAnyObjectSelected(strSelected);
   if (strSelected == "") 
      keyPressedOperation(intOperation); //No object selected - buy/sell.
   else {
      graphObject objSelected(strSelected);
      if (objSelected.isOperational()) 
         setLimitStop(objSelected, intOperation); //Is it operational? Set an object selected as a limit/stop.
      else 
         keyPressedOperation(intOperation); //Not operational - buy/sell.
      objSelected.setSelected(false); //Unselect it not to exclude it from a later considaration again.
   }  
}

void flagObject(int intLparam) { // Set the selected object decription to a trade/reversal/pending flag. 
   string strSelected;
   isAnyObjectSelected(strSelected);
   if (strSelected != "") { //Is a sinlge object selected.
      object* objObject = mobjObjects.item(strSelected);
      if (objObject != NULL) { //Does such an object exist?
         bool blnRefresh = false;
         switch(intLparam){
            case keyT: // Set the selected object decription to the trade flag. 
               if (!(objObject.getTrade() || objObject.getKept())) { //Is it a trade object?
                  #ifdef TRADE_IN_SMARTX
                     if (placeOrderSXDo(objObject)) { //Place an order in SmartX.
                        objObject.setTrade();
                        blnRefresh = true;
                     }                      
                  #else 
                     objObject.setTrade();
                     blnRefresh = true;
                  #endif 
               }
               break; 
            case keyK: // Set the selected object decription to the kept flag. 
               if (!objObject.getKept()) { //Do it, if changed.
                  objObject.setKept();
                  blnRefresh = true;
               }                              
               break;
            case keyP: // Set the selected object decription to the pending flag. 
               if (!objObject.getPending()) { //Do it, if changed.
                  objObject.setPending();
                  blnRefresh = true;
               }                              
               break;
            case keyM: // Set the selected object decription to the resuming flag.
               if (!objObject.getResuming()) { //Do it, if changed.
                  if (objObject.setResuming()) { //Flag an object resuming. Check if it is a limit order.
                     #ifdef TRADE_IN_SMARTX //Place a resuming order in SmartX.
                        if (!cancelOrdersSX(gsttVariousConsts.operationAll, SmartX_PresetOrderEntry)) //First cancel the corresponding all orders in SmartX.
                           return;
                        if (!syncSXOrders(gsttVariousConsts.operationAll)) //Syncronise the SmartX orders with the trade objects.
                           return; 
                     #endif 
                     blnRefresh = true;
                  }
               }               
               break; 
            case keyL: // Set the selected object decription to the reversing flag.
               if (!objObject.getReversing()) { //Do it, if changed.
                  objObject.setReversing();
                  #ifdef TRADE_IN_SMARTX //Place a reversing order in SmartX.
                     if (!cancelOrdersSX(gsttVariousConsts.operationAll, SmartX_PresetOrderEntry)) //First cancel the corresponding all orders in SmartX.
                        return;
                     if (!syncSXOrders(gsttVariousConsts.operationAll)) //Syncronise the SmartX orders with the trade objects.
                        return; 
                 	#endif 
                  blnRefresh = true;
               }               
               break; 
         }
         objObject.setSelected(false);
         if (blnRefresh) //Do it, if changed.
            setMessageRun(); //Refresh the advisor.
      }  
   }  
}

void cancelObjectDo(const string& strSelected) { // Implement canceling the seleced object. 
   object* objObject = mobjObjects.item(strSelected);
   if (objObject != NULL) { //Does such an object exist?
      int intCanceledOperation = gsttVariousConsts.operationNull;
      #ifdef TRADE_IN_SMARTX //Only for SmartX.
         intCanceledOperation = renamedSmartXOperation(objObject);
      #endif 
      objObject.rename();
      objObject.setSelected(false);
      setMessageRun(); //Refresh the advisor.
      #ifdef TRADE_IN_SMARTX //Only for SmartX.
         if (intCanceledOperation != gsttVariousConsts.operationNull) { //Syncronise the SmartX orders with the trade objects, in required above.
            if (cancelOrdersSX(intCanceledOperation, SmartX_PresetOrderEntry)) //First cancel the corresponding all/buy/sell orders in SmartX.
               syncSXOrders(intCanceledOperation);
         }
      #endif 
   } else { //Unflag a graphical objcect, if it's operational.
      graphObject objSelected(strSelected);
      if (objSelected.isOperational()) {
         objSelected.setDescription("");
         objSelected.setSelected(false);
      }  
   }  
}

void cancelObject() { // Cancel the seleced object. 
   string strSelected;
   isAnyObjectSelected(strSelected);
   if (strSelected != "") 
      cancelObjectDo(strSelected); //Is only one object selected? // Implement canceling the seleced object.
}

void setLotsV() { //Set lots or a volume flag to an object. 
   string strSelected;
   if (!isAnyObjectSelected(strSelected)) 
      setLots(keyNumSlash); //Is there no object selected?
   else if (strSelected != "") { //Is only one object selected? 
      const string strVolumeFlag = "v"; //The folume flag.
      graphObject objSelected(strSelected);
      if (objSelected.isOperational()) {
         cancelObjectDo(strSelected); // Implement canceling the seleced object.
         objSelected.setDescription(strVolumeFlag); //Is it operational?
      }  
   }  
}

int decodeNumber(int intKey) { // Decode a number from a number key. 
   switch (intKey) {
      case key1: case key1Num: 
         return 1;
      case key2: case key2Num: 
         return 2;
      case key3: case key3Num: 
         return 3;
      case key4: case key4Num: 
         return 4;
      case key5: case key5Num: 
         return 5;
      case key6: case key6Num: 
         return 6;
      case key7: case key7Num: 
         return 7;
      case key8: case key8Num: 
         return 8;
      case key9: case key9Num: 
         return 9;
      default: 
         return 0;
   }  
}

void setLots(int intKey) { // Set the number of the lots to trade within a single transaction. 
   switch (mobjPosition.getLabelLots().getColour()) {
      case clrWhite: //Gray it out to begin to set the colour.
         if (intKey == keyNumSlash) {
            mobjPosition.getLabelLots().setColourGray(); //Gray it out to begin to set the colour.
            mobjPosition.getLabelLots().setDescription(""); //Erase the content of the label to enter a new number of lots from scratch.
         }
         break;
      case clrGray: { //White it out to end to set the colour.
         string strLots = mobjPosition.getLabelLots().getDescription();
         if (intKey != keyNumSlash && intKey != keyEnter)
            mobjPosition.getLabelLots().setDescription( StringConcatenate(strLots, decodeNumber(intKey)) ); //Enter the numbers of the lots.
         else {
            mobjPosition.getLabelLots().setColourWhite(); //White it out to end to set the colour.
            if (strLots == "") 
               mobjPosition.getLabelLots().setDescription(Lots); //Unless entered, fill in the label with the prior number of lots.
            else { //Remember a new number of lots.
               int intLots = (int)strLots;
               if (intLots > LotsMax) { //The entered number of lots should not exeed the maximum.
                  if (intKey == keyEnter) 
                     keybd_event(keyEsc, 0, 0, 0); //Close the Fast Navigation box the Enter key has opened.
                  MessageBox("The number of lots should not exeed the maximum!", StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_ICONEXCLAMATION); 
               } else if (intKey == keyEnter) 
                  keybd_event(keyEsc, 0, 0, 0); //Close the Fast Navigation box the Enter key has opened.
               Lots = intLots;
               GlobalVariableSet(gsttVariousConsts.lots, Lots); //Arrange saving the lots.
               #ifdef TRADE_IN_QUIK
               	mobjMT4QuikConnector.setLots(intLots);
               #endif 
            }  
         }  
      }  
   }  
}

void savePicture() { // Save the chart as a picture. Affix its name with the indicator letter and/or day time frame letter. 
   const ENUM_TIMEFRAMES  intPeriodMax = PERIOD_H4;
   const string strIndicator = "Alligator(13,8,5)"; //The indicator sought that the picture file name will be affixed with.
   const string strDayAffix = " d"; //The day affix.
   
   datetime dtmTimeLocal = TimeLocal();
   string strPictureName = formatInteger(TimeHour(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec) + " " + formatInteger(TimeMinute(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec); //The current hour and the minute.
   strPictureName = StringConcatenate(strPictureName, " ", formatInteger(TimeSeconds(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec)); //Affix it with the seconds.
   if (Period() > intPeriodMax) //Is the timeframe larger than the maximal one needed? 
      StringAdd(strPictureName, strDayAffix); //Affix it with the day affix.
   postMessage(wmSavePicture); //Call the Save as picture menu command.
   keybd_event(keyEnter, 0, 0, 0); //Press Enter in the the Save As Picture dialogue box.
   Sleep((int)GlobalVariableGet(gsttVariousConsts.CtrlVsleep)); //Let the the Save As Picture dialogue box appear.
   saveSizePicture(strPictureName); //Save a picture and make its size actual in Windows Photo Viewer.
}

void login() { // Login to an account using EA @ https://www.mql5.com/en/forum/110932/page2 
   const int intPasswordLengthMax = 8; //The length of the password.
   const int intSleep = 500; //The total time the login dialogue box will be displayed.
   int hterminal = GetAncestor(WindowHandle(Symbol(), Period()), 2);          
   if(hterminal != 0) {
      int hwindow = GetLastActivePopup(hterminal);
      PostMessageA(hwindow, WM_COMMAND, wmLogin, 0); // OR use PostMessageA (hwindow, WM_COMMAND, 0x8A65,-0x30107D); //Open Login dialog window
      if (!IsConnected()) {
         Sleep(intSleep / 2);
         keybd_event(keyEnter, 0, 0, 0); //Press Enter, unless connected, to start connecting.
      }else { //Disconnect.
         int intSleepStep = intSleep / (intPasswordLengthMax + 2); //A single sleep session per disconnecting step to let MT4 digest key strokes.
         Sleep(intSleepStep);
         keybd_event(keyTab, 0, 0, 0); //Naviate to the password textbox.
         for (int i=0; i < intPasswordLengthMax; i++) {
            Sleep(intSleepStep);
            keybd_event(keyDel, 0, 0, 0); //Press Del as many times as the number of symbols in the longest password.
         }
         Sleep(intSleepStep);
         keybd_event(keyEnter, 0, 0, 0); //Press Enter to start disconnecting.
}  }  }

long chartWindowsHandle(long lngChartID) { // Chart window handle (HWND) //Как в скрипте активировать окно с нужным символом? @ https://www.mql5.com/ru/forum/22244 
   long lgnResult = -1; // Prepare the variable to get the property value
   ResetLastError(); // Reset the error value
   if (!ChartGetInteger(lngChartID, CHART_WINDOW_HANDLE, 0, lgnResult)) Print(__FUNCTION__ + ", Error Code = ", GetLastError()); // Receive the property value // Display the error message in Experts journal
   return(lgnResult); // Return the value of the chart property
}

void showWindow(long lngChartID, enmNCmdShow intShow) { ShowWindow( GetParent((int)chartWindowsHandle(lngChartID)), intShow ); } // Show a window. // ShowWindow. 1 - Activates and displays a window. 2 - Activates the window and displays it as a minimized window. 3 - Activates the window and displays it as a maximized window. 

void maximizeOrRestore(enmNCmdShow intShow) { // Maximize or restore the current window. Save the last state. 
  showWindow(ChartID(), intShow); //Show the current window.
  GlobalVariableSet(gsttVariousConsts.activateMaximizeRestore, intShow);
}

void maximizeOrRestoreSwitch() { // Switch maximizing or restoring the current window. Save the last state. 
   switch ((enmNCmdShow)GlobalVariableGet(gsttVariousConsts.activateMaximizeRestore)) {
      case showNormal: 
         maximizeOrRestore(showMaximized); 
         break;
      case showMaximized: 
         maximizeOrRestore(showNormal);
         break;
   }
   keybd_event(keyEnter, 0, 0, 0); //Press Enter before pressing Esc. Otherwise the advisor process Esc as an ordinary Esc resetting (cancels objects, deselects them, etc.). 
   keybd_event(keyEsc, 0, 0, 0); //Close the Fast Navigation box the Space key has opened.
}

void postMessage(enmWM wmCommand) { // The PostMessageA command. 
   PostMessageA(WindowHandle(Symbol(), Period()), WM_COMMAND, wmCommand, 0); 
}

void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam) { 
   int intOperation = gsttVariousConsts.operationNull;
   switch (id) {
      case CHARTEVENT_OBJECT_CREATE: case CHARTEVENT_OBJECT_CHANGE: case CHARTEVENT_OBJECT_DRAG: {
         graphObject objGraphObject(sparam);
         objGraphObject.setPriceRound();
         setMessageRun();
         } 
         break;
      case CHARTEVENT_OBJECT_DELETE:
         #ifdef TRADE_IN_QUIK
	         if (mobjObjects.getCount() == 1)
	            mobjMT4QuikConnector.setPass0(true);
			#endif 
         setMessageRun();
         break;
      case CHARTEVENT_KEYDOWN: {
         int intLparam = (int)lparam;
         switch(intLparam) {
            case keyEsc: //Escape pressed? //Unselect all objects / disable them / close position. 
               keyPressedEsc(); 
               break; 
            case keyArrowUp: case keyArrowDown: case keyR: case keyF: //Move a selected object up/down.
            case keyArrowLeft: case keyArrowRight: case keyA: case keyG: //Move a selected object left/right.
               moveObject(intLparam);
               break; 
            case keyB: 
               tradeOrOrder(OP_BUY); 
               break; //Buy or make a limit/stop order. 
            case keyS: //Sell or make a limit/stop order.  
               tradeOrOrder(OP_SELL); 
               break; 
            case keyT: case keyK: case keyP: case keyM: case keyL: // Set the selected object decription to a trade/reversal/pending/kept flag.
               flagObject(intLparam);
               break;
            case keyC: //Cancel the seleced object. 
               cancelObject(); 
               break; 
            case keyTilde:
               refreshEA();
               break;
            case keyF5:
               activateCharts(); //Activate or switch the daily-intraday time frame windows or indicator containing windows back and forth.
               break;
            case keyD: 
               deleteSelectedObjects(); //Delete selected objects by pressing the Del key. The Del key lets restore the objects deleted by pressing Ctrl+Z. IMPORTANT: The restored trade objects are not passed to SmartX.
               break; 
            case keyNumSlash: 
               setLotsV(); 
               break;
            case keyEnter: 
               setLots(intLparam); 
               break;
            case keyZ: 
               postMessage(wmCrossHair); 
               break;
            case keyQ: 
               postMessage(wmTrend); 
               break;
            case keyW: 
               postMessage(wmHLine); 
               break;
            case keyE: 
               postMessage(wmLeftArrow); 
               break;
            case keyV: 
               postMessage(wmVLine); 
               break;
            case key1: 
               postMessage(wmRectangle); 
               break;
            case key2: 
               postMessage(wmRegression);
               break;
            case keyX: // Save the chart as a picture. 
               savePicture(); 
               break; 
            case keyTab: //Open the login dialogue box.
               login(); 
               break; 
            case keySpace: 
               maximizeOrRestoreSwitch(); 
               break;
            default: 
               //OFF messageV(StringConcatenate("lparam: ", lparam));
               if ( (intLparam >= key0 && intLparam <= key9) || (intLparam >= key0Num && intLparam <= key9Num) ) 
                  setLots(intLparam);
         }  
      }  
   }  
}

void OnInit() {  
   const int intCtrlVsleep = 700;
   if (!GlobalVariableCheck(gsttVariousConsts.lots)) //Arrange saving the lots, unless arranged before.
      GlobalVariableSet(gsttVariousConsts.lots, Lots); 
   if (!GlobalVariableCheck(gsttVariousConsts.safetyLock)) //Arrange saving the safety lock, unless arranged before. 
      GlobalVariableSet(gsttVariousConsts.safetyLock, 1); 
   if (!GlobalVariableCheck(gsttVariousConsts.CtrlVsleep)) 
      GlobalVariableSet(gsttVariousConsts.CtrlVsleep, intCtrlVsleep); 
   if (!GlobalVariableCheck(gsttVariousConsts.activateMaximizeRestore)) 
      GlobalVariableSet(gsttVariousConsts.activateMaximizeRestore, showNormal); //Check/set the last window state.
	#ifdef REGRESSION
	   GlobalVariableTemp(gsttVariousConsts.rsiPeakChart);
	   GlobalVariableTemp(gsttVariousConsts.rsiPeakIndic);
	   GlobalVariableTemp(gsttVariousConsts.rsiPeakGlobalTester);
	   GlobalVariableSet(gsttVariousConsts.rsiPeakChart, 0);
	   GlobalVariableSet(gsttVariousConsts.rsiPeakIndic, 0);
	   GlobalVariableSet(gsttVariousConsts.rsiPeakGlobalTester, 0);
	#endif
   gsttVariousConsts.formatDecimals = StringConcatenate(".", _Digits, "f"); //'".", _Digits' denotes _Digits decimal digits after the decimal point, 'f' denotes a double number type.
   enableObjectCreateDeleteEvents(CHART_EVENT_OBJECT_CREATE); // Enables the mode of sending messages concerning the event of a graphic object creation to all mql4 applications on the chart. 
   enableObjectCreateDeleteEvents(CHART_EVENT_OBJECT_DELETE); // Enables the mode of sending messages concerning the event of a graphic object deletion to all mql4 applications on the chart.    
   mobjObjects.setTimeSet(0);
   setMessageRun();
	#ifdef SIMULATOR
		simulatorOnInit();
	#endif 
}

void OnDeinit(const int reason) { 
	#ifdef REGRESSION
	   if (mptrRegress != NULL) { //Delete the regression object, if any.
	      delete mptrRegress;
	      mptrRegress = NULL;
		}
	#endif
   messageV(""); //Clear any prior comments, if any.
}
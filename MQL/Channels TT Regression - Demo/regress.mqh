#property strict
#ifndef REGRESS_MQH
#define REGRESS_MQH

#include "switch.mqh"
#include "constants.mqh"
#include "functions.mqh"

#ifdef REGRESSION
	class regress {
	   const string cstrObject_name; //The name of the linear regression object.
	   const string cstrObject_nameX; //The name of the linear regression extrapolated trend line.
	   const int cintLine_idLR; //The MetaTrader regression object line indeces.
	   const int cintLine_idRes;
	   const int cintLine_idSup;
	   double cdblStdDev;

		double getPrice1(int intLine_id) const { // Get the values of the regression object point 1 only. Values at Point 2 were 0 in my cases, unless I did something wrong.
			if (ObjectFind(cstrObject_name) == 0) { //Is there an object?
			   return ObjectGetValueByTime(0, cstrObject_name, StringToTime(RegressBegTime), intLine_id);
			} else {
				messageV("""" + cstrObject_name + """ object not found!");
				return 0;
			}
		}
		  
	   double getPrice2() const { // Get point 2 from the custom uLinRegrBuf indicator. Values at Point 2 of the linear regression were 0 in my cases, unless I did something wrong.
	       const string strName = "uLinRegrBuf";
	       const int intModeLR_line = 0;
	       datetime dtmTime1 = (datetime)ObjectGet(cstrObject_name, OBJPROP_TIME1);
	       datetime dtmTime2 = getTime2();
	       int intShift = iBarShift(NULL, PERIOD_CURRENT, dtmTime2);
	       return iCustom(NULL, PERIOD_CURRENT, strName, UseClose, dtmTime1, dtmTime2, intModeLR_line, intShift);
	   }   	   		
		
		void setStdDev() { //The StdDev is the distance between the central regression line and ether a support or resistance.
			cdblStdDev = getPrice1(cintLine_idLR) - getPrice1(cintLine_idSup);
		}
	   
	public:      	   
	   regress(const string& strObject_name, datetime dtmTime1, datetime dtmTime2) :
	      cstrObject_name(strObject_name),
	      cstrObject_nameX(StringConcatenate(cstrObject_name, "x")),
	      cintLine_idLR(0),
	      cintLine_idRes(1),
			cintLine_idSup(2)
	   {			
	   	const int intClr = clrDarkGray; //The colour of the regression object.
	   	const bool blnRay_right = true; //The ray-right property: enable (true) or disable (false) the mode of continuation of the channel's display to the right.
	   	bool blnObjectCreate = false;
			ResetLastError(); //--- reset the error value
			blnObjectCreate = ObjectCreate(0, cstrObject_name, OBJ_REGRESSION, 0, dtmTime1, 0, dtmTime2, 0); //--- create a channel by the given coordinates
			if (blnObjectCreate) {
			   ObjectSetInteger(0, cstrObject_name, OBJPROP_COLOR, intClr); //--- set channel color
			   ObjectSetInteger(0, cstrObject_name, OBJPROP_RAY_RIGHT, blnRay_right); //--- enable (true) or disable (false) the mode of continuation of the channel's display to the right
			   blnObjectCreate = ObjectCreate(0, cstrObject_nameX, OBJ_TREND, 0, dtmTime1, getPrice1(cintLine_idLR), dtmTime2, getPrice2()); //Create a trend line to get extrapolated regression line's value because the regression object does not return values behond its point 2.
			   setStdDev(); // Set the StdDev ONLY AFTER another object has been created (e.g. the extrapolated line above). It gives time for the regression object to react to the calls for its values.
			   if (blnObjectCreate) { // Make the extrapolated line invisible.
			   	ObjectSet(cstrObject_nameX, OBJPROP_COLOR, clrNONE);
			   	ObjectSet(cstrObject_nameX, OBJPROP_SELECTABLE, false);
			   } else
			   	messageV("Failed to create an extrapolated regression line! Error code = " + (string)GetLastError());
			} else
			   messageV("Failed to create a linear regression channel! Error code = " + (string)GetLastError());
	   }

	   ~regress() { //delete the regression objects created.
			if (ObjectFind(cstrObject_name) == 0) //Is there an object?
				ObjectDelete(0, cstrObject_name);
			if (ObjectFind(cstrObject_nameX) == 0) //Is there an object?
				ObjectDelete(0, cstrObject_nameX);				
	   }

	   double getLR() const { // Use the exptrapolated regression line instead of the linear regression to get both intrapolated and extrapolated prices.
	       return ObjectGetValueByShift(cstrObject_nameX, gsttVariousConsts.idx0);
	   }	   
	   
	   double getRes() const {
			return getLR() + cdblStdDev;
	   }

	   double getSup() const {
			return getLR() - cdblStdDev;
	   }	   
	
		datetime getTime2() const {
			return (datetime)ObjectGet(cstrObject_name, OBJPROP_TIME2);
		}
		
		void setTime2(datetime dtmTime2) { // Move anchor point 2.
			const int intPoint_index = 1; //The anchor 2 point index.
			ObjectMove(0, cstrObject_name, intPoint_index, dtmTime2, 0); 
			setStdDev();
			ObjectSet(cstrObject_nameX, OBJPROP_TIME2, dtmTime2);
			ObjectSet(cstrObject_nameX, OBJPROP_PRICE2, getPrice2());
		}
	};
#endif //REGRESSION

#endif //REGRESS_MQH
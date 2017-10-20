#property strict

extern int SignalTeethFarness = 10; 
extern int JawsReverseRange = 3;
extern int BreakEven = 20;
extern double Lots = 0.1;
extern string TimeDelay = "2050.01.01 00:00";

const string mstrDelay = "Delay";
const string mstrDelayLong = "DelayLong";
const int mintIdx0 = 0;
const ENUM_TIMEFRAMES mintPeriodCurrent = PERIOD_CURRENT;

enum enmDirec {direc_down = -1, direc_flat, direc_up/*, direc_trend*/}; //DO NOT CHANGE THE CONSTANTS W/O ADAPTING THE ALGORITHM!!!
enum enmPhases {phase_beginning, phase_signal_appeared, phase_signal_triggered/*, phase_impulse_fixed, phase_impulse_resumed, phase_middle, trade_closed, phase_shifted*/, phase_end};
enum enmAlgStates {alg_flat, alg_crossing, alg_moving_away, alg_ahead_of_dashed_lips};
enum enmFibo {fibo_1 = 1, fibo_3 = 3, fibo_5 = 5, fibo_8 = 8, fibo_13 = 13, fibo_21 = 21, fibo_34 = 34, fibo_55 = 55, fibo_89 = 89};

class chartProperties { //+------------------------------------------------------------------+
protected:
   enmDirec cintDirec;
   ENUM_TIMEFRAMES cintTimeFrame;
public:
   enmDirec getDirec() { return cintDirec; } //+------------------------------------------------------------------+
   virtual enmDirec setGetDirec(int intIdx) = 0;
   virtual enmDirec getSetSaveDirec(int intIdx) = 0;
   //ENUM_TIMEFRAMES time_frame;
   //ENUM_TIMEFRAMES getTimeFrame() { return cintTimeFrame; }
   virtual bool time_frame_shift(ENUM_TIMEFRAMES intTimeFrame); //shift the time frame; return true, if the new time frame works in accordance with the prior one
};

class indicator : public chartProperties { //+------------------------------------------------------------------+
public:
   virtual double getSave(int intIdx) = 0;
};

class indicatorSingleValue : public indicator { //+------------------------------------------------------------------+
protected:
   double cdblValue;
public:
   virtual double setGetValue(int intIdx) = 0;
};

class alligator : public indicator { //+------------------------------------------------------------------+
   private:
      double cdblLips, cdblTeeth, cdblJaws;
      datetime cdtmSignalTime;
      double cdblSignalPrice;
      bool cblnSignalTeethFar;
      void initialise(ENUM_TIMEFRAMES intTimeFrame, int intIdx) {
         cintTimeFrame = intTimeFrame; 
         getSave(intIdx); 
         getSetSaveDirec(intIdx);
      }
   public:
      alligator(ENUM_TIMEFRAMES intTimeFrame, int intIdx) { initialise(intTimeFrame, intIdx); } //Get Alligator values, if the index is defined at the construction stage and get its location to the price. //+------------------------------------------------------------------+
      datetime getSignalTime() { return cdtmSignalTime; } //+------------------------------------------------------------------+
      void setSignalTime(datetime dtmSignalTime) { cdtmSignalTime = dtmSignalTime; } //+------------------------------------------------------------------+
      //double cdblSignalPrice;
      double getSignalPrice() { return cdblSignalPrice; } //+------------------------------------------------------------------+
      void setSignalPrice(double dblSignalPrice) { cdblSignalPrice = dblSignalPrice; } //+------------------------------------------------------------------+
      //bool cblnSignalTeethFar;
      enmDirec setGetDirec(int intIdx) { //the direction is defined based on where any bar prior to the specified one (intIdx) closes: above or below Alligator //+------------------------------------------------------------------+
         enmDirec intDirec = direc_up, intDirecUp = direc_up, intDirecDown = direc_down; //initialise with any direction just not to end up NULL in all of sudden
         int i = intIdx;
         while (i < iBars(NULL, cintTimeFrame)) {
            if (distance_pts(high(i), iClose(NULL, cintTimeFrame, i), intDirecUp) > 0) { //a bar closes above Alligator?
               intDirec = direc_up;
               break; //exit the loop as soon as a first closing outside Alligator occurs
            }else if(distance_pts(low(i), iClose(NULL, cintTimeFrame, i), intDirecDown) > 0) { //a bar closes below Alligator? this solution didn't work out, I didn't check why
               intDirec = direc_down;
               break; //exit the loop as soon as a first closing outside Alligator occurs
            }
            i++;
         }
         return intDirec;
      }
      enmDirec getSetSaveDirec(int intIdx)  { //+------------------------------------------------------------------+
         cintDirec = setGetDirec(intIdx);
         return cintDirec;
      }
      double lips_get( int intIdx) {return iAlligator(NULL, cintTimeFrame, fibo_13, fibo_8, fibo_8, fibo_5, fibo_5, fibo_3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS,  intIdx);}
      double teeth_get(int intIdx) {return iAlligator(NULL, cintTimeFrame, fibo_13, fibo_8, fibo_8, fibo_5, fibo_5, fibo_3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, intIdx);}
      double jaws_get( int intIdx) {return iAlligator(NULL, cintTimeFrame, fibo_13, fibo_8, fibo_8, fibo_5, fibo_5, fibo_3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW,   intIdx);}
      double getSave(int intIdx) { //+------------------------------------------------------------------+
         cdblLips = lips_get(intIdx);
         cdblTeeth = teeth_get(intIdx);
         cdblJaws = jaws_get(intIdx);
         return 0;
      }      
      double high() {return MathMax(cdblLips, MathMax(cdblTeeth, cdblJaws));} //the Alligator highest line value except dashed lips
      double high(int intIdx) {return MathMax(lips_get(intIdx), MathMax(teeth_get(intIdx), jaws_get(intIdx)));} //the Alligator highest line value except dashed lips
      double low() {return MathMin(cdblLips, MathMin(cdblTeeth, cdblJaws));} //the Alligator lowest line value except dashed lips*/
      double low(int intIdx) {return MathMin(lips_get(intIdx), MathMin(teeth_get(intIdx), jaws_get(intIdx)));} //the Alligator lowest line value except dashed lips
      bool time_frame_shift(ENUM_TIMEFRAMES intTimeFrame) { //+------------------------------------------------------------------+
         enmDirec intDirecPrior = cintDirec; //the prior direction
         initialise(intTimeFrame, mintIdx0);
         signalGet();
         return cintDirec * intDirecPrior == 1; //the prior direction remained?
      }
      bool signalGet() { //+------------------------------------------------------------------+
         int i = mintIdx0;
         do {i++;} while (setGetDirec(i) * cintDirec != -1); //an opposite direction from now on?
         do {i--;} while (setGetDirec(i) != cintDirec && i > mintIdx0); //cycle till the favourable direction begins but not beyond the current bar
         if (i == mintIdx0) {
            cdtmSignalTime = 0; //reset a signal time and price to flag no signal
            cdblSignalPrice = 0;
            return false; //the search has reached the current w/o a signal
         } else { //remember the signal
            cdtmSignalTime = iTime(NULL, cintTimeFrame, i); //remember the signal bar
            cdblSignalPrice = cintDirec == direc_up ? iHigh(NULL, cintTimeFrame, i) : iLow(NULL, cintTimeFrame, i);
            return true;
      }  }
      bool signalOvercome() {return distance_pts(cdblSignalPrice, Bid, cintDirec) > 0;} //Return true, if the signal has been overcome.
      bool signalTeethFarGetSave(int intSignalTeethFarness) { //Return true, if the signal is too far from the teeth. +------------------------------------------------------------------+
         if (distance_pts(cdblTeeth, Bid, cintDirec) > intSignalTeethFarness) cblnSignalTeethFar = true; 
         return cblnSignalTeethFar;
      }
};

class trade { //+------------------------------------------------------------------+
   private:
      int cintTicket, cintType;
      string cstrTicket;
      datetime cdtmTimeOpen, cdtmTimeClose; //If order close time is not 0, then the order selected and has been closed and retrieved from the account history. Open and pending orders close time is equal to 0.
      double cdblPriceOpen, cdblStopLoss, cdblTakeProfit, cdblLots;
      bool cblnBEReached;
      int cintSlippage;
      void direc_to_type_bid_ask(enmDirec intDirec, int& intType, double& dblPrice) { //convert direction to cintType and bid/ask +------------------------------------------------------------------+
         switch (intDirec) {
            case direc_up:
               intType = OP_BUY;
               dblPrice = Ask;
               break;
            case direc_down:
               intType = OP_SELL;
               dblPrice = Bid;
      }  }
      void type_to_direc_bid_ask(int intType, enmDirec& intDirec, double& dblPrice) { //convert cintType  to dirction and bid/ask +------------------------------------------------------------------+
         switch (intType) {
            case OP_BUY:
               intDirec = direc_up;
               dblPrice = Ask;
               break;
            case OP_SELL:
               intDirec = direc_down;
               dblPrice = Bid;
      }  }
      bool open(int intType, double dblPrice, double dblLots = 0, double dblStopLoss = 0, double dblTakeProfit = 0) { //+------------------------------------------------------------------+
         const int intFailureFlag = -1;
         const string strComment = "Expert advisor";
         cintTicket = OrderSend(Symbol(), intType, dblLots, dblPrice, cintSlippage, dblStopLoss, dblTakeProfit, strComment/*, cintMagic*/); //Returns number of the cintTicket assigned to the order by the trade server or -1 if it fails.
         if (cintTicket == intFailureFlag)
            return false;
         else {
            cintType = intType;
            cdtmTimeOpen = TimeCurrent();
            cdblPriceOpen = dblPrice; //develop to retrieve an exact open price and time from the history pool
            cdblLots = dblLots;
            return true;
      }  }
   public:
      //int cintTicket, cintType;
      //datetime cdtmTimeOpen, cdtmTimeClose; //If order close time is not 0, then the order selected and has been closed and retrieved from the account history. Open and pending orders close time is equal to 0.
      //double cdblPriceOpen, cdblStopLoss, cdblTakeProfit, cdblLots;
      //bool cblnBEReached;
      bool getBEReached() { return cblnBEReached; } //+------------------------------------------------------------------+
      void setBEReached(bool blnBEReached) { cblnBEReached = cblnBEReached; } //+------------------------------------------------------------------+
      void trade() { //+------------------------------------------------------------------+
         cintSlippage = 10;
         cstrTicket = "Ticket";
         cintTicket = -1; 
         cintType = -1;
      }
      bool open_bid_ask(enmDirec intDirec, double dblLots = 0, double dblStopLoss = 0, double dblTakeProfit = 0) { //+------------------------------------------------------------------+
         int intType;
         double dblPrice;
         direc_to_type_bid_ask(intDirec, intType, dblPrice);
         return open(intType, dblPrice, dblLots, dblStopLoss, dblTakeProfit);
      }
      double getProfit() { //for open orders, it is the current unrealized profit; for closed orders, it is the fixed profit +------------------------------------------------------------------+
         enmDirec intDirec;
         double dblPrice;
         type_to_direc_bid_ask(cintType, intDirec, dblPrice);
         return distance(cdblPriceOpen, dblPrice, intDirec);
      }
      bool close(double dblPrice) { //+------------------------------------------------------------------+
         if (!OrderClose(cintTicket, cdblLots, dblPrice, cintSlippage)) return false;
         else {
            cdtmTimeClose = TimeCurrent(); //develop to retrieve the profit, close price, and close time from the history pool
            return true;
      }  }
      bool close_bid_ask(enmDirec intDirec) { //+------------------------------------------------------------------+
         int intType;
         double dblPrice;
         direc_to_type_bid_ask(intDirec, intType, dblPrice);
         return close(dblPrice);
      }
      void copy(const trade &objTrade) { //+------------------------------------------------------------------+
         cintTicket = objTrade.cintTicket;
         cintType = objTrade.cintType;
         cdtmTimeOpen = objTrade.cdtmTimeOpen;
         cdtmTimeClose = objTrade.cdtmTimeClose;
         cdblPriceOpen = objTrade.cdblPriceOpen;
         cdblStopLoss = objTrade.cdblStopLoss;
         cdblTakeProfit = objTrade.cdblTakeProfit;
         cdblLots = objTrade.cdblLots;
      }
};

class trend : public chartProperties { //+------------------------------------------------------------------+
   private:
      enmPhases cintPhase;
      double cdblPeak; //the highest/lowest price over the trend
      ENUM_TIMEFRAMES cintTimeFrames[4]; //the four time frames involved
      alligator* cobjAlg;
      int cintIdxTFActive; //the current time frame
      trade* cobjTradeActive;
      trade* cobjTradePrior;
      void initialise(ENUM_TIMEFRAMES intTimeFrame) { //+------------------------------------------------------------------+
         cintTimeFrame = intTimeFrame;
         cobjAlg = new alligator(intTimeFrame, mintIdx0);
         cintDirec = cobjAlg.getDirec();         
         cintPhase = phase_beginning;
      }
   public:
      enmPhases getPhase() { return cintPhase; } //+------------------------------------------------------------------+
      void setPhase(enmPhases intPhase) { cintPhase = intPhase; } //+------------------------------------------------------------------+
      //alligator* cobjAlg;
      double alg_GetSave(int intIdx) { return cobjAlg.getSave(intIdx); } //+------------------------------------------------------------------+
      bool alg_SignalGet() { return cobjAlg.signalGet(); } //+------------------------------------------------------------------+
      bool alg_SignalTeethFarGetSave(int intSignalTeethFarness) { return cobjAlg.signalTeethFarGetSave(intSignalTeethFarness); } //+------------------------------------------------------------------+
      datetime alg_GetSignalTime() { return cobjAlg.getSignalTime(); } //+------------------------------------------------------------------+
      //trade* getTradeActive() { return cobjTradeActive; } //+------------------------------------------------------------------+
      bool tradeActive_GetBEReached() { return cobjTradeActive.getBEReached(); } //+------------------------------------------------------------------+
      void tradeActive_SetBEReached(bool blnBEReached) { cobjTradeActive.setBEReached(blnBEReached); } //+------------------------------------------------------------------+
      double tradeActive_GetProfit() { return cobjTradeActive.getProfit(); } //+------------------------------------------------------------------+
            
      void trend(double dblPeak) { //+------------------------------------------------------------------+
         cintTimeFrames[0] = PERIOD_M5;
         cintTimeFrames[1] = PERIOD_M30;
         cintTimeFrames[2] = PERIOD_H1;
         cintTimeFrames[3] = PERIOD_H4;
         cintIdxTFActive = mintIdx0;
         initialise(cintTimeFrames[cintIdxTFActive]);
         cdblPeak = dblPeak;
      }
      
      void ~trend(void) { //delete the parent and child trends, if created +------------------------------------------------------------------+
         if (CheckPointer(cobjTradeActive) == POINTER_DYNAMIC) delete cobjTradeActive;
         if (CheckPointer(cobjTradePrior) == POINTER_DYNAMIC) delete cobjTradePrior;
         if (CheckPointer(cobjAlg) == POINTER_DYNAMIC) delete cobjAlg; //check for POINTER_DYNAMIC just in case for more robustness despite it is unnecessary at the current stage
      }
      
      enmDirec setGetDirec(int intIdx) { return cobjAlg.setGetDirec(intIdx); } //+------------------------------------------------------------------+
      
      enmDirec getSetSaveDirec(int intIdx) { //+------------------------------------------------------------------+
         cintDirec = cobjAlg.getSetSaveDirec(intIdx);
         return cintDirec;
      }
      
      bool direc_reversed() { return distance_pts(cintDirec == direc_up ? cobjAlg.low() : cobjAlg.high(), Bid, cintDirec) < (JawsReverseRange * -1); } //return true, if direction reversed +------------------------------------------------------------------+
      void update_peak(double dblPrice) {if (distance_pts(cdblPeak, dblPrice, cintDirec) > 0) cdblPeak = dblPrice;} //update the current trend peak with the specified price //is a new price behind the current peak (taking into account the trend direction)? +------------------------------------------------------------------+
      
      void trade_open() { //+------------------------------------------------------------------+
         if (cobjAlg.signalOvercome()) { //Has the signal been overcome?
            cobjTradeActive = new trade;
            if (cobjTradeActive.open_bid_ask(cintDirec, Lots)) cintPhase = phase_signal_triggered;
      }  }
      
      bool time_frame_shift() { //+------------------------------------------------------------------+
         if (cintIdxTFActive < ArraySize(cintTimeFrames) - 1) { //Isn't the active time frame the biggest one already?
            if (cobjTradeActive.getProfit() >= 0) { //a profit trade in the old time frame?
               alligator objAlg(cintTimeFrames[cintIdxTFActive + 1], mintIdx0); //watch an appearance of an opposite direction
               if (objAlg.getDirec() == cintDirec) { //is the new time frame direction the same?
                  if (objAlg.signalGet()) { //has a signaled appeared in the new time frame?
                     if (objAlg.signalOvercome()) { //can trade in the new time frame, i.g. signal triggered?
                        datetime dtmSignalTimePrior = cobjAlg.getSignalTime(); //remember the prior signal to use it the shifted time frame //develop: trend_child/parent will contain the prior direction
                        double dblSignalPricePrior = cobjAlg.getSignalPrice();
                        delete cobjAlg;
                        initialise(cintTimeFrames[++cintIdxTFActive]); //Shift the active time frame index and initialise the trend.
                        cobjAlg.setSignalTime(dtmSignalTimePrior); //restore the original signal generated in the prior time frame //develop: trend_child/parent will contain the prior and new time frame signals; it's more robust to remember the new time frame signal in a way
                        cobjAlg.setSignalPrice(dblSignalPricePrior);
                        cintPhase = phase_signal_triggered;
                        return true;
         }  }  }  }  }
         return false;
      }
      
      bool trade_close() { //close a buy/sell position +------------------------------------------------------------------+
         if (!cobjTradeActive.close_bid_ask(cintDirec)) return false; //din't the currently active trade close?
         else { 
            if (CheckPointer(cobjTradePrior) == POINTER_DYNAMIC) delete cobjTradePrior; //delete the previously prior object, if it has been created before and not deleted yet
            cobjTradePrior = new trade; //for more robustness develop to use a prior trade retrieved from the history pool rather than my cobjTradePrior
            cobjTradePrior.copy(cobjTradeActive); //the current trade gets prior and cleared (next line)
            delete cobjTradeActive;
            cintPhase = phase_end; //flag the end of the trend
            return true;
      }  }
};

//+------------------------------------------------------------------+
trend* mobjTrend = NULL;
long mlngCounter = 0;

void message(const string& strMsg) { //+------------------------------------------------------------------+
   Print(strMsg);
   Comment(strMsg);
}

void message_v(string strMsg) { //+------------------------------------------------------------------+
   message(strMsg);
}

int round_to_pts(double dblValue) { //+------------------------------------------------------------------+
   return (int) MathRound(dblValue / Point);
}

double distance(double dblFrom, double dblTo, enmDirec intDirec) { //+------------------------------------------------------------------+
   return (dblTo - dblFrom) * intDirec;
}

int distance_pts(double dblFrom, double dblTo, enmDirec intDirec) { //+------------------------------------------------------------------+
   return round_to_pts((dblTo - dblFrom) * intDirec);
}

void delay() { //+------------------------------------------------------------------+
   long j = 0, lngDelay = (int) GlobalVariableGet(mstrDelay);
   if(Time[mintIdx0] >= StringToTime(TimeDelay)) lngDelay = (long) GlobalVariableGet(mstrDelayLong);
   for (long i=0; i < lngDelay; i++) {j++;}
}

bool delete_old_trend() { //delete the old trend, if a new signal appeared; return true, if deleted +------------------------------------------------------------------+
	static datetime dtmTimePrior; //avoid unnecessary computing at every tick, instead proceed once a bar on its opening
	datetime dtmTime = Time[mintIdx0];
	if (dtmTime > dtmTimePrior) { //has a new bar opened?
		dtmTimePrior = dtmTime; //remember the current bar openning time for the future
		alligator objAlg(mintPeriodCurrent, mintIdx0); //monitore a start of an opposite direction
		if (objAlg.signalGet()) {
			//if (objAlg.getSignalTime() > mobjTrend.cobjAlg.getSignalTime()) {
			if (objAlg.getSignalTime() > mobjTrend.alg_GetSignalTime()) {
				delete mobjTrend;/*5*/ //A new signal appeared? Delete the old trend.
				return true;
	}	}	}
	return false; //not deleted.
}

void OnTick() { //+------------------------------------------------------------------+
   delay();
   if (CheckPointer(mobjTrend) == POINTER_INVALID) mobjTrend = new trend(Bid); //a new trend began; create an object for it, unless available //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend
   //else mobjTrend.cobjAlg.getSave(mintIdx0); //otherwise refresh Alligator
   else mobjTrend.alg_GetSave(mintIdx0); //otherwise refresh Alligator
   switch (mobjTrend.getPhase()) {
      case phase_beginning:
         if (delete_old_trend()) OnTick(); //the old trend has become obsolete; restart the procedure
         else { //trend exists
            //if (mobjTrend.cobjAlg.signalGet()) {
            if (mobjTrend.alg_SignalGet()) {
               //if (!mobjTrend.cobjAlg.signalTeethFarGetSave(SignalTeethFarness)) { //Isn't the signal too far from the teeth?
               if (!mobjTrend.alg_SignalTeethFarGetSave(SignalTeethFarness)) { //Isn't the signal too far from the teeth?
                  //mobjTrend.cintPhase = phase_signal_appeared; //develop: incapsulate flagging this cintPhase into the trend class; currently this cintPhase can be switched either insdie alligator or outside trend
                  mobjTrend.setPhase(phase_signal_appeared); //develop: incapsulate flagging this cintPhase into the trend class; currently this cintPhase can be switched either insdie alligator or outside trend
                  Alert("Alligator signal_appeared!");
                  mobjTrend.trade_open();
         }  }  }
         break; //no signal yet? //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend
      case phase_signal_appeared:
         if (delete_old_trend()) OnTick(); //Has not the old trend become obsolete? Restart the procedure //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend
         mobjTrend.trade_open(); //isn't the signal too far from the teeth, when the signal has appeared?
         break;
      case phase_signal_triggered:
         //if (!mobjTrend.getTradeActive().getBEReached()) mobjTrend.getTradeActive().setBEReached(round_to_pts(mobjTrend.getTradeActive().profit()) >= BreakEven); //check for a break even, unless reached yet
         if (!mobjTrend.tradeActive_GetBEReached()) mobjTrend.tradeActive_SetBEReached(round_to_pts(mobjTrend.tradeActive_GetProfit()) >= BreakEven); //check for a break even, unless reached yet
         //else if (mobjTrend.getTradeActive().getProfit() <= 0) {
         else if (mobjTrend.tradeActive_GetProfit() <= 0) {
            mobjTrend.trade_close(); //exit, if returned to zero after a break even
            break; //skip the below steps
         }
         if (mobjTrend.direc_reversed()) { //Direction reversed? Close the position, unless shifted to the bigger time frame, or otherwise shift it.
            if (!mobjTrend.time_frame_shift()) mobjTrend.trade_close(); //Shifting rejected? Close the trade.
         }
         break;
      case phase_end: delete_old_trend(); break;
   }
   if (CheckPointer(mobjTrend) == POINTER_DYNAMIC) mobjTrend.update_peak(Bid); //update the peak for a later use, if a trend exists. //develop: why not placing it at the top below mobjTrend.cobjAlg.getSave(mintIdx0)?
}

void OnInit() { //+------------------------------------------------------------------+
   const long lngDelay = 0; //1000000;
   const long lngDelayLong = 0; //1000000000;
   GlobalVariableTemp(mstrDelay);
   GlobalVariableSet(mstrDelay, lngDelay);
   GlobalVariableTemp(mstrDelayLong);
   GlobalVariableSet(mstrDelayLong, lngDelayLong);
}

void OnDeinit(const int reason) {if (CheckPointer(mobjTrend) == POINTER_DYNAMIC) delete mobjTrend;} //delete dynamically created objects //+------------------------------------------------------------------+

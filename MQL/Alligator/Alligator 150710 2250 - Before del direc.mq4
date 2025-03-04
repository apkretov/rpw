#property strict

/*extern*/ bool HeikingAshiSmoothed = true;

struct directions {int flat, trend, trend_up, trend_down;}; directions mtrcDirec = {0, 1, 2, 3};
/*struct directions {int trend_up, trend_down, trend, flat;}; directions mtrcDirec = {OP_BUY, OP_SELL, 2, 3};*/
struct phases {int begin, end;}; phases mtrcPhases = {0, 1};
struct market_to_alg_states {int flat, crossing, moving_away, ahead_of_dashed_lips;};
struct fibo_num {int n1, n3, n5, n8, n13;}; fibo_num mtrcFibo = {1, 3, 5, 8, 13};

class tendency { //+------------------------------------------------------------------+
   public:
      int direc;
      virtual void get_direc() {return;}
};

class indicator { //+------------------------------------------------------------------+
   protected:
      int cintIdx;
   public:
      virtual void get(int intIdx) {return;}
};

class indicator_singlevalue : public indicator { //+------------------------------------------------------------------+
   public:
      double value;
};

class indicator_trend : public tendency { //+------------------------------------------------------------------+
   protected:
      int cintIdx;
   public:
      virtual void get(int intIdx) {return;}
};

class indicator_trend_singlevalue : public indicator_trend { //+------------------------------------------------------------------+
   public:
      double value;
};

class alligator : public indicator_trend { //+------------------------------------------------------------------+
   public:
      alligator(){cintIdx = 0;} //construct empty objects (to boost performance) for later use
      alligator(int intIdx) {get(intIdx); get_direc();} //Get Alligator values, if the index is defined at the construction stage and get its location to the price.
      double lips_dashed, lips, teeth, jaws/*, high, low*/;
      void get(int intIdx);
      void get_direc();
      //void signal_get();
      //datetime signal_time;
      //double signal_price;
      double high() {return MathMax(lips, MathMax(teeth, jaws));} //the Alligator highest line value except dashed lips
      double low() {return MathMin(lips, MathMin(teeth, jaws));} //the Alligator lowest line value except dashed lips
      /*double high_get(bool also_low = true); //the Alligator highest line value except dashed lips; optionally also get low
      double low_get(bool also_high = true); //the Alligator lowest line value except dashed lips; optionally also get high*/
};

void alligator::get(int intIdx) { //+------------------------------------------------------------------+
   cintIdx = intIdx;
   lips_dashed = iMA(NULL, 0, mtrcFibo.n3, mtrcFibo.n1, MODE_SMMA, PRICE_MEDIAN, cintIdx);
   lips = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx);
   teeth = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx);
   jaws = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx);
   //high = MathMax(lips, MathMax(teeth, jaws));
   //low = MathMin(lips, MathMin(teeth, jaws));
}      

void alligator::get_direc() { //+------------------------------------------------------------------+
   /*double dblLipsDashed = iMA(NULL, 0, mtrcFibo.n3, mtrcFibo.n1, MODE_SMMA, PRICE_MEDIAN, cintIdx - mtrcFibo.n1); //develop to make separate iMA and iAlligator functions for this function and the get one //this is a initial version of direction detection 
   double dblLips = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx - mtrcFibo.n3); 
   double dblTeeth = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx - mtrcFibo.n5); 
   double dblJaws = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx - mtrcFibo.n8); 
   if (dblLipsDashed > dblLips && dblLips > dblTeeth && dblTeeth > dblJaws) 
      direc = mtrcDirec.trend_up;
   else if (dblLipsDashed < dblLips && dblLips < dblTeeth && dblTeeth < dblJaws) 
      direc = mtrcDirec.trend_down;
   else 
      direc = mtrcDirec.flat;*/
   if (Close[cintIdx] > high())  //is the price above Alligator?
      direc = mtrcDirec.trend_up;
   else if(Close[cintIdx] < low()) //is the price above Alligator?
      direc = mtrcDirec.trend_down;
   else //the price is inside Alligator
      direc = mtrcDirec.flat;  
}

void signal_get(void) { //+------------------------------------------------------------------+
   alligator objAlg;
   for (int i = 1; i < Bars - 1; i++) { //check all the bars prior the current one for a signal
      objAlg.get(i);
      double dblAlgHigh = objAlg.high();
      double dblAlgLow = objAlg.low();
      if (Bid > dblAlgHigh) { //is the current price above Alligator?
         if (Close[i] < dblAlgHigh) {
            message("Check point 1");
            break;
         }else if (Close[i] >= dblAlgHigh) {
            
         }
      }else if (Bid < dblAlgLow) {//is the current price below Alligator?
         if (Close[i] > dblAlgLow) {
            message("Check point 2");
            break;
         }else if (Close[i] <= dblAlgLow) {
            
         }
      }
   }
}

/*double alligator::high_get(bool also_low = true) { //+------------------------------------------------------------------+
   high = MathMax(lips, MathMax(teeth, jaws));
   if (also_low) low = MathMin(lips, MathMin(teeth, jaws));
   return high;
}

double alligator::low_get(bool also_high=true) { //+------------------------------------------------------------------+
   low = MathMin(lips, MathMin(teeth, jaws));
   if (also_high) high = MathMax(lips, MathMax(teeth, jaws));
   return low;
}*/

class adx : public indicator_trend_singlevalue { //+------------------------------------------------------------------+
   public:
      adx() {;}
      adx(int intIdx) {get(intIdx);}
      void get(int intIdx);
      void get_direc();
};

void adx::get(int intIdx) { //+------------------------------------------------------------------+
   cintIdx = intIdx;
   value = iADX(NULL, 0, mtrcFibo.n13, PRICE_MEDIAN, MODE_MAIN, cintIdx);
}

void adx::get_direc(void) { //+------------------------------------------------------------------+
   const int intThreshold = 25;
   if (value >= intThreshold) direc = mtrcDirec.trend; 
   else direc = mtrcDirec.flat;
}

class bands : public indicator_trend { //+------------------------------------------------------------------+
   public:
      bands ();
      bands(int intIdx) {get(intIdx);}
      void get(int intIdx);
      double upper, lower;
};

void bands::get(int intIdx) { //+------------------------------------------------------------------+
   const int intDeviations = 2;
   cintIdx = intIdx;
   upper = iBands(NULL, 0, mtrcFibo.n13, intDeviations, 0, PRICE_MEDIAN, MODE_UPPER, intIdx);
   lower = iBands(NULL, 0, mtrcFibo.n13, intDeviations, 0, PRICE_MEDIAN, MODE_LOWER, intIdx);
}

class gator : public indicator { //to be developed +------------------------------------------------------------------+
   public:
      gator();
      gator(int intIdx) {get(intIdx);}
      void get(int intIdx) {return;}
};

class gator_13_8_5 : public gator { //to be developed +------------------------------------------------------------------+
};

class gator_8_5_3 : public gator { //to be developed +------------------------------------------------------------------+
};

/*http://www.forex-tsd.com/ideas-suggestions/2033-ea-based-heiken-ashi.html //+------------------------------------------------------------------+
double HeHa0=iCustom(NULL,TimeFrame1,"Heiken Ashi",0,0);
double HeHa1=iCustom(NULL,TimeFrame1,"Heiken Ashi",1,0);
double HeHa2=iCustom(NULL,TimeFrame1,"Heiken Ashi",2,0);
double HeHa3=iCustom(NULL,TimeFrame1,"Heiken Ashi",3,0);
Trendup=HeHa3>HeHa2;
Trenddown=HeHa3<HeHa2;
Stronguptrend=HeHa3>HeHa2 && HeHa1=HeHa3;
Strongdown=HeHa3<HeHa2 && HeHa0=HeHa2;

http://forum.mql4.com/11994
haOpen=iCustom(NULL,0,"Heiken_Ashi_Smoothed",MaMetod,MaPeriod,MaMetod2,MaPeriod2,2,0);
haClose=iCustom(NULL,0,"Heiken_Ashi_Smoothed",MaMetod,MaPeriod,MaMetod2,MaPeriod2,3,0);
haOpen2=iCustom(NULL,0,"Heiken_Ashi_Smoothed",MaMetod,MaPeriod,MaMetod2,MaPeriod2,1,0);
haClose2=iCustom(NULL,0,"Heiken_Ashi_Smoothed",MaMetod,MaPeriod,MaMetod2,MaPeriod2,0,0);*/
class heikin_ashi : public indicator_trend {
   private:
      bool cblnSmoothed; //develop applying inheritance: parent class is heiking_ashi is inherited by the classes heiking_ashi_ordinary and heiking_ashi_smoothed
      double HeHa0, HeHa1, HeHa2, HeHa3;
      double haOpen, haClose, haOpen2, haClose2;
   public:
      heikin_ashi(bool blnSmoothed);
      heikin_ashi(bool blnSmoothed, int intIdx);
      void get(int intIdx);
      void get_direc();
};

void heikin_ashi::heikin_ashi(bool blnSmoothed) { //initialise the direction because it must have an initial value before it will get defined the first time in the get_direc function later //+------------------------------------------------------------------+
   cblnSmoothed = blnSmoothed;
   direc = mtrcDirec.flat; 
}

void heikin_ashi::heikin_ashi(bool blnSmoothed,int intIdx) { //Get the values, if the index is defined at the construction stage and get its direction. Initialise the direction because it must have an initial value before it will get defined the first time in the get_direc function later //+------------------------------------------------------------------+
   cblnSmoothed = blnSmoothed;
   direc = mtrcDirec.flat; 
   get(intIdx); 
   get_direc();
}

void heikin_ashi::get(int intIdx) { //get the Heikin Ashi OHLC by their definition +------------------------------------------------------------------+
   const int MaMetod = 2; //develop optionally for performance to initialise onece
   const int MaPeriod = 6;
   const int MaMetod2 = 3;
   const int MaPeriod2 = 2;
   cintIdx = intIdx;
   switch(cblnSmoothed) { //develop applying inheritance: parent class is heiking_ashi is inherited by the classes heiking_ashi_ordinary and heiking_ashi_smoothed
      case false:
         HeHa0 = iCustom(NULL, 0, "Heiken Ashi", 0, cintIdx);
         HeHa1 = iCustom(NULL, 0, "Heiken Ashi", 1, cintIdx);
         HeHa2 = iCustom(NULL, 0, "Heiken Ashi", 2, cintIdx);
         HeHa3 = iCustom(NULL, 0, "Heiken Ashi", 3, cintIdx);
         break;
      case true:
         haOpen = iCustom(NULL,0, "Heiken_Ashi_Smoothed", MaMetod, MaPeriod, MaMetod2, MaPeriod2, 2, cintIdx); //develop optionally for performance: open is computed only once at a bar openning
         haClose = iCustom(NULL, 0, "Heiken_Ashi_Smoothed", MaMetod, MaPeriod, MaMetod2, MaPeriod2, 3, cintIdx);
         haOpen2 = iCustom(NULL, 0, "Heiken_Ashi_Smoothed", MaMetod, MaPeriod, MaMetod2, MaPeriod2, 1, cintIdx);
         haClose2 = iCustom(NULL, 0, "Heiken_Ashi_Smoothed", MaMetod, MaPeriod, MaMetod2, MaPeriod2, 0, cintIdx);
     }
}      

void heikin_ashi::get_direc() { //get the direction (i.e. the colour in the graph) by the Heikin Ashi definition +------------------------------------------------------------------+
   switch(cblnSmoothed) { //develop applying inheritance: parent class is heiking_ashi is inherited by the classes heiking_ashi_ordinary and heiking_ashi_smoothed
      case false:
         if (HeHa3 > HeHa2) direc = mtrcDirec.trend_up;
         else if (HeHa3 < HeHa2) direc = mtrcDirec.trend_down;
         break;
      case true:
         if((haOpen >= haClose) && (haOpen2 < haClose2)) direc = mtrcDirec.trend_down;
         else direc = mtrcDirec.trend_up;
   }
}

class trend : public tendency { //+------------------------------------------------------------------+
   public:
      void trend() {phase = mtrcPhases.begin;}
      void get_direc();
      int begin_bar; //the index of the beginning bar of the trend
      double peak; //the highest/lowest price during the trade
      int phase;
};

class trade { //+------------------------------------------------------------------+
   private:
      /*int cintMagic;*/
      int cintSlippage;
      string cstrTicket;
   public:
      trade();
      /*trade(int);*/ //develop to initialise the object from the history pool
      int ticket, type;
      datetime time_open, time_close; //If order close time is not 0, then the order selected and has been closed and retrieved from the account history. Open and pending orders close time is equal to 0.
      double price_open, /*price_close,*/ stop_loss, take_profit, lots;
      /*double profit;*/ //For open orders, it is the current unrealized profit. For closed orders, it is the fixed profit.
      bool open(int intType, double dblPrice, double dblStopLoss = 0, double dblTakeProfit = 0, double dblLots = 0.01);
      bool close(double dblPrice);
      /*double refresh();*/ //develop to get profit, close price, and close time
      void copy(trade&);
};

void trade::trade() { //+------------------------------------------------------------------+
   /*cintMagic = 150710;*/
   cintSlippage = 10;
   cstrTicket = "Ticket";
   ticket = -1; 
   type = -1;
   time_open = 0;
   time_close = 0;
   price_open = 0;
   /*price_close = 0;*/
   stop_loss = 0;
   take_profit = 0;
   /*profit = 0;*/
   lots = 0;
}

bool trade::open(int intType, double dblPrice, double dblStopLoss = 0, double dblTakeProfit = 0, double dblLots = 0.01) { //+------------------------------------------------------------------+
   const int intFailureFlag = -1;
   const string strComment = "Expert advisor";
   ticket = OrderSend(Symbol(), intType, dblLots, dblPrice, cintSlippage, dblStopLoss, dblTakeProfit, strComment/*, cintMagic*/); //Returns number of the ticket assigned to the order by the trade server or -1 if it fails.
   if (ticket == intFailureFlag)
      return false;
   else{
      type = intType;
      time_open = TimeCurrent();
      price_open = dblPrice; //develop to retrieve an exact open price and time from the history pool
      lots = dblLots;
      return true;
   }
}

bool trade::close(double dblPrice) { //+------------------------------------------------------------------+
   //return OrderClose(ticket, lots, dblPrice, cintSlippage); //develop to retrieve the profit, close price, and close time from the history pool
   if(OrderClose(ticket, lots, dblPrice, cintSlippage)) {
      time_close = TimeCurrent(); //develop to retrieve the profit, close price, and close time from the history pool
      return true;
   }else
      return false;
}

void trade::copy(trade &objTrade) { //+------------------------------------------------------------------+
   ticket = objTrade.ticket;
   type = objTrade.type;
   time_open = objTrade.time_open;
   time_close = objTrade.time_close;
   price_open = objTrade.price_open;
   stop_loss = objTrade.stop_loss;
   take_profit = objTrade.take_profit;
   lots = objTrade.lots;
}

void message(string strMsg) { //+------------------------------------------------------------------+
   Print(strMsg);
   Comment(strMsg);
}

bool trade_exists(trade* objTrade){ //check if an object exists //+------------------------------------------------------------------+
   return objTrade != NULL && CheckPointer(objTrade) == POINTER_DYNAMIC;
}

void close_position(int intDirec, double dblPrice) { //close a buy/sell position //+------------------------------------------------------------------+
   /*if (mobjHA.direc == intDirec) {*/ //right direction?
      if (mobjTrade.close(dblPrice)) { //closed?
         if(trade_exists(mobjTradePrior)) { //delete the previously prior object, if it has been created before
            delete mobjTradePrior;
            mobjTradePrior = NULL;
         }
         mobjTradePrior = new trade; //for more robustness develop to use a prior trade retrieved from the history pool rather than my mobjTradePrior
         mobjTradePrior.copy(mobjTrade); //the current trade gets prior and cleared (next line)
         if(trade_exists(mobjTrade)) {
            delete mobjTrade;
            mobjTrade = NULL;
         }
      }
   /*}*/
}

void delay() { //+------------------------------------------------------------------+
   int j = 0;
   for(int i=0; i < 100000; i++) {j++;}
}

alligator mobjAlg; //to boost performance create the object once for all future ticks
/*heikin_ashi mobjHA(HeikingAshiSmoothed);*/ //to boost performance create the object once for all future ticks
/*adx mobjADX();*/
trade* mobjTrade = NULL;
trade* mobjTradePrior = NULL;

bool one_trade_per_bar() { //make sure there is only one trade per bar //+------------------------------------------------------------------+
   if (trade_exists(mobjTradePrior)) return mobjTradePrior.time_open < Time[0]; //any prior trade? //traded before the open time of the current bar?
   return true; //no prior trade yet at all
}

void open_position(const int intDirec, const double& dblPrice) { //+------------------------------------------------------------------+
   if (one_trade_per_bar()) { //make sure there is only one trade per bar
      if (mobjTrade == NULL) mobjTrade = new trade;
      mobjTrade.open(intDirec, dblPrice);
   }
}

void OnTick() { //+------------------------------------------------------------------+
   /*mobjHA.get(0);
   mobjHA.get_direc();*/
   if(OrdersTotal() == 0) { //any open positions? //to be developed for the Magic number and the pending orders
      /*mobjADX.get(0);
      mobjADX.get_direc();
      if(mobjADX.direc == mtrcDirec.trend) {*/ //trade given a trend or outside a flat; prevent unnecessary computations below given a flat
         if(/*mobjHA.direc == mtrcDirec.trend_up &&*/ mobjAlg.direc == mtrcDirec.trend_up) open_position(OP_BUY, Ask);
         else if(/*mobjHA.direc == mtrcDirec.trend_down &&*/ mobjAlg.direc == mtrcDirec.trend_down) open_position(OP_SELL, Bid);
      /*}*/
   }else{
      if((mobjTrade.type == OP_BUY)) close_position(mtrcDirec.trend_down, Bid);  //check to close a buy position
      else close_position(mtrcDirec.trend_up, Ask); //check to close a sell position
   }
}

void OnDeinit(const int reason) { //delete dynamically created objects //+------------------------------------------------------------------+
   if(trade_exists(mobjTrade)) delete mobjTrade; //this deletion is optional and run for additional robustnes because an object is deleted after closing each trade
   if(trade_exists(mobjTradePrior)) delete mobjTradePrior;
}

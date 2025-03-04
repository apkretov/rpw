#property strict

extern int mintMagic = 150703;
const int mintSlippage = 10;
const string mstrTicket = "Ticket";

struct directions {int flat, trend, trend_up, trend_down;};
//directions mtrcDirec = {1, -1, 0};
directions mtrcDirec = {0, 1, 2, 3};

struct phases {int begin, end;};
phases mtrcPhases = {0, 1};

struct market_to_alg_states {int flat, crossing, moving_away, ahead_of_dashed_lips;};

struct fibo_num {int n1, n3, n5, n8, n13;};
fibo_num mtrcFibo = {1, 3, 5, 8, 13};

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
      alligator(int intIdx, bool blnInitPrLoc) {get(intIdx); get_direc();} //Get Alligator values, if the index is defined at the construction stage and get its location to the price.
      double lips_dashed, lips, teeth, jaws;
      void get(int intIdx);
      void get_direc();
      double min, max; //the Alligator minimum/maximum
};

void alligator::get(int intIdx) { //+------------------------------------------------------------------+
   cintIdx = intIdx;
   lips_dashed = iMA(NULL, 0, mtrcFibo.n3, mtrcFibo.n1, MODE_SMMA, PRICE_MEDIAN, cintIdx);
   lips = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx);
   teeth = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx);
   jaws = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx);
}      

void alligator::get_direc() { //+------------------------------------------------------------------+
   double dblLipsDashed = iMA(NULL, 0, mtrcFibo.n3, mtrcFibo.n1, MODE_SMMA, PRICE_MEDIAN, cintIdx - mtrcFibo.n1);
   double dblLips = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx - mtrcFibo.n3);
   double dblTeeth = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx - mtrcFibo.n5);
   double dblJaws = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx - mtrcFibo.n8);
   if (dblLipsDashed > dblLips && dblLips > dblTeeth && dblTeeth > dblJaws) 
      direc = mtrcDirec.trend_up;
   else if (dblLipsDashed < dblLips && dblLips < dblTeeth && dblTeeth < dblJaws) 
      direc = mtrcDirec.trend_down;
   else 
      direc = mtrcDirec.flat;
}

class adx : public indicator_trend_singlevalue { //+------------------------------------------------------------------+
   public:
      adx();
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

//http://www.forex-tsd.com/ideas-suggestions/2033-ea-based-heiken-ashi.html //+------------------------------------------------------------------+
//double HeHa0=iCustom(NULL,TimeFrame1,"Heiken Ashi",0,0);
//double HeHa1=iCustom(NULL,TimeFrame1,"Heiken Ashi",1,0);
//double HeHa2=iCustom(NULL,TimeFrame1,"Heiken Ashi",2,0);
//double HeHa3=iCustom(NULL,TimeFrame1,"Heiken Ashi",3,0);
//Trendup=HeHa3>HeHa2;
//Trenddown=HeHa3<HeHa2;
//Stronguptrend=HeHa3>HeHa2 && HeHa1=HeHa3;
//Strongdown=HeHa3<HeHa2 && HeHa0=HeHa2;
class heikin_ashi : public indicator_trend {
   private:
      //double open, high, low, close;
      double HeHa0, HeHa1, HeHa2, HeHa3;
   public:
      heikin_ashi() {direc = mtrcDirec.flat;} //initialise the direction because it must have an initial value before it will get defined the first time in the get_direc function later
      heikin_ashi(int intIdx) {direc = mtrcDirec.flat; get(intIdx); get_direc();} //Get the values, if the index is defined at the construction stage and get its direction. Initialise the direction because it must have an initial value before it will get defined the first time in the get_direc function later
      //double open, high, low, close;
      void get(int intIdx);
      void get_direc();
};

void heikin_ashi::get(int intIdx) { //get the Heikin Ashi OHLC by their definition +------------------------------------------------------------------+
   cintIdx = intIdx;
   //int intIdx1 = intIdx + 1; //the index prior to the current.
   //open =  (Open[intIdx1] + Close[intIdx1]) / 2; ///////////////ERROR!!!
   //high = MathMax(High[cintIdx], open);
   //low = MathMin(Low[cintIdx], open);
   //close = (Open[cintIdx] + High[cintIdx] + Low[cintIdx] + Close[cintIdx]) / 4;
   HeHa0 = iCustom(NULL, 0, "Heiken Ashi", 0, cintIdx);
   HeHa1 = iCustom(NULL, 0, "Heiken Ashi", 1, cintIdx);
   HeHa2 = iCustom(NULL, 0, "Heiken Ashi", 2, cintIdx);
   HeHa3 = iCustom(NULL, 0, "Heiken Ashi", 3, cintIdx);
}      

void heikin_ashi::get_direc() { //get the direction (i.e. the colour in the graph) by the Heikin Ashi definition +------------------------------------------------------------------+
   //if (close > open) direc = mtrcDirec.trend_up; //the direction maintains prior (unchanged), if close gets equal to open
   //else if (close < open) direc = mtrcDirec.trend_down;
   if (HeHa3 > HeHa2) 
//{Comment("165");
      direc = mtrcDirec.trend_up;
//}
   else if (HeHa3 < HeHa2) 
//{Comment("169");
      direc = mtrcDirec.trend_down;
//}      
//   else 
//{Comment("173");
//      direc = mtrcDirec.flat;
//}
}

class trend : public tendency { //+------------------------------------------------------------------+
   public:
      void trend() {phase = mtrcPhases.begin;}
      int phase;
      int begin_bar; //the index of the beginning bar of the trend
      void get_direc();
};

void message(string strMsg) { //+------------------------------------------------------------------+
   Print(strMsg);
   Comment(strMsg);
}

int order_send(int intTradeOperation, double dblPrice, double dblStopLoss = 0, double dblTakeProfit = 0, double dblVolume = 1) { //+------------------------------------------------------------------+
   return OrderSend(Symbol(), intTradeOperation, dblVolume, dblPrice, mintSlippage, dblStopLoss, dblTakeProfit, "HA Order", mintMagic);
}

void close_position(int intDirec, double dblPrice) { //close a buy/sell position //+------------------------------------------------------------------+
   heikin_ashi objHA(0); //to boost performance create the object when needed unlike at the beginning
   if (objHA.direc == intDirec) { 
      bool blnOrderClose = OrderClose(OrderTicket(), OrderLots(), dblPrice, mintSlippage);
      GlobalVariableDel(mstrTicket); //delete the ticket number to avoid a future misuse
   }
}

void OnTick() { // Expert tick function //+------------------------------------------------------------------+
   if(OrdersTotal() == 0) { //any open positions? //to be developed for pending orders
      heikin_ashi objHA(0); //to boost performance create the object when needed unlike at the beginning
      alligator objAlg;
      objAlg.get_direc();
      if(objAlg.direc != mtrcDirec.flat) { //trade given a trend or out of a flat; prevent unnecessary computations below given a flat
         if(objHA.direc == mtrcDirec.trend_up && objAlg.direc == mtrcDirec.trend_up) GlobalVariableSet(mstrTicket, order_send(OP_BUY, Ask));
         else if(objHA.direc == mtrcDirec.trend_down && objAlg.direc == mtrcDirec.trend_down) GlobalVariableSet(mstrTicket, order_send(OP_SELL, Bid));
      }
   }else{
      int intOrderSelect = OrderSelect((int)GlobalVariableGet(mstrTicket), SELECT_BY_TICKET); //(int) converts GlobalVariableGet value into integer
      if(OrderMagicNumber() == mintMagic) { //a position the system opened?
         if((OrderType() == OP_BUY)) close_position(mtrcDirec.trend_down, Bid);  //check to close a buy position
         else if((OrderType() == OP_SELL)) close_position(mtrcDirec.trend_up, Ask); //check to close a sell position
      }
   }
}
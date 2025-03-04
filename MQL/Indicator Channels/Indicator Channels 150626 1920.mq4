#property strict

struct directions {int flat, trend, up_trend, down_trend;};
directions mtrcDirec = {1, -1, 0};

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
      alligator();
      alligator(int intIdx, bool blnInitPrLoc) {get(intIdx); get_direc();} //Get Alligator values, if the index is defined at the constraction stage and get its location to the price.
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
   double dblLips = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx - mtrcFibo.n3);
   double dblTeeth = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx - mtrcFibo.n5);
   double dblJaws = iAlligator(NULL, 0, mtrcFibo.n13, mtrcFibo.n8, mtrcFibo.n8, mtrcFibo.n5, mtrcFibo.n5, mtrcFibo.n3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx - mtrcFibo.n8);
   if (dblLips > dblTeeth && dblTeeth > dblJaws) direc = mtrcDirec.up_trend;
   else if (dblLips < dblTeeth && dblTeeth < dblJaws) direc = mtrcDirec.down_trend;
   else direc = mtrcDirec.flat;
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

void OnTick() { // Expert tick function //+------------------------------------------------------------------+
   if (Volume[0] == 0) {
      message("The first tick of the bar!");
      alligator objAlg(0, true);
   }else {
      message("A next tick of the bar!");
   }
}
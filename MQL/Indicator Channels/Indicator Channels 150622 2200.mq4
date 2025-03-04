#property strict

struct directions {
   int up, down, mid;
};

directions mstcDirec = {1, -1, 0};

class alligator { //+------------------------------------------------------------------+
   private:
      int cintIdx;
   public:
      alligator();
      alligator(int intIdx); //Get Alligator values, if the index is defined at the constraction stage.
      alligator(int intIdx, bool blnInitPrLoc); //Get Alligator values, if the index is defined at the constraction stage and get its location to the price.
      double lips_dashed, lips, teeth, jaws;
      void get(int intIdx);
      void get_direc();
      int direc;
      double min, max;/////////////// //the Alligator minimum/maximum
};

alligator::alligator(int intIdx) { //+------------------------------------------------------------------+
   get(intIdx);
}

alligator::alligator(int intIdx, bool blnInitPrLoc) { //+------------------------------------------------------------------+
   get(intIdx);
   get_direc();
}

alligator::get(int intIdx) { //+------------------------------------------------------------------+
   cintIdx = intIdx;
   lips_dashed = iMA(NULL, 0, 3, 1, MODE_SMMA, PRICE_MEDIAN, cintIdx);
   lips = iAlligator(NULL, 0, 13, 8, 8, 5, 5, 3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORLIPS, cintIdx);
   teeth = iAlligator(NULL, 0, 13, 8, 8, 5, 5, 3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORTEETH, cintIdx);
   jaws = iAlligator(NULL, 0, 13, 8, 8, 5, 5, 3, MODE_SMMA, PRICE_MEDIAN, MODE_GATORJAW, cintIdx);
}
//AlligatorJawsBuffer[i]=iMA(NULL,0,13,8,MODE_SMMA,PRICE_MEDIAN,i);

void alligator::get_direc() { //location of Alligator to price (above: 1, below: -1, inside: 0) //+------------------------------------------------------------------+
   double close;
   close = Close[cintIdx];
   if (lips > close && teeth > close && jaws > close) direc = mstcDirec.down; //below the price
   else if (lips < close && teeth < close && jaws < close) direc = mstcDirec.up; //above the price
   else direc = mstcDirec.mid; //around the price
}

void OnTick() { // Expert tick function //+------------------------------------------------------------------+
   if (Volume[0] == 0) {
      alligator objAlg(0, true);
   }else 
      Print("A next tick of the bar!");
}
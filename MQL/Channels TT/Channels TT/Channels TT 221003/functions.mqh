#property strict
#ifndef FUNCTIONS_MQH
#define FUNCTIONS_MQH

#include "enumerators.mqh"
#include "constants.mqh"
#include "graphObject.mqh"
#include "objects.mqh"

string formatPrice(double dblPrice) { 
   return StringFormat(StringConcatenate("%", gsttVariousConsts.formatDecimals), dblPrice); 
}

string formatInteger(int intNumber, int intLength) { // Format an interger number with a specified length and if necessa leading zeroes. //"%06.2f" - "0" denotes leading zeroes (e.g. 099), '6' denotes the width (e.g. 123.45), '.2' denotes 2 decimal digits after the decimal point, 'f' denotes a double number type ('u' - unsigned decimal integer ). 
   return StringFormat( StringConcatenate("%0", intLength, "u"), intNumber ); 
} 

string anticollisionAffix() { 
   datetime dtmTimeLocal = TimeLocal();
   return StringConcatenate( " ", formatInteger(TimeMinute(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec), formatInteger(TimeSeconds(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec) ); 
} 

void message(const string& strMsg) { 
   if(strMsg != "") //Prevent the print log file from spamming with empty strings.
      Print(strMsg);
   Comment(strMsg);
}

void messageV(string strMsg) { 
   message(strMsg); 
} 

int roundToPts(double dblValue) { 
   return (int)MathRound(dblValue / Point); 
}

double roundToTickStep(double dblPrice) { // Round a price to the tick step. // mql4 - How to avoid Round-up from NormalizeDouble and OrderSend Pending Order (SELLLIMIT, BUYLIMIT) get Error -1 Invalid stops - Stack Overflow @ https://stackoverflow.com/questions/58880836/how-to-avoid-round-up-from-normalizedouble-and-ordersend-pending-order-selllimi
   if (TickStep > pts1) {
      double dblTickSize = _Point * TickStep;
      dblPrice = MathRound(dblPrice / dblTickSize) * dblTickSize;
   }
   return dblPrice;
}  

double distance(double dblFrom, double dblTo, enmDirec intDirec) {
   return (dblTo - dblFrom) * intDirec;
}

int distancePts(double dblFrom, double dblTo, enmDirec intDirec) {
   return roundToPts((dblTo - dblFrom) * intDirec);
}

int BUYtoSELL(int intOperation) { // Convert OP_BUY=0 to OP_SELL=1 and vice versa. 
   return (int)MathAbs(intOperation - 1); 
}

int LIMITSTOPtoBUYSELL(int intOperation) { 
   return intOperation % 2; // Convert OP_BUYLIMIT=2/OP_BUYSTOP=4 to OP_BUY=0 or OP_SELLLIMIT=3/OP_SELLSTOP=5 to OP_SELL=1. //You should use the '%' operator on positive numbers instead, as it is much faster. @ https://maurits.tv/data/garrysmod/wiki/wiki.garrysmod.com/indexdaf1.html
}

int resumingOperation(int intOperation) { //Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
   return BUYtoSELL(LIMITSTOPtoBUYSELL(intOperation)) + OP_BUYSTOP;
}

double resumingPrice(int intOperation, double dblPrice) { //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
   return dblPrice + ResumeRange * (intOperation == OP_BUYLIMIT ? -1 : 1) * Point;
}

void alert(graphObject& labelOpenedClosed, const objects& objObjects) { //Show a triggered alert. 
   const string strAlert = "Alert: ";
   string strMessage = StringConcatenate(strAlert, objObjects.getObjectTriggered().name, " ", formatPrice(objObjects.getObjectTriggered().getPrice()));
   messageV(StringConcatenate(strMessage));
   labelOpenedClosed.setDescription(strMessage);
}

void playSound() { 
   if(Sound)
   	PlaySound("alert.wav"); 
} 

#endif //FUNCTIONS_MQH
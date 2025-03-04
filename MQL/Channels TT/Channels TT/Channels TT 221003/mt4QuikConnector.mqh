#property strict
#ifndef MT4QUIKCONNECTOR_MQH
#define MT4QUIKCONNECTOR_MQH

#include "switch.mqh"
#include "constants.mqh"
#include "functions.mqh"

#import "MTQC.dll"
	#ifdef TRADE_IN_QUIK
   	string messsagToMTQC(string pWCBuffer); //"Transactions on Named Pipes" @ https://msdn.microsoft.com/en-us/library/aa365789(v=vs.85).aspx
   #endif 
#import

#ifdef TRADE_IN_QUIK
	class mt4QuikConnector { 
	   string cstrMessagePrior;
	   string cstrDisableOjects, cstrClosePosition, cstrSetLots;
	   string /*cstrKeyPressedEsc,*/ cstrKeyPressedBuySell;
	   bool cblnKeyPressedOperation;
	   bool cblnPaused;
	   bool cblnPass0;
	
	public:
	   void mt4QuikConnector() { //Test connection on construction //TO DO: Use the member initialisation list to ininialise the class members. 
	      cstrMessagePrior = ""; 
	      cstrDisableOjects = "cmdDO"; //The Disable Ojects command.
	      cstrClosePosition = "cmdCP"; //The Close Position command.
	      cstrKeyPressedBuySell = "cmdBS"; //The Buy/Sell command.
	      cstrSetLots = "cmdSL"; //The Set Lots command.
	   };
	
	   void setPaused(bool blnPaused) {
	      cblnPaused = blnPaused;
	   }   
	
	   void setPass0(bool blnPass0) {
	      cblnPass0 = blnPass0;
	   }
	
	   void passMessage(const string& strMessage) { 
         if (cblnPaused) {
            cstrMessagePrior = strMessage; //Is it paused? No action, just reset the pause flag. After a trade, the price of the triggered object is being changed that triggers a change event. That's why before changing the price the connector is paused to prevent both possible ambiguity in Quik and an unnecessary OS overhead. //Remember the messages for future comparisons.
            cblnPaused = false; //In a pause, the message is saved.
         } else { //If there are more than trading objects then their change events will be blocked by the current vs. prior message anti-duplication check below.
            if (strMessage != cstrMessagePrior || cblnKeyPressedOperation) { //Pass a message, if it differs from a prior one to prevent both possible ambiguity in Quik and an unnecessary OS overhead.
               if (strMessage != "0" || cblnPass0) { //Unless a zero is explicitly passed, the last current vs. prior message anti-duplication check makes sure that reiterating "0" (it usually reiterates after having triggered in MT4) doesn't reset all the objects passed to Quik before.
                  messsagToMTQC(strMessage);
                  cstrMessagePrior = strMessage; //Remember it for the later messages.
                  cblnPass0 = false;
               }  
            }  
         }  
	   }
	
	   void passMessageV(string strMessage) { 
	      passMessage(strMessage); 
	   } 
	
	   void disableObjects() { 
	      passMessage(cstrDisableOjects); 
	   } 
	
	   void closePosition() { 
	      passMessage(cstrClosePosition); 
	   } 
	
	   void keyPressedOperation(int intOperation) { 
	      cblnKeyPressedOperation = true; //Flag a key pressed operation to be passed through the strMessage vs. cstrMessagePrior check in the passMessage function.
	      passMessageV(StringConcatenate(cstrKeyPressedBuySell, gsttVariousConsts.priceSeparator, intOperation)); 
	      cblnKeyPressedOperation = false; //Reset the flag.
	   } 
	   
	   void setLots(int intLots) { 
	      passMessageV( StringConcatenate(cstrSetLots, gsttVariousConsts.priceSeparator, formatInteger(Lots, gsttVariousConsts.lengthLots)) ); 
	   } 
	};
#endif //TRADE_IN_QUIK

#endif //MT4QUIKCONNECTOR_MQH
#property strict
#ifndef OBJECT_MQH
#define OBJECT_MQH

class object : public graphObject { 
   int cintOperationInt;
   const string cstrDescrKept;
   const string cstrDescrPending;
   const string cstrDescrResuming;
   const string cstrDescrReversing;
   const string cstrDescrAlert;
   const string cstrDescrRegression;
   const string cstrDescrMoving;

	const unsigned char cchrFlagAlert;// = 1 << 0; // 0000 0001 // The bit positions of the flags. //3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
	const unsigned char cchrFlagTrade;// = 1 << 1; // 0000 0010
	const unsigned char cchrFlagPending;// = 1 << 2; // 0000 0100
	const unsigned char cchrFlagKept;// = 1 << 3; // 0000 1000
	const unsigned char cchrFlagResuming;// = 1 << 4; // 0001 0000
	const unsigned char cchrFlagReversing;// = 1 << 5; // 0010 0000
	const unsigned char cchrFlagMoving;// = 1 << 6; // 0100 0000
	unsigned char cchrFlag; //all flags/options turned off to start //TO DO: Add a regression flag, when the flags get used.
   
   bool compareDescr(const string& strDescrPattern, string strDescrCompared) const {
      if (strDescrCompared != "") {
         if (!StringToLower(strDescrCompared)) { //Get a lower case description to prevent misreading operational descriptions such as a - alert, r - reversing etc.
            //OFF Because there is an error it alerts about that should be corrected: Alert("A StringToLower error " + (string)_LastError + " " + ErrorDescription(_LastError) + " ocurred in the compareDescr function!");
            return false;
         }
      }
      return strDescrCompared == strDescrPattern;  
   }

public:
   object(string strName, int intOperation) :  //https://www.mql5.com/en/forum/7383 
      cstrDescrKept("k"),
      cstrDescrPending("p"),
      cstrDescrResuming("m"),
      cstrDescrReversing("r"),
      cstrDescrAlert(gsttVariousConsts.flagAlert),
      cstrDescrRegression(gsttVariousConsts.flagRegress),
      cstrDescrMoving("moving"),
    
      cchrFlagAlert(1 << 0), // 0000 0001 
   	cchrFlagTrade(1 << 1), // 0000 0010
   	cchrFlagPending(1 << 2), // 0000 0100
   	cchrFlagKept(1 << 3), // 0000 1000
   	cchrFlagResuming(1 << 4), // 0001 0000
   	cchrFlagReversing(1 << 5), // 0010 0000
   	cchrFlagMoving(1 << 6), // 0100 0000
   	cchrFlag(0), //all flags/options turned off to start
   	     
      graphObject(strName) { 
         cintOperationInt = intOperation; 
      }
   
   int getOperationInt() const { 
      return cintOperationInt; 
   };

   int getOperationBuySell() const { 
   	return LIMITSTOPtoBUYSELL(getOperationInt()); 
   } 

   bool getTrade(bool blnInclusiveOtherFlags = false) const { // A trade flag can include other flaggs: kept/resuming/reversing.
      if(!blnInclusiveOtherFlags)
         return getDescription() == "";
      else if (getDescription() == "" || getKept() || getResuming() || getReversing() ) // A trade object can be flagged kept/resuming/reversing.
         return true;
      else
         return false;
   } 
   
   void setTrade() const {
      setDescription("");
   } 

   bool getKept() const {
      return compareDescr(cstrDescrKept, getDescription());
   } 

  void setKept() const { //TO DO: Pressing k makes an alert and pending objects trading. Syncronise SmartX for that. Similar logic holds for other flags.
      setDescription(cstrDescrKept); 
   } 
   
   bool getPending() const { 
      return compareDescr(cstrDescrPending, getDescription());
   } 
   
   void setPending() const { 
      setDescription(cstrDescrPending); 
   } 
   
   bool getResuming() const { 
      return compareDescr(cstrDescrResuming, getDescription());
   } 
   
   bool setResuming() const { //Flag an object resuming. Check if it is a limit order.
      if (cintOperationInt == OP_BUYLIMIT || cintOperationInt == OP_SELLLIMIT) {
         setDescription(cstrDescrResuming);
         return true;
      } else {
         MessageBox("A resuming object must be a buy limit or sell limit!", StringSubstr(__FILE__, 0, StringLen(__FILE__) - 5), MB_ICONWARNING);
         return false;
      }
   } 
   
   bool getReversing() const { 
      return compareDescr(cstrDescrReversing, getDescription());
   } 
   
   void setReversing() const { 
         setDescription(cstrDescrReversing); 
   } 
   
   bool getAlert() const { 
      return compareDescr(cstrDescrAlert, getDescription());
   } 
   
   void setAlert() const {   
      setDescription(cstrDescrAlert); 
   } 

   bool getRegression() const { 
      return compareDescr(cstrDescrRegression, getDescription());
   } 
   
   void setRegression() const { 
      setDescription(cstrDescrRegression); 
   } 
 
   bool getMoving() const {
      return compareDescr(cstrDescrMoving, getDescription());
   } 
   
   void setMoving() const {   
      setDescription(cstrDescrMoving);
   } 

   void rename(string strOperationRename = NULL, int intTicket = 0, datetime dtmOrderTime = 0, double dblOrderPrice = 0) { // Rename a trade object and clear its description to prevent its accidential wrong reuse. 
      setDescription(""); //Clear the description of the initiating trade object to prevent its accidential wrong reuse.
      rename_( 
         StringConcatenate( 
            strOperationRename != NULL 
               ? strOperationRename 
               : StringConcatenate(
                  name, 
                  "",
                  intTicket == 0 
                     ? "" 
                     : IntegerToString(intTicket), 
                  dtmOrderTime == 0 
                     ? "" 
                     : StringConcatenate(
                        "", 
                        dtmOrderTime, 
                        "", 
                        roundToPts(dblOrderPrice))), 
            anticollisionAffix() 
         )
      );
   }
   
   bool operator==(const object& objObjectR) const { //Operation Overloading - Functions - Language Basics - MQL4 Reference @ https://docs.mql4.com/basis/function/operationoverload
   	return objObjectR.name == name;
   }

   bool operator!=(const object& objObjectR) const { //Operation Overloading - Functions - Language Basics - MQL4 Reference @ https://docs.mql4.com/basis/function/operationoverload
   	return !operator==(objObjectR);
   }
   
};

#endif //OBJECT_MQH
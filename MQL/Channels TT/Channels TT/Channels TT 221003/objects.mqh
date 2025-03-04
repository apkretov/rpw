#property strict
#ifndef OBJECTS_MQH
#define OBJECTS_MQH

#include "object.mqh"

class objects { 
   object* cobjObjects[]; //A dynamic array of trading objects available.
   object* cobjObjectTriggered;
   string cstrPricesForQuik; //Buy limit, sell limit, buy stop, and sell stop separated with semicolon.
   string cstrPricesToDisplay;
   double cdblPriceScanned; //The price last scanned for a trigger object.
   int cintCount;
   int cintCountPending;
   string cstrDescrEmpty; //A standardized-width empty decription of the flags for Quik.
   datetime cdtmTimeSet; //The time the last time the objects have been set.
   
   void setCount(int intCountPendingNew) { //Set the count of the trading objects and the pending ones, if any. 
      cintCount = ArraySize(cobjObjects);
      cintCountPending = intCountPendingNew; //Unlike setting cintCountPending throughout the class member functions as before, its done inside this function just to manipulate bouth counts in one place.
   } 
      
   void deleteAll() { // Delete all the dynamically created trading objects 
      cobjObjectTriggered = NULL; // disconnect pointer from free-store space //fig10_23.cpp @ C++ Fundamentals By Paul J. Deitel.
      for (int i = 0; i < getCount(); i++) 
         delete cobjObjects[i];
      ArrayResize(cobjObjects, 0, ArraySize(gstrOperations));
      setCount(0);
   } 
   
   object* add(const string& strOperation, int intOperation) { //Add a new trading onbject into the collection. Return a pointer to it. 
      int intIdxAdded = getCount();
      ArrayResize(cobjObjects, intIdxAdded + 1, ArraySize(gstrOperations)); //Increment the size of the array of trade operation types available.
      object* objObject = new object(strOperation, intOperation); //Remember an available trading object.
      cobjObjects[intIdxAdded] = objObject;
      setCount(objObject.getPending() ? cintCountPending + 1 : cintCountPending);
      return objObject;
   }

public:
   objects() : cintCount(0), cintCountPending(0), cdblPriceScanned(0), cstrDescrEmpty(" "), cdtmTimeSet(0) {
   } 
   
   ~objects() { // Delete all the dynamically created trading objects 
      deleteAll(); 
   } 

   int getCount() const { 
      return cintCount; 
   } 
   
   object* getObjectTriggered() const { 
      return cobjObjectTriggered; 
   } 
   
   string getPricesForQuik() const { //Buy limit, sell limit, buy stop, and sell stop separated with semicolon. 
      return cstrPricesForQuik; 
   } 
   
   datetime getTimeSet() const { 
      return cdtmTimeSet; 
   } 
   
   void setTimeSet(datetime dtmTimeSet) { 
      cdtmTimeSet = dtmTimeSet; 
   } 
    
   void set() { 
      cstrPricesToDisplay = "";
      cstrPricesForQuik = "";
      cobjObjectTriggered = NULL;
      deleteAll();
      for (int i = 0; i < ArraySize(gstrOperations); i++) {
         string strOperation = gstrOperations[i];
         if (ObjectFind(strOperation) == 0) { //Is there a trade object?
            object* objObject = add(strOperation, i + OP_BUYLIMIT);
            double dblPrice = NormalizeDouble(objObject.getPrice(), _Digits);
            StringAdd( cstrPricesForQuik, StringConcatenate(gsttVariousConsts.priceSeparator, i + OP_BUYLIMIT) ); //Add a MQL4 trade operation code.
            StringAdd( cstrPricesForQuik, StringFormat(StringConcatenate(
               StringConcatenate(gsttVariousConsts.priceSeparator, "%0", gsttVariousConsts.lengthPrice, gsttVariousConsts.formatDecimals)), dblPrice) ); //"%06.2f" - "0" denotes leading zeroes (e.g. 099), '6' denotes the width (e.g. 123.45), '.2' denotes 2 decimal digits after the decimal point, 'f' denotes a double number type.
            string strDescr = objObject.getDescription(); //Add the description of the object.
            if (strDescr == "") //If the description is empty add a double-space to keep a standardized width of the flags for Quik.
               strDescr = cstrDescrEmpty; 
            StringAdd( cstrPricesForQuik, StringConcatenate(gsttVariousConsts.priceSeparator, strDescr) );
            if (!objObject.getPending()) //Isn't it a pending order?
               cstrPricesToDisplay = StringConcatenate( cstrPricesToDisplay, ((getCount() - cintCountPending) > 1 ? ", " : " "), 
                  strOperation, " ", formatPrice(dblPrice), " ", objObject.getDescription()); 
         }  
      }  
      cdblPriceScanned = 0; //Reset the price last scanned for a trigger object.
      cstrPricesForQuik = StringConcatenate(getCount(), cstrPricesForQuik); //Prefix the prices for Quik with their quantity.
   }
   
   void scanTriggered() { // Alternatively the ojbects array can be always full but with dummy minimal or maximal prices instead of missing objects. Then distinguish buy/sell trades and scan only for a respective buy/sell object only 2 istead of all 4. 
      cobjObjectTriggered = NULL;
		if (Bid != cdblPriceScanned) { //Scan for a triggered object, if the new price differs from that scanned before.
         cdblPriceScanned = Bid; //Remember the new price scanned.
         object* objObject;
         for (int i = 0; i < getCount(); i++) {
            objObject = cobjObjects[i];
            if (!objObject.getPending()) { //Isn't it a pending order?
               switch (objObject.getOperationInt()) {
                  case OP_BUYLIMIT: 
                     if (roundToPts(Bid - objObject.getPrice()) <= 0) 
                        cobjObjectTriggered = objObject; 
                     break;
                  case OP_SELLLIMIT: 
                     if (roundToPts(Bid - objObject.getPrice()) >= 0) 
                        cobjObjectTriggered = objObject; 
                     break;
                  case OP_BUYSTOP: 
                     if (roundToPts(Bid - objObject.getPrice()) > 0) 
                        cobjObjectTriggered = objObject; 
                     break;
                  case OP_SELLSTOP: 
                     if (roundToPts(Bid - objObject.getPrice()) < 0) 
                        cobjObjectTriggered = objObject; 
                     break;
               }  
               if (cobjObjectTriggered != NULL) { //A triggered object found. TESTED: DO NOT MOVE playSound() INTO THE switch OPERATOR ABOVE. LEAVE IT HEAR.
                  playSound();
                  if (!cobjObjectTriggered.getAlert()) 
                     break; //This is a trade unlike an alert. Implement it right away despite there might be another alert triggered.
               }  
            }  
         }  
      }  
   }
  
   void renameAll(bool blnDisableAll, string strOperationSkip = "") const { //Rename all trade objects except skipped, pending, or kept (unless in the DisableAll mode) one to prevent their accidential misuse. 
      bool blnCanceledInSmartX = false;
      if (blnDisableAll) { //Rename all in the blnDisableAll mode.
         for (int i = 0; i < getCount(); i++)
            cobjObjects[i].rename();
      } else {
         object* objObject;
         for (int i = 0; i < getCount(); i++) {
            objObject = cobjObjects[i];
            if (objObject.name != strOperationSkip) { //Is it not a skipped object?
               if (!objObject.getKept()) { //Rename it, unless its name must be kept.
                  if (objObject.getPending()) 
                     objObject.setTrade(); //Clear the pending flag to enable the trading object to use it later on.
                  else
                     objObject.rename();
               }  
            }  
         }  
      }  
   }

   void displayPrices(int intTotalnet) const { //Dispay the prices of all the trade objects 
      if (getCount() - cintCountPending != 0) 
         messageV(StringConcatenate(intTotalnet, "   ", cstrPricesToDisplay));
      else 
         messageV("");
   }

   object* item(const string& strOperation) const { //Find an object by looking up the collection vs. FindObject() 
      for (int i = 0; i < getCount(); i++) {
         if (cobjObjects[i].name == strOperation) 
            return cobjObjects[i];
      }
      return NULL;
   }
   
   object* each(int intIndex) const {
      return cobjObjects[intIndex];
   }

   object* createResuming() { //Create a resuming trade object on closing the triggered object with a resume flag. 
      object* objObjectResuming = NULL;
      if (cobjObjectTriggered.getOperationInt() > OP_SELLLIMIT) 
         messageV(StringConcatenate(gsttVariousConsts.msgWrongOrder, " Only positions closed by limit orders can be resumed!")); //OP_SELLLIMIT=3. Is it OP_BUYSTOP=4 or OP_SELLSTOP=5?
      else {
         int intOperationResuming = resumingOperation(cobjObjectTriggered.getOperationInt()); //Convert OP_BUYLIMIT to OP_SELLSTOP and OP_SELLLIMIT to OP_BUYSTOP.
         string strOperationResuming = gstrOperations[intOperationResuming - OP_BUYLIMIT];
         double dblPriceResuming = resumingPrice(cobjObjectTriggered.getOperationInt(), cobjObjectTriggered.getPrice()); //Place the converted resuming trade object below (-1 multiplier) or above (+1 multiplier) the triggered one.
         object* objObjectExisting = item(strOperationResuming);
         if (objObjectExisting == NULL) 
            objObjectResuming = add(strOperationResuming, intOperationResuming);  //Prevent name collision between an existing and newly created object. //Does not an object with the same trade operation as a resuming one exist? Add one.
         else { //An object with the same trade operation as a resuming one exists.
            if (objObjectExisting.getPending()) { //Has it been pending?
               objObjectExisting.setTrade(); //The resuming object will not be pending.
               setCount(cintCountPending - 1); //Decrement the count of pending trade objects.
            }
            objObjectExisting.rename(StringConcatenate(objObjectExisting.name, " renamed")); //Rename only the chart object. From now on the collection of objects will refer not to it but to the resuming object that will be created below.
            Alert("Object ", objObjectExisting.name, " renamed!");
            objObjectResuming = objObjectExisting;
         }
         graphObject objGraphObject(objObjectResuming.name, Time[gsttVariousConsts.idx0], dblPriceResuming);
         cobjObjectTriggered.setDescription(""); //Clear the description of the triggered trade object to prevent its accidential wrong reuse.
      }  
      return objObjectResuming;
   }   
};

#endif //OBJECTS_MQH
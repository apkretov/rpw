#property strict
#ifndef POSITION_MQH
#define POSITION_MQH

#include <stdlib.mqh> //This is needed for ErrorDescription.
#include "functions.mqh"
#include "graphObject.mqh"

class position { 
   int cintTicket; //The ticket of an open posistion. In the trade disabled mode, the ticket encodes a trade operation: -1 is no ticket, 0/1 is buy/sell.
   int cintTicketNull;
   bool cblnTradeDisabled;
   int cintTotalnet;
   string cstrTotalnet;
   int cintSlippage;
   graphObject* cobjLabelOpened;
   graphObject* cobjLabelClosed;
   graphObject* cobjLabelLots; //TO DO: labelLots shouldn't be a member of this class.
   
   void displayOpenedClosed(const string& strOperation, double dblPrice, graphObject& objOpenedClosed) const { 
		#ifdef SIMULATOR
	      string strDescription = StringConcatenate(strOperation, " at ", formatPrice(dblPrice), "   ", cintTotalnet);
	      objOpenedClosed.setDescription(strDescription);
	      messageV( StringConcatenate(strDescription) ); //The tester does not display objOpenedClosed.getDescription(). That's why strDescription has been introduced.
		#else
	      objOpenedClosed.setDescription( StringConcatenate(strOperation, " at ", formatPrice(dblPrice), "   ", cintTotalnet) );
	      messageV( StringConcatenate(objOpenedClosed.getDescription()) );
		#endif
   }
   
   void getClosingPriceAndOperation(int intOperation, double& dblPrice, string& strOperation) const { 
      const string strBought = "Bought"; 
      const string strSold = "Sold"; 
      switch(intOperation) {
         case OP_BUY: 
            dblPrice = Bid;
            strOperation = strSold; 
            break; 
         case OP_SELL: 
            dblPrice = Ask;
            strOperation = strBought;
      }  
   }
   
   void setTotalnet(int intOperation, int intLots) { 
      cintTotalnet = cintTotalnet - (intOperation * 2 - 1) * intLots;
      GlobalVariableSet(cstrTotalnet, cintTotalnet);
   }
   
public:
   position() : cintTicketNull(-1), cintTotalnet(0), cstrTotalnet("Totalnet"), cintSlippage(10) { 
      const long lngXOpendedClosed = 4;
      const long lngYOpended = 27;
      const long lngYClosed = 41;
      const long lngXLots = 200; //190;
      const long lngYLots = 0;

      if (!GlobalVariableCheck(cstrTotalnet)) { //Arrange saving the total net, unless arranged before.
         GlobalVariableSet(cstrTotalnet, cintTotalnet);          
      } else //Get the cintTotalnet saved as a global variable unlike a member one to enable external manipulation.
         cintTotalnet = (int)GlobalVariableGet(cstrTotalnet); 

      cobjLabelOpened = new graphObject("opened", lngXOpendedClosed, lngYOpended);
      cobjLabelClosed = new graphObject("closed", lngXOpendedClosed, lngYClosed);
      cobjLabelLots = new graphObject("lots", lngXLots, lngYLots);

      cobjLabelLots.setDescription(Lots);
      cblnTradeDisabled = true; //OFF ((int)SymbolInfoInteger(_Symbol, SYMBOL_TRADE_MODE) == SYMBOL_TRADE_MODE_DISABLED); //Is trading disabled?
   }

   ~position() { // Delete the dynamically created graph objects. 
      cobjLabelOpened.deleteFromChart();
      delete cobjLabelOpened;
      cobjLabelClosed.deleteFromChart();
      delete cobjLabelClosed;
      cobjLabelLots.deleteFromChart();
      delete cobjLabelLots;
   }

   int getTicket() const { 
      return cintTicket; 
   } 
   
   int getTotalnet() const { 
      return cintTotalnet; 
   } 
   
   graphObject* getLabelOpened() const { 
      return cobjLabelOpened; 
   } 
   
   graphObject* getLabelClosed() const { 
      return cobjLabelClosed; 
   } 
   
   graphObject* getLabelLots() const { //TO DO: labelLots shouldn't be a member of this class. 
      return cobjLabelLots; 
   } 

   void refresh() { //Are there any Channels position? 
      cintTotalnet = (int)GlobalVariableGet(cstrTotalnet); //Get the cintTotalnet saved as a global variable unlike a member one to enable external manipulation.
      if (cblnTradeDisabled) { //Is trading disabled? Get the ticket as converted from the cintTotalnet.
         if (cintTotalnet == 0) 
            cintTicket = cintTicketNull;
         else if (cintTotalnet > 0) 
            cintTicket = OP_BUY;
         else 
            cintTicket = OP_SELL;
      } else { //Get it normally.
         cintTicket = cintTicketNull;
         for (int i = 0; i < OrdersTotal(); i++) {
            if (OrderSelect(i, SELECT_BY_POS)) {
               if (OrderMagicNumber() == MagicNumber) 
                  cintTicket = OrderTicket();
               break;
            }  
         }  
      }  
   }
   
   bool open(int intOperation, double dblStopLoss = 0, double dblTakeProfit = 0) { 
      const string strBought = "Bought"; 
      const string strSold = "Sold"; 
      bool blnOpen = false;
      int intLots = 0;
		int intTotalnetAbs = MathAbs(cintTotalnet);
		int intTotalnetResult = intTotalnetAbs + Lots; //The resulting lots.
		
		//TO DO: Use the opening lots calculation.
		if (intTotalnetResult <= LotsMax) //Won't the resulting lots exceed the maximum?
		   intLots = Lots;
		else if (intTotalnetAbs == LotsMax) //The maximum exeeded.
		   messageV("The maximal number of lots have been opened already before!");
		else 
		   intLots = LotsMax - intTotalnetAbs; //Open lots left till the maximum.
		
		if (intLots > 0) { //Are there lots to open?
         double dblPrice = 0;
         string strOperation;
         switch(intOperation) {
            case OP_BUY: 
               dblPrice = Ask;
               strOperation = strBought;
               break; 
            case OP_SELL: 
               dblPrice = Bid;
               strOperation = strSold;
         }
         setTotalnet(intOperation, intLots);
  
         if (cblnTradeDisabled) { //Is trading disabled?
            cintTicket = intOperation;
            displayOpenedClosed(strOperation, dblPrice, cobjLabelOpened);
            cobjLabelOpened.setColourWhite();
            cobjLabelClosed.setColourGray(); //Gray it out just in case it may be still displaying a prior close price.
            blnOpen = true;
         } else {
            cintTicket = OrderSend(Symbol(), intOperation, intLots, dblPrice, cintSlippage, dblStopLoss, dblTakeProfit, StringConcatenate(/*__FILE__, " ", _Period*/ EnumToString(MagicNumber)), MagicNumber);
            if (_LastError != ERR_NO_ERROR) 
            	Alert("Order not sent. Error: ", ErrorDescription(_LastError));
            else if (OrderSelect(cintTicket, SELECT_BY_TICKET)) {
               setTotalnet(intOperation, intLots);
               displayOpenedClosed(strOperation, OrderOpenPrice(), cobjLabelOpened);
               cobjLabelOpened.setColourWhite();
               cobjLabelClosed.setColourGray(); //Gray it out just in case it may be still displaying a prior close price.
               blnOpen = true;
            }  
         }  
      }
      return blnOpen;
   }

   bool matchClosingToOpened(int intOperationClosing) const { // A closing operation must match the open one. 
      bool blnMatchClosingToOpened = false;
      int intOperationOpened = gsttVariousConsts.operationNull;
      if (cblnTradeDisabled) 
         intOperationOpened = cintTicket;
      else if (OrderSelect(cintTicket, SELECT_BY_TICKET)) 
         intOperationOpened = OrderType();
      if (BUYtoSELL(intOperationClosing) == intOperationOpened) 
         blnMatchClosingToOpened = true;
      return blnMatchClosingToOpened;  
   }

   bool close(bool blnSelectOrder, int intLots) { // Close the open position. Reselect the order (if blnSelectOrder = true), unless it has been selected right before the function call. 
      string strOperation;
      double dblPrice = 0;
      bool blnClose = false;
      if (cblnTradeDisabled) {
         setTotalnet(BUYtoSELL(cintTicket), intLots);
         blnClose = true;
         getClosingPriceAndOperation(cintTicket, dblPrice, strOperation);
         displayOpenedClosed(strOperation, dblPrice, cobjLabelClosed);
         cobjLabelClosed.setColourWhite();
         cobjLabelOpened.setColourGray();
      } else {
         bool blnOrderSelected;
         if (blnSelectOrder) 
            blnOrderSelected = OrderSelect(cintTicket, SELECT_BY_TICKET); //Select the order (if blnSelectOrder = true), unless it has been selected right before the function call.
         else 
            blnOrderSelected = true;
         if (blnOrderSelected) { //Is the order selected?
            setTotalnet(BUYtoSELL(OrderType()), intLots);
            getClosingPriceAndOperation(OrderType(), dblPrice, strOperation);
            if (cintTotalnet != 0) 
               blnClose = true;
            else {
               blnClose = OrderClose(cintTicket, OrderLots(), dblPrice, cintSlippage); //Send a closing order, if the total position has been closed.
               if (_LastError != ERR_NO_ERROR) 
               	Alert("Position not closed. Error: ", ErrorDescription(_LastError));
            }
            if (blnClose) {
               displayOpenedClosed(strOperation, OrderClosePrice(), cobjLabelClosed);
               cobjLabelClosed.setColourWhite();
               cobjLabelOpened.setColourGray();
            }  
         }  
      }
      return blnClose;
   }

   datetime getOpenTime() const { 
      datetime dtmOpenTime = 0;
      if (!cblnTradeDisabled) { //If trading is disabled return 0. Otherwise get it normally. If the variable will be needed later arrange its storage and retrieval. 
         if (OrderSelect(cintTicket, SELECT_BY_TICKET)) dtmOpenTime = OrderOpenTime();         
      }
      return dtmOpenTime;
   }

   datetime getCloseTime() const { 
      datetime dtmCloseTime = 0;
      if (!cblnTradeDisabled) { //If trading is disabled return 0. Otherwise get it normally. If the variable will be needed later arrange its storage and retrieval. 
         if (OrderSelect(cintTicket, SELECT_BY_TICKET)) dtmCloseTime = OrderCloseTime();         
      }
      return dtmCloseTime;
   }

   double getOpenPrice() const { 
      double dblOpenPrice = 0;
      if (!cblnTradeDisabled) { //If trading is disabled return 0. Otherwise get it normally. If the variable will be needed later arrange its storage and retrieval. 
         if (OrderSelect(cintTicket, SELECT_BY_TICKET)) dblOpenPrice = OrderOpenPrice();         
      }
      return dblOpenPrice;
   }

   double getClosePrice() const { 
      double dblClosePrice = 0;
      if (!cblnTradeDisabled) { //If trading is disabled return 0. Otherwise get it normally. If the variable will be needed later arrange its storage and retrieval. 
         if (OrderSelect(cintTicket, SELECT_BY_TICKET)) dblClosePrice = OrderClosePrice();         
      }
      return dblClosePrice;
   }
};

#endif //POSITION_MQH
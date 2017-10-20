#include "MT4QuikConnector.h"
using std::string;
using std::to_string;
using std::exception;
//#include "terminal.h"
#include "events.h"
#include "mt4QuikConnector_.h"
#include "objects.h"
#include "position.h"
#include "alg.h"
#include "enumerators.h"
//#include "functionsMT4.h"
#include "terminalMT4.h"
using namespace mtqc;
using namespace mtqc::terminalMT4;
#include "trend.h"
#include "switch.h"
#include "messages.h"
#include "functions.h"
using namespace mtqc::functions;
//#include "constantsXML.h"
#include "algEA.h"
using namespace mtqc::algEA;
#include "constants.h"
using namespace mtqc::constants;
#include "server.h"

static int OnAllTrade(lua_State* L); //A forward declaration required in srvMessageToQuik. Declared ouside the MT4QuikConnector namespace becuase the function is out of the namespace's scope as well.
int server::startQuikServer(lua_State* L); //The forwrd declarations.

namespace mtqc {
	namespace MT4QuikConnector {
		//enum struct enmKeys { /*KTB keyEnter = 13,*/ keyEsc = 27, /*KTB keyArrowUp = 38, keyArrowDown = 40,*/ keyB = 66, keyS = 83 /*KTB, keyV = 86, keyF5 = 116*/ };
		enum struct enmKeys : int { /*KTB keyEnter = 13,*/ keyEsc = 27, /*KTB keyArrowUp = 38, keyArrowDown = 40,*/ keyB = 66, keyS = 83 /*KTB, keyV = 86, keyF5 = 116*/ };
	//}

		//extern const int gintOperationNull; //variousConsts
		//extern const string gstrOperations[6];
		//extern const bool	gblnTradeDisabled, gblnAllMessages;
		//extern const string gstrStock, gstrFutures;
		//extern const int gintLotsTraded;
		//extern const string gstrTagPrice;
		//extern const string gstrTagAlligator;
		//#ifdef BLN_ALG
		//	extern const int gintCandlesCount, gintChartOffset;
		//#endif
		constexpr int QTABLE_LBUTTONUP = 11, QTABLE_VKEY = 7;
		//constexpr int OP_BUY = 0, OP_SELL = 1, OP_BUYLIMIT = 2, OP_SELLLIMIT = 3, OP_BUYSTOP = 4, OP_SELLSTOP = 5; //Copy/pasted for MT4 compatability to make the switch operator work.
		//extern const string gstrMTQC;
		//extern constantsXML gobjConstantsXML;

		extern double Bid, Ask;
		//extern std::unique_ptr<trend> gobjTrend; //TO DO: ptr. //TO DO gptr.
		terminal gobjTerminal;
		static events mobjEvents;
		static mt4QuikConnector_ mobjMT4QuikConnector;
		static objects mobjObjects;
		//static position mobjPosition(gblnTradeDisabled, gintLotsTraded);
		//static position mobjPosition(gobjConstantsXML.getTradeDisabled(), gobjConstantsXML.getLotsTraded());
		static position mobjPosition;

		//int startQuikServer(lua_State* L); //The forwrd declarations.
		//static int OnAllTrade(lua_State* L); //A forward declaration required in srvMessageToQuik.
		//void readXML(constantsXML& objConstantsXML);

		void srvMessageToQuik(const char* const chrMessage) { // This function was in Qlua. 
			try {
				#ifdef BLN_DISPLAY_MESSAGE_TO_QUIK
					messages::message(string(chrMessage)); 
				#endif
				#ifdef BLN_TEST_NO_QUOTES_ERROR
					OnAllTrade(gobjTerminal.getL());
				#endif
				if (!mobjEvents.getSrvMessageToQuik()) { //No new action till the prvevious message has get processed.
					mobjEvents.setSrvMessageToQuik_message(chrMessage); //First set the message and then set the flag about it (below).
					mobjEvents.setSrvMessageToQuik(true);
				}	
			}
			catch(const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
		}

		inline static bool KTB_swap(int intIdx) { return false; } //Swap a support/resistance. To be developed, if necessary. +

		static void runOpenProcedure(bool blnAlert) { // The open procedure of the run fucntion. The function is called by the OnTransReply function unless trading is disabled. 
			int intOperationTriggered = mobjObjects.getObjectTriggered()->getOperation();
			if (blnAlert) mobjObjects.remove(intOperationTriggered);
			else {
				mobjObjects.renameAll(intOperationTriggered, false);
				if (!KTB_swap(0)) mobjObjects.remove(intOperationTriggered);
			}
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			mobjObjects.displayPrices(mobjPosition.strClose, false); // Dispay the close prices of all the trade objectes. If there is none don't display anyting.
		}

		static void runCloseProcedure() { // The close procedure of the run fucntion. The function is called by the OnTransReply function unless trading is disabled. 
			object_SP objObjectResuming{}; //Introducing C++11 Brace-Initialization //int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519
			string strOpenClose = mobjPosition.strOpen; //If after closing any object will remain display them as opening.
			object_SP objObjectTriggered = mobjObjects.getObjectTriggered();
			if (objObjectTriggered->isResuming()) objObjectResuming = mobjObjects.createResuming(); //Is resuming required? Remember the trade operation index of the opened position.
			else if (objObjectTriggered->isReversing()) strOpenClose = mobjPosition.strClose; //Is reversing required? //If any objects remain after reversing display them as closing.
			mobjObjects.remove(objObjectTriggered->getOperation()); //Rename the trade object to prevent its accidential wrong reuse.
			if (objObjectResuming) mobjObjects.renameAll(objObjectResuming->getOperation(), false);
			else mobjObjects.renameAll(gintOperationNull, false);
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			mobjObjects.displayPrices(strOpenClose, false); //Dispay the prices reset as opening or closing depending on the above commands.
		}

		static void runOpen(object_SP objObjectTriggered, string strAlert) { // The open procedure of the run fucntion. 
			if (objObjectTriggered) { //Has any trading object triggered?
				//if (!gobjTerminal.getOfferBid(gstrFutures.c_str())) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer?
				if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) 
					gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer?
				else {
					if (objObjectTriggered->isAlert()) { //Alert and skip opening while doing all the same operations as if it's opening in a trade disabled mode.
						if (gobjConstantsXML.getAllMessages()) messages::message( strAlert + gstrOperations[objObjectTriggered->getOperation()] + " " + numberToStringF(objObjectTriggered->getPrice()) );
						runOpenProcedure(true);
					} else if ( mobjPosition.open(objObjectTriggered->getOperationBuySell(), gobjTerminal) ) { //Fulfill an operation, unless it's just an alert.
						if (gobjTrend) gobjTrend->setPhase(enmPhases::phase_signal_triggered); //Make sure the pointer is currently valid. //Alligator connection.
						//if (gblnTradeDisabled) runOpenProcedure(false); //Continue the opening procedure directly in a trade disables mode.
						if (gobjConstantsXML.getTradeDisabled()) 
							runOpenProcedure(false); //Continue the opening procedure directly in a trade disables mode.
						else { //Continue the opening procedure after a transcation reply.
							mobjEvents.setOnSendTransaction_opening(true);
							mobjEvents.setOnSendTransaction(true);
						}	
					}	
				}	
			}	
		}

		static void run() { 
			/*KTB if (gobjTerminal.getPriceStock() == 0) gobjTerminal.messageNoPriceStock(); //The priceStock must be assigned on the OnAllTrade event.
			else*/ if (!mobjEvents.getOnSendTransaction()) { //Open/close a position, unless a previously sent transaction is waiting for a reply.
				mobjObjects.scanTriggered(gobjTerminal.getPriceStock());
				object_SP objObjectTriggered = mobjObjects.getObjectTriggered(); //Get a pointer for a quick reference.
				static string strAlert = "Alert: ";
				if (mobjPosition.getTotalnet() == 0) runOpen(objObjectTriggered, strAlert); //Is there no Channels position? Check to open one.
				else { //There is an open position. Check to close it.
					if (objObjectTriggered) { //Has any trading object triggered?
						//if (!gobjTerminal.getOfferBid(gstrFutures.c_str())) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
						//if (!gobjTerminal.getOfferBid(gstrFutures)) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
						if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
						else {
							if (!mobjPosition.matchClosingToOpened(objObjectTriggered->getOperationBuySell())) runOpen(objObjectTriggered, strAlert);
							else { //A closing trade operation must match the open one.
								if (objObjectTriggered->isAlert()) { //Alert and skip closing while doing all the same operations as if it's closing in a trade disabled mode.
									if (gobjConstantsXML.getAllMessages()) messages::message( strAlert + gstrOperations[objObjectTriggered->getOperation()] + " " + numberToStringF(objObjectTriggered->getPrice()) );
									mobjObjects.remove(objObjectTriggered->getOperation()); //Rename the trade object to prevent its accidential wrong reuse.
									mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
									mobjObjects.displayPrices(mobjPosition.strClose, false); //Dispay the prices reset as opening or closing depending on the above commands.
								}else if (mobjPosition.close(gobjTerminal, objObjectTriggered->isReversing())) { //If reversing is required open a new position to the same direction as the closing one. That is buy/sell all the lots opened before plus one more.
									//if (gblnTradeDisabled) runCloseProcedure(); //Continue the closing procedure directly in a trade disables mode.
									if (gobjConstantsXML.getTradeDisabled()) runCloseProcedure(); //Continue the closing procedure directly in a trade disables mode.
									else { //Continue the closing procedure after a transcation reply.
										mobjEvents.setOnSendTransaction_closing(true);
										mobjEvents.setOnSendTransaction(true);
		}	}	}	} 	}	}	}	}

		static bool checkPriceStockOfferBid() { // Make sure the stock price and the futures offer/bid are available. 
			/*KTB if (gobjTerminal.getPriceStock() == 0) gobjTerminal.messageNoPriceStock(); //The priceStock must be assigned on the OnAllTrade event.
			//else if (!gobjTerminal.getOfferBid(gstrFutures.c_str())) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
			//else if (!gobjTerminal.getOfferBid(gstrFutures)) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
			else*/ if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer? //ON gstrFutures DOM
			else return true;
			return false;
		}

		static void closePosition() { // Close an open position, if any. 
			if (checkPriceStockOfferBid()) { // Make sure that the stock price and the futures offer/bid are available.
				if (mobjPosition.getTotalnet() != 0) mobjPosition.close(gobjTerminal, false); //Is there a Channels position to be closed? //Close all the lots opened.
		}	}

		static void disableObjects() { // Disable objects / close position on a key press. 
			mobjObjects.renameAll(gintOperationNull, true);
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			messages::message("Objects disabled");
		}

		static void keyPressedEsc() { // Esc pressed to unselect all objects / disable them / close position. 
			//KTB if (mobjObjects.count > 0) disableObjects(); //Is there any object to be disabled?
			if (mobjObjects.getCount(true) > 0) disableObjects(); //Is there any object to be disabled?
			else closePosition(); //Close an open position, if any.
		}

		/*KTB
		static void keyPressedF5() { // F5 pressed to reset. 
			disableObjects();
			closePosition();
		}*/

		static void setTransactionKeyPressedOperation(int intOperation) { // Set OnSendTransaction_keyPressedOperation.
			mobjEvents.setOnSendTransaction_keyPressedOperation(true);
			mobjEvents.setOnSendTransaction_keyPressedOperationInt(intOperation);
			mobjEvents.setOnSendTransaction(true);
		}

		static void keyPressedOperationOpen(int intOperation) { // The open procedure of the keyPressedOperation fucntion.
			int intLotsOpened;
			if (mobjPosition.open(intOperation, gobjTerminal, intLotsOpened)) { // Has it opened? //Alligator connection.
				if (gobjTrend) { //Make sure the pointer is currently valid. //Alligator connection.
					gobjTrend->setPhase(enmPhases::phase_signal_triggered); //Alligator connection.
					gobjTrend->tradeActive_SetType(intOperation); //Alligator connection.
					gobjTrend->tradeActive_SetPriceOpen(gobjTerminal.getPriceStock()); //MT4 version Bid/Ask. //Alligator connection.
					gobjTrend->tradeActive_SetLots(intLotsOpened); //Alligator connection.
				}
				//if (gblnTradeDisabled) mobjObjects.renameAll(gintOperationNull, false); //Continue the opening procedure directly in a trade disables mode.
				if (gobjConstantsXML.getTradeDisabled()) 
					mobjObjects.renameAll(gintOperationNull, false); //Continue the opening procedure directly in a trade disables mode.
				else 
					setTransactionKeyPressedOperation(intOperation); //Set OnSendTransaction_keyPressedOperation.
			}	
		}

		void keyPressedOperation(int intOperation) { // KeyArrowUp/KeyB/KeyArrowDown/KeyS pressed to buy or sell. +
			if (checkPriceStockOfferBid()) { // Make sure that the stock price and the futures offer/bid are available.
				if (mobjPosition.getTotalnet() == 0) 
					keyPressedOperationOpen(intOperation); //Is there no Channels position?
				else { //Check to close a Channels position.
					if (!mobjPosition.matchClosingToOpened(intOperation)) 
						keyPressedOperationOpen(intOperation);
					else { //Does the closing operation match the open one?
						if (mobjPosition.close(gobjTerminal, false)) {
							if (gobjConstantsXML.getTradeDisabled()) mobjObjects.renameAll(gintOperationNull, false); //Continue the opening procedure directly in a trade disables mode.
							else setTransactionKeyPressedOperation(intOperation); //Set OnSendTransaction_keyPressedOperation.	
						}	
					}	
				}	
			}	
		}

		static void eventSrvMessageToQuik(const string& strMessage) { 
			try {
				mobjMT4QuikConnector.setMessage(strMessage);
				if (mobjMT4QuikConnector.pricesSent()) { //Is it a prices message (with a number of orders in front) vs. an initialisation message?
					mobjObjects.set(strMessage);
					mobjObjects.displayPrices( mobjPosition.getTotalnet() == 0 ? mobjPosition.strOpen : mobjPosition.strClose, true );
					run();
				} else if (mobjMT4QuikConnector.disableObjects()) 
					disableObjects(); //Is it a Disable Ojects command message?
				else if (mobjMT4QuikConnector.closePosition()) { //Is it a Close Position command message?
					if (checkPriceStockOfferBid()) { // Make sure that the stock price and the futures offer/bid are available.
						if (mobjPosition.getTotalnet() != 0) mobjPosition.close(gobjTerminal, false); //Is there a Channels position to be closed?
					}
				} else if (mobjMT4QuikConnector.refreshConstants()) 
					gobjConstantsXML.readXML(); // Refresh the constants.
				else {
					int intOperation = mobjMT4QuikConnector.keyPressedOperation(); //Is an operation key pressed?
					if (intOperation != gintOperationNull) 
						keyPressedOperation(intOperation);
					else {
						int intLots = mobjMT4QuikConnector.setLots();
						if (intLots != 0) { //Is a Set Lots command received? //Set the number of lots.
							mobjPosition.setLotsTraded(intLots);
							messages::message("Lots: " + to_string(intLots));
						}	
					}	
				}	
			}
			catch(const exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__); 
			}
		}

		static int tableNotificationCallback(lua_State* L) { //Register necessary events only. Формат вызова функции обратного вызова для обработки событий в таблице: FUNCTION (NUMBER t_id, NUMBER msg, NUMBER par1, NUMBER par2) Параметры: t_id – идентификатор таблицы, для которой обрабатывается сообщение, par1 и par2 – значения параметров определяются типом сообщения msg, msg – код сообщения. 
			try {
				int msg = lua_tointeger(L, -3);
				int par2 = lua_tointeger(L, -1);
				lua_pop(L, 4); //Clear the stack off the function's 4 parameters: operationsTable, msg, par1, par.
				bool blnContinue{}; //Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
				if (msg == QTABLE_LBUTTONUP) blnContinue = true; //A left mouse - click.
				else if (msg == QTABLE_VKEY) if (par2 == (int)enmKeys::keyEsc /*KTB || par2 == mintKeys.keyArrowUp*/ || par2 == (int)enmKeys::keyB /*KTB || par2 == mintKeys.keyArrowDown*/ || par2 == (int)enmKeys::keyS) blnContinue = true; //A key is pressed.
				if (blnContinue) {
					mobjEvents.setTableNotificationCallback(true);
					mobjEvents.setTableNotificationCallback_msg(msg);
					mobjEvents.setTableNotificationCallback_par2(par2);
			}	}
			catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
			return 0; //Return 0 because of the function declaration as static int.
		}

		static void eventTableNotificationCallback(int msg, int par2) { 
			if (msg == QTABLE_LBUTTONUP) keyPressedOperation(BUYtoSELL(par2)); //A left mouse-click. //Sell or buy. Convert the operation first (ref. table creation).
			else if (msg == QTABLE_VKEY) {
				if (par2 == (int)enmKeys::keyEsc) keyPressedEsc(); //Escape pressed? //Unselect all objects / disable them / close position.
				else if (/*KTB par2 == keyArrowUp ||*/ par2 == (int)enmKeys::keyB) keyPressedOperation(OP_BUY); //Buy.
				else if (/*KTB par2 == keyArrowDown ||*/ par2 == (int)enmKeys::keyS) keyPressedOperation(OP_SELL); //Sell.
				//KTB else if (par2 == keyF5) keyPressedF5();
		}	}

		/*KTB
		void getNumberOf(lua_State* L, const string& strFunction) { 
			lua_getglobal(L, "getNumberOf"); lua_pushstring(L, "all_trades"); lua_pcall(L, 1, 1, 0); double dblNumberOf = lua_tonumber(L, -1);
			message(strFunction + ": gobjTerminal.getPriceStock() = " + to_string(gobjTerminal.getPriceStock()) + "   dblNumberOf = " + to_string(dblNumberOf));
		}*/

		static bool initialise(lua_State* L) { // In addition to the OnInit function, complete initialisation invoked from mainQlua. The latter is more robust because of its parallel thread. 
			try {
				gobjTerminal.createOperationsTable(tableNotificationCallback);
				gobjConstantsXML.readXML();
				mobjPosition.initialise(gobjConstantsXML.getTradeDisabled(), gobjConstantsXML.getLotsTraded());
				#ifdef BLN_ALG
					#ifndef BLN_TRADE_SR
						setCandlesByIndex(L, wstringToString(gobjConstantsXML.getStockTagPrice()), wstringToString(gobjConstantsXML.getStockTagAlg()), gintCandlesCount, gintChartOffset);
					#else
						setCandlesByIndex(L, wstringToString(gobjConstantsXML.getFuturesTagPrice()), wstringToString(gobjConstantsXML.getFuturesTagAlg()), gintCandlesCount, gintChartOffset);
					#endif
				#endif
				#ifdef BLN_QUIK_SERVER
					server::startQuikServer(L);
				#endif
				return true;
			}
			catch (const exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__);
				return false;
}	}	}	}

using namespace mtqc::MT4QuikConnector;

static int OnStop(lua_State* L) { 
	try {
		gobjTerminal.destroyOperationsTable();
		//KTB functionsMT4::deleteCandlesByIndex();
		messages::messageInit("Quit Quik to quit " + gstrMTQC + ".", L); //Unlike message, use messageInit to prevent an error perhapse because L gets terminated.
		gobjTerminal.setRun(false);
	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int mainQlua(lua_State* L) { 
	try {
		if (initialise(L)) {
			gobjTerminal.setRun(true);
			while (gobjTerminal.getRun()) {
				if (mobjEvents.getOnSendTransaction_keyPressedOperationResumed()) { //Resuming the key pressed operation procedure? //TO DO: Try to apply priority_queue here.
					int intOperation = mobjEvents.getOnSendTransaction_keyPressedOperationInt(); //Remember the operation to be resumed.
					mobjEvents.OnSendTransaction_reset(); //Reset all the parameters of the previous key pressed operation before resuming it so that the procedure begins from scratch.
					keyPressedOperation(intOperation); //Resume it.
				}
				if (mobjEvents.getTableNotificationCallback()) {
					eventTableNotificationCallback(mobjEvents.getTableNotificationCallback_msg(), mobjEvents.getTableNotificationCallback_par2());
					mobjEvents.tableNotificationCallback_reset();
				}
				if (mobjEvents.getSrvMessageToQuik()) { //Check the events, implement them, and reset their flags.
					eventSrvMessageToQuik(mobjEvents.getSrvMessageToQuik_message());
					mobjEvents.srvMessageToQuik_reset();
				}
				if (mobjEvents.getOnTransReply()) {
					if (mobjEvents.getOnSendTransaction_opening()) runOpenProcedure(false); //Complete the opening procedure.
					else if (mobjEvents.getOnSendTransaction_closing()) runCloseProcedure(); //Complete the closing procedure.
					else if (mobjEvents.getOnSendTransaction_keyPressedOperation()) mobjObjects.renameAll(gintOperationNull, false); //Complete the opening/closing procedure.
					mobjEvents.setOnTransReply(false); //The opening/closing procedure is over. Reset the flags.
					mobjEvents.OnSendTransaction_reset();
				}
				if (mobjEvents.getOnAllTrade()) {
					run();
					mobjEvents.setOnAllTrade(false);
				}
				Sleep(1); //Sleep function @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms686298(v=vs.85).aspx
				//To test it for debugging -----------------------------------------------------------------------------------------------------------------------------------------------------------
				//OnStop(L);
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	}	}	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnAllTrade(lua_State* L) { 
	try {
		#ifndef BLN_TRADE_SR
			static string strStock = wstringToString(gobjConstantsXML.getStock()); //Keep the stock name in a local variable to boost performance.
		#else
			static string strStock = wstringToString(gobjConstantsXML.getFutures()); //Keep the stock name in a local variable to boost performance.
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			//gobjTerminal.setPriceStock(DBL_PRICE_STOCK);
			gobjTerminal.setPriceStock(gdblPriceStock);
		#else
		lua_getfield(L, -1, "sec_code");
		if (lua_tostring(L, -1) == strStock) { //Is that the selected stock?	//Get the stock's price. //TO DO: Use ds:SetUpdateCallback(MyFuncName); -- Позволяет задать пользователю функцию обратного вызова для обработки изменившихся свечей, т.е. когда по выбранному в CreateDataSource параметру в терминал поступит новое значение (возможно такое же), автоматически будет вызвана данная функция, в которую будут передан индекс последней свечи графика, а так же добавятся новые данные в таблицу ds
			lua_getfield(L, -2, "price"); gobjTerminal.setPriceStock(lua_tonumber(L, -1)); lua_pop(L, 2); //Clear the stack off 'sec_code' and 'price' Qlua passes.
			#endif 
			#ifdef BLN_TRADE_SR //To test it in the evening session
				//gobjTerminal.setPriceStock(gobjTerminal.getPriceStock() / INT_STOCK_TO_FUTURES_RATIO + DBL_STOCK_TO_FUTURES_ADJUSTMENT);
				gobjTerminal.setPriceStock(gobjTerminal.getPriceStock() / gintContractSize + gdblStockToFuturesAdjustment);
			#endif
			mobjEvents.setOnAllTrade(true);
			#ifdef BLN_ALG
				OnTick(gobjTerminal.getPriceStock()); //thread objThread(functionsMT4::OnTick, gobjTerminal.getPriceStock()); objThread.detach();
				algEA::OnTickAlg(); //Alligatort EA's OnTick function.
			#endif
			#ifndef BLN_TEST_NO_QUOTES_ERROR
		}else lua_pop(L, 2); //Clear the stack off 'sec_code' and 'price' Qlua passes.
		#endif 
	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnTransReply(lua_State* L) { //Результат транзакции можно получить, воспользовавшись функцией обратного вызова OnTransReply @ http://help.qlua.org/ch4_5_11.htm //See a detailed description @ http://robostroy.ru/community/article.aspx?id=765 
	try {
		lua_getfield(L, -1, "sec_code"); bool blnIsNil = lua_isnil(L, -1); lua_pop(L, 1);
		if (!blnIsNil)	mobjEvents.setOnTransReply(true); //Is a transaction successful? //Complete the opening procedure.
		else {
			lua_getfield(L, -1, "result_msg"); string strResult_msg = lua_tostring(L, -1); lua_pop(L, 1);
			messages::message("Transaction failed! result_msg: " + strResult_msg + " Resuming transaction...");
			if (mobjEvents.getOnSendTransaction_keyPressedOperation()) mobjEvents.setOnSendTransaction_keyPressedOperationResumed(true); //Resume the key pressed operation procedure.
			else if (mobjEvents.getOnSendTransaction_opening() || mobjEvents.getOnSendTransaction_closing()) { //Resume the opening/closing procedure.
				mobjEvents.OnSendTransaction_reset();
				mobjEvents.setOnAllTrade(true);
	}	}	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnFuturesClientHolding(lua_State* L) { // Функция вызывается терминалом QUIK при изменении позиции по срочному рынку. 
	try {
		lua_getfield(L, -1, "sec_code"); string strSec_code = lua_tostring(L, -1); lua_pop(L, 1);
		if (strSec_code == wstringToString(gobjConstantsXML.getFutures())) { // Is that my security that has changed?
			lua_getfield(L, -1, "totalnet"); mobjPosition.setTotalnet(lua_tointeger(L, -1)); lua_pop(L, 1);
	}	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnTrade(lua_State* L) { // Функция вызывается терминалом QUIK при совершении Вами новой сделки (обычно вызывается по 2 раза для каждой сделки) @ http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/ 
	try {
		lua_getfield(L, -1, "trade_num"); int intTrade_num = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, -1, "flags");		 int intFlags		= lua_tointeger(L, -1); lua_pop(L, 1); //assert(!"Make sure trade.flags is correctly converted into integer and iterpreted in mobjPosition.recordTrade.");
		lua_getfield(L, -1, "price");		 double dblPrice	= lua_tonumber(L, -1);	lua_pop(L, 1);
		lua_getfield(L, -1, "qty");		 int intQty			= lua_tointeger(L, -1);	lua_pop(L, 1);
		mobjPosition.recordTrade(intTrade_num, intFlags, to_string(dblPrice), to_string(intQty)); // Record a trade into the Trades CSV file.
	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnConnected(lua_State* L) { 
	try {	messages::message(gstrMTQC + " connected."); }
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static int OnInit(lua_State* L) { 
	try {
		messages::messageInit(gstrMTQC + " initialised.", L); //Ininialise L for messaging.
		gobjTerminal.setL(L);
	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

static struct luaL_reg ls_lib[] = { // Регистрация реализованных в dll функций, чтобы они стали "видимы" для Lua 
	{ "startQuikServer", server::startQuikServer },
	{ "tableNotificationCallback", tableNotificationCallback },
	{ NULL, NULL }
};

extern "C" LUALIB_API int luaopen_MTQC(lua_State* L) { // Регистрация названия библиотеки, видимого в скрипте Lua. IPMORTANT: When renaming the project luaopen_MTQC must be RENAMED as luaopen_PROJECTNAME! 
	try {
		luaL_openlib(L, gstrMTQC.c_str(), ls_lib, 0);
		lua_pushcclosure(L, OnStop, 0);
		lua_setglobal(L, "OnStop");
		lua_pushcclosure(L, mainQlua, 0);
		lua_setglobal(L, "main");
		lua_pushcclosure(L, OnAllTrade, 0); //Добавляет функцию в стек //ПРИМЕР РЕАЛИЗАЦИИ ФУНКЦИИ ОБРАТНОГО ВЫЗОВА ONALLTRADE ВНУТРИ DLL @ https://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/
		lua_setglobal(L, "OnAllTrade"); //Регистрирует её как коллбэк на OnAllTrade //ПРИМЕР РЕАЛИЗАЦИИ ФУНКЦИИ ОБРАТНОГО ВЫЗОВА ONALLTRADE ВНУТРИ DLL @ https://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/
		lua_pushcclosure(L, OnTransReply, 0);
		lua_setglobal(L, "OnTransReply");
		lua_pushcclosure(L, OnFuturesClientHolding, 0);
		lua_setglobal(L, "OnFuturesClientHolding");
		lua_pushcclosure(L, OnTrade, 0);
		lua_setglobal(L, "OnTrade");
		lua_pushcclosure(L, OnConnected, 0);
		lua_setglobal(L, "OnConnected");
		lua_pushcclosure(L, OnInit, 0);
		lua_setglobal(L, "OnInit");
	}
	catch (const exception& objException) { messages::messageException(objException, __FUNCTION__, __LINE__); }	
	return 0;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; } // Стандартная точка входа для DLL //Link an executable to a DLL - Implicit Linking. If any of the DLLs has an entry-point function for initialization and termination code such as DllMain, the operating system calls the function. One of the parameters passed to the entry-point function specifies a code that indicates the DLL is attaching to the process. If the entry-point function does not return TRUE, the system terminates the process and reports the error. @ https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll

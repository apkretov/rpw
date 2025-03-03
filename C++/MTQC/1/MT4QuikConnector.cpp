#include "MT4QuikConnector.h"

using std::string;
using std::to_string;
using std::exception;

#include "events.h"
#include "mt4QuikConnector_.h"
#include "objects.h"
#include "position.h"
#include "alg.h"
#include "enumerators.h"
#include "terminalMT4.h"

using namespace mtqc;
using namespace mtqc::terminalMT4;

#include "trend.h"
#include "switch.h"
#include "messages.h"

#include "functions.h"
using namespace mtqc::functions;

#include "algEA.h"
using namespace mtqc::algEA;

#include "constants.h"
using namespace mtqc::constants;

#include "server.h"

//A forward declaration required in srvMessageToQuik. Declared ouside the MT4QuikConnector namespace becuase the function is out of the namespace's scope as well.
static int OnAllTrade(lua_State* L); 

int server::startQuikServer(lua_State* L); //The forward declarations.

namespace mtqc {
	namespace MT4QuikConnector {

		enum struct enmKeys : int { 
			/*KTB keyEnter = 13,*/ 
			keyEsc = 27, 
			/*KTB 
			keyArrowUp = 38, 
			keyArrowDown = 40,
			*/ 
			keyB = 66, 
			keyS = 83 
			/*KTB
			,keyV = 86, 
			keyF5 = 116
			*/ 
		};

		constexpr int QTABLE_LBUTTONUP = 11, QTABLE_VKEY = 7;

		extern double Bid, Ask;

		terminal gobjTerminal;

		static events mobjEvents;
		static mt4QuikConnector_ mobjMT4QuikConnector;
		static objects mobjObjects;
		static position mobjPosition;

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
			catch(const exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__); 
			}	
		}

		//Swap a support/resistance. To be developed, if necessary.
		inline static bool KTB_swap(int intIdx) { 
			return false; 
		} 

		// The open procedure of the run fucntion. The function is called by the OnTransReply function unless trading is disabled. 
		static void runOpenProcedure(bool blnAlert) { 
			int intOperationTriggered = mobjObjects.getObjectTriggered()->getOperation();
			if (blnAlert) 
				mobjObjects.remove(intOperationTriggered);
			else {
				mobjObjects.renameAll(intOperationTriggered, false);
				if (!KTB_swap(0)) 
					mobjObjects.remove(intOperationTriggered);
			}
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			mobjObjects.displayPrices(mobjPosition.strClose, false); // Dispay the close prices of all the trade objectes. If there is none don't display anyting.
		}

		// The close procedure of the run fucntion. The function is called by the OnTransReply function unless trading is disabled. 
		static void runCloseProcedure() { 
			//Introducing C++11 Brace-Initialization //int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519
			object_SP objObjectResuming{}; 
			
			string strOpenClose = mobjPosition.strOpen; //If after closing any object will remain display them as opening.
			object_SP objObjectTriggered = mobjObjects.getObjectTriggered();
			
			if (objObjectTriggered->isResuming()) //Is resuming required? Remember the trade operation index of the opened position.
				objObjectResuming = mobjObjects.createResuming(); 
			else if (objObjectTriggered->isReversing()) //Is reversing required? //If any objects remain after reversing display them as closing.
				strOpenClose = mobjPosition.strClose; 

			mobjObjects.remove(objObjectTriggered->getOperation()); //Rename the trade object to prevent its accidential wrong reuse.
			if (objObjectResuming) 
				mobjObjects.renameAll(objObjectResuming->getOperation(), false);
			else 
				mobjObjects.renameAll(gintOperationNull, false);
			
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			mobjObjects.displayPrices(strOpenClose, false); //Dispay the prices reset as opening or closing depending on the above commands.
		}

		// The open procedure of the run fucntion. 
		static void runOpen(object_SP objObjectTriggered, string strAlert) { 
			if (objObjectTriggered) { //Has any trading object triggered?
				if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) 
					gobjTerminal.messageNoOfferBid(); //Is there neither a bid nor an offer?
				else {
					if (objObjectTriggered->isAlert()) { //Alert and skip opening while doing all the same operations as if it's opening in a trade disabled mode.
						if (gobjConstantsXML.getAllMessages()) 
							messages::message( 
								strAlert 
								+ gstrOperations[objObjectTriggered->getOperation()] + " " 
								+ numberToStringF(objObjectTriggered->getPrice()) 
							);
						runOpenProcedure(true);
					} 
					
					//Fulfill an operation, unless it's just an alert.
					else if ( mobjPosition.open(objObjectTriggered->getOperationBuySell(), gobjTerminal) ) { 
						//Make sure the pointer is currently valid. //Alligator connection.
						if (gobjTrend) 
							gobjTrend->setPhase(enmPhases::phase_signal_triggered); 
						
						//Continue the opening procedure directly in a trade disables mode.
						if (gobjConstantsXML.getTradeDisabled()) 
							runOpenProcedure(false); 
						else { //Continue the opening procedure after a transcation reply.
							mobjEvents.setOnSendTransaction_opening(true);
							mobjEvents.setOnSendTransaction(true);
						}	
					}	
				}	
			}	
		}

		static void run() { 
			/*KTB
			//The priceStock must be assigned on the OnAllTrade event.
			if (gobjTerminal.getPriceStock() == 0) 
				gobjTerminal.messageNoPriceStock(); 

			else*/ if (!mobjEvents.getOnSendTransaction()) { //Open/close a position, unless a previously sent transaction is waiting for a reply.
				mobjObjects.scanTriggered(gobjTerminal.getPriceStock());

				//Get a pointer for a quick reference.
				object_SP objObjectTriggered = mobjObjects.getObjectTriggered(); 
				static string strAlert = "Alert: ";
				
				//Is there no Channels position? Check to open one.
				if (mobjPosition.getTotalnet() == 0) 
					runOpen(objObjectTriggered, strAlert); 
				else { //There is an open position. Check to close it.
					
					//Has any trading object triggered?
					if (objObjectTriggered) { 

						//Is there neither a bid nor an offer? //ON gstrFutures DOM
						if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) 
							gobjTerminal.messageNoOfferBid(); 
						else {
							if (!mobjPosition.matchClosingToOpened(objObjectTriggered->getOperationBuySell())) 
								runOpen(objObjectTriggered, strAlert);

							else { //A closing trade operation must match the open one.
								//Alert and skip closing while doing all the same operations as if it's closing in a trade disabled mode.
								if (objObjectTriggered->isAlert()) { 
									if (gobjConstantsXML.getAllMessages()) 
										messages::message( 
											strAlert 
											+ gstrOperations[objObjectTriggered->getOperation()] + " " 
											+ numberToStringF(objObjectTriggered->getPrice()) 
										);
									//Rename the trade object to prevent its accidential wrong reuse.
									mobjObjects.remove(objObjectTriggered->getOperation()); 
									//Reset the displayed prires after the trade.
									mobjObjects.setPricesToDisplay(); 
									//Dispay the prices reset as opening or closing depending on the above commands.
									mobjObjects.displayPrices(mobjPosition.strClose, false); 
								} 

								//If reversing is required open a new position to the same direction as the closing one. That is buy/sell all the lots opened before plus one more.
								else if (mobjPosition.close(gobjTerminal, objObjectTriggered->isReversing())) { 

									//Continue the closing procedure directly in a trade disables mode.
									if (gobjConstantsXML.getTradeDisabled()) 
										runCloseProcedure(); 
									else { //Continue the closing procedure after a transcation reply.
										mobjEvents.setOnSendTransaction_closing(true);
										mobjEvents.setOnSendTransaction(true);
									}
								}
							}
						}
					}
				}
			}
		}

		// Make sure the stock price and the futures offer/bid are available. 
		static bool checkPriceStockOfferBid() { 
			/*KTB 
			//The priceStock must be assigned on the OnAllTrade event.
			if (gobjTerminal.getPriceStock() == 0) 
				gobjTerminal.messageNoPriceStock(); 
			else*/ if ( !gobjTerminal.getOfferBid(wstringToString(gobjConstantsXML.getFutures())) ) //Is there neither a bid nor an offer? //ON gstrFutures DOM
				gobjTerminal.messageNoOfferBid(); 
			else 
				return true;
			return false;
		}

		// Close an open position, if any. 
		static void closePosition() { 
			// Make sure that the stock price and the futures offer/bid are available.
			if (checkPriceStockOfferBid()) { 

				//Is there a Channels position to be closed? 
				if (mobjPosition.getTotalnet() != 0) 
					mobjPosition.close(gobjTerminal, false); //Close all the lots opened.
			}	
		}

		// Disable objects / close position on a key press. 
		static void disableObjects() { 
			mobjObjects.renameAll(gintOperationNull, true);
			mobjObjects.setPricesToDisplay(); //Reset the displayed prires after the trade.
			messages::message("Objects disabled");
		}

		// Esc pressed to unselect all objects / disable them / close position. 
		static void keyPressedEsc() { 
			/*KTB 
			//Is there any object to be disabled?
			if (mobjObjects.count > 0) 
				disableObjects(); 
			*/
			if (mobjObjects.getCount(true) > 0) //Is there any object to be disabled?
				disableObjects(); 
			else //Close an open position, if any.
				closePosition(); 
		}

		/*KTB
		static void keyPressedF5() { // F5 pressed to reset. 
			disableObjects();
			closePosition();
		}*/

		// Set OnSendTransaction_keyPressedOperation.
		static void setTransactionKeyPressedOperation(int intOperation) { 
			mobjEvents.setOnSendTransaction_keyPressedOperation(true);
			mobjEvents.setOnSendTransaction_keyPressedOperationInt(intOperation);
			mobjEvents.setOnSendTransaction(true);
		}

		// The open procedure of the keyPressedOperation fucntion.
		static void keyPressedOperationOpen(int intOperation) { 
			int intLotsOpened;
			// Has it opened? //Alligator connection.
			if (mobjPosition.open(intOperation, gobjTerminal, intLotsOpened)) { 

				//Make sure the pointer is currently valid. //Alligator connection.
				if (gobjTrend) { 
					gobjTrend->setPhase(enmPhases::phase_signal_triggered); //Alligator connection.
					gobjTrend->tradeActive_SetType(intOperation); //Alligator connection.
					gobjTrend->tradeActive_SetPriceOpen(gobjTerminal.getPriceStock()); //MT4 version Bid/Ask. //Alligator connection.
					gobjTrend->tradeActive_SetLots(intLotsOpened); //Alligator connection.
				}

				//Continue the opening procedure directly in a trade disables mode.
				if (gobjConstantsXML.getTradeDisabled()) 
					mobjObjects.renameAll(gintOperationNull, false); 
				else //Set OnSendTransaction_keyPressedOperation.
					setTransactionKeyPressedOperation(intOperation); 
			}	
		}

		// KeyArrowUp/KeyB/KeyArrowDown/KeyS pressed to buy or sell. +
		void keyPressedOperation(int intOperation) { 
			if (checkPriceStockOfferBid()) { // Make sure that the stock price and the futures offer/bid are available.
				if (mobjPosition.getTotalnet() == 0) //Is there no Channels position?
					keyPressedOperationOpen(intOperation); 
				else { //Check to close a Channels position.
					if (!mobjPosition.matchClosingToOpened(intOperation)) 
						keyPressedOperationOpen(intOperation);
					else { //Does the closing operation match the open one?
						if (mobjPosition.close(gobjTerminal, false)) {
							if (gobjConstantsXML.getTradeDisabled()) //Continue the opening procedure directly in a trade disables mode.
								mobjObjects.renameAll(gintOperationNull, false); 
							else //Set OnSendTransaction_keyPressedOperation.	
								setTransactionKeyPressedOperation(intOperation); 
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
				} 
				else if (mobjMT4QuikConnector.disableObjects()) //Is it a Disable Ojects command message?
					disableObjects(); 
				else if (mobjMT4QuikConnector.closePosition()) { //Is it a Close Position command message?
					if (checkPriceStockOfferBid()) { // Make sure that the stock price and the futures offer/bid are available.
						if (mobjPosition.getTotalnet() != 0) //Is there a Channels position to be closed?
							mobjPosition.close(gobjTerminal, false); 
					}
				} 
				else if (mobjMT4QuikConnector.refreshConstants()) 
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

		//Register necessary events only. 
		//Формат вызова функции обратного вызова для обработки событий в таблице: 
		//		FUNCTION (NUMBER t_id, NUMBER msg, NUMBER par1, NUMBER par2) 
		//Параметры: 
		//		t_id – идентификатор таблицы, для которой обрабатывается сообщение, 
		//		par1 и par2 – значения параметров определяются типом сообщения msg, 
		//		msg – код сообщения. 
		static int tableNotificationCallback(lua_State* L) { 
			try {
				int msg = lua_tointeger(L, -3);
				int par2 = lua_tointeger(L, -1);
				
				//Clear the stack off the function's 4 parameters: operationsTable, msg, par1, par.
				lua_pop(L, 4); 
				//Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
				bool blnContinue{}; 

				//A left mouse - click.
				if (msg == QTABLE_LBUTTONUP) 
					blnContinue = true; 
				else if (msg == QTABLE_VKEY) {
					//A key is pressed.
					if (par2 == (int)enmKeys::keyEsc 
						/*KTB 
						|| par2 == mintKeys.keyArrowUp
						*/ 
						|| par2 == (int)enmKeys::keyB 
						/*KTB 
						|| par2 == mintKeys.keyArrowDown
						*/ 
						|| par2 == (int)enmKeys::keyS
						) 
						blnContinue = true; 
				}
				
				if (blnContinue) {
					mobjEvents.setTableNotificationCallback(true);
					mobjEvents.setTableNotificationCallback_msg(msg);
					mobjEvents.setTableNotificationCallback_par2(par2);
				}	
			}

			catch (const exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__); 
			}	

			return 0; //Return 0 because of the function declaration as static int.
		}

		static void eventTableNotificationCallback(int msg, int par2) { 
			//A left mouse-click. 
			if (msg == QTABLE_LBUTTONUP) 
				//Sell or buy. Convert the operation first (ref. table creation).
				keyPressedOperation(BUYtoSELL(par2)); 
			else if (msg == QTABLE_VKEY) {
				//Escape pressed? 
				if (par2 == (int)enmKeys::keyEsc) 
					//Unselect all objects / disable them / close position.
					keyPressedEsc(); 
				else if (/*KTB par2 == keyArrowUp ||*/ par2 == (int)enmKeys::keyB) 
					//Buy.
					keyPressedOperation(OP_BUY); 
				else if (/*KTB par2 == keyArrowDown ||*/ par2 == (int)enmKeys::keyS)
					//Sell.
					keyPressedOperation(OP_SELL); 
				/*KTB 
				else if (par2 == keyF5) 
					keyPressedF5();
				*/
			}	
		}

		/*KTB
		void getNumberOf(lua_State* L, const string& strFunction) { 
			lua_getglobal(L, "getNumberOf"); 
			lua_pushstring(L, "all_trades"); 
			lua_pcall(L, 1, 1, 0); 
			double dblNumberOf = lua_tonumber(L, -1);
			message(
				strFunction 
				+ ": gobjTerminal.getPriceStock() = " 
				+ to_string(gobjTerminal.getPriceStock()) 
				+ "   dblNumberOf = " 
				+ to_string(dblNumberOf)
			);
		}*/

		// In addition to the OnInit function, complete initialisation invoked from mainQlua. The latter is more robust because of its parallel thread. 
		static bool initialise(lua_State* L) { 
			try {
				gobjTerminal.createOperationsTable(tableNotificationCallback);
				gobjConstantsXML.readXML();
				mobjPosition.initialise(gobjConstantsXML.getTradeDisabled(), gobjConstantsXML.getLotsTraded());
				#ifdef BLN_ALG
					#ifndef BLN_TEST_TRADE_SR_EVENING
						setCandlesByIndex(
							L, 
							wstringToString(gobjConstantsXML.getStockTagPrice()), 
							wstringToString(gobjConstantsXML.getStockTagAlg()), 
							gintCandlesCount, 
							gintChartOffset
						);
					#else
						setCandlesByIndex(
							L, 
							wstringToString(gobjConstantsXML.getFuturesTagPrice()), 
							wstringToString(gobjConstantsXML.getFuturesTagAlg()), 
							gintCandlesCount, 
							gintChartOffset
						);
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
			}
		}	
	}	
}

using namespace mtqc::MT4QuikConnector;

static int OnInit(lua_State* L) { 
	try {
		messages::messageInit(gstrMTQC + " initialised.", L); //Ininialise L for messaging.
		gobjTerminal.setL(L);
		
		gobjTerminal.setPriceStock(gdblPriceStock); // Intitialise it while awating the OnAlltrade event.
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
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
					if (mobjEvents.getOnSendTransaction_opening()) //Complete the opening procedure.
						runOpenProcedure(false); 
					else if (mobjEvents.getOnSendTransaction_closing()) //Complete the closing procedure.
						runCloseProcedure(); 
					else if (mobjEvents.getOnSendTransaction_keyPressedOperation()) //Complete the opening/closing procedure.
						mobjObjects.renameAll(gintOperationNull, false); 
					mobjEvents.setOnTransReply(false); //The opening/closing procedure is over. Reset the flags.
					mobjEvents.OnSendTransaction_reset();
				}
				if (mobjEvents.getOnAllTrade()) {
					run();
					mobjEvents.setOnAllTrade(false);
				}
				Sleep(1); //Sleep function @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms686298(v=vs.85).aspx
			}
		}
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

static int OnConnected(lua_State* L) { 
	try {	
		messages::message(gstrMTQC + " connected."); 
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

static int OnQuote(lua_State* L) { // Функция вызывается терминалом QUIK при получении изменения стакана котировок.
	try {	
		//SUSPENDED
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

static int OnAllTrade(lua_State* L) { // Функция вызывается терминалом QUIK при получении обезличенной сделки.
	try {
		#ifndef BLN_TEST_TRADE_SR_EVENING
			static string strStock = wstringToString(gobjConstantsXML.getStock()); // Keep the stock name in a local variable to boost performance.
		#else
			static string strStock = wstringToString(gobjConstantsXML.getFutures()); // Keep the stock name in a local variable to boost performance.
		#endif
		#ifdef BLN_TEST_NO_QUOTES_ERROR
			gobjTerminal.setPriceStock(gdblPriceStock);
		#else
		lua_getfield(L, -1, "sec_code");
		if (lua_tostring(L, -1) == strStock) { // Is that the selected stock?
			lua_getfield(L, -2, "price"); // Get the stock's price. //TO DO: Use ds:SetUpdateCallback(MyFuncName); //Позволяет задать пользователю функцию обратного вызова для обработки изменившихся свечей, т.е. когда по выбранному в CreateDataSource параметру в терминал поступит новое значение (возможно такое же), автоматически будет вызвана данная функция, в которую будут передан индекс последней свечи графика, а так же добавятся новые данные в таблицу ds
			gobjTerminal.setPriceStock(lua_tonumber(L, -1)); 
			lua_pop(L, 2); //Clear the stack off 'sec_code' and 'price' Qlua passes.
			#endif 
			#ifdef BLN_TEST_TRADE_SR_EVENING //To test it in the evening session
				gobjTerminal.setPriceStock(gobjTerminal.getPriceStock() / gintContractSize + gdblStockToFuturesAdjustment);
			#endif
			mobjEvents.setOnAllTrade(true);
			#ifdef BLN_ALG
				OnTick(gobjTerminal.getPriceStock()); //thread objThread(functionsMT4::OnTick, gobjTerminal.getPriceStock()); objThread.detach();
				algEA::OnTickAlg(); //Alligatort EA's OnTick function.
			#endif
			#ifndef BLN_TEST_NO_QUOTES_ERROR
		} else 
			lua_pop(L, 2); // Clear the stack off 'sec_code' and 'price' Qlua passes.
		#endif 
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

// Функция вызывается терминалом QUIK при совершении Вами новой сделки (обычно вызывается по 2 раза для каждой сделки) @ 
//http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/ 
static int OnTrade(lua_State* L) { 
	try {
		lua_getfield(L, -1, "trade_num"); 
		int intTrade_num = lua_tointeger(L, -1); 
		lua_pop(L, 1);

		lua_getfield(L, -1, "flags");		 
		int intFlags = lua_tointeger(L, -1); //assert(!"Make sure trade.flags is correctly converted into integer and iterpreted in mobjPosition.recordTrade.");
		lua_pop(L, 1); 

		lua_getfield(L, -1, "price");		 
		double dblPrice = lua_tonumber(L, -1);	
		lua_pop(L, 1);

		lua_getfield(L, -1, "qty");		 
		int intQty = lua_tointeger(L, -1);	
		lua_pop(L, 1);

		// Record a trade into the Trades CSV file.
		mobjPosition.recordTrade(intTrade_num, intFlags, to_string(dblPrice), to_string(intQty)); 
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

//Результат транзакции можно получить, воспользовавшись функцией обратного вызова OnTransReply @ http://help.qlua.org/ch4_5_11.htm 
//See a detailed description @ http://robostroy.ru/community/article.aspx?id=765 
static int OnTransReply(lua_State* L) { 
	try {
		lua_getfield(L, -1, "sec_code"); 
		bool blnIsNil = lua_isnil(L, -1); 
		lua_pop(L, 1);

		//Is a transaction successful? 
		if (!blnIsNil)	
			//Complete the opening procedure.
			mobjEvents.setOnTransReply(true); 
		else {
			lua_getfield(L, -1, "result_msg"); 
			string strResult_msg = lua_tostring(L, -1); 
			lua_pop(L, 1);
			
			messages::message("Transaction failed! result_msg: " + strResult_msg + " Resuming transaction...");
			
			//Resume the key pressed operation procedure.
			if (mobjEvents.getOnSendTransaction_keyPressedOperation()) 
				mobjEvents.setOnSendTransaction_keyPressedOperationResumed(true); 
			
			//Resume the opening/closing procedure.
			else if (mobjEvents.getOnSendTransaction_opening() || mobjEvents.getOnSendTransaction_closing()) { 
				mobjEvents.OnSendTransaction_reset();
				mobjEvents.setOnAllTrade(true);
			}
		}
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

// Функция вызывается терминалом QUIK при изменении позиции по срочному рынку. 
static int OnFuturesClientHolding(lua_State* L) { 
	try {
		lua_getfield(L, -1, "sec_code"); 
		string strSec_code = lua_tostring(L, -1); 
		lua_pop(L, 1);

		// Is that my security that has changed?
		if (strSec_code == wstringToString(gobjConstantsXML.getFutures())) { 
			lua_getfield(L, -1, "totalnet"); 
			mobjPosition.setTotalnet(lua_tointeger(L, -1)); 
			lua_pop(L, 1);
		}	
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

static int OnStop(lua_State* L) { 
	try {
		gobjTerminal.destroyOperationsTable();
		//KTB functionsMT4::deleteCandlesByIndex();
		
		//Unlike message, use messageInit to prevent an error perhapse because L gets terminated.
		messages::messageInit("Quit Quik to quit " + gstrMTQC + ".", L); 
		gobjTerminal.setRun(false);
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

// Регистрация реализованных в dll функций, чтобы они стали "видимы" для Lua 
static struct luaL_reg ls_lib[] = { 
	{ "startQuikServer", server::startQuikServer },
	{ "tableNotificationCallback", tableNotificationCallback },
	{ NULL, NULL }
};

// Регистрация названия библиотеки, видимого в скрипте Lua. IPMORTANT: When renaming the project luaopen_MTQC must be RENAMED as luaopen_PROJECTNAME! 
extern "C" LUALIB_API int luaopen_MTQC(lua_State* L) { 
	try {
		luaL_openlib(L, gstrMTQC.c_str(), ls_lib, 0);

		lua_pushcclosure(L, OnInit, 0);
		lua_setglobal(L, "OnInit");

		lua_pushcclosure(L, mainQlua, 0);
		lua_setglobal(L, "main");

		lua_pushcclosure(L, OnConnected, 0);
		lua_setglobal(L, "OnConnected");

		lua_pushcclosure(L, OnQuote, 0);
		lua_setglobal(L, "OnQuote");

		//Добавляет функцию в стек 
		//ПРИМЕР РЕАЛИЗАЦИИ ФУНКЦИИ ОБРАТНОГО ВЫЗОВА ONALLTRADE ВНУТРИ DLL @ 
		//https://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/
		lua_pushcclosure(L, OnAllTrade, 0); 
		//Регистрирует её как коллбэк на OnAllTrade //ПРИМЕР РЕАЛИЗАЦИИ ФУНКЦИИ ОБРАТНОГО ВЫЗОВА ONALLTRADE ВНУТРИ DLL @ 
		//https://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/
		lua_setglobal(L, "OnAllTrade"); 

		lua_pushcclosure(L, OnTrade, 0);
		lua_setglobal(L, "OnTrade");

		lua_pushcclosure(L, OnTransReply, 0);
		lua_setglobal(L, "OnTransReply");

		lua_pushcclosure(L, OnFuturesClientHolding, 0);
		lua_setglobal(L, "OnFuturesClientHolding");

		lua_pushcclosure(L, OnStop, 0);
		lua_setglobal(L, "OnStop");
	}
	catch (const exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}	
	return 0;
}

// Стандартная точка входа для DLL //Link an executable to a DLL - Implicit Linking. If any of the DLLs has an entry-point function for initialization and 
//termination code such as DllMain, the operating system calls the function. One of the parameters passed to the entry-point function specifies a code that indicates 
//the DLL is attaching to the process. If the entry-point function does not return TRUE, the system terminates the process and reports the error. @ 
//https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { 
	return TRUE; 
}  
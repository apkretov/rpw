#include "terminal.h"

using std::string;
#include "switch.h"
#include "messages.h"

#include "functions.h"
#include "constantsXML.h"
using namespace mtqc;
using namespace mtqc::functions;
#include "constants.h"
using namespace mtqc::constants;

#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

namespace mtqc {
	namespace terminal_ {

		inline static bool incrmentCompare(int& i, int intTo) { 
			return ++i <= intTo; 
		} 

		inline static bool decrmentCompare(int& i, int intTo) { 
			return --i >= intTo; 
		} 

		static bool incrmentCompareMessaging(int& i, int intTo, terminal* objTerminal) { 
			bool blnIncrmentCompare = ++i <= intTo;
			return ++i <= intTo; 
		} 

		static bool decrmentCompareMessaging(int& i, int intTo, terminal* objTerminal) { 
			bool blnDecrmentCompare = --i >= intTo; 
			return blnDecrmentCompare;
		} 
	}
}
using namespace mtqc::terminal_;

terminal::terminal(lua_State* L_) 
	: L(L_), cblnRun(false), cdblPriceStock(0), cintOperationsTable(0) 
{} 

// Release the memory an initialised pointer points to. 
terminal::~terminal() { 
	L = nullptr; 
} 

/*inline*/ double terminal::getOfferBidPrice(size_t intIx) const { 
	return cdblOfferBidPrice[intIx]; 
} 

/*inline*/ lua_State* terminal::getL() const { 
	return L; 
} 

void terminal::setL(lua_State* L_) { 
	//Hasn't L been initialised?
	if (terminal::L == nullptr) 
		terminal::L = L_; 
	else 
		messages::message("An illegal attemnt to reinitialise the lua_State L!");
}

/*inline*/ bool terminal::getRun() const { 
	return cblnRun; 
} 

/*inline*/ void terminal::setRun(bool blnRun) { 
	cblnRun = blnRun; 
} 

/*inline*/ double terminal::getPriceStock() const { 
	return cdblPriceStock; 
} 

/*inline*/ void terminal::setPriceStock(double dblPriceStock) { 
	cdblPriceStock = dblPriceStock; 
} 

// Get the best bid/offer. 
void terminal::getOfferBidBest(int intFrom, int intTo, bool(*fncInDecrmentCompare)(int&, int), double& dblPrice, int& intQuantity) { 
	//The best bid is placed at the top of the bids DOM, the best offer is at the botteom.
	while (fncInDecrmentCompare(intFrom, intTo)) { 
		//Go to a Price/Quantity record number intFrom.
		lua_rawgeti(L, -1, intFrom); 
		lua_getfield(L, -1, "quantity");
		//На некоторых ценах могут отсутствовать заявки 
		if (lua_isnil(L, -1)) 
			//Clear the stack off Price/Quantity record number intFrom and the nil quantity.
			lua_pop(L, 2); 
		else {
			intQuantity = lua_tointeger(L, -1); 
			lua_pop(L, 1); 

			lua_getfield(L, -1, "price"); 
			dblPrice = lua_tonumber(L, -1); 
			//Clear the stack off the price and the a Price/Quantity record number intFrom. Alternatively: lua_pushstring(L, "price"); lua_rawget(L, -2);
			lua_pop(L, 2); 
			
			return; //The best bid is assigned. Exit.
		}
	}
}

// Get the best bid/offer. 
void terminal::getOfferBidBestMessaging(int intFrom, int intTo, bool(*fncInDecrmentCompare)(int&, int, terminal*), double& dblPrice, int& intQuantity) { 
	//The best bid is placed at the top of the bids DOM, the best offer is at the botteom.
	while (fncInDecrmentCompare(intFrom, intTo, this)) { 
		//Go to a Price/Quantity record number intFrom.
		lua_rawgeti(L, -1, intFrom); 
		lua_getfield(L, -1, "quantity");
		//На некоторых ценах могут отсутствовать заявки 
		if (lua_isnil(L, -1)) 
			//Clear the stack off Price/Quantity record number intFrom and the nil quantity.
			lua_pop(L, 2); 
		else { 
			intQuantity = lua_tointeger(L, -1); lua_pop(L, 1); 
			lua_getfield(L, -1, "price"); dblPrice = lua_tonumber(L, -1); lua_pop(L, 2); 

			//The best bid is assigned. Exit.
			return; 
		}
	}
}

bool terminal::getOfferBid(const string& strFutures) { 
	#ifdef BLN_TEST_NO_QUOTES_ERROR
		const int intQuantity = 50;
		cdblOfferBidPrice[OP_BUY] = gdblPriceStock * gintContractSize + 1;
		cintOfferBidQuantity[OP_BUY] = intQuantity; 
		cdblOfferBidPrice[OP_SELL] = gdblPriceStock * gintContractSize - 1;
		cintOfferBidQuantity[OP_SELL] = intQuantity; 
		return true;
	#endif

	cdblOfferBidPrice[OP_BUY] = 0; 
	cintOfferBidQuantity[OP_BUY] = 0; 
	cdblOfferBidPrice[OP_SELL] = 0; 
	cintOfferBidQuantity[OP_SELL] = 0;
		
	lua_getglobal(L, "getQuoteLevel2"); 
	lua_pushstring(L, wstringToString(gobjConstantsXML.getCLASSCODE()).c_str()); 
	lua_pushstring(L, strFutures.c_str());
		
	//Call the getQuoteLevel2 QLua function. Did it succeed?
	if (lua_pcall(L, 2, 1, 0) != EXIT_SUCCESS || !lua_istable(L, -1)) 
		return false; 
		
	//KTB DEBUGGING L = luaL_newstate(); luaL_dofile(L, "Data.lua"); lua_getglobal(L, "ql2"); 
	int intBidCount = 0, intOfferCount = 0;
		
	lua_getfield(L, -1, "bid_count"); 
	intBidCount = lua_tointeger(L, -1); 
	//Количество котировок покупки. При отсутствии спроса возвращается значение «0» 
	//getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
	lua_pop(L, 1); 
		
	lua_getfield(L, -1, "offer_count"); 
	intOfferCount = lua_tointeger(L, -1); 
	//Количество котировок продажи. При отсутствии предложения возвращается значение «0» 
	//getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
	lua_pop(L, 1); 
		
	//Are there records?
	if (intBidCount > 0)	{ 
		//Go to the Bid table. 
		//Котировки спроса (покупки). При отсутствии спроса возвращается пустая строка 
		//getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
		lua_getfield(L, -1, "bid"); 
			
		// Get the best bid/offer. Begining from 'intBidCount + 1' is because of the pre-decrementing in the decrmentCompare function.
		getOfferBidBest(intBidCount + 1, 1, decrmentCompare, cdblOfferBidPrice[OP_BUY], cintOfferBidQuantity[OP_BUY]); 
	}
		
	//Removes the 'bid' table from the stack. Alternatively you can set the stack top to a lower position or use an incremented stack indexes 
	//when accessing the stack in all the commands below.
	lua_pop(L, 1); 
		
	//Are there records?
	if (intOfferCount > 0) { 
		//Go to the Offer table. 
		//Котировки спроса (покупки). При отсутствии спроса возвращается пустая строка 
		//getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
		lua_getfield(L, -1, "offer"); 
			
		// Get the best bid/offer. Begining from 0 unlike 1 is because of the pre-incrementing in the incrmentCompare function.
		getOfferBidBest(0, intOfferCount, incrmentCompare, cdblOfferBidPrice[OP_SELL], cintOfferBidQuantity[OP_SELL]); 
	} 
		
	//Is there a bid and an offer?
	return cdblOfferBidPrice[OP_BUY] 
		&& cintOfferBidQuantity[OP_BUY] 
		&& cdblOfferBidPrice[OP_SELL] 
		&& cintOfferBidQuantity[OP_SELL]; 
}

void terminal::createOperationsTable(int (*tableNotificationCallback)(lua_State*)) { 
	constexpr int intColumnWidht = 15;
	constexpr int intRows = 2;
	
	//KTB constexpr int intPosX = 912, intPosY = 549; //Right bottom window
	//KTB constexpr int intPosX = 457, intPosY = 238//Center top window
	//KTB constexpr int intPosX = 912, intPosY = 238; //Right top window
	//KTB constexpr int intPosDX = 160, intPosDY = 80;
	
	//Adjacent to volume.
	constexpr int intPosX = 456, intPosY = 318; 
	constexpr int intPosDX = 160, intPosDY = 74;
	
	//par_type – тип данных в колонке: строка. Because it isn't documented, I printed the constant's value from MT4QuikConnector_.lua. @ QLUA.chm\AddColumn.
	constexpr int QTABLE_STRING_TYPE = 3; 
	//Если в качестве цвета задана константа QTABLE_DEFAULT_COLOR, то используется цвет, заданный в цветовой схеме операционной системе Windows. 
	//Because it isn't documented, I printed the constant's value from MT4QuikConnector_.lua. //SetColor @ QLUA.chm.
	constexpr int QTABLE_DEFAULT_COLOR = -1; 
	
	lua_getglobal(L, "AllocTable"); 
	lua_pcall(L, 0, 1, 0); 
	cintOperationsTable = lua_tointeger(L, -1); 
	lua_pop(L, 1);
	
	//Функция возвращает «1», если колонка в таблицу добавлена, иначе – «0». //AddColumn @ QLUA.chm.
	lua_getglobal(L, "AddColumn"); 
	lua_pushinteger(L, cintOperationsTable); 
	lua_pushinteger(L, BUYtoSELL(OP_SELL)); 
	lua_pushstring(L, "SELL"); 
	lua_pushboolean(L, true); 
	lua_pushinteger(L, QTABLE_STRING_TYPE); 
	lua_pushinteger(L, intColumnWidht); 
	lua_pcall(L, 6, 1, 0); 
	lua_pop(L, 1); 
	
	//Функция возвращает «1», если колонка в таблицу добавлена, иначе – «0». //AddColumn @ QLUA.chm.
	lua_getglobal(L, "AddColumn"); 
	lua_pushinteger(L, cintOperationsTable); 
	lua_pushinteger(L, BUYtoSELL(OP_BUY)); 
	lua_pushstring(L, "BUY"); 
	lua_pushboolean(L, true); 
	lua_pushinteger(L, QTABLE_STRING_TYPE); 
	lua_pushinteger(L, intColumnWidht); 
	lua_pcall(L, 6, 1, 0); 
	lua_pop(L, 1); 
	
	//Функция возвращает «1» при успешном создании окна, иначе – «0». //CreateWindow @ QLUA.chm.
	lua_getglobal(L, "CreateWindow"); 
	lua_pushinteger(L, cintOperationsTable); 
	lua_pcall(L, 1, 1, 0); 
	lua_pop(L, 1); 
	
	int intRow, intB_colorSell, intB_colorBuy;
	
	//The sell columnt colour.
	lua_getglobal(L, "RGB"); 
	lua_pushinteger(L, 240); 
	lua_pushinteger(L, 128); 
	lua_pushinteger(L, 128); 
	lua_pcall(L, 3, 1, 0); 
	intB_colorSell = lua_tointeger(L, -1); 
	lua_pop(L, 1); 
	
	//The buy columnt colour.
	lua_getglobal(L, "RGB"); 
	lua_pushinteger(L, 153); 
	lua_pushinteger(L, 255); 
	lua_pushinteger(L, 153); 
	lua_pcall(L, 3, 1, 0); 
	intB_colorBuy = lua_tointeger(L, -1); 
	lua_pop(L, 1); 
	
	for (int i = 0; i < intRows; i++) {
		lua_getglobal(L, "InsertRow"); 
		lua_pushinteger(L, cintOperationsTable); 
		lua_pushinteger(L, -1); 
		lua_pcall(L, 2, 1, 0); 
		intRow = lua_tointeger(L, -1); 
		lua_pop(L, 1);
		
		//SetColor returns BOOLEAN. Clear the stack off it.
		lua_getglobal(L, "SetColor"); 
		lua_pushinteger(L, cintOperationsTable); 
		lua_pushinteger(L, intRow); 
		lua_pushinteger(L, BUYtoSELL(OP_SELL)); 
		lua_pushinteger(L, intB_colorSell); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pcall(L, 7, 1, 0); 
		lua_pop(L, 1); 
		
		//SetColor returns BOOLEAN. Clear the stack off it.
		lua_getglobal(L, "SetColor"); 
		lua_pushinteger(L, cintOperationsTable); 
		lua_pushinteger(L, intRow); 
		lua_pushinteger(L, BUYtoSELL(OP_BUY)); 
		lua_pushinteger(L, intB_colorBuy); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pushinteger(L, QTABLE_DEFAULT_COLOR); 
		lua_pcall(L, 7, 1, 0); 
		lua_pop(L, 1); 
	}
	
	//В случае успешного выполнения возвращает «true», иначе – «false». Clear the stack off it. //SetWindowCaption @ QLUA.chm.
	lua_getglobal(L, "SetWindowCaption"); 
	lua_pushinteger(L, cintOperationsTable), lua_pushstring(L, "5 SELL BUY"); 
	lua_pcall(L, 2, 1, 0); 
	lua_pop(L, 1); 
	
	//В случае успешного выполнения возвращает «true», иначе – «false». 
	lua_getglobal(L, "SetWindowPos"); 
	lua_pushinteger(L, cintOperationsTable); 
	lua_pushinteger(L, intPosX); 
	lua_pushinteger(L, intPosY); 
	lua_pushinteger(L, intPosDX); 
	lua_pushinteger(L, intPosDY); 
	lua_pcall(L, 5, 1, 0); 
	lua_pop(L, 1); 
	
	//В случае успешного завершения функция возвращает «1», иначе – «0». 
	lua_getglobal(L, "SetTableNotificationCallback"); 
	lua_pushinteger(L, cintOperationsTable); 
	lua_pushcfunction(L, tableNotificationCallback); 
	lua_pcall(L, 2, 1, 0); 
	lua_pop(L, 1); 
}

void terminal::destroyOperationsTable() { 
	if (cintOperationsTable != 0) { 
		lua_getglobal(L, "DestroyTable"); 
		lua_pushinteger(L, cintOperationsTable); 
		lua_pcall(L, 1, 0, 0); 
	} 
} 

//выводит сообщение в терминале //пример реализации функции обратного вызова onalltrade внутри dll 
//@ http://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/ 
void terminal::message_(const string& strMessage, int intIcon_type) const { 
	//Hasn't L been initialised?
	if (L == 0) 
		return; 
	
	//Возвращает «nil» при ошибке выполнения или при обнаружении ошибки во входных параметрах. В остальных случаях возвращает «1». 
	lua_getglobal(L, "message");	
	lua_pushstring(L, strMessage.c_str()); 
	lua_pushinteger(L, intIcon_type); 
	lua_pcall(L, 2, 1, 0); 
	lua_pop(L, 1); 
}

/*KTB 
void terminal::message(const char* chrMessage) const { 
	message_(chrMessage); 
} 
*/

/*KTB 
void terminal::message(const string& srtMessage) const { 
	message_(srtMessage.c_str()); 
} 
*/

/*KTB 
void terminal::messageNoPriceStock() const { 
	messages::messageExclamation("No OnAllTrade event to get alltrade.price for gobjTerminal.priceStock!"); 
} 
*/

void terminal::messageNoOfferBid() const { 
	messages::messageExclamation("There is neither bid nor offer!"); 
} 

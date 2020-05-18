#include "position.h"

using std::string;
using std::to_string;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

#include "terminal.h"
#include "messages.h"
#include "lua.h"

#include "functions.h"
using namespace mtqc;
using namespace mtqc::functions;

#include "constants.h"
using namespace mtqc::constants;

#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

namespace mtqc {

	// Check if the file exists and return true. Otherwise create one and write an input to it. 
	void position::checkOrCreate(const string& strFileName, const string& strInput) { 
		ifstream objFile(strFileName);
		//Does it exist?
		if (objFile.good()) 
			objFile.close(); 
		else { //Create a file and write an input to it, if necessary.
			ofstream objFile(strFileName);
			//Write an input to it, if necessary.
			if (strInput != "") 
				objFile << strInput; 
			objFile.close();
		}	
	}

	// Функция возвращает значение бита (число 0, или 1) под номером intBit (начинаются с 0) в числе intFlags, если такого бита нет, возвращает nil @ 
	//http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/ 
	//TO DO: Encapsulate this function into the class. 
	int position::checkBit(int intFlags, int intBit) { 
		// Перевернутое (задом наперед) строковое представление двоичного представления переданного десятичного числа (intFlags) 
		string strRevBitsStr; 
		// Остаток от деления
		int intFmod{}; 
		//Флаг работы цикла
		bool blnGo = true; 
		
		while (blnGo) {
			// Остаток от деления
			intFmod = intFlags % 2; 
			// Оставляет для следующей итерации цикла только целую часть от деления
			intFlags = (int)floor(intFlags / 2); 
			// Добавляет справа остаток от деления
			strRevBitsStr = strRevBitsStr + to_string(intFmod); 
			// Если был последний бит, завершает цикл
			if (intFlags == 0) 
				blnGo = false; 
		}
		
		// Возвращает значение бита 
		//Example of Substring Operations @ http://nepsweb.co.uk/pgtcpp/stringex/substr.htm
		string strResult = strRevBitsStr.substr(intBit, 1); 
		if (strResult == "0") 
			return 0;
		else if (strResult == "1") 
			return 1;
		else 
			return -1;
	}	
}

position::position() : 
	cstrFilePrefix(gstrMTQC + " - "), 
	cintTotalnet(0) 
{}

void position::initialise(bool blnTradeDisabled_, int intLotsTraded_) {
	cblnTradeDisabled = blnTradeDisabled_; 
	cintLotsTraded = intLotsTraded_; 

	cobjFileCSVOrders.initialise("Orders", "Date,Time,Open/Close,Operation,Price,Stock price,Quantity");
	cobjFileCSVTrades.initialise("Trades", "Дата,Время,Операция,Цена,Кол-во");

	//Get the total net in a trade disabled mode. //If a trade disabled mode, load cintTotalnet from the file saved in a prior session.
	if (cblnTradeDisabled) { 
		string strFileTotalnet = cstrFilePrefix + cstrTotalnetTxt;
		// Check if the file exists. Otherwise create one and write cintTotalnet to it.
		checkOrCreate(strFileTotalnet, to_string(cintTotalnet)); 

		//Read the total net from the file.
		ifstream objFileTotalnet(strFileTotalnet); 
		char chrTotalnet;
		objFileTotalnet >> chrTotalnet;
		cintTotalnet = stringToInt(string(&chrTotalnet));
		objFileTotalnet.close();

		string strFileTradeNums = cstrFilePrefix + cstrTradeNumsTxt;
		// Check if the file exists. Otherwise create one.
		checkOrCreate(strFileTradeNums); 
		//Get trade numbers saved before, in any.
		ifstream objFileTradeNums(strFileTradeNums); 
		
		string strLine;
		while (std::getline(objFileTradeNums, strLine)) 
			//How to read line by line or a whole text file at once? @ http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
			cintTradeNums.push_back(stringToInt(strLine)); 
		
		objFileTradeNums.close();
	}	
}

/*inline*/ void mtqc::position::setLotsTraded(int intLotsTraded_) { 
	cintLotsTraded = intLotsTraded_; 
}

// Record a trade into the Trades CSV file 
void position::recordTrade(int intTradeNum, int intFlags, const string& strPrice, const string& strQty) { 
	/*KTB
	// Перебирает массив с номерами записанных сделок (в обратном порядке).
	//for i = #cintTradeNums, 1, -1 do 
	for (int i = cintTradeNums.size() - 1; i >= 0; i--) { 
		// Если данная сделка уже была записана, выходит из функции
		if (cintTradeNums.at(i) == intTradeNum) 
			return; 
	}*/
	
	// Перебирает массив с номерами записанных сделок (в обратном порядке). 
	// Если данная сделка уже была записана, выходит из функции
	if (std::find(cintTradeNums.rbegin(), cintTradeNums.rend(), intTradeNum) != std::rend(cintTradeNums)) 
		return; 

	//cintTradeNums[#cintTradeNums + 1] = intTradeNum 
	//Если мы здесь, значит сделка не была найдена в числе уже записанных. Добавляет в массив номер новой сделки.
	cintTradeNums.push_back(intTradeNum); 
	
	// Save the trade number in the file for later use.
	ofstream objFileTradeNums(cstrFilePrefix + cstrTradeNumsTxt, ios::app || ios::ate); 
	objFileTradeNums << intTradeNum << "\n";
	objFileTradeNums.close();

	//Вычисляет операцию сделки. 
	//Introducing C++11 Brace-Initialization - string s{}; //same as: string s; @ http://www.informit.com/articles/article.aspx?p=1852519
	string strOperation; 

	int intCheckBit = checkBit(intFlags, 2);
	if (intCheckBit == 1) 
		strOperation = "Продажа";
	else if (intCheckBit == -1) 
		strOperation = "Купля";
	cobjFileCSVTrades.addLine(strOperation + "," + strPrice + "," + strQty, true);
}

bool position::sendTransaction_(int intOperation, const terminal& objTerminal, const string& strOpenClose, int intLots) { 
	//The difference between the prices of the stock and futures to order the worst futures price w/o the DOM.
	static int intStockFuturesDiff = 500; 
	//Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
	bool blnSendTransaction{}; 
	lua_State* L = objTerminal.getL();
	//Introducing C++11 Brace-Initialization //string s{}; //same as: string s; @ http://www.informit.com/articles/article.aspx?p=1852519
	string strPriceFractional, strPriceFractionalDOM;	

	double dblPrice = objTerminal.getPriceStock() 
		* gintContractSize 
		+ (intOperation == OP_BUY ? intStockFuturesDiff : -intStockFuturesDiff); 
	
	//Is the price fractional?
	if (gblnFuturesFractional) { 
		strPriceFractional = to_string(dblPrice);
		strPriceFractionalDOM = numberToStringF(objTerminal.getOfferBidPrice(intOperation));
	} else {
		strPriceFractional = to_string((int)(dblPrice));
		strPriceFractionalDOM = to_string((int)objTerminal.getOfferBidPrice(intOperation)); 
	}

	string strMessageCSV = strOpenClose + "," 
		+ gstrOperations[intOperation] + "," 
		+ strPriceFractionalDOM + "," 
		+ to_string(objTerminal.getPriceStock()) + "," 
		+ to_string(cintLotsTraded);
	
	string strMessagePart1 = strOpenClose + ": " 
		+ (intOperation == OP_BUY ? "Bought" : "Sold") 
		+ " at " + numberToStringF(objTerminal.getPriceStock()) 
		+ " (" + strPriceFractionalDOM + ") " 
		+ to_string(cintLotsTraded);
	
	string strMessagePart2 = "                                                                                                                               ," 
		+ strMessageCSV;

	// %x: date (e.g., 09/16/98); %X: time (e.g., 23:48:10) @ https://www.lua.org/pil/22.1.html
	cobjFileCSVOrders.addLine(strMessageCSV, true); 
	// %x: date (e.g., 09/16/98); %X: time (e.g., 23:48:10) @ https://www.lua.org/pil/22.1.html
	cobjFileCSVTrades.addLine(strOpenClose, true); 

	if (cblnTradeDisabled) {
		// ["flags"]: бит 2 (0x4)  Заявка на продажу, иначе – на покупку. Данный флаг для сделок и сделок для исполнения определяет направление сделки (BUY/SELL) 
		//@ QLUA.chm\Флаги для таблиц Заявки, Заявки на внебиржевые сделки, Сделки, Сделки для исполнения
		recordTrade(cintTradeNums.size() + 1, 
			(int)pow(2, 2) - 1 + intOperation, 
			strPriceFractionalDOM, 
			to_string(intLots)
		); 
		
		//The flag is first to prevent reopening/reclosing in the calling procedure just because of an error in the message below.
		blnSendTransaction = true; 
		//Set cintTotalnet by converting the operation to -1/1 in a gblnTradeDisabled mode.
		cintTotalnet = cintTotalnet - (intOperation * 2 - 1) * intLots; 
		//Save cintTotalnet in the file for reloading Quik.
		ofstream objFileTotalnet(cstrFilePrefix + cstrTotalnetTxt); 
		objFileTotalnet << cintTotalnet;
		objFileTotalnet.close();
		
		messages::message(strMessagePart1 + " Total net: " + to_string(cintTotalnet) + strMessagePart2);
	} 
	else {
		//sendTransaction она вернет нам сообщение. Обратите внимание, что res идет без кавычек, это переменная, а не жестко заданный текст, как в предыдущем примере. 
		//@ http://robostroy.ru/community/article.aspx?id=773 
		//Результат транзакции можно получить, воспользовавшись функцией обратного вызова OnTransReply @ http://help.qlua.org/ch4_5_11.htm
		lua_getglobal(L, "sendTransaction"); 
		lua_newtable(L); 
		lua::setField(L, "TRANS_ID", MagicNumber); 
		lua::setField(L, "ACTION", "NEW_ORDER"); 
		lua::setField(L, "CLASSCODE", wstringToString(gobjConstantsXML.getCLASSCODE())); 
		lua::setField(L, "SECCODE", wstringToString(gobjConstantsXML.getFutures()));	
		lua::setField(L, "OPERATION", gstrOperations[intOperation]); 
		lua::setField(L, "TYPE", "M"); 
		lua::setField(L, "QUANTITY", to_string(intLots)); 
		lua::setField(L, "ACCOUNT", ACCOUNT); 
		lua::setField(L, "CLIENT_CODE", CLIENT_CODE); 
		lua::setField(L, "PRICE", strPriceFractional); 
		lua_pcall(L, 1, 1, 0); 
		string strSendTransaction = lua_tostring(L, -1); 
	
		// ЕСЛИ функция вернула строку диагностики ошибки, ТО значит транзакция не прошла 
		// Выводит сообщение с ошибкой @ http://quikluacsharp.ru/quik-qlua/primer-skripta-qlua-lua-vypolnyayushhego-torgovye-operatsii-v-terminale-quik/
		if (strSendTransaction != "") 
			messages::messageExclamation("Sending the transaction failed! The error is " + strSendTransaction); 
		else {
			//The flag is first to prevent reopening/reclosing in the calling procedure just because of an error in the message below.
			blnSendTransaction = true; 
			messages::message(strMessagePart1 + strMessagePart2);
		}	
	} 
	return blnSendTransaction;
}

/*inline*/ int position::getTotalnet() const { 
	return cintTotalnet; 
} 

/*inline*/ void position::setTotalnet(int intTotalnet) { 
	cintTotalnet = intTotalnet; 
} 

// Get the operation by converting cintTotalnet to OP_BUY/OP_SELL. 
int position::getOperation() const { 
	if (cintTotalnet > 0) 
		return OP_BUY;
	else if (cintTotalnet < 0) 
		return OP_SELL;
	else //This is needed to prevent Warning	C4715	not all control paths return a value.
		return gintOperationNull; 
}

//Alligator connection. 
bool position::open_(int intOperation, const terminal& objTerminal, int& intLotsOpened) { 
	//Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
	bool blnOpen{}; 
	int intLots{};
	
	int intTotalnetAbs = abs(cintTotalnet);
	//The resulting lots.
	int intTotalnetResult = intTotalnetAbs + cintLotsTraded; 
	
	if (intTotalnetResult <= gobjConstantsXML.getLotsMax()) 
		//Won't the resulting lots exceed the maximum?
		intLots = cintLotsTraded; 
	else if (intTotalnetAbs == gobjConstantsXML.getLotsMax()) 
		//The maximum exeeded. 
		//TO DO: Disable Alligator, when it keeps continuosly re-opening the same position.
		messages::message("The maximal number of lots have been opened already before!"); 
	else 
		//Open lots left till the maximum.
		intLots = gobjConstantsXML.getLotsMax() - intTotalnetAbs; 
	
	//Are there lots to open?
	if (intLots > 0) 
		blnOpen = sendTransaction_(intOperation, objTerminal, strOpen, intLots); 
	
	return blnOpen;
}

//Alligator connection. 
bool position::open(int intOperation, const terminal& objTerminal) { 
	//n void variable for open_. 
	//Alligator connection.
	int _; 
	//Alligator connection.
	return open_(intOperation, objTerminal, _); 
} 

//Alligator connection. 
bool position::open(int intOperation, const terminal& objTerminal, int& intLotsOpened) { 
	return open_(intOperation, objTerminal, intLotsOpened); 
} 

//A closing trade operation must match the open one. 
bool position::matchClosingToOpened(int intOperationClosing) const { 
	bool blnMatchClosingToOpened{};
	
	/* KTB Unnecessary self-contradiction: CORRECT THE LINE BELOW: GET cintTotalnet FROM QUIK:
	if (cblnTradeDisabled) { intOperationOpened = getOperation()
	else intOperationOpened = getOperation() }*/
	
	int intOperationOpened = getOperation();
	if (BUYtoSELL(intOperationClosing) == intOperationOpened) 
		blnMatchClosingToOpened = true;
	/*KTB
	else 
		message( variousConsts::gstrMsgWrongOrder 
			+ (intOperationOpened == OP_BUY 
				? " An OP_BUY position cannot be closed with an OP_BUYSTOP/OP_BUYLIMIT order!" 
				: " An OP_SELL position cannot be closed with an OP_SELLSTOP/OP_SELLLIMIT order!" 
			) 
		);
	*/
	
	return blnMatchClosingToOpened;
}

// Close all open lots or reverse the whole position. 
bool position::close(const terminal& objTermninal, bool blnReverse) { 
	int intClosingOperation = BUYtoSELL(getOperation());
	return sendTransaction_( 
		intClosingOperation, 
		objTermninal, 
		strClose, 
		abs(cintTotalnet) 
		* (blnReverse ? 2 : 1) 
	);
}

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
	void position::checkOrCreate(const string& strFileName, const string& strInput) { // Check if the file exists and return true. Otherwise create one and write an input to it. 
		ifstream objFile(strFileName);
		if (objFile.good()) objFile.close(); //Does it exist?
		else { //Create a file and write an input to it, if necessary.
			ofstream objFile(strFileName);
			if (strInput != "") objFile << strInput; //Write an input to it, if necessary.
			objFile.close();
	}	}

	int position::checkBit(int intFlags, int intBit) { // Функция возвращает значение бита (число 0, или 1) под номером intBit (начинаются с 0) в числе intFlags, если такого бита нет, возвращает nil @ http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/ //TO DO: Encapsulate this function into the class. 
		string strRevBitsStr; // Перевернутое (задом наперед) строковое представление двоичного представления переданного десятичного числа (intFlags) 
		int intFmod{}; // Остаток от деления
		bool blnGo = true; // Флаг работы цикла
		while (blnGo) {
			intFmod = intFlags % 2; // Остаток от деления
			intFlags = (int)floor(intFlags / 2); // Оставляет для следующей итерации цикла только целую часть от деления
			strRevBitsStr = strRevBitsStr + to_string(intFmod); // Добавляет справа остаток от деления
			if (intFlags == 0) blnGo = false; // Если был последний бит, завершает цикл
		}
		string strResult = strRevBitsStr.substr(intBit, 1); // Возвращает значение бита //Example of Substring Operations @ http://nepsweb.co.uk/pgtcpp/stringex/substr.htm
		if (strResult == "0") return 0;
		else if (strResult == "1") return 1;
		else return -1;
	}	
}

//position::position(bool blnTradeDisabled_, int intLotsTraded_) : cblnTradeDisabled(blnTradeDisabled_), cintLotsTraded(intLotsTraded_), cstrFilePrefix(gstrMTQC + " - "), cintTotalnet(0) {
//	messageMBFncNum(intLotsTraded_);
//	cobjFileCSVOrders.open("Orders", "Date,Time,Open/Close,Operation,Price,Stock price,Quantity");
//	cobjFileCSVTrades.open("Trades", "Дата,Время,Операция,Цена,Кол-во");
//	messageMBFncNum(blnTradeDisabled_);
//	if (cblnTradeDisabled) { //Get the total net in a trade disabled mode. //If a trade disabled mode, load cintTotalnet from the file saved in a prior session.
//		string strFileTotalnet = cstrFilePrefix + cstrTotalnetTxt;
//		checkOrCreate(strFileTotalnet, to_string(cintTotalnet)); // Check if the file exists. Otherwise create one and write cintTotalnet to it.
//		ifstream objFileTotalnet(strFileTotalnet); //Read the total net from the file.
//		char chrTotalnet;
//		objFileTotalnet >> chrTotalnet;
//		cintTotalnet = stringToInt(string(&chrTotalnet));
//		objFileTotalnet.close();
//		string strFileTradeNums = cstrFilePrefix + cstrTradeNumsTxt;
//		checkOrCreate(strFileTradeNums); // Check if the file exists. Otherwise create one.
//		ifstream objFileTradeNums(strFileTradeNums); //Get trade numbers saved before, in any.
//		string strLine;
//		while (std::getline(objFileTradeNums, strLine)) cintTradeNums.push_back(stringToInt(strLine)); //How to read line by line or a whole text file at once? @ http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
//		objFileTradeNums.close();
//	}	
//}

position::position() : 
	cstrFilePrefix(gstrMTQC + " - "), 
	cintTotalnet(0) 
{
	//cobjFileCSVOrders.open("Orders", "Date,Time,Open/Close,Operation,Price,Stock price,Quantity");
	//cobjFileCSVTrades.open("Trades", "Дата,Время,Операция,Цена,Кол-во");
}

//void position::init(bool blnTradeDisabled_, int intLotsTraded_) {
//	cblnTradeDisabled = blnTradeDisabled_;
//	cintLotsTraded = intLotsTraded_;
//	cstrFilePrefix = gstrMTQC + " - ";
//	cintTotalnet = 0;
//	messageMBFncNum(intLotsTraded_);
//	cobjFileCSVOrders.open("Orders", "Date,Time,Open/Close,Operation,Price,Stock price,Quantity");
//	cobjFileCSVTrades.open("Trades", "Дата,Время,Операция,Цена,Кол-во");
//	messageMBFncNum(blnTradeDisabled_);
//	if (cblnTradeDisabled) { //Get the total net in a trade disabled mode. //If a trade disabled mode, load cintTotalnet from the file saved in a prior session.
//		string strFileTotalnet = cstrFilePrefix + cstrTotalnetTxt;
//		checkOrCreate(strFileTotalnet, to_string(cintTotalnet)); // Check if the file exists. Otherwise create one and write cintTotalnet to it.
//		ifstream objFileTotalnet(strFileTotalnet); //Read the total net from the file.
//		char chrTotalnet;
//		objFileTotalnet >> chrTotalnet;
//		cintTotalnet = stringToInt(string(&chrTotalnet));
//		objFileTotalnet.close();
//		string strFileTradeNums = cstrFilePrefix + cstrTradeNumsTxt;
//		checkOrCreate(strFileTradeNums); // Check if the file exists. Otherwise create one.
//		ifstream objFileTradeNums(strFileTradeNums); //Get trade numbers saved before, in any.
//		string strLine;
//		while (std::getline(objFileTradeNums, strLine)) cintTradeNums.push_back(stringToInt(strLine)); //How to read line by line or a whole text file at once? @ http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
//		objFileTradeNums.close();
//	}	
//}

void position::initialise(bool blnTradeDisabled_, int intLotsTraded_) {
	cblnTradeDisabled = blnTradeDisabled_; 
	cintLotsTraded = intLotsTraded_; 

	cobjFileCSVOrders.initialise("Orders", "Date,Time,Open/Close,Operation,Price,Stock price,Quantity");
	cobjFileCSVTrades.initialise("Trades", "Дата,Время,Операция,Цена,Кол-во");

	if (cblnTradeDisabled) { //Get the total net in a trade disabled mode. //If a trade disabled mode, load cintTotalnet from the file saved in a prior session.
		string strFileTotalnet = cstrFilePrefix + cstrTotalnetTxt;
		checkOrCreate(strFileTotalnet, to_string(cintTotalnet)); // Check if the file exists. Otherwise create one and write cintTotalnet to it.

		ifstream objFileTotalnet(strFileTotalnet); //Read the total net from the file.
		char chrTotalnet;
		objFileTotalnet >> chrTotalnet;
		cintTotalnet = stringToInt(string(&chrTotalnet));
		objFileTotalnet.close();

		string strFileTradeNums = cstrFilePrefix + cstrTradeNumsTxt;
		checkOrCreate(strFileTradeNums); // Check if the file exists. Otherwise create one.
		ifstream objFileTradeNums(strFileTradeNums); //Get trade numbers saved before, in any.
		
		string strLine;
		while (std::getline(objFileTradeNums, strLine)) 
			cintTradeNums.push_back(stringToInt(strLine)); //How to read line by line or a whole text file at once? @ http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
		
		objFileTradeNums.close();
	}	
}

//static int checkBit(int intFlags, int intBit) { // Функция возвращает значение бита (число 0, или 1) под номером intBit (начинаются с 0) в числе intFlags, если такого бита нет, возвращает nil @ http://quikluacsharp.ru/qlua-osnovy/iz-qlua-lua-v-excel-csv/ //TO DO: Encapsulate this function into the class. 
//	string strRevBitsStr; // Перевернутое (задом наперед) строковое представление двоичного представления переданного десятичного числа (intFlags) 
//	int intFmod{}; // Остаток от деления
//	bool blnGo = true; // Флаг работы цикла
//	while (blnGo) {
//		intFmod = intFlags % 2; // Остаток от деления
//		intFlags = (int)floor(intFlags / 2); // Оставляет для следующей итерации цикла только целую часть от деления
//		strRevBitsStr = strRevBitsStr + to_string(intFmod); // Добавляет справа остаток от деления
//		if (intFlags == 0) blnGo = false; // Если был последний бит, завершает цикл
//	}
//	string strResult = strRevBitsStr.substr(intBit, 1); // Возвращает значение бита //Example of Substring Operations @ http://nepsweb.co.uk/pgtcpp/stringex/substr.htm
//	if (strResult == "0") return 0;
//	else if (strResult == "1") return 1;
//	else return -1;
//}

/*inline*/ void mtqc::position::setLotsTraded(int intLotsTraded_) { cintLotsTraded = intLotsTraded_; }

void position::recordTrade(int intTradeNum, int intFlags, const string& strPrice, const string& strQty) { // Record a trade into the Trades CSV file 
	/*KTB for (int i = cintTradeNums.size() - 1; i >= 0; i--) { //for i = #cintTradeNums, 1, -1 do // Перебирает массив с номерами записанных сделок (в обратном порядке).
		if (cintTradeNums.at(i) == intTradeNum) return; // Если данная сделка уже была записана, выходит из функции
	}*/
	if (std::find(cintTradeNums.rbegin(), cintTradeNums.rend(), intTradeNum) != std::rend(cintTradeNums)) 
		return; // Перебирает массив с номерами записанных сделок (в обратном порядке). // Если данная сделка уже была записана, выходит из функции

	cintTradeNums.push_back(intTradeNum); //cintTradeNums[#cintTradeNums + 1] = intTradeNum //Если мы здесь, значит сделка не была найдена в числе уже записанных. Добавляет в массив номер новой сделки.
	ofstream objFileTradeNums(cstrFilePrefix + cstrTradeNumsTxt, ios::app || ios::ate); // Save the trade number in the file for later use.
	objFileTradeNums << intTradeNum << "\n";
	objFileTradeNums.close();

	string strOperation; //Вычисляет операцию сделки. //Introducing C++11 Brace-Initialization - string s{}; //same as: string s; @ http://www.informit.com/articles/article.aspx?p=1852519
	int intCheckBit = checkBit(intFlags, 2);
	if (intCheckBit == 1) 
		strOperation = "Продажа";
	//else if (intCheckBit == 0) 
	//else
	else if (intCheckBit == -1) 
		strOperation = "Купля";
	cobjFileCSVTrades.addLine(strOperation + "," + strPrice + "," + strQty, true);
}

bool position::sendTransaction_(int intOperation, const terminal& objTerminal, const string& strOpenClose, int intLots) { 
	static int intStockFuturesDiff = 500; //The difference between the prices of the stock and futures to order the worst futures price w/o the DOM.
	bool blnSendTransaction{}; //Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
	lua_State* L = objTerminal.getL();
	string strPriceFractional, strPriceFractionalDOM;	//Introducing C++11 Brace-Initialization //string s{}; //same as: string s; @ http://www.informit.com/articles/article.aspx?p=1852519
	//double dblPrice = objTerminal.getPriceStock() * 100 + (intOperation == OP_BUY ? intStockFuturesDiff : -intStockFuturesDiff); //local dblPrice = tonumber(gobjTerminal.getPriceStock()) * 100 + ({[OP_BUY] = intStockFuturesDiff, [OP_SELL] = -intStockFuturesDiff})[intOperation]
	double dblPrice = objTerminal.getPriceStock() * gintContractSize + (intOperation == OP_BUY ? intStockFuturesDiff : -intStockFuturesDiff); //local dblPrice = tonumber(gobjTerminal.getPriceStock()) * 100 + ({[OP_BUY] = intStockFuturesDiff, [OP_SELL] = -intStockFuturesDiff})[intOperation]
	if (gblnFuturesFractional) { //Is the price fractional?
		strPriceFractional = to_string(dblPrice);
		strPriceFractionalDOM = numberToStringF(objTerminal.getOfferBidPrice(intOperation));
	} else {
		strPriceFractional = to_string((int)(dblPrice));
		strPriceFractionalDOM = to_string((int)objTerminal.getOfferBidPrice(intOperation)); //strPriceFractionalDOM = tostring( math.floor(tonumber(strPriceDOM)) ) //ON gstrFutures DOM
	}
	string strMessageCSV = strOpenClose + "," + gstrOperations[intOperation] + "," + strPriceFractionalDOM + "," + to_string(objTerminal.getPriceStock()) + "," + to_string(cintLotsTraded);
	string strMessagePart1 = strOpenClose + ": " + (intOperation == OP_BUY ? "Bought" : "Sold") + " at " + numberToStringF(objTerminal.getPriceStock()) + " (" + strPriceFractionalDOM + ") " + to_string(cintLotsTraded);
	string strMessagePart2 = "                                                                                                                               ," + strMessageCSV; //ON gstrFutures DOM
	cobjFileCSVOrders.addLine(strMessageCSV, true); // %x: date (e.g., 09/16/98); %X: time (e.g., 23:48:10) @ https://www.lua.org/pil/22.1.html
	cobjFileCSVTrades.addLine(strOpenClose, true); // %x: date (e.g., 09/16/98); %X: time (e.g., 23:48:10) @ https://www.lua.org/pil/22.1.html
	if (cblnTradeDisabled) {
		recordTrade(cintTradeNums.size() + 1, (int)pow(2, 2) - 1 + intOperation, strPriceFractionalDOM, to_string(intLots)); // ["flags"]: бит 2 (0x4)  Заявка на продажу, иначе – на покупку. Данный флаг для сделок и сделок для исполнения определяет направление сделки (BUY/SELL) @ QLUA.chm\Флаги для таблиц Заявки, Заявки на внебиржевые сделки, Сделки, Сделки для исполнения
		blnSendTransaction = true; //The flag is first to prevent reopening/reclosing in the calling procedure just because of an error in the message below.
		cintTotalnet = cintTotalnet - (intOperation * 2 - 1) * intLots; //Set cintTotalnet by converting the operation to -1/1 in a gblnTradeDisabled mode.
		ofstream objFileTotalnet(cstrFilePrefix + cstrTotalnetTxt); //Save cintTotalnet in the file for reloading Quik.
		objFileTotalnet << cintTotalnet;
		objFileTotalnet.close();
		messages::message(strMessagePart1 + " Total net: " + to_string(cintTotalnet) + strMessagePart2);
	} else {
		lua_getglobal(L, "sendTransaction"); lua_newtable(L); lua::setField(L, "TRANS_ID", MagicNumber); lua::setField(L, "ACTION", "NEW_ORDER"); lua::setField(L, "CLASSCODE", wstringToString(gobjConstantsXML.getCLASSCODE())); lua::setField(L, "SECCODE", wstringToString(gobjConstantsXML.getFutures()));	lua::setField(L, "OPERATION", gstrOperations[intOperation]); lua::setField(L, "TYPE", "M"); lua::setField(L, "QUANTITY", to_string(intLots)); lua::setField(L, "ACCOUNT", ACCOUNT); lua::setField(L, "CLIENT_CODE", CLIENT_CODE); lua::setField(L, "PRICE", strPriceFractional); lua_pcall(L, 1, 1, 0); string strSendTransaction = lua_tostring(L, -1); //sendTransaction она вернет нам сообщение. Обратите внимание, что res идет без кавычек, это переменная, а не жестко заданный текст, как в предыдущем примере. @ http://robostroy.ru/community/article.aspx?id=773 //Результат транзакции можно получить, воспользовавшись функцией обратного вызова OnTransReply @ http://help.qlua.org/ch4_5_11.htm
		if (strSendTransaction != "") messages::messageExclamation("Sending the transaction failed! The error is " + strSendTransaction); // ЕСЛИ функция вернула строку диагностики ошибки, ТО значит транзакция не прошла // Выводит сообщение с ошибкой //@ http://quikluacsharp.ru/quik-qlua/primer-skripta-qlua-lua-vypolnyayushhego-torgovye-operatsii-v-terminale-quik/
		else {
			blnSendTransaction = true; //The flag is first to prevent reopening/reclosing in the calling procedure just because of an error in the message below.
			messages::message(strMessagePart1 + strMessagePart2);
	}	} 
	return blnSendTransaction;
}

/*inline*/ int position::getTotalnet() const { return cintTotalnet; } 
/*inline*/ void position::setTotalnet(int intTotalnet) { cintTotalnet = intTotalnet; } 

int position::getOperation() const { // Get the operation by converting cintTotalnet to OP_BUY/OP_SELL. 
	if (cintTotalnet > 0) return OP_BUY;
	else if (cintTotalnet < 0) return OP_SELL;
	else return gintOperationNull; //This is needed to prevent Warning	C4715	not all control paths return a value.
}

bool position::open_(int intOperation, const terminal& objTerminal, int& intLotsOpened) { //Alligator connection. 
	bool blnOpen{}; //Get to Know the New C++11 Initialization Forms @ http://www.informit.com/articles/article.aspx?p=1852519
	int intLots{};
	int intTotalnetAbs = abs(cintTotalnet);
	int intTotalnetResult = intTotalnetAbs + cintLotsTraded; //The resulting lots.
	//if (intTotalnetResult <= LotsMax) intLots = cintLotsTraded; //Won't the resulting lots exceed the maximum?
	//else if (intTotalnetAbs == LotsMax) messages::message("The maximal number of lots have been opened already before!"); //The maximum exeeded. //TO DO: Disable Alligator, when it keeps continuosly re-opening the same position.
	//else intLots = LotsMax - intTotalnetAbs; //Open lots left till the maximum.
	if (intTotalnetResult <= gobjConstantsXML.getLotsMax()) 
		intLots = cintLotsTraded; //Won't the resulting lots exceed the maximum?
	else if (intTotalnetAbs == gobjConstantsXML.getLotsMax()) 
		messages::message("The maximal number of lots have been opened already before!"); //The maximum exeeded. //TO DO: Disable Alligator, when it keeps continuosly re-opening the same position.
	else 
		intLots = gobjConstantsXML.getLotsMax() - intTotalnetAbs; //Open lots left till the maximum.
	if (intLots > 0) 
		blnOpen = sendTransaction_(intOperation, objTerminal, strOpen, intLots); //Are there lots to open?
	return blnOpen;
}

bool position::open(int intOperation, const terminal& objTerminal) { //Alligator connection. 
	int _; //n void variable for open_. //Alligator connection.
	return open_(intOperation, objTerminal, _); //Alligator connection.
} 

bool position::open(int intOperation, const terminal& objTerminal, int& intLotsOpened) { return open_(intOperation, objTerminal, intLotsOpened); } //Alligator connection. 

bool position::matchClosingToOpened(int intOperationClosing) const { //A closing trade operation must match the open one. 
	bool blnMatchClosingToOpened{};
	/* KTB Unnecessary self-contradiction: CORRECT THE LINE BELOW: GET cintTotalnet FROM QUIK:
	if (cblnTradeDisabled) { intOperationOpened = getOperation()
	else intOperationOpened = getOperation() }*/
	int intOperationOpened = getOperation();
	if (BUYtoSELL(intOperationClosing) == intOperationOpened) blnMatchClosingToOpened = true;
	//KTB else message( variousConsts::gstrMsgWrongOrder + ( intOperationOpened == OP_BUY ? " An OP_BUY position cannot be closed with an OP_BUYSTOP/OP_BUYLIMIT order!" : " An OP_SELL position cannot be closed with an OP_SELLSTOP/OP_SELLLIMIT order!" ) );
	return blnMatchClosingToOpened;
}

bool position::close(const terminal& objTermninal, bool blnReverse) { // Close all open lots or reverse the whole position. 
	int intClosingOperation = BUYtoSELL(getOperation());
	return sendTransaction_( intClosingOperation, objTermninal, strClose, abs(cintTotalnet) * (blnReverse ? 2 : 1) );
}

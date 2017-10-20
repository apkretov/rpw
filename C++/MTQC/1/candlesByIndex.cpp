#include "candlesByIndex.h"
using std::string;
using namespace mtqc;

candlesByIndex::candlesByIndex(lua_State* L_, const string& strTag, int intLine, int intCount, int intOffset) : //+
	L(L_), 
	cstrTag(strTag), //tag Ц строковый идентификатор графика или индикатора, 
	cintLine(intLine), //line Ц номер линии графика или индикатора.ѕерва€ лини€ имеет номер 0, first_candle Ц индекс первой свечки. ѕерва€(сама€ лева€) свечка имеет индекс 0.
	cintCount(intCount), //count Ц количество запрашиваемых свечек.
	cintOffset(intOffset) 
{ refresh(); }

candlesByIndex::~candlesByIndex() { 
	deleteCandlesByIndex();
	L = nullptr; // Release the memory an initialised pointer points to. 
}

int candlesByIndex::iBars() const { // Introduced for MT4 compatability. +
	lua_getglobal(L, "getNumCandles"); lua_pushstring(L, cstrTag.c_str()); lua_pcall(L, 1, 1, 0); int intBars = lua_tointeger(L, -1); lua_pop(L, 1); //Qlua: getNumCandles("AlgSR").
	return intBars;
}

inline void candlesByIndex::setBars() { cintBars = iBars(); }

void candlesByIndex::setCandlesByIndex() { // Set the object. 
	setBars();
	lua_getglobal(L, "getCandlesByIndex"); lua_pushstring(L, cstrTag.c_str()); lua_pushinteger(L, cintLine); lua_pushinteger(L, cintBars - cintOffset - cintCount); lua_pushinteger(L, cintCount); lua_pcall(L, 4, 3, 0); //Qlua: local t, n, l = getCandlesByIndex(strTag, intLine, intCount - intOffset - 1, 1); TABLE t, NUMBER n, STRING l getCandlesByIndex (STRING tag, NUMBER line, NUMBER first_candle, NUMBER count). ¬озвращаемые значени€ : t Ц таблица, содержаща€ запрашиваемые свечки, n Ц количество свечек в таблице t, l Ц легенда(подпись) графика.
	cintN = lua_tointeger(L, -2); lua_pop(L, 2); //Clear the stack off n and l.
	cintT = luaL_ref(L, LUA_REGISTRYINDEX); //Save the t table, the 1st result getCandlesByIndex returns. //Pop a value from the stack, stores it into the registry with a fresh integer key, and returns that key. 27.3.2 Ц References @ http://www.lua.org/pil/27.3.2.html
}

void candlesByIndex::deleteCandlesByIndex() { luaL_unref(L, LUA_REGISTRYINDEX, cintT); } // Release both the value and the reference. 27.3.2 Ц References @ http://www.lua.org/pil/27.3.2.html 

void candlesByIndex::refresh() { // Refresh the object. 
	deleteCandlesByIndex(); // Release both the value and the reference. 
	setCandlesByIndex(); // Set the object. 
}

double candlesByIndex::OHLC(const string& strOHLC, int intShift) const { 
	lua_rawgeti(L, LUA_REGISTRYINDEX, cintT); 
	lua_rawgeti(L, -1, cintN - intShift - 1); //Go to the 1st record in the t table. Its index is 0.
	lua_getfield(L, -1, strOHLC.c_str()); /*ѕолучить значение Close дл€ указанной свечи (цена закрыти€ свечи).*/ double dblOHLC = lua_tonumber(L, -1); lua_pop(L, 3); //Clear the stack off the t table, the record in the t table, and the value.
	return dblOHLC;
}

double candlesByIndex::getOpen(int intShift) const { return OHLC("open", intShift); } 
double candlesByIndex::getHigh(int intShift) const { return OHLC("high", intShift); } 
double candlesByIndex::getLow(int intShift) const { return OHLC("low", intShift); } 
double candlesByIndex::getClose(int intShift) const { return OHLC("close", intShift); } 

datetime candlesByIndex::getDatetime(int intShift) const { 
	int intTop = lua_gettop(L); //The current stack top index.
	lua_rawgeti(L, LUA_REGISTRYINDEX, cintT);
	lua_rawgeti(L, -1, cintN - intShift); //Go to the 1st record in the t table. Its index is 0.
	lua_getfield(L, -1, "datetime"); //Go to datetime  TABLE  ‘ормат даты и времени. "—вечки графика" @ QLUA.chm.
	int intTopDatetime = lua_gettop(L); //The current stack top index where the datetime table resides.
	lua_getfield(L, intTopDatetime, "mcs"); int intMcs = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "ms"); int intMs = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "sec"); int intSec = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "min"); int intMin = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "hour"); int intHour = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "day"); int intDay = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "month"); int intMonth = lua_tointeger(L, -1);
	lua_getfield(L, intTopDatetime, "year"); int intYear = lua_tointeger(L, -1);
	lua_pop(L, lua_gettop(L) - intTop - intTopDatetime); //Clear the stack off the t table, the record in the t table, the datatime table, and all the datetime values (from intTopDatetime atop).
	return datetime(intMcs, intMs, intSec, intMin, intHour, intDay, intMonth, intYear);
}
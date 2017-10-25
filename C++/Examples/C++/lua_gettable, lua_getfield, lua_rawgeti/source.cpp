#include "stdafx.h"
#include "Lua\lua.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::to_string;

void get1DimTable1() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "int1DimTable");
	lua_rawgeti(L, -1, 1); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 1 value.
	lua_rawgeti(L, -1, 2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 2 value.
	lua_rawgeti(L, -1, 3); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 3 value.
	cout << endl << endl;
}

void get1DimTable2() {
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "stt1DimTable");
	lua_getfield(L, -1, "a"); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1);
	lua_getfield(L, -1, "b"); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1);
	lua_getfield(L, -1, "c"); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1);
	cout << endl << endl;
}

void get1DimTable3() {
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "stt1DimTable");
	lua_getfield(L, -1, "a");
	lua_getfield(L, -2, "b");
	lua_getfield(L, -3, "c");
	cout << lua_tonumber(L, -3) << " " << lua_tonumber(L, -2) << " " << lua_tonumber(L, -1) << endl << endl;
	lua_pop(L, 3); //Clear the stack off the variables.
}

void getBackground() { //25.1 – Table Manipulation @ https://www.lua.org/pil/25.1.html
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttBackground");
	lua_getfield(L, -1, "r"); cout << lua_tonumber(L, -1) << " ";	lua_pop(L, 1);
	lua_getfield(L, -1, "g"); cout << lua_tonumber(L, -1) << " ";	lua_pop(L, 1);
	lua_getfield(L, -1, "b"); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1);
	cout << endl << endl;
}

void getTableWithinTable1() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttTableWithinTable1");
	lua_getfield(L, 1, "b"); //Get the table at the field with the index = "b".
	lua_rawgeti(L, -1, 1); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 1 value.
	lua_rawgeti(L, -1, 2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 2 value.
	lua_rawgeti(L, -1, 3); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 3 value.
	cout << endl << endl;
}

void getTableWithinTable2() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttTableWithinTable1");
	lua_getfield(L, 1, "b"); //Get the table at the field with the index = "b".
	lua_rawgeti(L, -1, 1); //Index 1 value.
	lua_rawgeti(L, -2, 2); //Index 2 value.
	lua_rawgeti(L, -3, 3); //Index 3 value.
	cout << lua_tonumber(L, -3) << " " << lua_tonumber(L, -2) << " " << lua_tonumber(L, -1) << endl << endl;
	lua_pop(L, 3); //Clear the stack off the variables.
}

void getTableWithinTable3() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttTableWithinTable1");
	lua_pushstring(L, "b"); lua_rawget(L, -2); //Get the table at the field with the index = "b".
	lua_rawgeti(L, -1, 1); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 1 value.
	lua_rawgeti(L, -1, 2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 2 value.
	lua_rawgeti(L, -1, 3); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 3 value.
	cout << endl << endl;
}

void getTableWithinTable4() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttTableWithinTable2");
	lua_pushnumber(L, 100); lua_rawget(L, -2); //Get the table at the field with the index = 100.
	lua_rawgeti(L, -1, 1); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 1 value.
	lua_rawgeti(L, -1, 2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 2 value.
	lua_rawgeti(L, -1, 3); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 3 value.
	cout << endl << endl;
}

void getTableWithinTable5() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "sttTableWithinTable2");
	lua_rawgeti(L, -1, 100); //Get the table at the field with the index = 100.
	lua_rawgeti(L, -1, 1); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 1 value.
	lua_rawgeti(L, -1, 2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 2 value.
	lua_rawgeti(L, -1, 3); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Index 3 value.
	cout << endl << endl;
}

void get1DimTable4() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua"); lua_getglobal(L, "int1DimTable");
	lua_pushnumber(L, 1); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_rawgeti(L, -1, 1)
	lua_pushnumber(L, 2); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_rawgeti(L, -1, 2)
	lua_pushnumber(L, 3); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_rawgeti(L, -1, 3)
	cout << endl << endl;
}

void get1DimTable5() { //Accessing a Lua table within a table from C++ @ http://stackoverflow.com/questions/11974806/accessing-a-lua-table-within-a-table-from-c
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua"); lua_getglobal(L, "stt1DimTable");
	lua_pushstring(L, "a"); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_getfield(L, -1, "a")
	lua_pushstring(L, "b"); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_getfield(L, -1, "b")
	lua_pushstring(L, "c"); lua_rawget(L, -2); cout << lua_tonumber(L, -1) << " "; lua_pop(L, 1); //Equivalent of: lua_getfield(L, -1, "c")
	cout << endl << endl;
}

int get2DimTable_WithError() { //Lua Tutorial 27: Multidimensional Tables In The C Library @ https://www.youtube.com/watch?v=beLLHyui7-c&list=PL0o3fqwR2CsWg_ockSMN6FActmMOJ70t_&index=31
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua"); lua_getglobal(L, "int2DimTable");
	int i, j;
	i = 2;
	lua_pushnumber(L, i); //Table i within the int2DimTable table.
	lua_gettable(L, -2);
	j = 3;
	lua_pushnumber(L, j); //Value j within table 1.
	lua_gettable(L, -2);
	cout << lua_tonumber(L, -1) << endl;
	/*
	j = 1; //ERROR.
	lua_pushnumber(L, j); //Value j within table 1.
	lua_gettable(L, -2);
	cout << lua_tonumber(L, -1) << endl;
	*/
	cout << endl;
	return 0;
}

void get1DimTable_WithError() {
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua"); lua_getglobal(L, "int1DimTable");
	int i, j;
	i = 2;
	lua_pushnumber(L, i); //Table i within the int1DimTable table.
	lua_gettable(L, -2);
	cout << lua_tonumber(L, -1) << endl;
	/*
	j = 3; //ERROR.
	lua_pushnumber(L, j); //Value j within table 1.
	lua_gettable(L, -2);
	cout << lua_tonumber(L, -1) << endl;
	*/
	cout << endl;
}

void displayBidOffer(lua_State* L, int intCount) {
	double dblPrice, intQuantity;
	for (int i = intCount; i >= 1; i--) {
		cout << "i = " + to_string(i);
		lua_rawgeti(L, -1, i); //Go to a Price/Quantity table record number i.
		lua_getfield(L, -1, "price");		cout << "   lua_isnil = " << lua_isnil(L, -1); dblPrice = lua_tonumber(L, -1);		cout << "   dblPrice = "		<< dblPrice;				lua_pop(L, 1); //Alternatively: lua_pushstring(L, "price"); lua_rawget(L, -2);
		lua_getfield(L, -1, "quantity"); cout << "   lua_isnil = " << lua_isnil(L, -1); intQuantity = lua_tointeger(L, -1);	cout << "   intQuantity = "	<< intQuantity << endl; lua_pop(L, 2); //Alternatively: lua_pushstring(L, "quantity"); lua_rawget(L, -2); 
}	}

void getquotelevel2() {
	lua_State* L = luaL_newstate(); luaL_dofile(L, "Data.lua");	lua_getglobal(L, "ql2");
	lua_getfield(L, -1, "bid_count"); int intBidCount = lua_tointeger(L, -1); lua_pop(L, 1); cout << "intBidCount = " + to_string(intBidCount) << endl; //Количество котировок покупки. При отсутствии спроса возвращается значение «0» //getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
	lua_getfield(L, -1, "offer_count"); int intOfferCount = lua_tointeger(L, -1); lua_pop(L, 1); /*cout << "intOfferCount = " + to_string(intBidCount) << endl;*/ //Количество котировок продажи. При отсутствии предложения возвращается значение «0» //getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
	if (intBidCount > 0) { //Are there records?
		lua_getfield(L, -1, "bid"); //Go to the Bid table. //Котировки спроса (покупки). При отсутствии спроса возвращается пустая строка //getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
		displayBidOffer(L, intBidCount);
		cout << "\nRepeatedly accessing the 'bid' table to show that it does't get removed from the stack automatically:\n";
		displayBidOffer(L, intBidCount);
	}
	cout << "\nlua_pop(L, 1) - Removes the 'bid' table from the stack. Alternatively you can set the stack top to a lower position or use an incremented stack indexes when accessing the stack in all the commands below.\n";
	lua_pop(L, 1);
	cout << endl << "intOfferCount = " + to_string(intBidCount) << endl;
	if (intOfferCount > 0) { //Are there records?
		lua_getfield(L, -1, "offer"); //Go to the Offer table. //Котировки спроса (покупки). При отсутствии спроса возвращается пустая строка //getQuoteLevel2 @ C:\Program Files (x86)\Lua\5.1\docs\lua5_1_4_Docs.chm
		displayBidOffer(L, intOfferCount);
	}
	cout << endl;
}

int main() {
	//get1DimTable1();
	//get1DimTable2();
	//get1DimTable3();
	//get1DimTable4();
	//get1DimTable5();
	//getBackground();
	getTableWithinTable1();
	//getTableWithinTable2();
	//getTableWithinTable3();
	//getTableWithinTable4();
	//getTableWithinTable5();
	//get2DimTable_WithError();
	//get1DimTable_WithError();
	//getquotelevel2();
	return 0;
}

#include "lua.h"
using std::string;
using std::to_string;
using namespace mtqc;

void lua::setField(lua_State* L, const string& strKey, const string& strValue) { lua_pushstring(L, strValue.c_str()); lua_setfield(L, -2, strKey.c_str()); } 

string lua::stackValue(lua_State * L) { 
	string strValue;
	switch (lua_type(L, -1)) {
		case LUA_TNUMBER:	 strValue = to_string(lua_tonumber(L, -1)); break;
		case LUA_TBOOLEAN: strValue = to_string(lua_toboolean(L, -1)); break;
		case LUA_TSTRING:  strValue = lua_tostring(L, -1); break;
		default:				 return "";
	}
	return "Value = " + strValue;
}

string lua::typeName(lua_State * L) {	return "lua_typename = " + string(lua_typename(L, lua_type(L, -1))); } 

string lua::stackState(lua_State* L) { return("lua_gettop = " + to_string(lua_gettop(L)) + "   " + typeName(L)) + "   " + stackValue(L); } 

#pragma once

namespace mtqc {
	class lua {
	public:
		static void setField(lua_State* L, const std::string& strKey, const std::string& strValue);
		static std::string stackValue(lua_State * L);
		static std::string typeName(lua_State * L);
		static std::string stackState(lua_State* L);
	};
}

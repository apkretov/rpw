#pragma once

namespace mtqc {
	class messages {
		static void message_atomic(const std::string& strMessage, int intIcon_type, lua_State* L_ = nullptr);
		static void message_(const std::string& strMessage, int intIcon_type, lua_State* L_ = nullptr);
	public:
		static void messageAtomic(const std::string& srtMessage); 
		static void messageInit(const std::string& strMessage, lua_State* L);
		static void message(const std::string& srtMessage);
		static void messageExclamation(const std::string& srtMessage);
		static void messageException(const std::exception& objException, const char* chrFunction, long double lngLine);
};	}
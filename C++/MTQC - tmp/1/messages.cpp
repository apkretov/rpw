#include "messages.h"
using std::string;
#include <queue>
#include "display.h"
using namespace mtqc;

namespace mtqc {
	static struct { //The messages.
		std::atomic_flag messageFlag = ATOMIC_FLAG_INIT;
		std::queue<string> messages; 
	} msttMessages;
}

//extern const string gstrMTQC;

void messages::message_atomic(const string& strMessage, int intIcon_type, lua_State* L_) { 
	try {
		static lua_State* L = L_;
		while (msttMessages.messageFlag.test_and_set()) {} //Acquire lock. //Spin.
	
		//Возвращает «nil» при ошибке выполнения или при обнаружении ошибки во входных параметрах. В остальных случаях возвращает «1». 
		lua_getglobal(L, "message"); 
		lua_pushstring(L, strMessage.c_str()); 
		lua_pushinteger(L, intIcon_type); 
		lua_pcall(L, 2, 1, 0); 
		lua_pop(L, 1); 
		
		msttMessages.messageFlag.clear(); //Release lock.
	}
	catch (const std::exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
	}
}

void messages::messageAtomic(const string& srtMessage) { 
	static int intIcon_type_information = 1;
	std::thread objThread(message_atomic, srtMessage, intIcon_type_information, nullptr); 
	objThread.detach();
}

void messages::message_(const string& strMessage, int intIcon_type, lua_State* L_) { 
	//KTB try {
		static lua_State* L = L_;
		
		//Возвращает «nil» при ошибке выполнения или при обнаружении ошибки во входных параметрах. В остальных случаях возвращает «1». 
		lua_getglobal(L, "message"); 
		lua_pushstring(L, strMessage.c_str()); 
		lua_pushinteger(L, intIcon_type); 
		lua_pcall(L, 2, 1, 0); 
		lua_pop(L, 1); 

	/*KTB }
		catch (const std::exception& objException) { 
		messages::messageException(objException, __FUNCTION__, __LINE__); 
		}
	*/
}

// The message safe version.
void messages::messageInit(const string& strMessage, lua_State* L) { 
	static int intIcon_type_information = 1;
	if (L == nullptr) 
		return; //Make sure L isn't null.
	message_(strMessage, intIcon_type_information, L);
}

void messages::message(const string& srtMessage) { 
	static int intIcon_type_information = 1;
	message_(srtMessage, intIcon_type_information); 
}

void messages::messageExclamation(const string& srtMessage) { 
	static int intIcon_type_exclamation = 2;
	message_(srtMessage, intIcon_type_exclamation);
}

// Dislplay an exception. 
void messages::messageException(const std::exception& objException, const char* chrFunction, long double lngLine) { 
	string strMessage = 
		"An exception in " + string(chrFunction) 
		+ ", line " + std::to_string(long(lngLine)) 
		+ (string(":\n") + objException.what());
	MessageBox(NULL, strMessage.c_str(), STR_PROJECT_NAME, MB_ICONERROR);
	//KTB message(strMessage); 
}

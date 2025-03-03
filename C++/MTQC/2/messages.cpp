#include "messages.h"
#include "display.h"
using namespace mtqcWinAPI;
using std::string;

void messages::messageException(const std::exception& objException, const char* chrFunction, long double lngLine) { // Dislplay an exception. 
	string strMessage = "An exception in " + string(chrFunction) + ", line " + std::to_string(long(lngLine)) + (string(":\n") + objException.what());
	/////////MessageBox(NULL, (stringToWstring(strMessage)).c_str(),	TEXT(STR_PROJECT_NAME), MB_ICONERROR);
} 



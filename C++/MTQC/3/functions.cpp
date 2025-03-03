#include "functions.h"
#include "stdafx.h"
using std::string;
using std::wstring;

namespace mtqcMFC {
	namespace functions {
	/*inline*/ wstring stringToWstring(const string& str) { return wstring(str.cbegin(), str.cend()); } 
	/*inline*/ string wstringToString(const wstring& str) { return string(str.cbegin(), str.cend()); }; //How to convert wstring into string? @ https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string 
	}
}
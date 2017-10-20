#pragma once

namespace mtqc {
	namespace functions {
		int roundToPts(double dblValue);
		int BUYtoSELL(int intOperation);
		int LIMITSTOPtoBUYSELL(int intOperation);
		int stringToInt(const std::string& strNumber);
		double stringToDouble(const std::string& strNumber);
		std::string threadIdToString(std::thread::id& objID);
		std::string numberToStringF(double dblNumber);
		//wchar_t* charToWchar_t(const char* const chrOrig);
		//char* wchar_tToChar(const wchar_t* const chrOrig);
		std::wstring stringToWstring(const std::string& str);
		std::string wstringToString(const std::wstring& str);
	}
}
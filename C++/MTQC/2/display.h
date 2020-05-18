#pragma once

#define displayNum(varNum) std::string(#varNum " = " + to_string(varNum)) //Token-Pasting Operator (##) @ https://msdn.microsoft.com/en-us/library/09dwwt6y.aspx
#define displayStr(str_) (#str_ " = " + std::string(str_))
#define displayWStr(str_) (#str_ L" = " + std::wstring(str_))

#define stringise(str_) (#str_)

#define STR_FUNCTION_LINE ( std::to_string(__COUNTER__) + " " + __FUNCTION__ + " " + std::to_string(__LINE__) )

#define messageMBFnc() MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE)).c_str(),	TEXT(STR_PROJECT_NAME), NULL )
//#define messageMBFnc() MessageBoxW((stringToWstring(STR_FUNCTION_LINE)).c_str())
#define messageMBFncNum(varNum) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE + ": " + displayNum(varNum))).c_str(), TEXT(STR_PROJECT_NAME), NULL )
//#define messageMBFncNum(varNum) MessageBoxW((stringToWstring(STR_FUNCTION_LINE + ": " + displayNum(varNum))).c_str())
#define messageMBFncStr(str_) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE + ": " + displayStr(str_))).c_str(), TEXT(STR_PROJECT_NAME), NULL )
//#define messageMBFncStr(str_) MessageBoxW((stringToWstring(STR_FUNCTION_LINE + ": " + displayStr(str_))).c_str())
#define messageMBFncWStr(str_) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE) + L": " + displayWStr(str_)).c_str(), TEXT(STR_PROJECT_NAME), NULL )
//#define messageMBFncWStr(str_) MessageBoxW((stringToWstring(STR_FUNCTION_LINE) + L": " + displayWStr(str_)).c_str())

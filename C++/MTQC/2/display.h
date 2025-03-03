#pragma once

#define displayNum(varNum) std::string(#varNum " = " + to_string(varNum)) //Token-Pasting Operator (##) @ https://msdn.microsoft.com/en-us/library/09dwwt6y.aspx
#define displayStr(str_) (#str_ " = " + std::string(str_))
#define displayWStr(str_) (#str_ L" = " + std::wstring(str_))

#define stringise(str_) (#str_)

#define STR_FUNCTION_LINE ( std::to_string(__COUNTER__) + " " + __FUNCTION__ + " " + std::to_string(__LINE__) )

#define msgMBFnc() MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE)).c_str(),	TEXT(STR_PROJECT_NAME), NULL )
#define msgMBFncNum(varNum) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE + ": " + displayNum(varNum))).c_str(), TEXT(STR_PROJECT_NAME), NULL )
#define msgMBFncStr(str_) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE + ": " + displayStr(str_))).c_str(), TEXT(STR_PROJECT_NAME), NULL )
#define msgMBFncWStr(str_) MessageBox( NULL, (stringToWstring(STR_FUNCTION_LINE) + L": " + displayWStr(str_)).c_str(), TEXT(STR_PROJECT_NAME), NULL )

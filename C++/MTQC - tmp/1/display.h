#pragma once

#include "messages.h"
#include "functions.h"

//KTB void log(string strLog);

#define displayNum(varNum) std::string(#varNum " = " + std::to_string(varNum)) //Token-Pasting Operator (##) @ https://msdn.microsoft.com/en-us/library/09dwwt6y.aspx
#define displayStr(str_) (#str_ " = " + std::string(str_))
#define displayWStr(str_) (#str_ L" = " + std::wstring(str_))
#define stringise(str_) (#str_)

//#define STR_FUNCTION_LINE ( std::to_string(__COUNTER__) + " " + __FUNCTION__ + " " + std::to_string(__LINE__) )
#define STR_FUNCTION_LINE ( std::string("Function: """) + __FUNCTION__ + """, line: " + std::to_string(__LINE__) )


#define msgFnc() messages::message(STR_FUNCTION_LINE)
#define msgFncNum(varNum) messages::message( STR_FUNCTION_LINE + ": " + displayNum(varNum) )
#define msgFncStr(str_) messages::message( STR_FUNCTION_LINE + ": " + displayStr(str_) ) 
#define msgFncWStr(str_) messages::message( STR_FUNCTION_LINE + ": " + wstringToString(displayWStr(str_)) )
#define msgFncThread() messages::message( STR_FUNCTION_LINE + ": This thread's id: " +  mtqc::functions::threadIdToString(std::this_thread::get_id()) ) 
//KTB #define logFnc() log(std::string(__DATE__) + " " + __TIME__ + " " + STR_FUNCTION_LINE)

//Copied from the MTQC - WinAPI project wstring to string adaption might be needed.
#define msgMBFnc() MessageBox( NULL, (STR_FUNCTION_LINE).c_str(), STR_PROJECT_NAME, NULL ) 
#define msgMBFncNum(varNum) MessageBox( NULL, (STR_FUNCTION_LINE + ": " + displayNum(varNum)).c_str(), STR_PROJECT_NAME, NULL )
#define msgMBFncStr(str_) MessageBox( NULL, (STR_FUNCTION_LINE + ": " + displayStr(str_)).c_str(), STR_PROJECT_NAME, NULL )
#define msgMBFncWStr(str_) MessageBox( NULL, (STR_FUNCTION_LINE + ": " + wstringToString(displayWStr(str_))).c_str(), STR_PROJECT_NAME, NULL )

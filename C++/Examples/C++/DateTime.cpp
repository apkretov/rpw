#include "stdafx.h"

#include <Windows.h> //get date time in C++ @ https://www.youtube.com/watch?v=Z_qHEWXUxnE
#include <wchar.h> 
void getDateTime() {
	SYSTEMTIME time;
	GetLocalTime(&time);
	wprintf(L"The local time: %02d:%02d:%02d\n", time.wHour, time.wMinute, time.wSecond);
	wprintf(L"The date: %02d.%02d.%02d\n", time.wDay, time.wMonth, time.wYear);
}

//C++ Date and Time @ https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
#pragma warning(disable: 4996)
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
void fnc_ctime() {
	cout << endl;
	time_t now = time(0); // current date/time based on current system
	cout << "Number of sec since January 1,1970:" << now << endl;
	tm *ltm = localtime(&now);
	cout << "Date: " << ltm->tm_mday << "." << 1 + ltm->tm_mon << "." << 1900 + ltm->tm_year << endl;
	cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl << endl;
}

#pragma warning(disable: 4996) //C++: Date & Time @ https://www.youtube.com/watch?v=qXB5icpo0qY
void cppDateTime() { 
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now); //Warns to use a safe alternative localtime_s.
	cout << "Today is " << nowLocal.tm_mday << "." << nowLocal.tm_mon + 1 << "." << nowLocal.tm_year + 1900 << endl;
	cout << "Time is " << nowLocal.tm_hour << ":" << nowLocal.tm_min << ":" << nowLocal.tm_sec << endl << endl;
}

#include <time.h>  // crt_wctime_s.c //This program gets the current time in time_t form and then uses _wctime_s to display the time in string form. //ctime_s, _ctime32_s, _ctime64_s, _wctime_s, _wctime32_s, _wctime64_s @  https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(time%2Fctime_s);k(ctime_s);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
#include <stdio.h>  
#define SIZE 26  
void fnc_wctime_s() {
	time_t ltime;
	wchar_t buf[SIZE];
	time(&ltime);
	_wctime_s(buf, SIZE, &ltime);
	wprintf_s(L"The time is %s\n", buf);
}

#pragma warning(disable: 4996) //Current date and time as string @ http://stackoverflow.com/questions/16357999/current-date-and-time-as-string
void strftimeFormatting() { 
	time_t dtmRawtime;
	struct tm* sttTimeinfo;
	const int intSize = 80; //Equivalent of sizeof(chrBuffer).
	char chrBuffer[intSize];
	time(&dtmRawtime);
	sttTimeinfo = localtime(&dtmRawtime);
	strftime(chrBuffer, intSize, "%d.%m.%Y %H:%M:%S", sttTimeinfo); cout << chrBuffer << endl;
	strftime(chrBuffer, intSize, "%d.%m.%Y", sttTimeinfo); cout << chrBuffer << endl;
	strftime(chrBuffer, intSize, "%H:%M:%S", sttTimeinfo); cout << chrBuffer << endl;
	cout << endl;
}

int main() {
	getDateTime();
	fnc_ctime();
	cppDateTime();
	fnc_wctime_s();
	strftimeFormatting();
	return 0;
}
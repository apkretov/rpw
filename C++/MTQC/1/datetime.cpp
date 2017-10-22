#include "datetime.h"
using namespace mtqc;

//Class Member Initialization 
//Bear in mind that if the same data member has both a class member initializer and a mem-init in the constructor, the latter takes precedence. 
//In fact, you can take advantage of this behavior by specifying a default value for a member in the form of a class member initializer 
//that will be used if the constructor doesn't have an explicit mem-init for that member. Otherwise, the constructor's mem-init will take effect, 
//overriding the class member initializer. @ http://www.informit.com/articles/article.aspx?p=1852519
datetime::datetime() {} 

datetime::datetime(int intMcs, int intMs, int intSec, int intMin, int intHour, int intDay, int intMonth, int intYear) :
	cintMcs(intMcs),
	cintMs(intMs),
	cintSec(intSec),
	cintMin(intMin),
	cintHour(intHour),
	cintDay(intDay),
	cintMonth(intMonth),
	cintYear(intYear)
{}

bool datetime::operator<(const datetime& objDatetimeR) const { 
	if (cintYear < objDatetimeR.cintYear) return true; //A member function can access private members of the same class's object.
	if (cintMonth < objDatetimeR.cintMonth) return true;
	if (cintDay < objDatetimeR.cintDay) return true;
	if (cintHour < objDatetimeR.cintHour) return true;
	if (cintMin < objDatetimeR.cintMin) return true;
	if (cintSec < objDatetimeR.cintSec) return true;
	if (cintMs < objDatetimeR.cintMs) return true;
	if (cintMcs < objDatetimeR.cintMcs) return true;
	return false;
}

// Introduced for MT4 compatability. 
const datetime& datetime::operator=(int intNum) { 
	this->cintMcs = intNum; //An explicit use of the this pointer.
	this->cintMs = intNum;
	this->cintSec = intNum;
	this->cintMin = intNum;
	this->cintHour = intNum;
	this->cintDay = intNum;
	this->cintMonth = intNum;
	this->cintYear = intNum;
	return *this; // enables x = y = z, for example //C++ Fundamentals By Paul J. @ Lesson10\Fig11_06_08.
}

// Introduced for MT4 compatability. 
//TO DO: Optimise the algorithm by comparing membmer multiplications only. E.g: Years * 1000 + Month * 100 + Day * 10 etc. 
const datetime& datetime::operator=(const datetime& objDatetimeR) { 
	(*this).cintMcs = objDatetimeR.cintMcs; //An explicit use of a dereferenced this pointer.
	(*this).cintMs = objDatetimeR.cintMs; 
	(*this).cintSec = objDatetimeR.cintSec;
	(*this).cintMin = objDatetimeR.cintMin;
	(*this).cintHour = objDatetimeR.cintHour;
	(*this).cintDay = objDatetimeR.cintDay;
	(*this).cintMonth = objDatetimeR.cintMonth;
	(*this).cintYear = objDatetimeR.cintYear;
	return *this; // enables x = y = z, for example //C++ Fundamentals By Paul J. @ Lesson10\Fig11_06_08.
}

/*KTB
//Practicing with rvalue. 
//Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c 
const datetime& datetime::operator=(datetime&& objDatetimeR) { 
	swap((*this).cintMcs, objDatetimeR.cintMcs); 
	swap((*this).cintMs, objDatetimeR.cintMs); 
	swap((*this).cintSec, objDatetimeR.cintSec);
	swap((*this).cintMin, objDatetimeR.cintMin);
	swap((*this).cintHour, objDatetimeR.cintHour);
	swap((*this).cintDay, objDatetimeR.cintDay);
	swap((*this).cintMonth, objDatetimeR.cintMonth);
	swap((*this).cintYear, objDatetimeR.cintYear);
	return *this; // enables x = y = z, for example //C++ Fundamentals By Paul J. @ Lesson10\Fig11_06_08.
}
*/

// Despite this function can be a member (alike operator<), I made it friend purposefuly for practice. Introduced for MT4 compatability. 
bool mtqc::operator>(const datetime& objDatetimeL, const datetime& objDatetimeR) { 
	if (objDatetimeL.cintYear > objDatetimeR.cintYear) return true; //A friend function can access private members.
	if (objDatetimeL.cintMonth > objDatetimeR.cintMonth) return true;
	if (objDatetimeL.cintDay > objDatetimeR.cintDay) return true;
	if (objDatetimeL.cintHour > objDatetimeR.cintHour) return true;
	if (objDatetimeL.cintMin > objDatetimeR.cintMin) return true;
	if (objDatetimeL.cintSec > objDatetimeR.cintSec) return true;
	if (objDatetimeL.cintMs > objDatetimeR.cintMs) return true;
	if (objDatetimeL.cintMcs > objDatetimeR.cintMcs) return true;
	return false; 
} 

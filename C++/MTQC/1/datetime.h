#pragma once

namespace mtqc {
	class datetime {
		int cintMcs = 0; //Class Member Initialization @ http://www.informit.com/articles/article.aspx?p=1852519
		int cintMs{}; //Introducing C++11 Brace-Initialization @ http://www.informit.com/articles/article.aspx?p=1852519
		int cintSec = 0;
		int cintMin{};
		int cintHour = 0;
		int cintDay{};
		int cintMonth = 0;
		int cintYear{};

		friend bool operator>(const datetime& objDatetimeL, const datetime& objDatetimeR);

	public:
		datetime();
		datetime(int intMcs, int intMs, int intSec, int intMin, int intHour, int intDay, int intMonth, int intYear);

		int getMcs() const { return cintMcs; } 
		int getMs() const { return cintMs; } 
		int gettSec() const { return cintSec; } 
		int gettMin() const { return cintMin; } 
		int gettHour() const { return cintHour; } 
		int gettDay() const { return cintDay; } 
		int gettMonth() const { return cintMonth; } 
		int gettYear() const { return cintYear; } 

		void setMcs(int intMcs) { cintMcs = intMcs; } 
		void setMs(int intMs) { cintMs = intMs; } 
		void setSec(int intSec) { cintSec = intSec; } 
		void setMin(int intMin) { cintMin = intMin; } 
		void setHour(int intHour) { cintHour = intHour; } 
		void setDay(int intDay) { cintDay = intDay; } 
		void setMonth(int intMonth) { cintMonth = intMonth; } 
		void setYear(int intYear) { cintYear = intYear; } 

		bool operator<(const datetime& objDatetime) const;
		const datetime& operator=(int intNum);
		const datetime& operator=(const datetime& objDatetimeR);
		//KTB const datetime& operator=(datetime&& objDatetimeR);
	};	
}
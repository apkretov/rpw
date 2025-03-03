#if 0

#include "../../stdafx.h"
using namespace std;

struct Day { //TEST!
	int value;
	explicit Day(int new_value) {
		value = new_value;
	}
};

struct Month {
	int value;
	explicit Month(int new_value) {
		value = new_value;
	}
};

struct Year {
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};

struct Date {
	int day;
	int month;
	int year;

	Date(Day new_day, Month new_month, Year new_year) {
		day = new_day.value; //TEST!
		month = new_month.value;
		year = new_year.value;
	}
};

void PrintDate(const Date &date) {
	cout << date.day << '.' << date.month << '.' << date.year << '\n';
}

int main() {
	PRINT_FILE_LINE();

	Date date = {Day{10}, Month{11}, Year{22}}; //TEST
	//TEST! Date date = {{10}, {11}, {22}};
	PrintDate(date);
}
#endif
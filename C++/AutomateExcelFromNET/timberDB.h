#pragma once
#include <vector>
using std::vector;
#include <string>
using std::wstring;

namespace timberDB {
	struct timberDB { 
		const wchar_t* server;
		const wchar_t* DSN;
		const wchar_t* UID; 
		const wchar_t* PWD;
		const wchar_t* database;
		const wchar_t* table; 
	};

	bool insertIntoData(const timberDB& sttTimberDB, const vector<vector<wstring>>* strCountryDim, const vector<vector<double>>* dblYearValue);
	bool deleteData(const timberDB& sttTimberDB);
}
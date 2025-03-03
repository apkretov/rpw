#pragma once
#include <vector>
using std::vector;
#include <string>
using std::wstring;

namespace timberDB {
	struct DB { 
		const wchar_t* server;
		const wchar_t* DSN;
		const wchar_t* UID; 
		const wchar_t* PWD;
		const wchar_t* database;
		const wchar_t* table; 
	};

	struct SQLSelect {
		wstring strYear; //TO DO: Use long instead of wstring, if possible.
		wstring strCountry_ID; //TO DO: Distinguish between Country_ID and Country_ID_ISO.
		wstring strProduct_Code; //TO DO: Distinguish between Product_Code and Product_ID.
		wstring strItem_ID;
		double dblValue;
		int intStatus_ID;
	};

	bool insertIntoData(const DB& sttTimberDB, const vector<vector<wstring>>* vecCountryDim, const vector<vector<wstring>>* vecYearValue);
	bool insertIntoDataText(const DB& sttTimberDB, const vector<vector<wstring>>* vecCountryDim, const vector<wstring>* vecValueText);
	bool deleteData(const DB& sttTimberDB);
	bool selectData(const DB& sttTimberDB, SQLSelect& sttSQLSelect);
}
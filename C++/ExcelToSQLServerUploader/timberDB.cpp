#include "timberDB.h" 
#include <windows.h> // How to connect SQL Server to C+ Program - Solution 2 @ https://www.codeproject.com/Questions/341111/How-to-connect-SQL-Server-to-Cplus-Program
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
using std::string;
using std::to_string;
using std::to_wstring;
using std::vector;
using std::exception;
#include <boost\shared_array.hpp>
typedef boost::shared_array<wchar_t> wcharSP_t;
 
#define STR_FUNCTION_LINE ( to_string(__COUNTER__) + " " + __FUNCTION__ + " " + to_string(__LINE__) )

bool executeStoredProcedure(timberDB::SQLSelect*);

namespace timberDB {

	enum struct SQLStatements : int { insert, insertText, delete_ };
	
	static void messageException(const exception& objException) { // Dislplay an exception.
		string strException = STR_FUNCTION_LINE + ":\n" + string(objException.what()) + "\nException name: " + typeid(objException).name();
		MessageBox( NULL, (LPCWSTR)strException.c_str(), L"TimberDB exception", MB_ICONERROR );
	}

	static wcharSP_t concatWchars(const wchar_t* chrOne, const wchar_t* chrTwo) { // After concatinating wstring's, c_str() produced an unusable wchar_t string. That's why this complicate technique had been applied.
		size_t const intCount = wcslen(chrOne) + wcslen(chrTwo) + 1; 
		wcharSP_t ptrDest{new wchar_t[intCount]};
		wcscpy_s(ptrDest.get(), intCount, chrOne);
		wcscat_s(ptrDest.get(), intCount, chrTwo);	
		return ptrDest;
	}

	static bool executeSQL(
			SQLStatements intSQLStatement, 
			const DB& sttTimberDB, 
			const vector<vector<wstring>>* vecCountryDim = nullptr, 
			const vector<vector<wstring>>* vecYearValue = nullptr, 
			const vector<wstring>* vecValueText = nullptr
			) 
	{
		try {
			SQLHANDLE hndSQLEnv = nullptr;
			SQLHANDLE hndSQLConnection = nullptr;
			SQLHANDLE hndStatement = nullptr;
			SQLRETURN intRetCode;
			bool blnSQLbreak{}; //The SQL loop break flag.

			auto show_error = [](unsigned int intHandleType, const SQLHANDLE& handle) { //lambda.
				const int intSize = 1024;
				SQLWCHAR chrSQLstate[intSize];
				SQLWCHAR chrMessage[intSize];
				if (SQL_SUCCESS == SQLGetDiagRec(intHandleType, handle, 1, chrSQLstate, NULL, chrMessage, intSize, NULL)) 
					MessageBox(NULL, chrMessage, L"", NULL);
			};

			do {
				if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hndSQLEnv)) 
					break;
				if (SQL_SUCCESS != SQLSetEnvAttr(hndSQLEnv,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) 
					break;
				if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, hndSQLEnv, &hndSQLConnection)) 
					break;
 
				wcharSP_t ptrConnStr = concatWchars(L"SERVER=", sttTimberDB.server); //Compile a connection string such as: L"SERVER=KIRILL-HP; DSN=PCAxis2; UID=Alex2; PWD=110502; DATABASE=timberFO;". After concatinating wstring's, c_str() produced an unusable wchar_t string. That's why this complicate technique had been applied.
				ptrConnStr = concatWchars(ptrConnStr.get(), L"; DSN=");
				ptrConnStr = concatWchars(ptrConnStr.get(), sttTimberDB.DSN);
				ptrConnStr = concatWchars(ptrConnStr.get(), L"; UID=");
				ptrConnStr = concatWchars(ptrConnStr.get(), sttTimberDB.UID);
				ptrConnStr = concatWchars(ptrConnStr.get(), L"; PWD=");
				ptrConnStr = concatWchars(ptrConnStr.get(), sttTimberDB.PWD);
				ptrConnStr = concatWchars(ptrConnStr.get(), L"; DATABASE=");
				ptrConnStr = concatWchars(ptrConnStr.get(), sttTimberDB.database);
				ptrConnStr = concatWchars(ptrConnStr.get(), L";");

				SQLWCHAR chrRetConString[1024];
				SQLRETURN intSQLDriverConnect = SQLDriverConnect(hndSQLConnection, NULL, ptrConnStr.get(), SQL_NTS, chrRetConString, 1024, NULL,SQL_DRIVER_NOPROMPT);
				
				switch(intSQLDriverConnect) { //SQL Server Browsing Example @ https://docs.microsoft.com/en-us/sql/odbc/reference/develop-app/sql-server-browsing-example
				/*OFF case SQL_SUCCESS_WITH_INFO: 
					show_error(SQL_HANDLE_DBC, hndSQLConnection); 
					break; */
				case SQL_INVALID_HANDLE:
				case SQL_ERROR:
					show_error(SQL_HANDLE_DBC, hndSQLConnection);
					intRetCode = -1;
					break;
				default: 
					break;
				}
 
				if (intRetCode == -1) 
					break;
				if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, hndSQLConnection, &hndStatement)) 
					break;
 
				switch (intSQLStatement) {
				case SQLStatements::delete_: 
					{
						wstring strSQLStr = L"delete from [" + wstring(sttTimberDB.table) + L"]";
						if ( SQL_SUCCESS != SQLExecDirect(hndStatement, (SQLWCHAR*)strSQLStr.c_str(), SQL_NTS) ) {
							show_error(SQL_HANDLE_STMT, hndStatement);
							blnSQLbreak = true; //Break the SQL loop.
						}
					}
					break;
				
				case SQLStatements::insert:
					{
						auto j = vecYearValue->begin();
						for (auto i = vecCountryDim->begin(); i < vecCountryDim->end(); i++) { 
							auto ptrCountryDim = i._Ptr->begin(); //Accessing via pointers vs. [][] indexes.
							wstring strCountry_ID = *ptrCountryDim;
							wstring strDimension_ID = *(++ptrCountryDim);
							auto ptrYearValue = j._Ptr->begin();
							wstring strYear = *ptrYearValue;
							wstring strValue = *(++ptrYearValue);
							wstring strSQLStr = 
								L"insert into [" + 
								wstring(sttTimberDB.table) + 
								/* The Forest Ownership settings. //TO DO: Arrange a GUI switch.
								L"] (Country_ID, Dimension_ID, Year, Value) values ('" + 
								*/
								L"] (UN_Country_Code, Dimension_ID, Year, Value) values ('" + //TO DO: Arrange a GUI entry for the table fields as well as for the table itself: sttTimberDB.table.
								strCountry_ID + L"', '" + 
								strDimension_ID + L"', " + 
								strYear + L", " + 
								strValue + L")";
							j++; //Next year and value.

							if ( SQLExecDirect(hndStatement, (SQLWCHAR*)strSQLStr.c_str(), SQL_NTS) != SQL_SUCCESS ) {
								show_error(SQL_HANDLE_STMT, hndStatement);
								blnSQLbreak = true; //Break the SQL loop.
								break;
							}	
						}
					}
					break;
				
				case SQLStatements::insertText:
					{
						auto j = vecValueText->begin();
						for (auto i = vecCountryDim->begin(); i < vecCountryDim->end(); i++) { 
							auto ptrCountryDim = i._Ptr->begin(); //Accessing via pointers vs. [][] indexes.
							wstring strCountry_ID = *ptrCountryDim;
							wstring strDimension_ID = *(++ptrCountryDim);
							wstring strValueText = *j;
							wstring strSQLStr = 
								L"insert into [" + 
								wstring(sttTimberDB.table) + 
								L"] (UN_Country_Code, Dimension_ID, Value) values ('" + //TO DO: Arrange a GUI entry for the table fields as well as for the table itself: sttTimberDB.table.
								strCountry_ID + 
								L"', '" + strDimension_ID + 
								L"', N'" + strValueText + L"')"; // Select cyrillic character in SQL: When user insert Russian word like 'пример' to database,database saves it like '??????'. @ https://stackoverflow.com/questions/32350950/select-cyrillic-character-in-sql
							j++; //The next text value.
							if ( SQLExecDirect(hndStatement, (SQLWCHAR*)strSQLStr.c_str(), SQL_NTS) != SQL_SUCCESS ) {
								show_error(SQL_HANDLE_STMT, hndStatement);
								blnSQLbreak = true; //Break the SQL loop.
								break;
							}	
						}
					}
					break;
				}
			} while(FALSE && !blnSQLbreak); //Loop, unless the SQL loop is broken.

			SQLFreeHandle(SQL_HANDLE_STMT, hndStatement);
			SQLDisconnect(hndSQLConnection);
			SQLFreeHandle(SQL_HANDLE_DBC, hndSQLConnection);
			SQLFreeHandle(SQL_HANDLE_ENV, hndSQLEnv);
			return !blnSQLbreak && intRetCode != -1;
		}
		catch (const exception& objException) { 
			messageException(objException); 
			return false;
		}	
	}	

	bool insertIntoData(const DB& sttTimberDB, const vector<vector<wstring>>* vecCountryDim, const vector<vector<wstring>>* vecYearValue) {
		try { 
			return executeSQL(SQLStatements::insert, sttTimberDB, vecCountryDim, vecYearValue);
		}
		catch (
			const exception& objException) { messageException(objException); 
		}
		return false;
	}

	bool insertIntoDataText(const DB& sttTimberDB, const vector<vector<wstring>>* vecCountryDim, const vector<wstring>* vecValueText) {
		try { 
			return executeSQL(SQLStatements::insertText, sttTimberDB, vecCountryDim, nullptr, vecValueText);
		}
		catch (
			const exception& objException) { messageException(objException); 
		}
		return false;
	}

	bool deleteData(const DB& sttTimberDB) {
		try { 
			return executeSQL(SQLStatements::delete_, sttTimberDB);
		}
		catch (
			const exception& objException) { messageException(objException); 
		}
		return false;
	}

	bool selectData(const DB& sttTimberDB, SQLSelect& sttSQLSelect) {
		try { 
			return executeStoredProcedure(&sttSQLSelect); 
		}
		catch (
			const exception& objException) { messageException(objException); 
		}
		return false;
	}
}
#include "stdafx.h" // How to connect SQL Server to C+ Program - Solution 2 @ https://www.codeproject.com/Questions/341111/How-to-connect-SQL-Server-to-Cplus-Program
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
using namespace std;
 
void show_error(unsigned int handletype, const SQLHANDLE& handle) {
	SQLWCHAR sqlstate[1024];
	SQLWCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))	cout << "Message: " << message << "\nSQLSTATE: " << sqlstate << endl;
	//KTB if (SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL)) MessageBox(NULL, message, L"", NULL);
}
 
int main() {
	SQLHANDLE sqlenvhandle = nullptr;
	SQLHANDLE sqlconnectionhandle = nullptr;
	SQLHANDLE sqlstatementhandle = nullptr;
	SQLRETURN retcode;
 
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle)) break;
		if (SQL_SUCCESS != SQLSetEnvAttr(sqlenvhandle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) break;
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle)) break;
 
		SQLWCHAR retconstring[1024];
		switch( SQLDriverConnect(sqlconnectionhandle, NULL, L"DSN=PCAxis2; SERVER=KIRILL-HP; UID=Alex2; PWD=110502; DATABASE=timber;", SQL_NTS, retconstring, 1024, NULL,SQL_DRIVER_NOPROMPT) ) { //SQL Server Browsing Example @ https://docs.microsoft.com/en-us/sql/odbc/reference/develop-app/sql-server-browsing-example
		case SQL_SUCCESS_WITH_INFO: show_error(SQL_HANDLE_DBC, sqlconnectionhandle); break;
		case SQL_INVALID_HANDLE:
		case SQL_ERROR:
			show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
			retcode = -1;
			break;
		default:
			break;
		}
 
		if (retcode == -1) break;
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle)) break;
 
		if (SQL_SUCCESS != SQLExecDirect(sqlstatementhandle, L"select * from Unit", SQL_NTS)) {
			show_error(SQL_HANDLE_STMT, sqlstatementhandle);
			break;
		}else{
			char field1[64];
			char field2[64];
			int id;
			while (SQLFetch(sqlstatementhandle) == SQL_SUCCESS) {
				SQLGetData(sqlstatementhandle, 1, SQL_C_ULONG, &id, 0, NULL);
				SQLGetData(sqlstatementhandle, 2, SQL_C_CHAR, field1, 64, NULL);
				SQLGetData(sqlstatementhandle, 3, SQL_C_CHAR, field2, 64, NULL);
				cout << id << " " << field1 << " " << field2 << endl;
	}	}	}
	while(FALSE);
	SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle );
	SQLDisconnect(sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
}

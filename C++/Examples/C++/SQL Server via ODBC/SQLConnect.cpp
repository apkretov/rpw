#include "stdafx.h" //SQLConnect Function @ https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqlconnect-function#syntax
#include <windows.h> //Code Example. In the following example, an application allocates environment and connection handles. It then connects to the SalesOrders data source with the user ID JohnS and the password Sesame and processes data. When it has finished processing data, it disconnects from the data source and frees the handles.
#include <sqlext.h>  // SQLConnect_ref.cpp  compile with: odbc32.lib  

int main() {
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
	SQLRETURN retcode;

	SQLCHAR* OutConnStr = (SQLCHAR *)malloc(255);
	SQLSMALLINT * OutConnStrLen = (SQLSMALLINT *)malloc(255);
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv); // Allocate environment handle  

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { // Set the ODBC version environment attribute  
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { 	// Allocate connection handle  
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { // Set login timeout to 5 seconds  
				SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
				retcode = SQLConnect(hdbc, L"PCAxis2", 7, L"Alex2", 5, L"110502", 6); // Connect to data source  
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { // Allocate statement handle  
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { // Process data  
						MessageBox(NULL, L"Connected!", L"", NULL);
						SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
					}
					SQLDisconnect(hdbc);
				}
				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		}	}
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
}	}
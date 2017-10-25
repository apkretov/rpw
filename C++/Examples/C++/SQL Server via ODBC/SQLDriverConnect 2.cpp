#include "stdafx.h" // SQLDriverConnect_ref.cpp compile with: odbc32.lib user32.lib  //SQLDriverConnect Function @ https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqldriverconnect-function
#include <windows.h>  
#include <sqlext.h>  

int main() {  
   SQLHENV henv;  
   SQLHDBC hdbc;  
   SQLHSTMT hstmt;  
   SQLRETURN retcode;  
	SQLWCHAR OutConnStr[255];  
   SQLSMALLINT OutConnStrLen;  
   HWND desktopHandle = GetDesktopWindow();   // desktop's window handle  
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);  // Allocate environment handle  
   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {  // Set the ODBC version environment attribute  
      retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);   
      if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {  // Allocate connection handle  
         retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);   
         if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {  // Set login timeout to 5 seconds  
            SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);  
            retcode = SQLDriverConnect( hdbc, desktopHandle, (SQLWCHAR*)"driver=SQL Server", _countof("driver=SQL Server"), OutConnStr, 255, &OutConnStrLen, SQL_DRIVER_PROMPT ); // SQL_NULL_HDBC
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { // Allocate statement handle  
               retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);   
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						MessageBox(NULL, L"Connected!", L"", NULL);
						SQLFreeHandle(SQL_HANDLE_STMT, hstmt); // Process data  
					}
               SQLDisconnect(hdbc);  
            }  
            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);  
		}  }  
      SQLFreeHandle(SQL_HANDLE_ENV, henv);  
}  }
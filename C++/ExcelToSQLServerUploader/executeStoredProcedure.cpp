//Execute Stored Procedure with ODBC CALL and Process Output @ https://docs.microsoft.com/en-us/sql/relational-databases/native-client-ole-db-how-to/results/execute-stored-procedure-with-odbc-call-and-process-output

//#define UNICODE //Warning	C4005	'UNICODE': macro redefinition	G:\_\__\AutomateExcelFromNET\executeStoredProcedure.cpp
#define DBINITCONSTANTS  
#define INITGUID  
#define OLEDBVER 0x0250   // to include correct interfaces
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_ //Warning	C4996	'CLSID_SQLNCLI11': The SQL Server Native Client OLEDB provider is deprecated and will be removed in a future release of SQL Server Native Client. To disable this warning, define the following symbol in your application: _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_

#include <windows.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <iostream>  
#include <oledb.h>  
#include <oledberr.h>  
#include "SQLNCLI.h" //The SQL Server Native Client header and library files (sqlncli.h and sqlncli11.lib) are installed in the following location: %PROGRAMFILES%\Microsoft SQL Server\110\SDK @ https://docs.microsoft.com/en-us/sql/relational-databases/native-client/applications/installing-sql-server-native-client
#include <boost/lexical_cast.hpp> //How to convert std::wstring to numeric type(int, long, float)? @ https://stackoverflow.com/questions/5118308/how-to-convert-stdwstring-to-numeric-typeint-long-float

using namespace std;  

#include "timberDB.h"
using namespace timberDB;

IDBInitialize* pIDBInitialize = NULL;
IDBCreateSession* pIDBCreateSession = NULL;  
IDBCreateCommand* pIDBCreateCommand = NULL;  
ICommandText* pICommandText = NULL;  

IRowset* pIRowset = NULL;  
ICommandWithParameters* pICommandWithParams = NULL;  
IAccessor* pIAccessor = NULL;  
IDBProperties* pIDBProperties = NULL;  

WCHAR* pStringsBuffer;  
DBBINDING* pBindings;  
const ULONG nInitProps = 4;  
DBPROP InitProperties[nInitProps];  

const ULONG nPropSet = 1;  
DBPROPSET rgInitPropSet[nPropSet];  
HRESULT hr;  
HACCESSOR hAccessor;  

const ULONG nParams = 6;   // Number of parameters in the command  
DBPARAMBINDINFO ParamBindInfo[nParams];  
ULONG i;  
ULONG cbColOffset = 0;  

ULONG ParamOrdinals[nParams];  
DBROWCOUNT cNumRows = 0;  
DBPARAMS Params;  

// Declare an array of DBBINDING structures, one for each parameter in the command.  
DBBINDING acDBBinding[nParams];  
DBBINDSTATUS acDBBindStatus[nParams];  

// The following buffer is used to store parameter values.  
typedef struct tagSPROCPARAMS {  
   long lReturnValue;  
   long outParam;
	long lngYear;
	long lngCountry_ID; //TO DO: Distinguish between Country_ID and Country_ID_ISO.
	long lngProduct_Code; //TO DO: Distinguish between Product_Code and Product_ID.
	long lngItem_ID;
} SPROCPARAMS;  

// compile with: ole32.lib oleaut32.lib  
static void initializeAndEstablishConnection() {      
   // Initialize the COM library.  
   CoInitialize(NULL);  

   // Obtain access to the SQL Server Native Client OLE DB provider.      
   hr = CoCreateInstance( CLSID_SQLNCLI11,   
                          NULL,   
                          CLSCTX_INPROC_SERVER,  
                          IID_IDBInitialize,   
                          (void **) &pIDBInitialize);  
   if (FAILED(hr))  
      cout << "Failed in CoCreateInstance().\n";  

   // Initialize the property values needed to establish the connection.  
   for ( i = 0 ; i < nInitProps ; i++ )  
      VariantInit(&InitProperties[i].vValue);  

   // Specify server name.  
   InitProperties[0].dwPropertyID = DBPROP_INIT_DATASOURCE;  
   InitProperties[0].vValue.vt = VT_BSTR;  

   // Replace "MySqlServer" with proper value.  
   InitProperties[0].vValue.bstrVal = SysAllocString(L"(local)");  
   InitProperties[0].dwOptions = DBPROPOPTIONS_REQUIRED;  
   InitProperties[0].colid = DB_NULLID;  

   // Specify database name.  
   InitProperties[1].dwPropertyID = DBPROP_INIT_CATALOG;  
   InitProperties[1].vValue.vt = VT_BSTR;  
	InitProperties[1].vValue.bstrVal = SysAllocString(L"timber");  
   InitProperties[1].dwOptions = DBPROPOPTIONS_REQUIRED;  
   InitProperties[1].colid = DB_NULLID;  

   InitProperties[2].dwPropertyID = DBPROP_AUTH_INTEGRATED;  
   InitProperties[2].vValue.vt = VT_BSTR;  
   InitProperties[2].vValue.bstrVal = SysAllocString(L"SSPI");  
   InitProperties[2].dwOptions = DBPROPOPTIONS_REQUIRED;  
   InitProperties[2].colid = DB_NULLID;  

   // Now that properties are set, construct the DBPROPSET structure  
   // (rgInitPropSet).  The DBPROPSET structure is used to pass an array  
   // of DBPROP structures (InitProperties) to the SetProperties method.  
   rgInitPropSet[0].guidPropertySet = DBPROPSET_DBINIT;  
   rgInitPropSet[0].cProperties = 4;  
   rgInitPropSet[0].rgProperties = InitProperties;  

   // Set initialization properties.  
   hr = pIDBInitialize->QueryInterface(IID_IDBProperties, (void **)&pIDBProperties);  
   if (FAILED(hr))  
      cout << "Failed to obtain IDBProperties interface.\n";  

   hr = pIDBProperties->SetProperties(nPropSet, rgInitPropSet);  
   if (FAILED(hr))  
      cout << "Failed to set initialization properties.\n";  

   pIDBProperties->Release();

   // Now establish a connection to the data source.  
   if (FAILED(pIDBInitialize->Initialize()))  
      cout << "Problem in initializing.\n";  
}

bool executeStoredProcedure(SQLSelect* sttSQLSelect) {
   const int intDecConver = 1000; //The decimal converter. //IMPORTANT: 3 zeros. The 4th lead to an error in the US.

	// The command to execute.  
	WCHAR* wCmdString = L"{? = call uspDataAndAggretages_NoDuplicates_2000_2015_execSP(?,?,?,?,?)}";

	SPROCPARAMS sprocparams = {
		0,
		0,
		boost::lexical_cast<long>(sttSQLSelect->strYear), //How to convert std::wstring to numeric type(int, long, float)? @ https://stackoverflow.com/questions/5118308/how-to-convert-stdwstring-to-numeric-typeint-long-float
		boost::lexical_cast<long>(sttSQLSelect->strCountry_ID), 
		boost::lexical_cast<long>(sttSQLSelect->strProduct_Code), 
		boost::lexical_cast<long>(sttSQLSelect->strItem_ID) };

   // All the initialization activities in a separate function.  
   initializeAndEstablishConnection();  

   // Create a new activity from the data source object.  
   if ( FAILED(pIDBInitialize->QueryInterface( IID_IDBCreateSession,   
      (void**) &pIDBCreateSession))) {  
         cout << "Failed to access IDBCreateSession interface.\n";  
         goto EXIT;  
   }  
   if (FAILED(pIDBCreateSession->CreateSession( NULL, IID_IDBCreateCommand,   
      (IUnknown**) &pIDBCreateCommand))) {  
         cout << "pIDBCreateSession->CreateSession failed.\n";  
      goto EXIT;  
   }  

   // Create a Command object.  
   if (FAILED(pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText,   
      (IUnknown**) &pICommandText))) {  
         cout << "Failed to access ICommand interface.\n";  
         goto EXIT;  
   }  

   // Set the command text.  
   if (FAILED(pICommandText->SetCommandText(DBGUID_DBSQL, wCmdString))) {  
      cout << "Failed to set command text.\n";  
      goto EXIT;  
   }  
   // No need to describe command parameters (parameter name, data type  
   // etc) in DBPARAMBINDINFO structure and then SetParameterInfo(). The  
   // provider obtains this information by calling appropriate helper  
   // function.  

   // Describe the consumer buffer by filling in the array of DBBINDING structures.    
   // Each binding associates a single parameter to the consumer's buffer.  
   for ( i = 0 ; i < nParams ; i++ ) {  
      acDBBinding[i].obLength = 0;  
      acDBBinding[i].obStatus = 0;  
      acDBBinding[i].pTypeInfo = NULL;  
      acDBBinding[i].pObject = NULL;  
      acDBBinding[i].pBindExt = NULL;  
      acDBBinding[i].dwPart = DBPART_VALUE;  
      acDBBinding[i].dwMemOwner = DBMEMOWNER_CLIENTOWNED;  
      acDBBinding[i].dwFlags = 0;  
      acDBBinding[i].bScale = 0;  
   }   // end for  

   acDBBinding[0].iOrdinal = 1; //TO DO: Use constants!!!  
   acDBBinding[0].obValue = offsetof(SPROCPARAMS, lReturnValue);  
   acDBBinding[0].eParamIO = DBPARAMIO_OUTPUT;  
   acDBBinding[0].cbMaxLen = sizeof(long);  
   acDBBinding[0].wType = DBTYPE_I4;  
   acDBBinding[0].bPrecision = 11;  

   acDBBinding[1].iOrdinal = 2;  
	acDBBinding[1].obValue = offsetof(SPROCPARAMS, lngYear);
   acDBBinding[1].eParamIO = DBPARAMIO_INPUT;  
   acDBBinding[1].cbMaxLen = sizeof(long);  
   acDBBinding[1].wType = DBTYPE_I4;  
   acDBBinding[1].bPrecision = 11;  

	acDBBinding[2].iOrdinal = 3;
	acDBBinding[2].obValue = offsetof(SPROCPARAMS, lngCountry_ID);
   acDBBinding[2].eParamIO = DBPARAMIO_INPUT;  
   acDBBinding[2].cbMaxLen = sizeof(long);  
   acDBBinding[2].wType = DBTYPE_I4;  
   acDBBinding[2].bPrecision = 11;

	acDBBinding[3].iOrdinal = 4;
	acDBBinding[3].obValue = offsetof(SPROCPARAMS, lngProduct_Code);
   acDBBinding[3].eParamIO = DBPARAMIO_INPUT;  
   acDBBinding[3].cbMaxLen = sizeof(/*long*/wchar_t);
   acDBBinding[3].wType = DBTYPE_I4;  
   acDBBinding[3].bPrecision = 11;

	acDBBinding[4].iOrdinal = 5;
	acDBBinding[4].obValue = offsetof(SPROCPARAMS, lngItem_ID);
   acDBBinding[4].eParamIO = DBPARAMIO_INPUT;  
   acDBBinding[4].cbMaxLen = sizeof(/*long*/wchar_t);
   acDBBinding[4].wType = DBTYPE_I4;  
   acDBBinding[4].bPrecision = 11;

	acDBBinding[5].iOrdinal = 6;
	acDBBinding[5].obValue = offsetof(SPROCPARAMS, outParam);
	acDBBinding[5].eParamIO = DBPARAMIO_OUTPUT;
	acDBBinding[5].cbMaxLen = sizeof(long);
	acDBBinding[5].wType = DBTYPE_I4;
	acDBBinding[5].bPrecision = 11;

	// Create an accessor from the above set of bindings.  
   hr = pICommandText->QueryInterface( IID_IAccessor, (void**)&pIAccessor);  
   if (FAILED(hr))  
      cout << "Failed to get IAccessor interface.\n";  

   hr = pIAccessor->CreateAccessor( DBACCESSOR_PARAMETERDATA,   
                                    nParams,         
                                    acDBBinding,   
                                    sizeof(SPROCPARAMS),   
                                    &hAccessor,  
                                    acDBBindStatus);  
   if (FAILED(hr))  
      cout << "Failed to create accessor for the defined parameters.\n";  

   // Fill in DBPARAMS structure for the command execution. This structure   
   // specifies the parameter values in the command and is then passed to Execute.  
   Params.pData = &sprocparams;  
   Params.cParamSets = 1;  
   Params.hAccessor = hAccessor;  

   // Execute the command.  
   if ( FAILED(hr = pICommandText->Execute( NULL,   
                                            IID_IRowset,   
                                            &Params,   
                                            &cNumRows,   
                                            (IUnknown **) &pIRowset))) {  
      cout << "Failed to execute command.\n";  
      goto EXIT;  
   }  

   // Result set is not important in this example; release it without processing.  
   //ORIG: TURNED OFF FOR NON-ROWSET QUERIES: pIRowset->Release();  

	sttSQLSelect->dblValue = static_cast<double>(sprocparams.outParam) / intDecConver;
	sttSQLSelect->intStatus_ID = sprocparams.lReturnValue;

   // Release memory.  
   pIAccessor->ReleaseAccessor(hAccessor, NULL);  
   pIAccessor->Release();  
   pICommandText->Release();  
   pIDBCreateCommand->Release();  
   pIDBCreateSession->Release();      
   if (FAILED(pIDBInitialize->Uninitialize()))  
      // Uninitialize is not required, but it fails if an interface  
      // has not been released.  This can be used for debugging.  
      cout << "Problem uninitializing.\n";  

   pIDBInitialize->Release();  

   CoUninitialize();  
	return true;

EXIT:  
   if (pIAccessor != NULL)  
      pIAccessor->Release();  
   if (pICommandText != NULL)  
      pICommandText->Release();  
   if (pIDBCreateCommand != NULL)  
      pIDBCreateCommand->Release();  
   if (pIDBCreateSession != NULL)  
      pIDBCreateSession->Release();  
   if (pIDBInitialize != NULL)  
      if (FAILED(pIDBInitialize->Uninitialize()))  
         // Uninitialize is not required, but it fails if an  
         // interface has not been released.  This can be used for debugging.  
         cout << "Problem in uninitializing.\n";  
      pIDBInitialize->Release();  

   CoUninitialize();
	return false; //TO DO: Make sure false is returned in all failures.
};  

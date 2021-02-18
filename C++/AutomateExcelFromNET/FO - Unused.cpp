#include "FO.h"

////FO::FO(String strPath) {
//	//cobjExcelApp = gcnew Excel::ApplicationClass(); //1. Create the Excel application //How to use Managed C++ to Automate Excel @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-Excel
//FO::FO(wchar_t * chrPath) {
//	cobjExcelApp = gcnew Excel::ApplicationClass(); //1. Create the Excel application //How to use Managed C++ to Automate Excel @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-Excel
//	cobjWorkbook = cobjExcelApp->Workbooks->Open(gcnew String(chrPath), Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing); //C++/CLI How to open Excel file using relative path? @ http://stackoverflow.com/questions/31915610/c-cli-how-to-open-excel-file-using-relative-path
//}
//
//void FO::setActiveSheet(char* chrWorksheetName) {
//	//safe_cast<Worksheet^>(cobjExcelApp->ActiveWorkbook->Sheets->Item["Albania"])->Select(Type::Missing);
//	//safe_cast<Worksheet^>(cobjExcelApp->ActiveWorkbook->Sheets->Item[chrWorksheetName])->Select(Type::Missing);
//	//cobjActiveSheet = safe_cast<Worksheet^>(cobjExcelApp->ActiveSheet); //Use Visual Studio 2008 C++/CLI to Automate Excel @ https://www.codeproject.com/Articles/28083/Use-Visual-Studio-C-CLI-to-Automate-Excel
//	/////////cobjActiveSheet = safe_cast<Worksheet^>(cobjExcelApp->ActiveWorkbook->Sheets->Item[chrWorksheetName]);
//}

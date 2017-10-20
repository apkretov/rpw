#pragma once
namespace AutomateExcelFromNET {
	//using namespace Microsoft::Office::Interop::Excel;
	//#define Excel Microsoft::Office::Interop::Excel

	public ref class FO {
		Excel::Application^ cobjExcelApp = nullptr;
		Workbook^ cobjWorkbook = nullptr;
		Worksheet^ cobjActiveSheet = nullptr;
		Range^ cobjRange = nullptr;
	public:
		//FO(wchar_t* chrPath);
		//void setActiveSheet(char* chrWorksheetName);
	};
}
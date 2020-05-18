/*Based on:
1) How to use Managed C++ to Automate EXCEL @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-EXCEL
2) Use Visual Studio 2008 C++/CLI to Automate EXCEL @ https://www.codeproject.com/Articles/28083/Use-Visual-Studio-C-CLI-to-Automate-EXCEL
3) Reading cells in EXCEL with Visual C++ @ https://social.msdn.microsoft.com/Forums/office/en-US/5547ed18-6b32-4151-96d8-a6963acfe1a3/reading-cells-in-excel-with-visual-c?forum=exceldev
*/
#include "main.h"
#include <vcclr.h>
#using <Microsoft.VisualBasic.dll> //The Visual Basic Library @ http://www.functionx.com/vccli/topics/libraries.htm
#define VB Microsoft::VisualBasic
#include <boost\algorithm\string.hpp>
using namespace System::Threading;

void AutomateExcelFromNET::main::addGrdSingleCol(vector<string> vecItems, DataGridView_t^ grd) {
	uint32_t intRow{};
	for (auto& strItem : vecItems) {
		grd->Rows->Add(); 
		grd->Rows[intRow++]->Cells[0]->Value = gcnew String(strItem.c_str());
}	}

void AutomateExcelFromNET::main::addGrdTables(bool blnActive, String^ strDesctription, String^ strRange, uint32_t intYearsOrder, uint32_t intYearsAlign, uint32_t intTopics, uint32_t intGroups, uint32_t intSubgroups, uint32_t intRowDim1) {
	static uint32_t intRow{};
	grdTables->Rows->Add(); 
	grdTables->Rows[intRow]->Cells[colActive->Name]->Value = blnActive;
	grdTables->Rows[intRow]->Cells[colDescription->Name]->Value = strDesctription;
	grdTables->Rows[intRow]->Cells[colRange->Name]->Value = strRange;
	grdTables->Rows[intRow]->Cells[colYearsOrder->Name]->Value = colYearsOrder->Items[intYearsOrder]->ToString();
	grdTables->Rows[intRow]->Cells[colYearsAlign->Name]->Value = colYearsAlign->Items[intYearsAlign]->ToString();
	grdTables->Rows[intRow]->Cells[colTopics->Name]->Value = intTopics;
	grdTables->Rows[intRow]->Cells[colGroups->Name]->Value = intGroups;
	grdTables->Rows[intRow]->Cells[colSubgroups->Name]->Value = intSubgroups;
	grdTables->Rows[intRow]->Cells[colRowDim1->Name]->Value = intRowDim1;
	intRow++; //Post-increment for a future call.
}

AutomateExcelFromNET::main::main(void)	{ 
	InitializeComponent(); 
	
	addGrdSingleCol(vector<string>{"1990", "2010", "2015"}, grdYears);
	addGrdSingleCol(vector<string>{
		"N/A", 
		"-", 
		"Main management level:", 
		"Major Ministry managing Public Forests",
		"Of which managed by state forest management organisation",
		"Other Ministry managing Public Forests",
		"G",
		"**",
		"n.a",
		"n.a.",
		"Na",
		"n,a",
		"Area: n.a.",
		//OFF "Number:85", "Number:3263", //Slovakia, Table 2.
		"n. a.",
		"na",
		"na,",
		"na.",
		"n/a",
		"NA",
		"n. a"
	}, grdNonNum);

	addGrdTables(true, "Table 1a", "E63:J76", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 14, 2, 0, 2);
	addGrdTables(true, "Table 1b", "E81:M94", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 14, 3, 0, 30);
	addGrdTables(true, "Table 2", "R65:AA79", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 5, 5, 2, 72);
	addGrdTables(true, "Table 3", "AE64:AM68", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 5, 3, 0, 122);
	addGrdTables(true, "Table 4a", "AR64:AT78", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 5, 3, 0, 137);
	addGrdTables(true, "Table 6", "BD63:BK65", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 3, 4, 2, 152);
	addGrdTables(true, "Table 7", "BN65:BY69", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 5, 6, 2, 176);
	addGrdTables(true, "Table 8", "CB63:CE65", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 3, 4, 0, 236);
	addGrdTables(false, "Table 9", "CI63:CM63", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 1, 5, 0, 248); //The latest year is 2010.
	addGrdTables(true, "Table 10", "CR62:CS73", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 4, 2, 0, 253);
	addGrdTables(true, "Table 11a", "CX63:CY67", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 5, 2, 0, 261);
	addGrdTables(true, "Table 11b", "CX71:CY74", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 4, 2, 0, 271);
	addGrdTables(true, "Table 11c", "CX78:CY84", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 7, 2, 0, 279);

	cmdRunExcel->Select();
}

AutomateExcelFromNET::main::~main() {
	quitExcel();
	if (components) delete components;
}

void AutomateExcelFromNET::main::enableControls(bool blnEnable) {
	cmdRunExcel->Enabled = blnEnable; 
	cmdInsertData->Enabled = blnEnable;
	cbxSheetCountry->Enabled = blnEnable;
	cbxSheetDim->Enabled = blnEnable;
}

void AutomateExcelFromNET::main::cmdRunExcel_Click_Thread() {
	enableControls(false);
	Monitor::Enter(lstCountrySheets); //Lock lstCountrySheets while it's being filled in.
	if (cxlsApp != nullptr) quitExcel(); //Quit a prior EXCEL, if any.
	cxlsApp = gcnew EXCEL::ApplicationClass(); //1. Create the EXCEL application //How to use Managed C++ to Automate EXCEL @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-EXCEL
	cwbkFO = cxlsApp->Workbooks->Open(cstrFileName, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing); //C++/CLI How to open EXCEL file using relative path? @ http://stackoverflow.com/questions/31915610/c-cli-how-to-open-excel-file-using-relative-path 
	if (cwbkFO != nullptr) { //Did the file open?
		for each (auto sht in cxlsApp->ActiveWorkbook->Worksheets) { //Fiil in the sheet names.
			lstCountrySheets->Items->Add((safe_cast<Worksheet^>(sht))->Name); //Fiil in the sheet names.
			cbxSheetCountry->Items->Add((safe_cast<Worksheet^>(sht))->Name);
			cbxSheetDim->Items->Add((safe_cast<Worksheet^>(sht))->Name);
		}
	cbxSheetCountry->SelectedItem = "Countries"; //Default pre-filling. Using a constant (const String^ strCountries = "Countries";) isn't straitforward.
	cbxSheetDim->SelectedItem = "Dimensions";
	}
	cxlsApp->Visible = true;
	Monitor::Exit(lstCountrySheets); //Unlock lstCountrySheets filled in.
	enableControls(true);
}

System::Void AutomateExcelFromNET::main::cmdRunExcel_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		OpenFileDialog^ dlgOpenFile = gcnew OpenFileDialog(); // Displays an OpenFileDialog so the user can select a Cursor. //To open a file as a file using the OpenFileDialog component @ https://msdn.microsoft.com/en-us/library/61097ykx(v=vs.110).aspx
		dlgOpenFile->Filter = "Excel Files|*.xlsx";
		dlgOpenFile->Title = "Select an Excel File";
		if (dlgOpenFile->ShowDialog() != System::Windows::Forms::DialogResult::OK) cstrFileName = ""; //Clear the file name.
		else { // Show the Dialog. // If the user clicked OK in the dialog and  a .CUR file was selected, open it.  
			cstrFileName = dlgOpenFile->FileName;
			Thread^ objTread = gcnew Thread(gcnew ThreadStart(this, &main::cmdRunExcel_Click_Thread));
			objTread->Start();
	}	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

wstring AutomateExcelFromNET::main::cliStringToWstring(String ^ strCli) { //LESSON #5: MOVE SEMANTICS //Returning large objects from functions @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
	pin_ptr<const wchar_t> chr = PtrToStringChars(strCli->ToString());
	return wstring(chr);
}

const wchar_t * AutomateExcelFromNET::main::cliStringToWchar(String ^ strCli) {
	pin_ptr<const wchar_t> chr = PtrToStringChars(strCli->ToString());
	return chr;
}

void AutomateExcelFromNET::main::fillTimberDB(timberDB::timberDB& sttTimberDB) {
	sttTimberDB.server = cliStringToWchar(txtServer->Text);
	sttTimberDB.DSN = cliStringToWchar(txtDSN->Text);
	sttTimberDB.UID = cliStringToWchar(txtUID->Text);
	sttTimberDB.PWD = cliStringToWchar(txtPWD->Text);
	sttTimberDB.database = cliStringToWchar(txtDatabase->Text);
	sttTimberDB.table = cliStringToWchar(txtTable->Text);
}

System::Void AutomateExcelFromNET::main::cmdInsertData_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		if (MessageBox::Show("Start uploading data?", "Question", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes) {
			vector<double> vecYearsAsc;
			for (int i = 0; i < grdYears->Rows->Count - 1; i++) vecYearsAsc.push_back(Convert::ToDouble(grdYears->Rows[i]->Cells[colYears->Name]->Value)); //Fill the ascending set of years.
			vector<double> vecYearsDesc(vecYearsAsc.crbegin(), vecYearsAsc.crend()); //Descending vector of the same years.
			vector<double> vecYearsLatest(vecYearsDesc.begin(), ++vecYearsDesc.begin()); //The only and the latest year (i.e. the greatest).
			mapYears_t mapYears; //Map the Years Order combobox items to the respective years.
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Ascending)]->ToString()), vecYearsAsc));
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Descending)]->ToString()), vecYearsDesc));
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Latest)]->ToString()), vecYearsLatest));
			
			vector<vector<wstring>> vecCountryDim;
			vector<vector<double>> vecYearValue;
			uint32_t intCountriesUploaded{};
			for each (auto objCountrySheet in lstCountrySheets->CheckedItems) { //Read each country in the Excel file.
				if (!uploadCountry(safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets->Item[objCountrySheet->ToString()]), mapYears, vecCountryDim, vecYearValue)) 
					return System::Void();
				intCountriesUploaded++;
			}
			timberDB::timberDB sttTimberDB;
			fillTimberDB(sttTimberDB);
			if (intCountriesUploaded > 0 && timberDB::insertIntoData(sttTimberDB, &vecCountryDim, &vecYearValue)) MessageBox::Show("Data have been uploaded successfully.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

System::Void AutomateExcelFromNET::main::cmdDeleteData_Click(System::Object^ sender, System::EventArgs^ e) {
	try {	
		if (MessageBox::Show("Delete data?", "Question", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes) {
			timberDB::timberDB sttTimberDB;
			fillTimberDB(sttTimberDB);
			if (timberDB::deleteData(sttTimberDB)) MessageBox::Show("Data have been deleted successfully.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

void AutomateExcelFromNET::main::quitExcel() {
	if (cxlsApp != nullptr) {
		cxlsApp->Quit(); //Quit EXCEL.
		cxlsApp = nullptr;
		lstCountrySheets->Items->Clear();
		cbxSheetCountry->Items->Clear();
		cbxSheetDim->Items->Clear();
}	}

bool AutomateExcelFromNET::main::validateNonNum(Range_t^ rngValue) {
	try {	
		string strValue2Trimmed = boost::trim_copy( cliStringToString(rngValue->/*KTB Value2*/Text->ToString()) );
		String^ strValue2 = gcnew String(strValue2Trimmed.c_str());
		for (int i = 0; i < grdNonNum->Rows->Count - 1; i++) { //The last row is empty. Skip it.
			if (strValue2 == grdNonNum->Rows[i]->Cells[colNonNum->Name]->Value->ToString() ) return true; //Such a non-numeric value is valid because is available among grdNonNum.
		}	
		String^ strAddress = rngValue->Address[Type::Missing, Type::Missing, EXCEL::XlReferenceStyle::xlA1, Type::Missing, Type::Missing]; //Range.Address Property (Excel) @ https://msdn.microsoft.com/en-us/library/office/ff837625.aspx
		Worksheet_t^ shtParent = safe_cast<Worksheet_t^>(rngValue->Parent);
		MessageBox::Show("A non-numeric value \"" + strValue2 + "\" found in cell \"" + strAddress + "\" of sheet \"" + shtParent->Name + "\"!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning); //Alert on a invalid non-numeric value.
		shtParent->Select(Type::Missing);
		rngValue->Select();
	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return false;
}

bool AutomateExcelFromNET::main::uploadTable(const vector<double>& vecYears, const wstring& strCountryCode, Range_t^ rngTable, DataGridViewCellCollection_t^ objTableRowCells, vector<vector<wstring>>& vecCountryDim, vector<vector<double>>& vecYearValue) { // Upload a table with years located horizontally. intRowDim1 is row in the Dimensions sheet with the 1st dimension of the table. intTopics is number of rows with values in the table. intGroups is number of groups in the table. rngTable are the table cells with the values
	Worksheet_t^ shtDimensions = safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets->Item[cbxSheetDim->SelectedItem]); //Dimensions.
	Range_t^ rngCellsDim = shtDimensions->Cells;
	uint32_t intColDim = Convert::ToUInt32(txtColDim->Text); //C Programming/stdint.h @ https://en.wikibooks.org/wiki/C_Programming/stdint.h
	uint32_t intRowDim = Convert::ToUInt32(objTableRowCells[colRowDim1->Name]->Value);
	uint32_t intSubgroups = Convert::ToUInt32(objTableRowCells[colSubgroups->Name]->Value);
	uint32_t intYearsAlign{};
	for each (auto objItem in colYearsAlign->Items)	{ //Get the selected colYearsAlign index.
		if (objItem->ToString() == objTableRowCells[colYearsAlign->Name]->Value) break;
		intYearsAlign++;
	}
	if (intSubgroups == 0) intSubgroups++; //If a user enters 0 subgroups then increment them because there is in fact 1 hidden default subrgroup.
	for (uint32_t i = 1; i <= Convert::ToUInt32(objTableRowCells[colGroups->Name]->Value); i++) { //Groups.
		for (uint32_t j = 1; j <= intSubgroups; j++) { //Subgroups.
			for (uint32_t k = 1; k <= Convert::ToUInt32(objTableRowCells[colTopics->Name]->Value); k++) { //Topics.
				for (auto ptrYear = vecYears.begin(); ptrYear < vecYears.end(); ptrYear++) { //Years.
					Range_t^ rngValue{};
					if (intYearsAlign == uint32_t(itemsColYearsAlign::Horizontally)) rngValue = (Range_t^)rngTable->Item[k, (ptrYear - vecYears.begin() + 1) + vecYears.size() * (i - 1)]; //Only vertically aligned year tables contain subgroups and their year order is descending.
					else rngValue = (Range_t^)rngTable->Item[(ptrYear - vecYears.begin() + 1) + vecYears.size() * (k - 1), (i - 1) * intSubgroups + j]; //Only vertically aligned year tables contain subgroups and their year order is descending.
					if (rngValue->Value2 != nullptr) { //Is the cell filled in? //What is the difference between .text, .value, and .value2? @ https://stackoverflow.com/questions/17359835/what-is-the-difference-between-text-value-and-value2
						if (!VB::Information::IsNumeric(rngValue->/*KTB Value2*/Text)) { //Is not the cell value a number? Unlike a faster Value2, Text is used to make a full validtion for even accidential wrong date formatting (e.g. see 16.Sep in Netherlands, Table 4a). //The Visual Basic Library @ http://www.functionx.com/vccli/topics/libraries.htm //Alternatives: C# Equivalent of VB's IsNumeric() @ https://www.codeproject.com/articles/16329/c-equivalent-of-vb-s-isnumeric
							if (!validateNonNum(rngValue)) return false; //Is not this non-numeric value valid?
						}else{ 
							vector<wstring> vecCountryDimRow;
							vecCountryDimRow.push_back(strCountryCode); //Accessing via pointers vs. [][] indexes.
							vecCountryDimRow.push_back( cliStringToWstring( ((Range_t^)rngCellsDim->Item[intRowDim, intColDim])->Value2->ToString() ) );
							vecCountryDim.push_back(move(vecCountryDimRow)); //LESSON #5: MOVE SEMANTICS //Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
							vecYearValue.push_back( vector<double> {*ptrYear, Convert::ToDouble(rngValue->Value2)} );
				}	}	}
				intRowDim++; //Insert values for the next dimension.
	}	}	}
	return true;
}

wstring AutomateExcelFromNET::main::getCountryCode(String^ strCountryName) {
	if (cbxSheetCountry->SelectedItem != nullptr) { //Continue, if a Countries sheet is selected.
		Worksheet_t^ shtCounties = safe_cast<Worksheet_t^>( cxlsApp->ActiveWorkbook->Sheets->Item[cbxSheetCountry->SelectedItem] ); //Countries.
		const int intColCode = 1, intColCountry = 2; //The columns with country codes and names.
		int intRow = 0;
		Range_t^ rngCellsCountries = shtCounties->Cells;
		String^ strCountryValue2 = String::Empty;
		do	{ //Iterate while there are countries.
			intRow++;
			Range_t^ rngCountry = ((Range_t^)rngCellsCountries->Item[intRow, intColCountry]);
			if (rngCountry->Value2 == nullptr) strCountryValue2 = String::Empty;
			else {
				strCountryValue2 = rngCountry->Value2->ToString();
				if (strCountryValue2 == strCountryName) { //Get the code of the country found.
					pin_ptr<const wchar_t> chrCountryCode = PtrToStringChars( ((Range_t^)rngCellsCountries->Item[intRow, intColCode])->Value2->ToString() ); //String conversion from System::String ^ to const wchar_t * @ http://stackoverflow.com/
					return wstring(chrCountryCode); //Sussess.
				}	}
		} while (!String::IsNullOrEmpty(strCountryValue2));
	}
	return wstring();
}

bool AutomateExcelFromNET::main::uploadCountry(Worksheet_t^ shtCountry, const mapYears_t& mapYears, vector<vector<wstring>>& strCountryDim, vector<vector<double>>& dblYearValue) { // Upload a group with years placed in columns
	uint32_t intTablesUploaded{};
	wstring strCountryCode{getCountryCode(shtCountry->Name)};
	if (strCountryCode.empty()) MessageBox::Show("No country code for the \"" + shtCountry->Name + "\" sheet is found in the \"" + cbxSheetCountry->SelectedItem + "\" sheet.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	else { //Continue, if the country's code is available.
		if (grdTables->Rows->Count == 0) MessageBox::Show("No table parameters enetered!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		else { //Continue, if there are table parameters.
			for (int i = 0; i < grdTables->Rows->Count - 1; i++) { //The last row is empty. Skip it.
				auto objTableRowCells = grdTables->Rows[i]->Cells; //C# Tutorial - How To Know If DataGridView CheckBoxCell Is Checked In C# [ With Source Code ] @ https://www.youtube.com/watch?v=AkLrQt6rs0o&index=17&list=PLFDH5bKmoNqyDKntkVv-NURTAlPIhMPqA
				if (bool(objTableRowCells[colActive->Name]->Value)) { //Read active rows only.
					if ( !uploadTable(mapYears.at(cliStringToString(objTableRowCells[colYearsOrder->Name]->Value->ToString())), strCountryCode, shtCountry->Range[objTableRowCells[colRange->Name]->Value, Type::Missing], objTableRowCells, strCountryDim, dblYearValue) ) 
						return false; //Suspend uploading on an error. //How to get Cell value of DataGridView by column name? @ https://stackoverflow.com/questions/13436553/how-to-get-cell-value-of-datagridview-by-column-name
					intTablesUploaded++;
			}	}	
			if (intTablesUploaded == 0) MessageBox::Show("No active tables selected!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}	}
	return intTablesUploaded > 0;
}

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
using std::to_wstring;

void AutomateExcelFromNET::main::addGrdSingleCol(vector<string> vecItems, DataGridView_t^ grd) {
	uint32_t intRow{};
	for (auto& strItem : vecItems) {
		grd->Rows->Add(); 
		grd->Rows[intRow++]->Cells[0]->Value = gcnew String(strItem.c_str());
	}	
}

void AutomateExcelFromNET::main::addGrdTables(bool blnActive, String^ strDesctription, bool blnText, String^ strRange, uint32_t intYearsOrder, uint32_t intYearsAlign, uint32_t intTopics, uint32_t intGroups, uint32_t intSubgroups, uint32_t intRowDim1) {
	static uint32_t intRow{};
	grdTables->Rows->Add(); 
	grdTables->Rows[intRow]->Cells[colActive->Name]->Value = blnActive;
	grdTables->Rows[intRow]->Cells[colDescription->Name]->Value = strDesctription;
	grdTables->Rows[intRow] ->Cells[colText->Name]->Value = blnText;
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
	
	/* The Forest Ownership settings. //TO DO: Arrange a GUI switch.
	addGrdSingleCol(vector<string>{"1990", "2010", "2015"}, grdYears);
	*/
	addGrdSingleCol(vector<string>{"1990", "2000", "2005", "2010", "2015", "2020"}, grdYears); //Ordinary years.
/*OFF
	addGrdSingleCol(vector<string>{ 
		"1988", "1989", "1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", //3.2 Years.
		"1998", "1999", "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", 
		"2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017" 
	}, grdYears);	
*/
//OFF	 addGrdSingleCol(vector<string>{"2007", "2009", "2011", "2013", "2015"}, grdYears); //6.9 Years.

	/* The Forest Ownership settings. //TO DO: Arrange a GUI switch.
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
	*/
	addGrdSingleCol(vector<string>{
		"n/a",
		"d.i.",
		"na",
		"nn",
		"…",
		"n.a.",
		"i.d."
	}, grdNonNum);

	/* The Forest Ownership settings. //TO DO: Arrange a GUI switch.
	addGrdTables(true, "Table 1a", false, "E63:J76", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 14, 2, 0, 2);
	addGrdTables(true, "Table 1b", false, "E81:M94", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 14, 3, 0, 30);
	addGrdTables(true, "Table 2", false, "R65:AA79", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 5, 5, 2, 72);
	addGrdTables(true, "Table 3", false, "AE64:AM68", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 5, 3, 0, 122);
	addGrdTables(true, "Table 4a", false, "AR64:AT78", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 5, 3, 0, 137);
	addGrdTables(true, "Table 6", false, "BD63:BK65", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 3, 4, 2, 152);
	addGrdTables(true, "Table 7", false, "BN65:BY69", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 5, 6, 2, 176);
	addGrdTables(true, "Table 8", false, "CB63:CE65", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 3, 4, 0, 236);
	addGrdTables(false, "Table 9", false, "CI63:CM63", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 1, 5, 0, 248); //The latest year is 2010.
	addGrdTables(true, "Table 10", false, "CR62:CS73", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 4, 2, 0, 253);
	addGrdTables(true, "Table 11a", false, "CX63:CY67", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 5, 2, 0, 261);
	addGrdTables(true, "Table 11b", false, "CX71:CY74", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 4, 2, 0, 271);
	addGrdTables(true, "Table 11c", false, "CX78:CY84", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 7, 2, 0, 279);
	*/

	//Years 1990 - 2020.
	addGrdTables(false, "1.1a", false, "C10:C45", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 6, 1, 0, 2);
	addGrdTables(false, "1.1b", false, "B51:G53", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 3, 1, 0, 8);
	addGrdTables(false, "1.2a", false, "K12:M35", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 4, 3, 0, 11);
	addGrdTables(false, "1.2b", false, "J41:O43", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 3, 1, 0, 23);
	addGrdTables(false, "1.2cFRA2", false, "L49:Q60", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 12, 1, 0, 479);
	addGrdTables(false, "1.4a", false, "AM12:AQ29", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 5, 0, 85);
	//++ Kirusha's
	addGrdTables(false, "4.3a", false, "DS11:DU28", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 3, 0, 152);
	addGrdTables(false, "4.3b", false, "DS36:DY41", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 7, 0, 547);
	//-- Kirusha's
	
	addGrdTables(false, "4.4aD1", false, "EC11:EC16", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 161); //4.4a is splitted into 2 dimension-set subtables for uploading. Topic 1 is reported up to 2020.
	addGrdTables(false, "4.4aD4", false, "ED11:ED16", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 164);
	
	//++ Kirusha's
	addGrdTables(false, "4.9", false, "FA12:FD29", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 4, 0, 217);
	addGrdTables(false, "5.1", false, "FI12:FK29", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 3, 0, 229);
	//-- Kirusha's
	
	//Years 1990 - 2015.
	addGrdTables(false, "1.3a1", false, "U11:Y35", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 5, 5, 0, 26);
	addGrdTables(false, "1.3a2", false, "U41:Y60", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 4, 5, 0, 51);
	addGrdTables(false, "1.3b", false, "AC12:AI21", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 2, 7, 0, 71);
	addGrdTables(false, "1.4b", false, "AM35:AM39", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, /*KIRUSHA'S ERROR: 537*/491);
	addGrdTables(false, "2.4", false, "AV13:BD27", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 9, 0, 100);
	addGrdTables(false, "2.5", false, "BH13:BQ27", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 10, 0, 492);
	//++ Kirusha's
	addGrdTables(false, "3.1", false, "BU12:BY21", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 2, 5, 0, 522);
	addGrdTables(false, "4.1", false, "DC11:DF25", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 4, 0, 132);
	addGrdTables(false, "4.2a", false, "DK12:DM16", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 3, 0, 144);
	addGrdTables(false, "4.2b", false, "DK23:DO27", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 5, 0, 147);
	//-- Kirusha's

	addGrdTables(false, "4.4aD2-3", false, "EC17:EC26", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 2, 1, 0, 162); //4.4a is splitted into 2 dimension-set subtables for uploading. Topics 2-3 are reported up to 2015.
	addGrdTables(false, "4.4aD5-6", false, "ED17:ED26", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 2, 1, 0, 165);

	//++ Kirusha's
	addGrdTables(false, "4.5a", false, "EK11:EM25", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 3, 0, 167);
	addGrdTables(false, "4.8", false, "ES12:EW46", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 7, 5, 0, 182);
	addGrdTables(false, "6.1", false, "FQ12:FX26", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 8, 0, 238);
	addGrdTables(false, "6.2", false, "GB11:GC25", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 2, 0, 262);
	addGrdTables(false, "6.3", false, "GI11:GJ15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 2, 0, 268);
	addGrdTables(false, "6.4a", false, "GO11:GR15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 4, 0, 554);
	addGrdTables(false, "6.4b", false, "GO21:GO25", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 558);
	addGrdTables(false, "6.4c", false, "GO31:GO35", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 559);
	addGrdTables(false, "6.5a", false, "GV12:GZ26", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 5, 0, 270);
	addGrdTables(false, "6.5b", false, "GV33:GZ47", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 3, 5, 0, 285);
	
	addGrdTables(false, "6.6D1", false, "HD11:HD15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 300); //6.6 is splitted into 4 single-dimension subtables for uploading.
	addGrdTables(false, "6.6D2", false, "HE11:HE15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 301);
	addGrdTables(false, "6.6D3", false, "HF11:HF15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 302);
	addGrdTables(false, "6.6D4", false, "HG11:HG15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 303);
	
	addGrdTables(false, "6.10aD1", false, "HX11:HX15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 367); //6.10a is splitted into 4 single-dimension subtables for uploading.
	addGrdTables(false, "6.10aD2", false, "HY11:HY15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 368);
	addGrdTables(false, "6.10aD3", false, "HZ11:HZ15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 369);
	addGrdTables(false, "6.10aD4", false, "IA11:IA15", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 370);
	//-- Kirusha's

	//Years 2005 - 2015.
	//++ Kirusha's
	addGrdTables(false, "4.4bFRA2", false, "EB32:ED38", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 7, 1, 0, 592);
	addGrdTables(false, "4.4cFRA2", false, "EB44:ED50", uint32_t(itemsColYearsOrder::Ascending), uint32_t(itemsColYearsAlign::Horizontally), 7, 1, 0, 956);
	//-- Kirusha's
	addGrdTables(false, "6.10bD1", false, "HX21:HX23", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 532);
	addGrdTables(false, "6.10bD2", false, "HY21:HY23", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 1, 0, 533); //Here and above: 6.10a is splitted into 4 single-dimension subtables for uploading.
	
	//Years 1988 - 2017.
	//++ Kirusha's
	addGrdTables(false, "3.2", false, "CC12:CG41", uint32_t(itemsColYearsOrder::Descending), uint32_t(itemsColYearsAlign::Vertically), 1, 5, 0, 127);
	//-- Kirusha's
	
	//Single year.
	//++ Kirusha's
	addGrdTables(false, "1.2cFRA1", true, "J49:K58", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 2, 0, 459);
	addGrdTables(false, "2.5Oth", true, "BM10:BO10", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 1, 3, 0, 953);
	addGrdTables(false, "3.3FRA1", true, "CK11:CM20", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 3, 0, 639);
	addGrdTables(false, "3.3FRA2", false, "CN11:CP23", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 13, 3, 0, 878);
	addGrdTables(false, "3.4FRA1", true, "CS11:CT20", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 2, 0, 702);
	addGrdTables(false, "3.4FRA2", false, "CU11:CW22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 12, 3, 0, 917);
	addGrdTables(false, "4.4bFRA1", true, "EA32:EA38", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 7, 1, 0, 572);
	addGrdTables(false, "4.4cFRA1", true, "EA44:EA50", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 7, 1, 0, 612);
	addGrdTables(false, "4.5b", false, "EK27:EM28", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 3, 0, 176);
	addGrdTables(false, "6.9Y1G1T1", false, "HK11:HK19", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 9, 1, 0, 304); //Year 2007, Group 1, Topic set 1. //6.9 is splitted into 5 single-year subtables for uploading. Then the subtables are splitted into single-group sub-subtables. Finally there are two tipic sets.
	addGrdTables(false, "6.9Y1G1T2", false, "HK21:HK22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 1, 0, 313); //Topic set 2.
	addGrdTables(false, "6.9Y1G2", false, "HL13:HL22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 1, 0, 315); //Group 2.

	addGrdTables(false, "6.9Y2G1T1", false, "HM11:HM19", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 9, 1, 0, 304); //Year 2009, Group 1, Topic set 1.
	addGrdTables(false, "6.9Y2G1T2", false, "HM21:HM22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 1, 0, 313); //Topic set 2.
	addGrdTables(false, "6.9Y2G2", false, "HN13:HN22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 1, 0, 315); //Group 2.

	addGrdTables(false, "6.9Y3G1T1", false, "HO11:HO19", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 9, 1, 0, 304); //Year 2011, Group 1, Topic set 1.
	addGrdTables(false, "6.9Y3G1T2", false, "HO21:HO22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 1, 0, 313); //Topic set 2.
	addGrdTables(false, "6.9Y3G2", false, "HP13:HP22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 1, 0, 315); //Group 2.

	addGrdTables(false, "6.9Y4G1T1", false, "HQ11:HQ19", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 9, 1, 0, 304); //Year 2013, Group 1, Topic set 1.
	addGrdTables(false, "6.9Y4G1T2", false, "HQ21:HQ22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 1, 0, 313); //Topic set 2.
	addGrdTables(false, "6.9Y4G2", false, "HR13:HR22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 1, 0, 315); //Group 2.

	addGrdTables(false, "6.9Y5G1T1", false, "HS11:HS19", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 9, 1, 0, 304); //Year 2015, Group 1, Topic set 1.
	addGrdTables(false, "6.9Y5G1T2", false, "HS21:HS22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 2, 1, 0, 313); //Topic set 2.
	addGrdTables(false, "6.9Y5G2", false, "HT13:HT22", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 10, 1, 0, 315); //Group 2.

	addGrdTables(false, "6.10c", false, "HX29:HY29", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 1, 2, 0, 560);
	addGrdTables(false, "6.10dD1", true, "HW34:HW39", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 6, 1, 0, 798);
	addGrdTables(false, "6.10dD2", true, "HX34:HX39", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 6, 1, 0, 818);
	addGrdTables(false, "6.10dD3", false , "HY34:HY39", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 6, 1, 0, 838);
	addGrdTables(false, "6.10dD4", false, "HZ34:HZ39", uint32_t(itemsColYearsOrder::Latest), uint32_t(itemsColYearsAlign::None), 6, 1, 0, 858);
	//-- Kirusha's

	
	cmdRunExcel->Select();
}

AutomateExcelFromNET::main::~main() {
	quitExcel();
	if (components) 
		delete components;
}

void AutomateExcelFromNET::main::enableControls(bool blnEnable) {
	cmdRunExcel->Enabled = blnEnable; 
	cmdInsertData->Enabled = blnEnable;
	cmdDeleteData->Enabled = blnEnable;
	cmdCancel->Enabled = blnEnable;
	cmdSelectData->Enabled = blnEnable;
	cbxSheetCountry->Enabled = blnEnable;
	cbxSheetDim->Enabled = blnEnable;
}

System::Void AutomateExcelFromNET::main::cmdCountrySheets_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		Monitor::Enter(lstCountrySheets); //Lock lstCountrySheets while it's being filled in.
		for (int intItem = 0; intItem < lstCountrySheets->Items->Count; ++intItem) {
			lstCountrySheets->SetItemChecked(intItem, chkCountrySheets->Checked); //Check/uncheck all the items to make selecting countries easier. A better solution is a special command button.
		}	
		Monitor::Exit(lstCountrySheets); //Unlock lstCountrySheets filled in.
	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

void AutomateExcelFromNET::main::cmdRunExcel_Click_Thread() {
	try {
		int intItemAdded{};
		enableControls(false);
		Monitor::Enter(lstCountrySheets); //Lock lstCountrySheets while it's being filled in.
		if (cxlsApp == nullptr) //Has no Excel application opened before yet? Open one.
			cxlsApp = gcnew EXCEL::ApplicationClass(); //1. Create the EXCEL application //How to use Managed C++ to Automate EXCEL @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-EXCEL
		if (cxlsApp != nullptr) { //Succeeded?
			if (cwbkFO != nullptr) //Close a prior file, if open.
				cwbkFO->Close(false, Type::Missing, Type::Missing);
			cwbkFO = cxlsApp->Workbooks->Open(cstrFileName, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing); //C++/CLI How to open EXCEL file using relative path? @ http://stackoverflow.com/questions/31915610/c-cli-how-to-open-excel-file-using-relative-path 
			if (cwbkFO != nullptr) { //Did the file open?
				lstCountrySheets->Items->Clear(); //Remove all items from the collection.
				for each (auto sht in cxlsApp->ActiveWorkbook->Worksheets) { //Fiil in the sheet names.
					intItemAdded = lstCountrySheets->Items->Add((safe_cast<Worksheet^>(sht))->Name); //Fiil in the sheet names.
					lstCountrySheets->SetItemChecked(intItemAdded, chkCountrySheets->Checked); //Check/uncheck all the items to make selecting countries easier. A better solution is a special command button.
					cbxSheetCountry->Items->Add((safe_cast<Worksheet^>(sht))->Name);
					cbxSheetDim->Items->Add((safe_cast<Worksheet^>(sht))->Name);
				}
			cbxSheetCountry->SelectedItem = "Countries"; //Default pre-filling. Using a constant (const String^ strCountries = "Countries";) isn't straitforward.
			cbxSheetDim->SelectedItem = "Dimensions";
			}
			cxlsApp->Visible = true;
		}
		Monitor::Exit(lstCountrySheets); //Unlock lstCountrySheets filled in.
		enableControls(true);
	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

System::Void AutomateExcelFromNET::main::cmdRunExcel_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		OpenFileDialog^ dlgOpenFile = gcnew OpenFileDialog(); // Displays an OpenFileDialog so the user can select a Cursor. //To open a file as a file using the OpenFileDialog component @ https://msdn.microsoft.com/en-us/library/61097ykx(v=vs.110).aspx
		dlgOpenFile->Filter = "Excel Files|*.xls; *.xlsx";
		dlgOpenFile->Title = "Select an Excel File";
		if (dlgOpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // Show the Dialog. //If the user clicked OK in the dialog and a .CUR file was selected, open it.  
			cstrFileName = dlgOpenFile->FileName /*"G:\\_\\apk\\My_Documents\\Business\\_05\\UN\\11 FAO Web database\\Timber_2020.xlsx"*/;
			Thread^ objTread = gcnew Thread(gcnew ThreadStart(this, &main::cmdRunExcel_Click_Thread));
			objTread->Start();
		} else  
			cstrFileName = ""; //Clear the file name.
	}
	catch (System::Exception^ objException) { MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	return System::Void();
}

wstring AutomateExcelFromNET::main::cliStringToWstring(String^ strCli) { //LESSON #5: MOVE SEMANTICS //Returning large objects from functions @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
	pin_ptr<const wchar_t> chr = PtrToStringChars(strCli->ToString());
	return wstring(chr);
}

const wchar_t * AutomateExcelFromNET::main::cliStringToWchar(String^ strCli) {
	pin_ptr<const wchar_t> chr = PtrToStringChars(strCli->ToString());
	return chr;
}

void AutomateExcelFromNET::main::fillTimberDB(timberDB::DB& sttTimberDB) {
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
			for (int i = 0; i < grdYears->Rows->Count - 1; i++) //Fill the ascending set of years.
				vecYearsAsc.push_back(Convert::ToDouble(grdYears->Rows[i]->Cells[colYears->Name]->Value)); 
			vector<double> vecYearsDesc(vecYearsAsc.crbegin(), vecYearsAsc.crend()); //Descending vector of the same years.
			vector<double> vecYearsLatest(vecYearsDesc.begin(), ++vecYearsDesc.begin()); //The only and the latest year (i.e. the greatest).
			mapYears_t mapYears; //Map the Years Order combobox items to the respective years.
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Ascending)]->ToString()), vecYearsAsc));
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Descending)]->ToString()), vecYearsDesc));
			mapYears.insert(mapYears_t::value_type(cliStringToString(colYearsOrder->Items[uint32_t(itemsColYearsOrder::Latest)]->ToString()), vecYearsLatest));
			
			vector<vector<wstring>> vecCountryDim;
			vector<vector<wstring>> vecYearValue;
			vector<wstring> vecValueText;
			uint32_t intCountriesUploaded{};
			for each (auto objCountrySheet in lstCountrySheets->CheckedItems) { //Read each country in the Excel file.
				if (!uploadCountry(
						safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets->Item[objCountrySheet->ToString()]), 
						mapYears, 
						vecCountryDim, 
						vecYearValue,
						vecValueText)
					) 
					return System::Void();
				intCountriesUploaded++;
			}
			timberDB::DB sttTimberDB;
			fillTimberDB(sttTimberDB);
			if (intCountriesUploaded > 0) {
				bool blnInsertIntoData{};
				if (!vecYearValue.empty()) //Insert number data, if any.
					blnInsertIntoData = timberDB::insertIntoData(sttTimberDB, &vecCountryDim, &vecYearValue);
				if (!vecValueText.empty()) //Insert text data, if any.
					blnInsertIntoData = timberDB::insertIntoDataText(sttTimberDB, &vecCountryDim, &vecValueText);
				if (blnInsertIntoData) //Message a success, in any data have been inserted.
					MessageBox::Show("Data have been uploaded successfully.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}	
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
	return System::Void();
}

System::Void AutomateExcelFromNET::main::cmdDeleteData_Click(System::Object^ sender, System::EventArgs^ e) {
	try {	
		if (MessageBox::Show("Delete data?", "Question", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes) {
			timberDB::DB sttTimberDB;
			fillTimberDB(sttTimberDB);
			if (timberDB::deleteData(sttTimberDB)) 
				MessageBox::Show("Data have been deleted successfully.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
	return System::Void();
}

void AutomateExcelFromNET::main::selecetItem(
	const wstring& strItem_ID, 
	Worksheet_t^ shtJQ,
	const wstring& strCountryID,
	int intRowBeg, 
	int intRowEnd,
	int intColBeg,
	int intColEnd) {
	try {
		const int intStatus3 = 3, intStatus5 = 5, intStatus8 = 8, intStatus10 = 10;
		const int intYellow = System::Drawing::ColorTranslator::ToOle(System::Drawing::Color::Yellow); //A yellow colour. //How can fill I cells A1:A5 with a color using C#? @ https://stackoverflow.com/questions/4871067/how-can-fill-i-cells-a1a5-with-a-color-using-c
		const int intEmptyFlag = -1; //The empty flag.
		String^ const strNA = "..."; //No data available.
		vector<wstring> strYears = { L"2000", L"2005", L"2010", L"2015" }; //The years.
		
		shtJQ->Select(Type::Missing); //Show the sheet to see how filling in goes on.

		timberDB::DB sttTimberDB;
		fillTimberDB(sttTimberDB);
		
		Range_t^ rngCellsJQ = shtJQ->Cells;
		for (int i = intRowBeg; i <= intRowEnd; i++) { //All the rows - products.
			for (int j = intColBeg; j <= intColEnd; j++) { //All the columns - years.
				Range_t^ rngProd = ((Range_t^)rngCellsJQ[i, cintColProd]);
				if (rngProd->Value2 != nullptr) { //Is there a product code? E.g. row 31 in sheet JQ1-Production is empty.
					timberDB::SQLSelect sttSQLSelect{ 
						strYears[j - intColBeg],
						strCountryID,
						cliStringToWchar(rngProd->Value2->ToString()),
						strItem_ID,
						0, 
						0
					};
					Range_t^ rngCell = ((Range_t^)rngCellsJQ[i, j]);
					if (timberDB::selectData(sttTimberDB, sttSQLSelect)) {
						rngCell->Value2 = sttSQLSelect.dblValue; //Range.Value2 Property (Excel) @ https://msdn.microsoft.com/en-us/vba/excel-vba/articles/range-value2-property-excel
						if (sttSQLSelect.dblValue > intEmptyFlag) {
						if (sttSQLSelect.intStatus_ID == intStatus3 
							|| sttSQLSelect.intStatus_ID == intStatus5 
							|| sttSQLSelect.intStatus_ID == intStatus8 
							|| sttSQLSelect.intStatus_ID == intStatus10
							)  
							rngCell->Interior->Color = intYellow; //Highlight these statuses. //How can fill I cells A1:A5 with a color using C#? @ https://stackoverflow.com/questions/4871067/how-can-fill-i-cells-a1a5-with-a-color-using-c
						} else
							rngCell->Value2 = strNA; //No data available.
					}
				} 
				else
					MessageBox::Show(L"No product code in row " + Convert::ToString(i) + L"!", L"Attention", MessageBoxButtons::OK, MessageBoxIcon::Exclamation); 
			}
		}
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
}


void AutomateExcelFromNET::main::deleteColProd(Worksheet_t^ shtJQ) { //Delete a Product_ID colum.
	Range_t^ rngCol = (Range_t^)shtJQ->/*KTB Range["M1", Type::Missing]*/Columns[cintColProd, Type::Missing]; //Excel automation C#: How to delete a column? @ https://stackoverflow.com/questions/3517698/excel-automation-c-how-to-delete-a-column
	rngCol->EntireColumn->Delete(Type::Missing);
	System::Runtime::InteropServices::Marshal::ReleaseComObject(rngCol);
}

System::Void AutomateExcelFromNET::main::cmdSelectData_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		vector<vector<int>> intRowsBegEnd = {
			{13, 30},
			{32, 83},
			{11, 68},
			{11, 68}	};
		vector<vector<int>> intColsBegEnd = {
			{4, 7},
			{4, 7},
			{4, 7},
			{8, 11} };
		vector<wstring> strItems = { L"2", L"1", L"3", L"4" };
		vector<wstring> strCountryIDs = { //The country codes. //TO DO: Populate them from Excel or SQL Server.
			L"3",  L"8",  L"11", L"12", L"13", //The first 22 countries that are invited to the meeting on Dec 5.
			L"21", L"25", L"26", L"27", L"28",
			L"29", L"31", L"32", L"34", L"35",
			L"46", L"51", L"54", L"57", L"59",
			L"60", L"73",
			
			L"1",	 L"5",  L"6",  L"9",  L"10", //The rest 32 countries with data.
			L"16", L"17", L"18", L"19", L"20", 
			L"22", L"23", L"33", L"37", L"38", 
			L"39", L"40", L"41", L"44", L"45", 
			L"47", L"48", L"49", L"50", L"52", 
			L"53", L"55", L"56", L"58", L"74", 
			L"118", L"119"
		};
		array<String^>^ strCountries = { //The country names. //TO DO: Populate them from Excel or SQL Server.
			"Austria",					"Czech Republic", 		"Finland",					"France",						"Germany", //The first 22 countries that are invited to the meeting on Dec 5.
			"Italy",						"Netherlands",				"Norway",					"Poland",						"Portugal",
			"Romania",					"Spain",						"Sweden",					"Turkey",						"United Kingdom",
			"Belarus",					"Latvia",					"Russian Federation",	"Ukraine",						"Canada",
			"United States",			"Belgium",
			
			"Albania",					"Bulgaria",					"Cyprus",					"Slovakia",						"Denmark", //The rest 32 countries with data.
			"Greece",					"Hungary",					"Iceland",					"Ireland",						"Israel", 
			"Liechtenstein",			"Malta",						"Switzerland",				"Bosnia and Herzegovina",	"Croatia", 
			"Slovenia", 				"The fYR of Macedonia", "Serbia and Montenegro","Armenia",						"Azerbaijan", 
			"Estonia", 					"Georgia",					"Kazakhstan",				"Kyrgyzstan",					"Lithuania", 
			"Republic of Moldova",	"Tajikistan",				"Turkmenistan", 			"Uzbekistan",					"Luxembourg", 
			"Serbia",					"Montenegro"
		};

		Worksheet_t^ shtWB = safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets["wood-fibre-balance"]); //The sheets.
		Worksheet_t^ shtJQ1 = safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets["JQ1-Production"]);
		Worksheet_t^ shtJQ2 = safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets["JQ2-Trade"]);

		Range_t^ rngCountryWB = shtWB->Range["D3", Type::Missing]; //The country name cells on the sheets. //Get Range of Groups of Cells Excel C++/cli @ https://stackoverflow.com/questions/17558229/get-range-of-groups-of-cells-excel-c-cli
		Range_t^ rngCountryJQ1 = shtJQ1->Range["D1", Type::Missing];
		Range_t^ rngCountryJQ2 = shtJQ2->Range["H2", Type::Missing];

		Range_t^ rngDataJQ1 = shtJQ1->Range["D13", "G83"]; //The JQ sheets' data cells.
		Range_t^ rngDataJQ2 = shtJQ2->Range["D11", "K68"];
		
		if (MessageBox::Show("Start selecting data?", "Question", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes) {
			auto varCalculationCurrent = cxlsApp->Calculation; //Remember the user's calculation setting before setting it to manual. //Thread: xlCalculationManual/Automatic @ https://www.mrexcel.com/forum/excel-questions/403785-xlcalculationmanual-automatic.html
			cxlsApp->Calculation = XlCalculation::xlCalculationManual;
			
			for (size_t i = Convert::ToUInt32(txtCountryCodes->Text) /*KTB UInt32::Parse(txtCountryCodes->Text)*/; i < strCountryIDs.size(); i++) { //All the countries //string to integer type conversion if the string is taken from text box in visual c++ using visual studion n windows forms @ https://stackoverflow.com/questions/2517699/string-to-integer-type-conversion-if-the-string-is-taken-from-text-box-in-visual
				rngCountryWB->Value2 = strCountries[i]; //Set the country names.
				rngCountryJQ1->Value2 = strCountries[i];
				rngCountryJQ2->Value2 = strCountries[i];
				
				for (size_t j = 0; j < strItems.size(); j++) { //All the items.
					selecetItem(
						strItems.at(j), 
						j < strItems.size() / 2 ? shtJQ1 : shtJQ2, // Items sets 0 and 1 are in the 1st sheet, 2 and 3 are in the 2nd.
						strCountryIDs.at(i),
						intRowsBegEnd[j][0], 
						intRowsBegEnd[j][1], 
						intColsBegEnd[j][0], 
						intColsBegEnd[j][1] );
				}
				/*OFF
				if (i < strCountryIDs.size() - 1) {
					if (MessageBox::Show(
						strCountries[i] + " has been uploaded.\nUpload a next country?", 
						"Question", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::No) {*/
						break; //The countries.
					/*}
				}*/
			}
			deleteColProd(shtJQ1); //Delete the Product_ID colums.
			deleteColProd(shtJQ2);

			/*OFF
			shtJQ1->Select(Type::Missing); //Select the data cells to check their totals.
			rngDataJQ1->Select();
			shtJQ2->Select(Type::Missing);
			rngDataJQ2->Select();
			*/

			shtWB->Select(Type::Missing); //Show the sheet to see how filling in goes on.
			rngCountryWB->Select();
			
			cxlsApp->Calculate(); //Run calculation.
			cxlsApp->Calculation = varCalculationCurrent; //Restore the user's calculation setting. //Thread: xlCalculationManual/Automatic @ https://www.mrexcel.com/forum/excel-questions/403785-xlcalculationmanual-automatic.html

			MessageBox::Show("Data have been selected successfully.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
	return System::Void();
}

System::Void AutomateExcelFromNET::main::cmdCancel_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close(); //What is the best way to terminate a c++/cli windows form application? @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/473ceb32-dc60-4669-9a4d-ff2a37807529/what-is-the-best-way-to-terminate-a-ccli-windows-form-application?forum=vclanguage
	return System::Void();
}

void AutomateExcelFromNET::main::cmdFindEdited_Click_Thread() {
	Range_t^ rngCellErr{};
	try {	
		const uint32_t intRowBeg = Convert::ToUInt32(txtCountryCodes->Text); //The top left and bottom right cells of the range sought.
		const uint32_t intRowEnd = Convert::ToUInt32(txtCountryNames->Text);
		const uint32_t intColBeg = 1;
		const uint32_t intColEnd = Convert::ToUInt32(txtRowCountry1->Text);
		String^ const strColor0  = "0";
		String^ const strColorHyperLink  = "16711680";
		for each (auto objCountrySheet in lstCountrySheets->CheckedItems) { //Read each country in the Excel file.
			Worksheet_t^ sht = safe_cast<Worksheet_t^>(cxlsApp->ActiveWorkbook->Sheets->Item[objCountrySheet->ToString()]);
			sht->Select(Type::Missing); //C# with Excel -- How to select a sheet? @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/02419ea7-1666-461e-b9f2-445d82e66322/c-with-excel-how-to-select-a-sheet?forum=vsto
			Range_t^ rngCells = sht->Range[	((Range_t^)sht->Cells[intRowBeg, intColBeg]), 
														((Range_t^)sht->Cells[intRowEnd, intColEnd])	];
			for each (Range_t^ rngCell in rngCells) { //rngCell->Select();
				if (rngCell->Value2 != nullptr) { //Is the cell filled in? //What is the difference between .text, .value, and .value2? @ https://stackoverflow.com/questions/17359835/what-is-the-difference-between-text-value-and-value2
					rngCellErr = rngCell; //Remember a cell in case of an error to select.
					String^ strColor = rngCell->Font->Color->ToString();
					if ( (bool)rngCell->Font->Strikethrough || (strColor != strColor0 && strColor != strColorHyperLink) ) { //Is a cell font Strikethrough //i want to bold the words in excel @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/4dc83fdc-f8b8-4320-a199-67372e6febb3/i-want-to-bold-the-words-in-excel?forum=vclanguage
						rngCell->Select();
						String^ strAddress = rngCell->Address[Type::Missing, Type::Missing, EXCEL::XlReferenceStyle::xlA1, Type::Missing, Type::Missing]; //Range.Address Property (Excel) @ https://msdn.microsoft.com/en-us/library/office/ff837625.aspx
						::DialogResult varDialogResult = MessageBox::Show(this, 
							"An edition found in cell \"" + strAddress + "\" of sheet \"" + sht->Name + 
							"!\n\nCell text:\n" + rngCell->Value2 +
							"\n\nCell colour: " + rngCell->Font->Color->ToString() + 
							"\nContinue the search?", 
							L"Find Edited", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Information); 
						if (varDialogResult != ::DialogResult::Yes) 
							return System::Void(); //Exit from the outer loop as well at once.
					}
					rngCellErr = nullptr; //Reset an error bookmark cell.
				}
			}
		}
		MessageBox::Show(this, L"The search has finished!", L"Find Edited", MessageBoxButtons::OK, MessageBoxIcon::Information); 
	}
	catch (System::Exception^ objException) { 
		if (rngCellErr != nullptr) //Select an erroneous cell, if any.
			rngCellErr->Select();
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
}

System::Void AutomateExcelFromNET::main::cmdFindEdited_Click(System::Object^ sender, System::EventArgs^ e) {	
	try {	
		Thread^ objTread = gcnew Thread(gcnew ThreadStart(this, &main::cmdFindEdited_Click_Thread));
		objTread->Start();
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
	return System::Void();
}

//System::Void AutomateExcelFromNET::main::cmdFindEdited_Click(System::Object^ sender, System::EventArgs^ e) {	
//	try {	
//		for each (Worksheet_t^ sht in cxlsApp->ActiveWorkbook->Worksheets) { sht->Select(Type::Missing); if (/*System::String^)*/sht->Name != /*(System::String^)*/L"SoEF Definitions") continue; //Scan all sheets.
//			Range_t^ rngCells = sht->Range[/*"A1"*/"A153", /*"Z1000"*/"H121"/*"B10"*/]; //Select the cells.
//			for each (Range_t^ rngCell in rngCells) { /*rngCell->Select();*/
//				if ((bool)rngCell->Font->Strikethrough) { //Is a cell font Strikethrough //i want to bold the words in excel @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/4dc83fdc-f8b8-4320-a199-67372e6febb3/i-want-to-bold-the-words-in-excel?forum=vclanguage
//					sht->Select(Type::Missing); //C# with Excel -- How to select a sheet? @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/02419ea7-1666-461e-b9f2-445d82e66322/c-with-excel-how-to-select-a-sheet?forum=vsto
//					rngCell->Select();
//					String^ strAddress = rngCell->Address[Type::Missing, Type::Missing, EXCEL::XlReferenceStyle::xlA1, Type::Missing, Type::Missing]; //Range.Address Property (Excel) @ https://msdn.microsoft.com/en-us/library/office/ff837625.aspx
//					MessageBox::Show(this, "An edition found in cell \"" + strAddress + "\" of sheet \"" + sht->Name + "\"!", L"Find Edited", MessageBoxButtons::OK, MessageBoxIcon::Information); 
//					return System::Void(); //Exit from the outer loop as well at once.
//				}
//			}
//		}
//		MessageBox::Show(this, L"The search finished!", L"Find Edited", MessageBoxButtons::OK, MessageBoxIcon::Information); 
//	}
//	catch (System::Exception^ objException) { 
//		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
//	}
//	return System::Void();
//}

void AutomateExcelFromNET::main::quitExcel() {
	try {	
		if (cxlsApp != nullptr) {
			if (cwbkFO != nullptr) //Close a file, if open.
				cwbkFO->Close(false, Type::Missing, Type::Missing);		
			cxlsApp->Quit(); //Quit EXCEL.
			cxlsApp = nullptr;
			lstCountrySheets->Items->Clear();
			cbxSheetCountry->Items->Clear();
			cbxSheetDim->Items->Clear();
		}	
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
}

bool AutomateExcelFromNET::main::validateNonNum(Range_t^ rngValue) {
	try {	
		string strTextTrimmed = boost::trim_copy( cliStringToString(rngValue->/*KTB Value2*/Text->ToString()) );
		String^ strText = gcnew String(strTextTrimmed.c_str());
		for (int i = 0; i < grdNonNum->Rows->Count - 1; i++) { //The last row is empty. Skip it.
			if (strText == grdNonNum->Rows[i]->Cells[colNonNum->Name]->Value->ToString() ) 
				return true; //Such a non-numeric value is valid because is available among grdNonNum.
		}	
		String^ strAddress = rngValue->Address[Type::Missing, Type::Missing, EXCEL::XlReferenceStyle::xlA1, Type::Missing, Type::Missing]; //Range.Address Property (Excel) @ https://msdn.microsoft.com/en-us/library/office/ff837625.aspx
		Worksheet_t^ shtParent = safe_cast<Worksheet_t^>(rngValue->Parent);
		shtParent->Select(Type::Missing);
		rngValue->Select();
		MessageBox::Show("A non-numeric value \"" + strText + "\" found in cell \"" + strAddress + "\" of sheet \"" + shtParent->Name + "\"!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning); //Alert on a invalid non-numeric value.
	}
	catch (System::Exception^ objException) { 
		MessageBox::Show(this, objException->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
	return false;
}

void AutomateExcelFromNET::main::replaceStringInPlace(wstring & strSubject, const wstring & strSearch, const wstring & strReplace) {
	size_t intPos = 0;
	while ((intPos = strSubject.find(strSearch, intPos)) != std::string::npos) {
		strSubject.replace(intPos, strSearch.length(), strReplace);
		intPos += strReplace.length();
	}	
}

// Upload a table with years located horizontally. intRowDim1 is row in the Dimensions sheet with the 1st dimension of the table. 
// intTopics is number of rows with values in the table. intGroups is number of groups in the table. rngTable are the table cells with the values
bool AutomateExcelFromNET::main::uploadTable(
		const vector<double>& vecYears, 
		const wstring& strCountryCode, 
		Range_t^ rngTable, 
		DataGridViewCellCollection_t^ objTableRowCells, 
		vector<vector<wstring>>& vecCountryDim, 
		vector<vector<wstring>>& vecYearValue,
		vector<wstring>& vecValueText) 
{ 
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
					if (intYearsAlign == uint32_t(itemsColYearsAlign::Horizontally)) 
						rngValue = (Range_t^)rngTable->Item[k, (ptrYear - vecYears.begin() + 1) + vecYears.size() * (i - 1)]; //Only vertically aligned year tables contain subgroups and their year order is descending.
					else 
						rngValue = (Range_t^)rngTable->Item[(ptrYear - vecYears.begin() + 1) + vecYears.size() * (k - 1), (i - 1) * intSubgroups + j]; //Only vertically aligned year tables contain subgroups and their year order is descending.
					if (rngValue->Value2 != nullptr) { //Is the cell filled in? //What is the difference between .text, .value, and .value2? @ https://stackoverflow.com/questions/17359835/what-is-the-difference-between-text-value-and-value2
						if (!bool(objTableRowCells[colText->Name]->Value)) { //A non-textual table must contain numbers. So, first validate it for numbers.
							if (VB::Information::IsNumeric(rngValue->/*KTB Value2*/Text)) { //Is not the cell value a number? Unlike a faster Value2, Text is used to make a full validtion for even accidential wrong date formatting (e.g. see 16.Sep in Netherlands, Table 4a). //The Visual Basic Library @ http://www.functionx.com/vccli/topics/libraries.htm //Alternatives: C# Equivalent of VB's IsNumeric() @ https://www.codeproject.com/articles/16329/c-equivalent-of-vb-s-isnumeric
								vector<wstring> vecCountryDimRow;
								vecCountryDimRow.push_back(strCountryCode); //Accessing via pointers vs. [][] indexes.
								vecCountryDimRow.push_back( cliStringToWstring( ((Range_t^)rngCellsDim->Item[intRowDim, intColDim])->Value2->ToString() ) );
								vecCountryDim.push_back(move(vecCountryDimRow)); //LESSON #5: MOVE SEMANTICS //Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
								vecYearValue.push_back( vector<wstring> {to_wstring(int(*ptrYear)), move(cliStringToWstring(rngValue->Value2->ToString()))} ); //LESSON #5: MOVE SEMANTICS //Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
							} else if (rngValue->Text != "") { //Is this not an empty value?
								if (!validateNonNum(rngValue)) 
									return false; //Is not this non-numeric value valid?
							}
						} else if (rngValue->Text != "") { //A textual datum. Is this not an empty value?
							vector<wstring> vecCountryDimRow;
							vecCountryDimRow.push_back(strCountryCode); //Accessing via pointers vs. [][] indexes.
							vecCountryDimRow.push_back( cliStringToWstring( ((Range_t^)rngCellsDim->Item[intRowDim, intColDim])->Value2->ToString() ) );
							vecCountryDim.push_back(move(vecCountryDimRow)); //LESSON #5: MOVE SEMANTICS //Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
							wstring strTextTrimmed = boost::trim_copy( cliStringToWstring(rngValue->Text->ToString()) );
							if (!strTextTrimmed.empty())
								replaceStringInPlace(strTextTrimmed, L"'", L"''"); // Replce single quote with double ones. An SQL statement parses a text with a single quote as two texts. For example, an SQL statement parses "Populus deltoides or trichocarpa or canadensis or 'interamericain' or other selectionned poplar" as more than one string and raises an error. // sql query single quote problem @ https://www.codeproject.com/Questions/580705/sqlplusqueryplussingleplusquoteplusproblem
							vecValueText.push_back( move(strTextTrimmed) ); //LESSON #5: MOVE SEMANTICS //Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/
						}
					}	
				}
				intRowDim++; //Insert values for the next dimension.
			}	
		}	
	}
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
			if (rngCountry->Value2 == nullptr) 
				strCountryValue2 = String::Empty;
			else {
				strCountryValue2 = rngCountry->Value2->ToString();
				if (strCountryValue2 == strCountryName) { //Get the code of the country found.
					pin_ptr<const wchar_t> chrCountryCode = PtrToStringChars( ((Range_t^)rngCellsCountries->Item[intRow, intColCode])->Value2->ToString() ); //String conversion from System::String ^ to const wchar_t * @ http://stackoverflow.com/
					return wstring(chrCountryCode); //Sussess.
				}	
			}
		} while (!String::IsNullOrEmpty(strCountryValue2));
	}
	return wstring();
}

bool AutomateExcelFromNET::main::uploadCountry( // Upload a group with years placed in columns
		Worksheet_t^ shtCountry, 
		const mapYears_t& mapYears, 
		vector<vector<wstring>>& vecCountryDim, 
		vector<vector<wstring>>& vecYearValue,
		vector<wstring>& vecValueText) 
{ 
	uint32_t intTablesUploaded{};
	wstring strCountryCode{getCountryCode(shtCountry->Name)};
	if (strCountryCode.empty()) 
		MessageBox::Show("No country code for the \"" + shtCountry->Name + "\" sheet is found in the \"" + cbxSheetCountry->SelectedItem + "\" sheet.", 
			"Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	else { //Continue, if the country's code is available.
		if (grdTables->Rows->Count == 0) 
			MessageBox::Show("No table parameters enetered!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		else { //Continue, if there are table parameters.
			for (int i = 0; i < grdTables->Rows->Count - 1; i++) { //The last row is empty. Skip it.
				auto objTableRowCells = grdTables->Rows[i]->Cells; //C# Tutorial - How To Know If DataGridView CheckBoxCell Is Checked In C# [ With Source Code ] @ https://www.youtube.com/watch?v=AkLrQt6rs0o&index=17&list=PLFDH5bKmoNqyDKntkVv-NURTAlPIhMPqA
				if (bool(objTableRowCells[colActive->Name]->Value)) { //Read active rows only.
					if (!uploadTable(mapYears.at(cliStringToString(objTableRowCells[colYearsOrder->Name]->Value->ToString())), 
							strCountryCode, 
							shtCountry->Range[objTableRowCells[colRange->Name]->Value, Type::Missing], 
							objTableRowCells, 
							vecCountryDim, 
							vecYearValue,
							vecValueText)) 
						return false; //Suspend uploading on an error. //How to get Cell value of DataGridView by column name? @ https://stackoverflow.com/questions/13436553/how-to-get-cell-value-of-datagridview-by-column-name
					intTablesUploaded++;
				}	
			}	
			if (intTablesUploaded == 0) 
				MessageBox::Show("No active tables selected!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}	
	}
	return intTablesUploaded > 0;
}

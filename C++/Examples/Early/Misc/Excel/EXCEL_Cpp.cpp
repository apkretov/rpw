#include "stdafx.h" //A brief introduction to C++ and Interfacing with Excel @ http://www.maths.manchester.ac.uk/~ahazel/EXCEL_C++.pdf
#include <iostream>
#include <cmath>
using namespace std;

//MicroSoft Office Objects
#import \
	"c:\Program Files (x86)\Common Files\microsoft shared\OFFICE15\MSO.DLL" \
	rename("DocumentProperties", "DocumentPropertiesXL") \
	rename("RGB", "RGBXL")

//Microsoft VBA Objects
#import \
"c:\Program Files (x86)\Common Files\microsoft shared\VBA\VBA6\VBE6EXT.OLB"

//Excel Application Objects
#import "c:\Program Files (x86)\Microsoft Office\Office15\EXCEL.EXE" \
rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") \
rename("DocumentProperties", "DocumentPropertiesXL") \
rename("ReplaceText", "ReplaceTextXL") \
rename("CopyFile", "CopyFileXL") \
exclude("IFont", "IPicture") no_dual_interfaces

double f(const double& x) { return (sin(x) * exp(-x)); } //Define our own function, e^{-x} sin(x) //In general this could be the result of a simulation, etc.

auto displayCell(const Excel::RangePtr& pRange, int intRow, int intCol) {
	_variant_t varValue = pRange->Item[intRow][intCol];
	_bstr_t strBstr_t = varValue.operator _bstr_t(); //How to convert a _variant_t datatype to wstring @ http://stackoverflow.com/questions/17927298/how-to-convert-a-variant-t-datatype-to-wstring
	return strBstr_t.operator const wchar_t*();
};

/*KTB
Excel::_WorksheetPtr* getSheetByName(Excel::_ApplicationPtr* xl, const wchar_t* const name) { //Access to sheet by name @ http://www.libxl.com/access-excel-sheet.html
   for (unsigned short i = 0; i < book->sheetCount(); ++i) {
       if(wcscmp(book->getSheet(i)->name(), name) == 0)
       {
           return book->getSheet(i);
       }
   }
   return 0;
}*/

int main() { //Main driver program
	try { //Surround the entire interfacing code with a try block
		CoInitialize(NULL); //Initialise the COM interface
		Excel::_ApplicationPtr xl; //Define a pointer to the Excel application
		xl.CreateInstance(L"Excel.Application"); //Start one instance of Excel
		xl->Visible = true; //Make the Excel application visible

		xl->Workbooks->Add(Excel::xlWorksheet); //Add a (new) workbook
		Excel::_WorksheetPtr pSheet = xl->ActiveSheet; //Get a pointer to the active worksheet
		pSheet->Name = "Chart Data"; //Set the name of the sheet

		_bstr_t bRet = pSheet->Range["A3"]->GetValue(); cout << static_cast<char*>(bRet) << endl; //Thread: c++ for excel worksheets \ Easiest way to extract values? @ https://cboard.cprogramming.com/cplusplus-programming/34470-cplusplus-excel-worksheets.html
		char* chrTest = static_cast<char*>(bRet);	cout << chrTest << endl; //
		double dblTest = pSheet->Range["A3"]->GetValue(); cout << dblTest << endl;

		Excel::RangePtr pRange = pSheet->Cells; //Get a pointer to the cells on the active worksheet
		unsigned Nplot = 100; //Define the number of plot points
		double x_low = 0.0, x_high = 20.0; //Set the lower and upper limits for x
		double h = (x_high - x_low) / (double)Nplot; //Calculate the size of the (uniform) x interval //Note a cast to an double here
		pRange->Item[1][1] = "x"; pRange->Item[1][2] = "f(x)"; //Create two columns of data in the worksheet //We put labels at the top of each column to say what it 

		for (unsigned i = 0; i < Nplot; i++) { //Now we fill in the rest of the actual data by using a single for loop
			double x = x_low + i * h; //Calculate the value of x (equally-spaced over the range)
			pRange->Item[i + 2][1] = x; //The first column is our equally-spaced x values
			pRange->Item[i + 2][2] = f(x); //The second column is f(x)
		}
		
		Excel::RangePtr pBeginRange = pRange->Item[1][1]; //The sheet "Chart Data" now contains all the data required to generate the chart //In order to use the Excel Chart Wizard, we must convert the data into Range Objects //Set a pointer to the first cell containing our data
		Excel::RangePtr pEndRange = pRange->Item[Nplot + 1][2]; //Set a pointer to the last cell containing our data
		Excel::RangePtr pTotalRange = pSheet->Range[(Excel::Range*)pBeginRange][(Excel::Range*)pEndRange]; //Make a "composite" range of the pointers to the start and end of our data //Note the casts to pointers to Excel Ranges	

		Excel::_ChartPtr pChart = xl->ActiveWorkbook->Charts->Add(); // Create the chart as a separate chart item in the workbook
		//Use the ChartWizard to draw the chart.
		//The arguments to the chart wizard are
		//Source: the data range,
		//Gallery: the chart type,
		//Format: a chart format (number 1-10),
		//PlotBy: whether the data is stored in columns or rows,
		//CategoryLabels: an index for the number of columns
		// containing category (x) labels
		// (because our first column of data represents
		// the x values, we must set this value to 1)
		//SeriesLabels: an index for the number of rows containing
		// series (y) labels
		// (our first row contains y labels,
		// so we set this to 1)
		//HasLegend: boolean set to true to include a legend
		//Title: the title of the chart
		//CategoryTitle: the x-axis title
		//ValueTitle: the y-axis title
		pChart->ChartWizard((Excel::Range*)pTotalRange, (long)Excel::xlXYScatter, 6L, (long)Excel::xlColumns, 1L, 1L, true, "My Graph", "x", "f(x)");
		pChart->Name = "My Data Plot"; //Give the chart sheet a name
	}
	
	catch (_com_error & error) { cout << "COM ERROR" << endl; } //If there has been an error, say so
	
	CoUninitialize(); //Finally Uninitialise the COM interface
	return 0; //Finish the C++ program
}
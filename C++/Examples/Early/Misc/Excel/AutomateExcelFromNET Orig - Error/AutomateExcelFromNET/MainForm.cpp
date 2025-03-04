#include "MainForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	AutomateExcelFromNET::MainForm frmMain;
	Application::Run(%frmMain);
}

System::Void AutomateExcelFromNET::MainForm::cmdRunExcel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	//Excel::Application^ xlApp = gcnew Excel::ApplicationClass(); //1. Create the Excel application //How to use Managed C++ to Automate Excel @ https://www.codeproject.com/Articles/10886/How-to-use-Managed-C-to-Automate-Excel
	//Workbook^ wb = xlApp->Workbooks->Add(Type::Missing); //2. Add a Workbook
	//Worksheet^ ws = safe_cast<Worksheet^>(xlApp->ActiveSheet); //Use Visual Studio 2008 C++/CLI to Automate Excel @ https://www.codeproject.com/Articles/28083/Use-Visual-Studio-C-CLI-to-Automate-Excel
	//xlApp->ActiveWorkbook->Worksheets->Add(Type::Missing, Type::Missing, 2, Type::Missing);
	//safe_cast<Worksheet^>(xlApp->ActiveWorkbook->Sheets->Item[3])->Select(Type::Missing);
	//safe_cast<Worksheet^>(xlApp->ActiveWorkbook->Sheets->Item["Sheet2"])->Select(Type::Missing);
   //xlApp->Visible = true;
	RunExcel();
	return System::Void();
}

void AutomateExcelFromNET::MainForm::RunExcel() {
      //1. Create a new Excel application

      Excel::Application^ exApp = gcnew Excel::ApplicationClass();
 
      //2. Add a workbook (comes with three Worksheets)

      Workbook^   exWb  = exApp->Workbooks->Add(Type::Missing);
 
      /*ORIG
		//3. Delete the last two worksheets
      safe_cast<Worksheet^>(exApp->ActiveWorkbook->Sheets[3])->Delete();
      safe_cast<Worksheet^>(exApp->ActiveWorkbook->Sheets[2])->Delete();
		*/
 
      //4. Create a variable for the active Worksheet's tracking handle

//  (first Worksheet is the default active one)

      Worksheet^  exWs  = safe_cast<Worksheet^>(exApp->ActiveSheet);
 
      //5. Rename the active worksheet

      exWs->Name = "Charts";
 
      //6. Load the data

      LoadData();
 
      //7. Make the bar chart

      //ERROR MakeBarChart(exWs, 2, 1);
 
      //8. Make a line chart

      //ERROR MakeLineChart(exWs, 2, 8);
 
      // Show the Workbook

      exApp->Visible = true;
}

void AutomateExcelFromNET::MainForm::LoadData() {
      slTonsRcvd              = gcnew SortedList();   //Global, declared in Form1.h

      slByDayNYProjected      = gcnew SortedList();   //Global, declared in Form1.h

      slByDayNYActual         = gcnew SortedList();   //Global, declared in Form1.h

 
      slTonsRcvd->Add("New York",   46.826);
      slTonsRcvd->Add("New Jersey", 21.865);
      slTonsRcvd->Add("Boston",     4.8);
      slTonsRcvd->Add("Los Angles", 30.87);
      slTonsRcvd->Add("Portland",   16.4876);
 
      slByDayNYProjected->Add(1, 2.0);
      slByDayNYProjected->Add(2, 11.5);
      slByDayNYProjected->Add(3, 7.5);
      slByDayNYProjected->Add(4, 5);
      slByDayNYProjected->Add(5, 10);
      slByDayNYProjected->Add(6, 6.5);
      slByDayNYProjected->Add(7, .5);
 
      slByDayNYActual->Add(1, 2.3);
      slByDayNYActual->Add(2, 12.345);
      slByDayNYActual->Add(3, 8.331);
      slByDayNYActual->Add(4, 5.702);
      slByDayNYActual->Add(5, 10.45);
      slByDayNYActual->Add(6, 6.718);
      slByDayNYActual->Add(7, .98);
}

/*ERROR
void AutomateExcelFromNET::MainForm::MakeBarChart(Worksheet^ ws, int row, int col) {
      int         xPos = (col+2)*48;      //Col width 48 points. Chart starts in 3rd col

      int         yPos = row*9;           //Row height = 9, Chart starts in 2nd row

      double      tons = 0;
      String^     port;
 
      //1. Format a Worksheet column to 2 decimal places for chart data

      ws->Range["B1", Type::Missing]->EntireColumn->NumberFormat = "#,##0.00";
 
      //2. Set all Worksheet column widths to 12 to fit column titles and data

      safe_cast<Range^>(ws->Columns)->ColumnWidth = 12;
 
      //3. Extract Tons Received data from the SortedList and place on the chart

      IDictionaryEnumerator^ ide = slTonsRcvd->GetEnumerator();
      while (ide->MoveNext()) {
            port = ide->Key->ToString();
            tons = Convert::ToDouble(ide->Value);
            ws->Cells[row, col]     =  port;
            ws->Cells[row, col+1]   = tons;
            row++;
      }
 
      //4. Create a ChartObjects Collection for the Worksheet

      ChartObjects^ chObjs = safe_cast<ChartObjects^>(ws->ChartObjects(Type::Missing));
 
      //5. Add a ChartObject to the collection at(x, y, width, height) in points

      ChartObject^ chObj = chObjs->Add(xPos, yPos, 300, 300);
 
      //6. Create a chart from the ChartObject

      Chart^ ch = chObj->Chart;
 
      //7. Create a Range object & set the data range.

      Range^ rn = ws->Range["A2:B6", Type::Missing];
 
      //8. Do the chart using ChartWizard

      ch->ChartWizard(rn->CurrentRegion,                    //Source

                        Constants::xlColumn,                //Gallery

                        Type::Missing,                      //Format

                        XlRowCol::xlColumns,                //Plot by

                        1,                                  //Category Labels

                        Type::Missing,                      //Series Labels

                        false,                              //Has Legend

                        "Weekly Tons Received by Port",     //Title

                        "Port",                             //Category Title (X)

                        "Tons",                             //Value Title (Y)

                        Type::Missing);                     //Extra Title

 
      //9. Format the x-axis of the Cargo graph

      safe_cast<Axis^>(ch->Axes(XlAxisType::xlValue, XlAxisGroup::xlPrimary))-> \
                                                      TickLabels->NumberFormat = "#,##0";
}

void AutomateExcelFromNET::MainForm::MakeLineChart(Worksheet^ ws, int row, int col) {
      int         xPos = (col+5)*48;      //Col width 48 points. Chart starts in 3rd col

      int         yPos = row*9;           //Row height = 9, Chart starts in 2nd row

      double      tonsA = 0;              //Actual tons

      double      tonsP = 0;              //Projected tons

      String^     day;                    //Day being plotted

      String^     title = "Tons Received at NY port by day";
 
      //1. Format two Worksheet columns to two decimal places for chart data

      ws->Range["I1:J1", Type::Missing]->EntireColumn->NumberFormat = "#,##0.00";
 
      //2. Reset the three Worksheet data column widths to better fit data

      ws->Range["H1",    Type::Missing]->EntireColumn->ColumnWidth = 5;
      ws->Range["I1:J1", Type::Missing]->EntireColumn->ColumnWidth = 9;
 
      //3. Put Column titles on the chart – two are Legend titles

      ws->Cells[row, col]       = "Day";
      ws->Cells[row, col+1] = "Projected";
      ws->Cells[row, col+2] = "Actual";
 
      //4. Extract the data from two SortedLists and put it on the chart

      IDictionaryEnumerator^ ide = slByDayNYProjected->GetEnumerator();
      while (ide->MoveNext()) {
            //Day and projected tons form one SortedList

            day = ide->Key->ToString();
            tonsP = Convert::ToDouble(ide->Value);
            ws->Cells[row+1, col] = day;
            ws->Cells[row+1, col+1] = tonsP;
            //Use key to get actual tons form the other SortedList

            tonsA = Convert::ToDouble(slByDayNYActual[ide->Key]);
            ws->Cells[row+1, col+2] = tonsA;
            row++;
      }
 
      //5. Create a ChartObject Collection for the Worksheet

      ChartObjects^ chObjs = safe_cast<ChartObjects^>(ws->ChartObjects(Type::Missing));
 
      //6. Add the ChartObject to the collection at(x, y, width, height) in points

      //   Width = 350 to prevent title from wrapping

      ChartObject^  chObj = chObjs->Add(xPos, yPos, 350, 300);
 
      //7. Create a chart from the ChartObject

      Chart^ ch = chObj->Chart;
 
      //8. Create a Range object & set the data range.

      Range^ rn = ws->Range["I2:J9", Type::Missing];
 
      //9. Do the chart

      ch->ChartWizard(rn->CurrentRegion,        //Source

                        XlChartType::xlLine,    //Gallery

                        Type::Missing,          //Format

                        XlRowCol::xlColumns,    //Plot by

                        1,                      //Category Labels

                        1,                      //Series Labels

                        true,                   //Has Legend

                        title,                  //Title

                        "Day",                  //Category Title

                        "Tons",                 //Value Title

                        Type::Missing);         //Extra Title

 
      //10. Tell it the chart type again - initially comes up as a "lineMarked" type

      ch->ChartType = safe_cast<XlChartType>(XlChartType::xlLine);
 
      //11. Position the Chart Legend from the side to the bottom

      ch->Legend->Position = XlLegendPosition::xlLegendPositionBottom;
 
      //12. Format the Y-axis numbers to integers

      safe_cast<Axis^>(ch->Axes(XlAxisType::xlValue, \
                         XlAxisGroup::xlPrimary))->TickLabels->NumberFormat = "#,##0";
 
      //13. Make the lines thick

      safe_cast<Series^>(ch->SeriesCollection(1))->Border->Weight = \
XlBorderWeight::xlThick;
      safe_cast<Series^>(ch->SeriesCollection(2))->Border->Weight = \
XlBorderWeight::xlThick;
 
      //14. Change the line colors

      safe_cast<Series^>(ch->SeriesCollection(1))->Border->ColorIndex = 3;
      safe_cast<Series^>(ch->SeriesCollection(2))->Border->ColorIndex = 32;
}
*/
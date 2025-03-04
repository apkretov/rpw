#property strict
#define HWND int
#define BOOL bool    
#import "user32.dll"
HWND GetParent(HWND hWnd); // GetParent.Retrieves a handle to the specified window's parent or owner.
BOOL ShowWindow(HWND hWnd, int nCmdShow); // ShowWindow. 1 - Activates and displays a window. 2 - Activates the window and displays it as a minimized window. 3 - Activates the window and displays it as a maximized window.
#import

bool containsIndicator(long lngChartID, string strIndicatorName) { // Does a chart contain an indicator on the main chart subwindow? +------------------------------------------------------------------+
   const int intSubWindow = 0; //Look up the indicarot on the main chart subwindow only.
   for (int i = 0; i < ChartIndicatorsTotal(lngChartID, intSubWindow); i++) { //Look up the indicarot on the main chart subwindow only sub_window of ChartIndicatorsTotal = 0.
      if (ChartIndicatorName(lngChartID, intSubWindow, i) == strIndicatorName) return true; //Is this the indicator sought?
   }
   return false;
}

long chartWindowsHandle(long lngChartID) { // Chart window handle (HWND) //Как в скрипте активировать окно с нужным символом? @ https://www.mql5.com/ru/forum/22244 +------------------------------------------------------------------+
   long lgnResult = -1; // Prepare the variable to get the property value
   ResetLastError(); // Reset the error value
   if (!ChartGetInteger(lngChartID, CHART_WINDOW_HANDLE, 0, lgnResult)) Print(__FUNCTION__ + ", Error Code = ", GetLastError()); // Receive the property value // Display the error message in Experts journal
   return(lgnResult); // Return the value of the chart property
}

void showWindow(long lngChartID) { ShowWindow( GetParent((int)chartWindowsHandle(lngChartID)), 3 ); } // Show a window. +------------------------------------------------------------------+

//+----------------------------------------------------------------------+ 
//| Send command to the terminal to display the chart above all others.  | 
//+----------------------------------------------------------------------+ 
bool ChartBringToTop(const long chart_ID=0) 
  { 
//--- reset the error value 
   ResetLastError(); 
//--- show the chart on top of all others 
   if(!ChartSetInteger(chart_ID,CHART_BRING_TO_TOP,0,true)) 
     { 
      //--- display the error message in Experts journal 
      Print(__FUNCTION__+", Error Code = ",GetLastError()); 
      return(false); 
     } 
//--- successful execution 
   return(true); 
  }

void OnStart() { // Как в скрипте активировать окно с нужным символом? @ https://www.mql5.com/ru/forum/22244 +------------------------------------------------------------------+
   const int intSubWindow = 0; //Look up the indicarot on the main chart subwindow only.
   const ENUM_TIMEFRAMES  intPeriodMax = PERIOD_H4;
   const string strIndicatorSought = "Alligator(13,8,5)";
   const int intLimit = 100;
   long lngChartNext; // variables for chart ID
   long lngChartPrior = ChartFirst();
   int i = 0;
   int intPeriodCurr = Period(); //Remember the period (time frame) of current chart.
   long lngChartCurrPeriod = 0; //The variable for a chart with the current chart's period.
   bool blnContainsIndicatorSought = containsIndicator(ChartID(), strIndicatorSought); //Does the current chart contain the indicator sought?
   while (i < intLimit) { // We have certainly not more than 100 open charts
      lngChartNext = ChartNext(lngChartPrior); // Get the new chart ID by using the previous chart ID
      if (lngChartNext < 0) break;  // Have reached the end of the chart list
      int intPeriodNext = ChartPeriod(lngChartNext); //The period of the next chart.
      if (intPeriodNext <= intPeriodMax) { //Is the timeframe smaller or equal to the maximal one needed?
         //if (containsIndicator(lngChartNext, strIndicatorSought) != blnContainsIndicatorSought) { //Does/doesn't a chart contain an indicator on the main chart subwindow?
         if (containsIndicator(lngChartNext, strIndicatorSought) == blnContainsIndicatorSought) { //Does/doesn't a chart contain an indicator on the main chart subwindow?
            //showWindow(lngChartNext); //Show that window.
            ChartBringToTop(lngChartNext);
            if (intPeriodNext == intPeriodCurr) lngChartCurrPeriod = lngChartNext; //Remember the chart with the initially current chart's period.
      }  }
      lngChartPrior = lngChartNext; // Let's save the current chart ID for the ChartNext()
      i++; // Do not forget to increase the counter
   }  
   //showWindow(lngChartCurrPeriod); //Show the chart with the initially current chart's period.
   ChartBringToTop(lngChartCurrPeriod); //Send command to the terminal to display the chart above all others.
}

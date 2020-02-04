#include <WinUser32.mqh> //It is needed for MessageBox.
#import "user32.dll"
   int GetParent(int hWnd);
   void keybd_event(int bVk, int bScan, int dwFlags, int dwExtraInfo); //http://www.forexfactory.com/showthread.php?t=468143        http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
   //KTB int SetFocus(int hWnd); //Sets the keyboard focus to the specified window. //SetFocus function @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms646312(v=vs.85).aspx
#import

#property strict
//KTB #property show_inputs

enum enmKeys { keyTab = 9, keyEnter = 13, keyEsc = 27, keyEnd = 35, keyArrowLeft = 37, keyArrowUp, keyArrowRight, keyArrowDown, keyDel = 46, key0 = 48, key1, key2, key3, key4, key5, key6, key7, key8, key9,  keyA = 65, keyB, keyC, keyD, keyE, keyF, keyG, keyQ = 81, keyR, keyS = 83, keyT, keyV = 86, keyW, keyX, keyZ = 90, key0Num = 96, key1Num, key2Num, key3Num, key4Num, key5Num, key6Num, key7Num, key8Num, key9Num, keyNumMinus = 109, /*keyNumSlash = 111,*/ keyF5 = 116 /*keyTilde 192*/};
enum enmVK { vkTab = 0x09, vkShift, vkCtrl, vkMenu }; //bVirtualKey for keybd_event: Virtual keycode that has to be send as key input. The following are the available predefined virtual key codes. @ http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
enum enmNCmdShow { showNormal = 1, /*KTB showMinimized,*/ showMaximized = 3};
enum enmActivate { ActivateIndicator, ActivateTimeFrame, ActivateMaximizeRestore };

input enmActivate Activate = ActivateMaximizeRestore;
input ENUM_TIMEFRAMES TimeFrameMax = PERIOD_H4;
input string IndicatorSought = "Alligator(13,8,5)";

const string mstrActivateMaximizeRestore = "ActivateMaximizeRestore";

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

void showWindow(long lngChartID, enmNCmdShow intShow) { ShowWindow( GetParent((int)chartWindowsHandle(lngChartID)), intShow ); } // Show a window. // ShowWindow. 1 - Activates and displays a window. 2 - Activates the window and displays it as a minimized window. 3 - Activates the window and displays it as a maximized window. +------------------------------------------------------------------+

/*KTB bool chartBringToTop(const long chart_ID=0) { //Send command to the terminal to display the chart above all others. +----------------------------------------------------------------------+ 
   ResetLastError(); //--- reset the error value 
   if(!ChartSetInteger(chart_ID,CHART_BRING_TO_TOP,0,true)) { //--- show the chart on top of all others 
      Print(__FUNCTION__+", Error Code = ",GetLastError()); //--- display the error message in Experts journal 
      return(false); 
   } 
   return(true); //--- successful execution 
}*/

void restoreWindow() { // Restore an MDI-child widnow maximised by pressing Alt+NumMinus, Enter. +------------------------------------------------------------------+
   //KTB keybd_event(vkMenu,0xb8, 0 , 0); // Press. //Keyboard Events Simulation using keybd_event() function @ http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
   keybd_event(keyNumMinus, 0x9e, 0 , 0); //Press.
   //KTB keybd_event(keyNumMinus, 0x9e, KEYEVENTF_KEYUP, 0); //Release.
   //KTB keybd_event(vkMenu, 0xb8, KEYEVENTF_KEYUP, 0); //Release.
   keybd_event(keyEnter, 0, 0, 0);
}

bool activateIndicatorTF(int& intPeriodNext, long& lngChartNext) { // To activate indicator containing vs. maxiimal TF charts?  +------------------------------------------------------------------+
   static bool blnContainsIndicator = containsIndicator(ChartID(), IndicatorSought); //Does the current chart contain the indicator sought? 
   switch (Activate) {
      case ActivateIndicator:
         if (intPeriodNext <= TimeFrameMax) { //Is the timeframe smaller or equal to the maximal one needed?
            if (containsIndicator(lngChartNext, IndicatorSought) != blnContainsIndicator) return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
         }
         break;
      case ActivateTimeFrame: {
         static int intDiffTarget = (TimeFrameMax - Period()) * (-1); //The difference between the current and the maximal period. //The target difference, i.e. the negative to the current.      
         if (TimeFrameMax - intPeriodNext < intDiffTarget) { //Is the timeframe smaller or equal to the maximal one needed?
            if (containsIndicator(lngChartNext, IndicatorSought) == blnContainsIndicator) return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
   }  }  }
   return false; 
}

void maximizeOrRestore(enmNCmdShow intShow) { // Maximize or restore the current window. Save the last state. +------------------------------------------------------------------+
  showWindow(ChartID(), intShow); //Show the current window.
  GlobalVariableSet(mstrActivateMaximizeRestore, intShow);
}

void OnStart() { // Как в скрипте активировать окно с нужным символом? @ https://www.mql5.com/ru/forum/22244 +------------------------------------------------------------------+
   switch(Activate) {
      case ActivateMaximizeRestore: { //Maximize or restore.
         if (!GlobalVariableCheck(mstrActivateMaximizeRestore)) GlobalVariableSet(mstrActivateMaximizeRestore, showNormal); //Check/set the last window state.
         switch ((enmNCmdShow)GlobalVariableGet(mstrActivateMaximizeRestore)) {
            case showNormal: maximizeOrRestore(showMaximized); break;
            case showMaximized: maximizeOrRestore(showNormal);
         }
         break;
      }case ActivateIndicator:
      case ActivateTimeFrame: {
         const int intLimit = 100;
         long lngChartNext; // variables for chart ID
         long lngChartPrior = ChartFirst();
         long lngChartCurrPeriod = 0; //The variable for a chart with the current chart's period.
         int intPeriodCurr = Period(); //Remember the period (time frame) of current chart.
         int i = 0;
         while (i < intLimit) { // We have certainly not more than 100 open charts
            lngChartNext = ChartNext(lngChartPrior); // Get the new chart ID by using the previous chart ID
            if (lngChartNext < 0) break; // Have reached the end of the chart list
            int intPeriodNext = ChartPeriod(lngChartNext); //The period of the next chart.
            if (activateIndicatorTF(intPeriodNext, lngChartNext)) { // To activate indicator containing vs. maxiimal TF charts?
               showWindow(lngChartNext, showMaximized); //Show that window.
               if (intPeriodNext == intPeriodCurr) lngChartCurrPeriod = lngChartNext; //Remember the chart with the initially current chart's period.
            }
            lngChartPrior = lngChartNext; // Let's save the current chart ID for the ChartNext()
            i++; // Do not forget to increase the counter
         }  
         showWindow(lngChartCurrPeriod, showNormal); //KTB SetFocus((int)lngChartCurrPeriod); //Show the chart with the initially current chart's period.
         //KTB SetFocus((int)lngChartCurrPeriod);
         restoreWindow(); // Restore an MDI-child widnow maximised by pressing Alt+NumMinus, Enter.
         break;
}  }  }

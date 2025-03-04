#property strict

#include <WinUser32.mqh>
#import "MTQC.dll"
   void saveSizePicture(string strPictureName); //Save a picture and make its size actual in Windows Photo Viewer.
   void altDown(int _); // Press and hold Alt.
   void altUp(int _); // Release Alt.   
#import "user32.dll"
   int GetLastActivePopup(int hWnd);
   int GetAncestor(int hWnd, int gaFlags);    
   void keybd_event(int bVk, int bScan, int dwFlags, int dwExtraInfo); //http://www.forexfactory.com/showthread.php?t=468143        http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
#import   

#include "enumerators.mqh"
#include "functions.mqh"
#include "constants.mqh"
#include "object.mqh"
#include "objects.mqh"

void postMessage(enmWM wmCommand) { PostMessageA(WindowHandle(Symbol(), Period()), WM_COMMAND, wmCommand, 0); } // The PostMessageA command. +------------------------------------------------------------------+

bool containsIndicator(long lngChartID, string strIndicatorName) { // Does a chart contain an indicator on the main chart subwindow? +------------------------------------------------------------------+
   const int intSubWindow = 0; //Look up the indicarot on the main chart subwindow only.
   for (int i = 0; i < ChartIndicatorsTotal(lngChartID, intSubWindow); i++) { //Look up the indicarot on the main chart subwindow only sub_window of ChartIndicatorsTotal = 0.
      if (ChartIndicatorName(lngChartID, intSubWindow, i) == strIndicatorName) return true; //Is this the indicator sought?
   }
   return false;
}

bool isAnyObjectSelected(string& strSingleObject) { // Return true if any object is selected. If there is only one selected return its name. +------------------------------------------------------------------+
   strSingleObject = "";
   int intCount = 0; //The selected objects count.
   for (int i = 0; i < ObjectsTotal(); i++) { //Find selected objects.
      string strObjectName = ObjectName(i);
      graphObject objGraphObject(strObjectName);
      //if (objGraphObject.isSelected()) { //Is it selected?
      if (objGraphObject.getSelected()) { //Is it selected?
         if (intCount++ == 0) strSingleObject = strObjectName; //Remember the object selected.
         else {
            strSingleObject = "";
            break; //Stop, if there are more than one object selected.
   }  }  }
   return intCount > 0;
}

void keyPressedEsc() { // +------------------------------------------------------------------+
   string _;
   if (isAnyObjectSelected(_)) postMessage(wmEsc); //Is any object selected to be unselected? //Графики -> Объекты -> Снять все выделения @ http://ruforum.mt5.com/threads/892-arhiv-mql4-besplatnoe-napisanie-programm?p=10823666&viewfull=1 and @ http://forum.mql4.com/ru/9807
}

/*KTB void deleteSelectedObjects() { // Delete all selected objects. +------------------------------------------------------------------+
   for (int i = ObjectsTotal(); i >= 0; i--) { //Find selected objects. Loop backwards because deleting causes skipping a following object after the one being deleted.
      graphObject objGraphObject(ObjectName(i));
      if (objGraphObject.isSelected()) objGraphObject.deleteFromChart(); //Is it selected?
   }
}*/

bool moveObject(int intKeyNavigation) { // Move selected objects up by the up arrow key press +------------------------------------------------------------------+
   string strObjectMoved;
   isAnyObjectSelected(strObjectMoved);
   if (strObjectMoved != "") { //Contunue, if there is only one object selected.
      graphObject objGraphObjectMoved(strObjectMoved);
      if (objGraphObjectMoved.isMovable()) { //Conitnue, if the object movable.
         switch (intKeyNavigation) {
            case keyArrowUp: case keyR: objGraphObjectMoved.moveUp(); break;//Move a selected object up.
            case keyArrowDown: case keyF: objGraphObjectMoved.moveDown(); break; //Move a selected object down.
            case keyArrowLeft: case keyA: objGraphObjectMoved.moveLeft(); break;//Move a selected object up.
            case keyArrowRight: case keyG: objGraphObjectMoved.moveRight(); //Move a selected object down.
      }  }
      return true;
   }
   return false;
}

void savePicture() { // Save the chart as a picture. Affix its name with the indicator letter and/or day time frame letter. 
   const ENUM_TIMEFRAMES  intPeriodMax = PERIOD_H4;
   const string strIndicator = "Alligator(13,8,5)"; //The indicator sought that the picture file name will be affixed with.
   const string strDayAffix = " d"; //The day affix.
   
   datetime dtmTimeLocal = TimeLocal();
   string strPictureName = formatInteger(TimeHour(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec) + " " + formatInteger(TimeMinute(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec); //The current hour and the minute.
   strPictureName = StringConcatenate(strPictureName, " ", formatInteger(TimeSeconds(dtmTimeLocal), gsttVariousConsts.lengthHrMinSec)); //Affix it with the seconds.
   /*KTB 
   if (containsIndicator(ChartID(), strIndicator)) //Does a chart contain an indicator on the main chart subwindow? 
      string strIndicatortLetter1 = StringConcatenate(" ",  StringSubstr(strIndicator, 0, 1)); //The 1st letter of the indicator sought.
      StringToLower(strIndicatortLetter1); //Lower the 1st letter.
      StringAdd(strPictureName, strIndicatortLetter1); //Affix the indicator letter.
   */
   if (Period() > intPeriodMax) //Is the timeframe larger than the maximal one needed? 
      StringAdd(strPictureName, strDayAffix); //Affix it with the day affix.
   postMessage(wmSavePicture); //Call the Save as picture menu command.
   keybd_event(keyEnter, 0, 0, 0); //Press Enter in the the Save As Picture dialogue box.
   Sleep((int)GlobalVariableGet(gsttVariousConsts.CtrlVsleep)); //Let the the Save As Picture dialogue box appear.
   saveSizePicture(strPictureName); //Save a picture and make its size actual in Windows Photo Viewer.
}

void login() { // Login to an account using EA @ https://www.mql5.com/en/forum/110932/page2 //+------------------------------------------------------------------+
   const int intPasswordLengthMax = 8; //The length of the password.
   const int intSleep = 500; //The total time the login dialogue box will be displayed.
   int hterminal = GetAncestor(WindowHandle(Symbol(), Period()), 2);          
   if(hterminal != 0) {
      int hwindow = GetLastActivePopup(hterminal);
      PostMessageA(hwindow, WM_COMMAND, wmLogin, 0); // OR use PostMessageA (hwindow, WM_COMMAND, 0x8A65,-0x30107D); //Open Login dialog window
      /*KTB (it doesn't work) if (hwindow != 0) {
         PostMessageA(hwindow, WM_COMMAND, vkTab, 0); //Cursor first field
         PostMessageA(hwindow, WM_COMMAND, vkTab, 0); //Cursor to password field
      }*/  
      if (!IsConnected()) {
         Sleep(intSleep / 2);
         keybd_event(keyEnter, 0, 0, 0); //Press Enter, unless connected, to start connecting.
      }else { //Disconnect.
         int intSleepStep = intSleep / (intPasswordLengthMax + 2); //A single sleep session per disconnecting step to let MT4 digest key strokes.
         Sleep(intSleepStep);
         keybd_event(keyTab, 0, 0, 0); //Naviate to the password textbox.
         for (int i=0; i < intPasswordLengthMax; i++) {
            Sleep(intSleepStep);
            keybd_event(keyDel, 0, 0, 0); //Press Del as many times as the number of symbols in the longest password.
         }
         Sleep(intSleepStep);
         keybd_event(keyEnter, 0, 0, 0); //Press Enter to start disconnecting.
}  }  }

long chartWindowsHandle(long lngChartID) { // Chart window handle (HWND) //Как в скрипте активировать окно с нужным символом? @ https://www.mql5.com/ru/forum/22244 +------------------------------------------------------------------+
   long lgnResult = -1; // Prepare the variable to get the property value
   ResetLastError(); // Reset the error value
   if (!ChartGetInteger(lngChartID, CHART_WINDOW_HANDLE, 0, lgnResult)) Print(__FUNCTION__ + ", Error Code = ", GetLastError()); // Receive the property value // Display the error message in Experts journal
   return(lgnResult); // Return the value of the chart property
}

void showWindow(long lngChartID, enmNCmdShow intShow) { ShowWindow( GetParent((int)chartWindowsHandle(lngChartID)), intShow ); } // Show a window. // ShowWindow. 1 - Activates and displays a window. 2 - Activates the window and displays it as a minimized window. 3 - Activates the window and displays it as a maximized window. +------------------------------------------------------------------+

void maximizeOrRestore(enmNCmdShow intShow) { // Maximize or restore the current window. Save the last state. +------------------------------------------------------------------+
  showWindow(ChartID(), intShow); //Show the current window.
  GlobalVariableSet(gsttVariousConsts.activateMaximizeRestore, intShow);
}

void maximizeOrRestoreSwitch() { // Switch maximizing or restoring the current window. Save the last state. 
   switch ((enmNCmdShow)GlobalVariableGet(gsttVariousConsts.activateMaximizeRestore)) {
      case showNormal: 
         maximizeOrRestore(showMaximized); 
         break;
      case showMaximized: 
         maximizeOrRestore(showNormal);
         break;
   }
   keybd_event(keyEnter, 0, 0, 0); //Press Enter before pressing Esc. Otherwise the advisor process Esc as an ordinary Esc resetting (cancels objects, deselects them, etc.). 
   keybd_event(keyEsc, 0, 0, 0); //Close the Fast Navigation box the Space key has opened.
}

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
            if (containsIndicator(lngChartNext, IndicatorSought) != blnContainsIndicator) 
               return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
         }
         break;
      case ActivateTimeFrame: {
         static int intDiffTarget = (TimeFrameMax - Period()) * (-1); //The difference between the current and the maximal period. //The target difference, i.e. the negative to the current.      
         if (TimeFrameMax - intPeriodNext < intDiffTarget) { //Is the timeframe smaller or equal to the maximal one needed?
            if (containsIndicator(lngChartNext, IndicatorSought) == blnContainsIndicator) 
               return true; //Does/doesn't a chart contain an indicator on the main chart subwindow?
         }  
      }  
   }
   return false; 
}

void activateCharts() { //Activate or switch the daily-intraday time frame windows or indicator containing windows back and forth. This is the ActivateCharts.mq4 sctrips built-in to the EA. The code is built-in because the scripts' short-cut (Alt+D/F) do not work due to overlapping the AutoIt automatic Alt holding.
   const int intLimit = 100;
   long lngChartNext; // variables for chart ID
   long lngChartPrior = ChartFirst();
   long lngChartCurrPeriod = 0; //The variable for a chart with the current chart's period.
   int intPeriodCurr = Period(); //Remember the period (time frame) of current chart.
   int i = 0;
   
   altDown(0); // Press and hold Alt to restore the windows' size to normal at the end.     
   while (i < intLimit) { // We have certainly not more than 100 open charts
      lngChartNext = ChartNext(lngChartPrior); // Get the new chart ID by using the previous chart ID
      if (lngChartNext < 0) 
         break; // Have reached the end of the chart list
      int intPeriodNext = ChartPeriod(lngChartNext); //The period of the next chart.
      if (activateIndicatorTF(intPeriodNext, lngChartNext)) { // To activate indicator containing vs. maxiimal TF charts?
         showWindow(lngChartNext, showMaximized); //Show that window.
         if (intPeriodNext == intPeriodCurr) lngChartCurrPeriod = lngChartNext; //Remember the chart with the initially current chart's period.
      }
      lngChartPrior = lngChartNext; // Let's save the current chart ID for the ChartNext()
      i++; // Do not forget to increase the counter
   }  
   showWindow(lngChartCurrPeriod, showNormal); //KTB SetFocus((int)lngChartCurrPeriod); //Show the chart with the initially current chart's period.
   restoreWindow(); // Restore an MDI-child widnow maximised by pressing Alt+NumMinus, Enter. 
   altUp(0); // Release Alt.
}

void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam) { //+------------------------------------------------------------------+
   int intOperation = gsttVariousConsts.operationNull;
   switch (id) {
      case CHARTEVENT_OBJECT_CREATE: case CHARTEVENT_OBJECT_CHANGE: case CHARTEVENT_OBJECT_DRAG: {
         graphObject objGraphObject(sparam);
         objGraphObject.setPriceRound();
      } 
      case CHARTEVENT_KEYDOWN: 
         switch((int)lparam) {
            case keyEsc: //Escape pressed? //Unselect all objects / disable them / close position. 
               keyPressedEsc(); 
               break; 
            case keyR: //Move a selected object up. 
               moveObject((int)lparam); 
               break; 
            case keyF: //Move a selected object down. 
               moveObject((int)lparam); 
               break; 
            case keyArrowUp: case keyArrowDown: //Move a selected object up.
               keybd_event(keyEnd, 0, 0, 0); //Return the chart back by simulating an End key stroke after pressing a navigation key.
               moveObject((int)lparam); 
               break;  
            case keyArrowLeft: case keyArrowRight: case keyA: case keyG: //Return the chart back by simulating an End key stroke after pressing a navigation key.
               if (moveObject((int)lparam)) 
               keybd_event(keyEnd, 0, 0, 0); 
               break; 
            case keyD: //Delete selected objects by pressing the Del key. Unlike the deleteSelectedObjects function the Del key enables restoring the objects deleted by pressing Ctrl+Z.
               keybd_event(keyDel, 0, 0, 0); 
               break; 
            case keyZ: 
               postMessage(wmCrossHair); 
               break;
            case keyQ: 
               postMessage(wmTrend); 
               break;
            case keyW: 
               postMessage(wmHLine); 
               break;
            case keyE: 
               postMessage(wmLeftArrow); 
               break;
            case keyV: 
               postMessage(wmVLine); 
               break;
            case key1: 
               postMessage(wmRectangle); 
               break;
            case key2: 
               //KTB postMessage(wmFibonacci); 
               postMessage(wmRegression);
               break;
            case keyX: // Save the chart as a picture. 
               savePicture(); 
               break; 
            case keyTab: //Open the login dialogue box.
               login(); 
               break; 
            case keySpace: 
               maximizeOrRestoreSwitch(); 
               break;
            case keyF5:
               activateCharts(); //Activate or switch the daily-intraday time frame windows or indicator containing windows back and forth.
               break;               
         }  
   }     
}     

void enableObjectCreateDeleteEvents(ENUM_CHART_PROPERTY_INTEGER intCreateDelete) { // Enables the mode of sending messages concerning the event of a graphic object creation to all mql4 applications on the chart. //+------------------------------------------------------------------+
   ResetLastError();
   if (!ChartSetInteger(0, intCreateDelete, true)) 
      Alert(__FUNCTION__ + ", Error Code = ", GetLastError()); // Enables the mode of sending messages concerning the event of a graphic object creation/deletion to all mql4 applications on the chart. 
}

void OnInit() { //+------------------------------------------------------------------+
   const int intCtrlVsleep = 700;
   enableObjectCreateDeleteEvents(CHART_EVENT_OBJECT_CREATE); // Enables the mode of sending messages concerning the event of a graphic object creation to all mql4 applications on the chart. 

   if (!GlobalVariableCheck(gsttVariousConsts.CtrlVsleep)) 
      GlobalVariableSet(gsttVariousConsts.CtrlVsleep, intCtrlVsleep); 
   if (!GlobalVariableCheck(gsttVariousConsts.activateMaximizeRestore)) 
      GlobalVariableSet(gsttVariousConsts.activateMaximizeRestore, showNormal); //Check/set the last window state.            
}
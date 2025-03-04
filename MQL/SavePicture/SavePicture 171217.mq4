#include <WinUser32.mqh>
#import "MTQC.dll"
   void textToClipboard(string); // Copy text to clipboard. @ http://www.cplusplus.com/forum/beginner/14349/
#import "user32.dll"
   int GetLastActivePopup(int hWnd);
   int GetAncestor(int hWnd, int gaFlags);    
   void keybd_event(int bVk, int bScan, int dwFlags, int dwExtraInfo); //http://www.forexfactory.com/showthread.php?t=468143        http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
#import   
#property strict

enum enmKeys { keyTab = 9, keyEnter = 13, keyEsc = 27, keySpace = 32, keyEnd = 35, keyArrowLeft = 37, keyArrowUp, keyArrowRight, keyArrowDown, keyDel = 46, key0 = 48, key1, key2, key3, key4, key5, key6, key7, key8, key9,  keyA = 65, keyB, keyC, keyD, keyE, keyF, keyG, keyQ = 81, keyR, keyS = 83, keyT, keyV = 86, keyW, keyX, keyZ = 90, key0Num = 96, key1Num, key2Num, key3Num, key4Num, key5Num, key6Num, key7Num, key8Num, key9Num, /*keyNumMinus = 109, keyNumSlash = 111,*/ keyF5 = 116 /*keyTilde 192*/};
enum enmWM { wmSavePicture = 33054, wmCrossHair = 33233, wmHLine = 33244, wmTrend = 33257, wmLogin = 35429, wmEsc = 35462, wmLeftArrow }; //The PostMessageA codes @ https://forum.mql4.com/ru/14463

struct variables { 
   const int idx_1; 
   const int idx0; 
   const int operationNull; 
   const string msgWrongOrder; 
   string formatDecimals;
   const string priceSeparator;
   const int lengthPrice;
   const int lengthLots;   
   const int lengthHrMinSec;
   const string lots;
   const string safetyLock;
   const string tradeFlag;
   const string activateMaximizeRestore;
   const string CtrlVsleep;
   /*KTB const string KTB_Swap; 
   const int KTB_SwapYes; 
   const int KTB_SwapNo;*/
   int KTB_Ticket; 
}; 
variables msttVariousConsts = {
   -1, 
   0, 
   -1, 
   "Wrong order type!",    
   "",                           
   ",",
   6,
   6,
   2,
   "Lots",
   "SafetyLock",
   "t",
   "ActivateMaximizeRestore",
   "CtrlVsleep",
   /*KTB "Swap_Yes1_No0",     
   1,                      
   0,*/                
}; 

const string mstrTimeActive = "TimeActive";
const string mstrTimeActivePrior = "TimeActivePrior"; //Time active prior.
const string mstrTimeActiveIncrement = "TimeActiveIncrement"; //Time active increment.

string formatInteger(int intNumber, int intLength) { return StringFormat( StringConcatenate("%0", intLength, "u"), intNumber ); } // Format an interger number with a specified length and if necessa leading zeroes. //"%06.2f" - "0" denotes leading zeroes (e.g. 099), '6' denotes the width (e.g. 123.45), '.2' denotes 2 decimal digits after the decimal point, 'f' denotes a double number type ('u' - unsigned decimal integer ). +------------------------------------------------------------------+

void postMessage(enmWM wmCommand) { PostMessageA(WindowHandle(Symbol(), Period()), WM_COMMAND, wmCommand, 0); } // The PostMessageA command. +------------------------------------------------------------------+

void savePicture() { // Save the chart as a picture. Affix its name with the indicator letter and/or day time frame letter. +------------------------------------------------------------------+
   datetime dtmTime0 = 0;
   int intIncrement = 0;
   if (GlobalVariableCheck(mstrTimeActive)) { //Is this a simulatore mode?
      double dblTime0 = GlobalVariableGet(mstrTimeActive); //The latest bar's time that Simulator sets on every tick.
      dtmTime0 = (datetime)dblTime0;
      if (GlobalVariableGet(mstrTimeActivePrior) == dblTime0) //Is that the same bar that has been saved before?
         intIncrement = (int)GlobalVariableGet(mstrTimeActiveIncrement) + 1;
      GlobalVariableSet(mstrTimeActivePrior, dblTime0);
      GlobalVariableSet(mstrTimeActiveIncrement, intIncrement); //Save TimeActiveIncrement for the future.
   } else
      dtmTime0 = Time[0]; //The latest bar's time.
   string strPictureName = 
      formatInteger(TimeHour(dtmTime0), msttVariousConsts.lengthHrMinSec) 
      + " " + formatInteger(TimeMinute(dtmTime0), msttVariousConsts.lengthHrMinSec) 
      + " " + formatInteger(intIncrement, msttVariousConsts.lengthHrMinSec); //The current hour and the minute.
   textToClipboard(StringConcatenate(strPictureName, " ")); //Put the file name to the clipboard. Add " " at the end because by some reason the last symbol gets lost when putting into the clipboard.
   postMessage(wmSavePicture); //Call the Save as picture menu command.
   keybd_event(keyEnter, 0, 0, 0); //Press Enter in the the Save as picture dialogue box.
   Sleep((int)GlobalVariableGet(msttVariousConsts.CtrlVsleep));
   keybd_event(keyV, 0xAF, 0 , 0); // ‘V’ Press
   keybd_event(keyEnter, 0, 0, 0); //Press Enter in the the Save as picture dialogue box.
}

void OnStart() { // Save the chart as a picture. Affix its name with the indicator letter and/or day time frame letter. +------------------------------------------------------------------+
   if (GlobalVariableCheck(mstrTimeActive)) { //Is this a simulatore mode?
      if (!GlobalVariableCheck(mstrTimeActivePrior)) //Normally unnecessary but for an ultimate robustness, make sure Simulator also has arranged TimeActivePrior.
         GlobalVariableTemp(mstrTimeActivePrior);
      if (!GlobalVariableCheck(mstrTimeActiveIncrement)) //Arrange or make sure TimeActivePriorIncrd has been arranged.
         GlobalVariableTemp(mstrTimeActiveIncrement);
   }
   savePicture(); // Save the chart as a picture.
}

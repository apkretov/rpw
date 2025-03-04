#include <WinUser32.mqh>
#import "user32.dll"
    int GetParent(int hWnd);
    int GetLastActivePopup(int hWnd);
    int GetDlgItem(int hDlg, int nIDDlgItem);
#import   
#property strict
#define keyEsc 27

bool isAnyObjectSelected() { // Return true, if at least one object is selected. +------------------------------------------------------------------+
   for (int i = 0; i < ObjectsTotal(); i++) {
      if (ObjectGet(ObjectName(i), OBJPROP_SELECTED)) return true;
   }
   return false;    
}

void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam) { //+------------------------------------------------------------------+
   if (id == CHARTEVENT_KEYDOWN) {
      if((int)lparam == keyEsc) if (isAnyObjectSelected()) PostMessageA(WindowHandle(Symbol(), Period()), WM_COMMAND, 35462, 0); //Is any object selected to be unselected? //Графики -> Объекты -> Снять все выделения @ http://ruforum.mt5.com/threads/892-arhiv-mql4-besplatnoe-napisanie-programm?p=10823666&viewfull=1 and @ http://forum.mql4.com/ru/9807
   }
}

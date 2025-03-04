#property strict

#ifndef GRAPHOBJECT_MQH
#define GRAPHOBJECT_MQH

#include "constants.mqh"

class graphObject { //TO DO: Here and in the other classes: Separate class member function definitions from their implementation (as in C++ class1.h, class1.cpp). Use inlining whereever a member function is rather short. That is leave its defenition in the declaration (in class1.h) as it's currently the case.   
   void moveUpDown(int intUpDown) const { // Move the object up. 
      double dblPoints = _Point * intUpDown * TickStep;
      switch (ObjectType(name)) {
         case OBJ_TREND: 
         case OBJ_RECTANGLE:
            ObjectSet(name, OBJPROP_PRICE2, ObjectGet(name, OBJPROP_PRICE2) + dblPoints);
         case OBJ_HLINE: 
         case OBJ_ARROW: 
            setPriceHLineArrow(getPriceHLineArrow() + dblPoints);
      }  
   }
   
   void moveLeftRight(int intLeftRight) const { // Move the object to the left/right. 
      double dblPoints = _Period * 60 * intLeftRight;
      switch (ObjectType(name)) {
         case OBJ_TREND: case OBJ_RECTANGLE:
            ObjectSet(name, OBJPROP_TIME2, ObjectGet(name, OBJPROP_TIME2) + dblPoints);
         case OBJ_ARROW: case OBJ_VLINE: 
            ObjectSet(name, OBJPROP_TIME1, ObjectGet(name, OBJPROP_TIME1) + dblPoints);
      }  
   } 
        
public:
   string name;
   graphObject(string strName) : name(strName) { //https://www.mql5.com/en/forum/7383 //TO DO: Here and below: "name = strName" is unnecessary according to the functionality of the member initialisation list ("name(strName)"). 
   	name = strName; 
   } 
   
   graphObject(string strNameArrow, datetime dtmTime1, double dblPrice1) : name(strNameArrow) { // Create a new arrow. 
      const long lngArrowCode = 5; //The left-text arrow code.
      name = strNameArrow;
      ObjectCreate(0, strNameArrow, OBJ_ARROW, 0, dtmTime1, dblPrice1); //Place a buy/sell stop at ResumeRange points above/below the current price.
      ObjectSetInteger(0,strNameArrow, OBJPROP_ARROWCODE, lngArrowCode); // Set the arrow code
      setColourWhite();
   } 
   
   graphObject(string strNameLabel, long lngX, long lngY) : name(strNameLabel) { // Create a label. //TO DO: Use the member initialisation list to ininialise the class members. 
      const long lngFontSize = 8;
      name = strNameLabel;
      ObjectCreate(0, strNameLabel, OBJ_LABEL, 0, 0, 0);
      setDescription("");
      setColourWhite();
      setXDdistance(lngX);
      setYDdistance(lngY);
      setFontSize(lngFontSize);
      setHidden();
      setUnselectable();
   } 
   
   void rename_(string strNewName) { 
      ObjectSetString(0, name, OBJPROP_NAME, strNewName);
      name = strNewName;     
   } 
   
   void setDescription(string strDescr) const { //TO DO: A set member function cannot be const. It shows that the member function is redundant. Instead, get the pointer to the MQL graph object only and set its decription via its standard method. GRO similar redundancy everywhere.
      ObjectSetString(0, name, OBJPROP_TEXT, strDescr); 
      } 
   
   void setDescription(int intDescr) const { 
      ObjectSetString(0, name, OBJPROP_TEXT, (string)intDescr); 
      } 
   
   string getDescription() const { 
      return ObjectGetString(0, name, OBJPROP_TEXT); 
   } 
   
   double getPrice() const { //Get the price of the graph object
      double dblPrice = 0;
      switch (ObjectType(name)) {
         case OBJ_HLINE: 
         case OBJ_ARROW: 
            dblPrice = getPriceHLineArrow(); 
            break;
         case OBJ_TREND: 
            dblPrice = ObjectGetValueByShift(name, gsttVariousConsts.idx0);
            break;
      }
      return dblPrice;
   }
   
   double getPriceHLineArrow() const { //TO DO: Make it public.
      return ObjectGet(name, OBJPROP_PRICE1);
   }    
   
   void setPriceHLineArrow(double dblPrice) const { 
      ObjectSet(name, OBJPROP_PRICE1, NormalizeDouble(roundToTickStep(dblPrice), _Digits));
   }       
   
   void setPriceRound() const { // Set a round price of a horizontal line or an arrow object. //TO DO: Remove this redundant function. Use setPrice.
      int intObjectType = ObjectType(name);
      switch(intObjectType){
         case OBJ_RECTANGLE:
            ObjectSet(name, OBJPROP_PRICE2, NormalizeDouble(ObjectGet(name, OBJPROP_PRICE2), _Digits));
         case OBJ_HLINE: 
         case OBJ_ARROW:
            setPriceHLineArrow(getPriceHLineArrow());
      }
   }
     
   bool getSelected() const {
      return (bool)(ObjectGet(name, OBJPROP_SELECTED)); 
   }
   
   void setSelected(bool blnSelected) const {
      ObjectSet(name, OBJPROP_SELECTED, blnSelected); 
   }    
   
   void setColourWhite() const { 
      ObjectSet(name, OBJPROP_COLOR, clrWhite); 
   } 
   
   void setColourGray() const { 
      ObjectSet(name, OBJPROP_COLOR, clrGray); 
   } 
   
   int getColour() const { 
      return (int)ObjectGet(name, OBJPROP_COLOR); 
   }
   
   void setXDdistance(long lngX) const { 
      ObjectSetInteger(0, name, OBJPROP_XDISTANCE, lngX); 
   } 
   
   void setYDdistance(long lngY) const { 
      ObjectSetInteger(0, name, OBJPROP_YDISTANCE, lngY); 
   } 
   
   void setFontSize(long lngSize) const { 
      ObjectSetInteger(0, name, OBJPROP_FONTSIZE, lngSize); 
   } 
   
   void setHidden() const { //Don't show the name of a graphical object in the list of objects. @ http://indo.mt5.com/showthread.php?32830-MQL4-600-Hide-and-Unselectable-Object
      ObjectSet(name, OBJPROP_HIDDEN, true); 
   } 
     
   void setUnselectable() const { //Don't let an object be selected by mouse-double click. 
      ObjectSet(name, OBJPROP_SELECTABLE, false); 
   } 

   bool isOperational() const { // Is the object operational? 
      switch (ObjectType(name)) {
         case OBJ_ARROW: case OBJ_HLINE: case OBJ_TREND: 
            return true; 
            break;
         default: 
            return false;
      }  
   } 

   bool isMovable() const { // Is the object movable? 
      switch (ObjectType(name)) {
         case OBJ_ARROW: case OBJ_HLINE: case OBJ_TREND: case OBJ_VLINE: case OBJ_RECTANGLE:
            return true; 
            break;
         default: 
            return false;
      }  
   } 

   void moveUp() const { // Move the object up. 
      moveUpDown(1); 
   } 
   
   void moveDown() const { // Move the object down. 
      moveUpDown(-1); 
   } 
   
   void moveLeft() const { // Move the object to the left. 
      moveLeftRight(-1); 
   } 
   
   void moveRight() const { // Move the object to the right. 
      moveLeftRight(1); 
   } 
   
   void deleteFromChart() const {
      ObjectDelete(0, name);
   } 
};

#endif //GRAPHOBJECT_MQH 
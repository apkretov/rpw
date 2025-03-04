#property strict

extern string TimeDelay = "2050.01.01 00:00";
const string mstrDelay = "Delay";
const string mstrDelayLong = "DelayLong";
const string mstrTimeDelay = "TimeDelay";
const string mstrTimeAcitve = "TimeActive";

void delay() { //+------------------------------------------------------------------+
   long j = 0, lngDelay = (long) GlobalVariableGet(mstrDelay);
   if (Time[0] >= MathMin(StringToTime(TimeDelay), GlobalVariableGet(mstrTimeDelay))) lngDelay = (long) GlobalVariableGet(mstrDelayLong);
   for (long i = 0; i < lngDelay; i++) {j++;}
}

void OnTick() { //+------------------------------------------------------------------+
   static datetime dtmM1priorTime;
   datetime dtmTimeM1 = Time[0];
   if (dtmTimeM1 > dtmM1priorTime) { //has a new bar opened?
      dtmM1priorTime = dtmTimeM1; //remember the current bar openning time for the future
      GlobalVariableSet(mstrTimeAcitve, Time[0]);
      Comment("Time[0]: ", Time[0], "   long: ", (long) GlobalVariableGet(mstrTimeAcitve));
   }
   delay();
}

void OnInit() { //+------------------------------------------------------------------+
   const long lngDelay = 1000000;
   const long lngDelayLong = 10000000000;
   GlobalVariableTemp(mstrDelay);
   GlobalVariableSet(mstrDelay, lngDelay);
   GlobalVariableTemp(mstrDelayLong);
   GlobalVariableSet(mstrDelayLong, lngDelayLong);
   GlobalVariableTemp(mstrTimeDelay);
   GlobalVariableSet(mstrTimeDelay, StringToTime(TimeDelay));
   GlobalVariableTemp(mstrTimeAcitve);
}
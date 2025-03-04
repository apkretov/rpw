#property strict

input string TimeDelay = "2050.01.01 00:00";
const string mstrDelay1BeforeSuspense = "Delay1BeforeSuspense";
const string mstrDelay2AfterSuspense = "Delay2AfterSuspense";
const string mstrTimeDelay = "TimeDelay";
const string mstrTimeActive = "TimeActive";

void delay() {
   const string strSuspend = "sus";
   const int intMultiplicator = 250000;
   long lngDelay = (long)GlobalVariableGet(mstrDelay1BeforeSuspense) * intMultiplicator;
   if (ObjectFind(strSuspend) == 0) {
      if (Time[0] >= ObjectGet(strSuspend, OBJPROP_TIME1)) 
         lngDelay = (long)GlobalVariableGet(mstrDelay2AfterSuspense) * intMultiplicator;
   } else if (Time[0] >= MathMin(StringToTime(TimeDelay), GlobalVariableGet(mstrTimeDelay))) 
      lngDelay = (long)GlobalVariableGet(mstrDelay2AfterSuspense) * intMultiplicator;
   for (long i = 0; i < lngDelay; ++i);	   
}

void OnTick() {
   static datetime dtmM1priorTime;
   datetime dtmTimeM1 = Time[0];
   if (dtmTimeM1 > dtmM1priorTime) { //has a new bar opened?
      dtmM1priorTime = dtmTimeM1; //remember the current bar openning time for the future
      GlobalVariableSet(mstrTimeActive, Time[0]);
      Comment("Time[0]: ", Time[0], "   long: ", (long)GlobalVariableGet(mstrTimeActive));
   }  
   delay();
}

void OnInit() {
   //const int intDelay = 1000;
   const int intDelay1BeforeSuspense = 1000;
   const int intDelay2AfterSuspense = 1000;
   GlobalVariableTemp(mstrDelay1BeforeSuspense);
   GlobalVariableSet(mstrDelay1BeforeSuspense, intDelay1BeforeSuspense);
   GlobalVariableTemp(mstrDelay2AfterSuspense);
   GlobalVariableSet(mstrDelay2AfterSuspense, intDelay2AfterSuspense);
   GlobalVariableTemp(mstrTimeDelay);
   GlobalVariableSet(mstrTimeDelay, StringToTime(TimeDelay));
   GlobalVariableTemp(mstrTimeActive);
}
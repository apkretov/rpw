#property indicator_chart_window
#property indicator_buffers 1
#property indicator_width1 /*1*/3
#property indicator_color1 /*DarkGray*/Yellow/*0*/
#property indicator_style1 /*STYLE_DOT*/STYLE_SOLID

input bool UseCloseForSupRes = true;
input datetime TimeBeg = 0/*D'2019.02.08 08:00'*/;
input datetime TimeEnd = 0/*D'2019.02.11 10:00'*/;

double LR_line[];

void shiftsBegEnd(int& intShiftBeg, int& intShiftEnd) { // Get the beginning and end shifts.
   const int intShiftDefault = 34/*21*//*3*//*2*/;
	if (TimeBeg != 0) //Check whehter TimeBeg has been input.
		intShiftBeg = iBarShift(NULL, PERIOD_CURRENT, TimeBeg);
	else //Set a default count;
		intShiftBeg = intShiftDefault;
	if (TimeEnd != 0) //Check whehter TimeEnd has been input.
		intShiftEnd = iBarShift(NULL, PERIOD_CURRENT, TimeEnd);
	else
		intShiftEnd = 0;	
}

int start() {
   double a, b, c, sumy = 0.0, sumx = 0.0, sumxy = 0.0, sumx2 = 0.0; // variables
   int i, x = 0, intShiftBeg = 0, intShiftEnd = 0, intBarCount = 0;
  	
   shiftsBegEnd(intShiftBeg, intShiftEnd); //Recompute intBarCount on fly because new bars keep appearing.
   intBarCount = intShiftBeg - intShiftEnd + 1; //Recompute intBarCount on fly because new bars keep appearing.
   
   for (i = intShiftEnd; i <= intShiftBeg; ++i) { // calculate linear regression.
      sumy += Close[i];
      sumxy += Close[i] * i;
      sumx += i;
      sumx2 += i * i;
   }  
   
   c = sumx2 * intBarCount - sumx * sumx;
   if (c == 0.0) {
      Alert("Error in linear regression!");
      return 0;
   }   
   b = (sumxy * intBarCount - sumx * sumy) / c; // Line equation
   a = (sumy - sumx * b) / intBarCount;
   for (i = 0; i < intBarCount; ++i) { // Linear regression line in buffer
      x = i + intShiftEnd;
      LR_line[x] = a + b * x;
   } 

   return(0);
}

int init() {
   IndicatorShortName("Linear regression channel");
   
   SetIndexStyle(0, DRAW_LINE);
   SetIndexBuffer(0, LR_line);
   SetIndexEmptyValue(0, 0.0);
   
   return 0;
}

int deinit() {  
   return(0);
}

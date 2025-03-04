//+------------------------------------------------------------------+
//|                                      LinearRegressionChannel.mq4 |
//|                                                           dimicr |
//|                                         http://www.signalsbg.com |
//|      SignalsBG.com - development of trading tools for Metatrader |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2008 signalsbg.com"
#property link      "http://www.signalsbg.com"
#property indicator_chart_window

#property indicator_buffers 3
#property indicator_width1 1
#property indicator_width2 1
#property indicator_width3 1
#property indicator_color1 Gold
#property indicator_color2 Aqua
#property indicator_color3 OrangeRed

extern bool UseClose = true;
extern int  BarsToCount = 21;
extern double Sup_Res_Adjustment = .975;

double LR_line[];
double Sup_line[];
double Res_line[];

int init() {
   IndicatorShortName("LinearRegressionChannel: " + BarsToCount);
   
   SetIndexStyle(0, DRAW_LINE);
   SetIndexBuffer(0, LR_line);
   SetIndexEmptyValue(0, 0.0);
   
   SetIndexStyle(1, DRAW_LINE);
   SetIndexBuffer(1, Sup_line);
   SetIndexEmptyValue(1, 0.0);
   
   SetIndexStyle(2, DRAW_LINE);
   SetIndexBuffer(2, Res_line);
   SetIndexEmptyValue(2, 0.0);
   
   return(0);
}

int deinit() {  
   return(0);
}

int start() {
   double a, b, c, // variables
          sumy = 0.0,
          sumx = 0.0,
          sumxy = 0.0,
          sumx2 = 0.0,
          h = 0.0, l = 0.0;   
   int x;
     
   /*ORIG
   for (int i = 0; i < BarsToCount; ++i) { // calculate linear regression
      sumy += Close[i];
      sumxy += Close[i] * i;
      sumx += i;
      sumx2 += i * i;
   }
   */
   for (int j = 0; j < BarsToCount; ++j) { // calculate linear regression.
      int i = j + 1; //Fix the regression line by calculating it from the prior bar vs. the current one.
      sumy += Close[i];
      sumxy += Close[i] * i;
      sumx += i;
      sumx2 += i * i;
   }  
   
   c = sumx2 * BarsToCount - sumx * sumx;
   if (c == 0.0) {
      Alert("Error in linear regression!");
      return 0;
   }
   
   b = (sumxy * BarsToCount - sumx * sumy) / c; // Line equation    
   a = (sumy - sumx * b) / BarsToCount;
   
   for (x = 0; x < BarsToCount; ++x) // Linear regression line in buffer
      LR_line[x] = a + b * x;
   
   if (UseClose) // Use PRICE_CLOSE for support-resistance
     for (x = 0; x < BarsToCount; ++x) {
       if (Close[x] - LR_line[x] > h) 
         h = Close[x] - LR_line[x];
       if (LR_line[x] - Close[x]> l) 
         l = LR_line[x] - Close[x];
     }  
   else // Use HIGH - LOW
     for (x = 0; x < BarsToCount; ++x) {
       if (High[x] - LR_line[x] > h) 
         h = High[x] - LR_line[x];
       if (LR_line[x] - Low[x]> l) 
         l = LR_line[x] - Low[x];
     }
   
   if (h > l) { // Drawing support - resistance lines   
     for (x = 0; x < BarsToCount; ++x) {
       Sup_line[x] = a - h + b * x;
       Res_line[x] = a + h + b * x;
     } 
   } else {
     for (x = 0; x < BarsToCount; ++x) {
       /*ORIG
       Sup_line[x] = a - l + b * x;
       Res_line[x] = a + l + b * x;
       */
       Sup_line[x] = (a - l + b * x) * (2 - Sup_Res_Adjustment); //Adjust the support by lifting it up to the standard deviation because my change to the indicator computation is not fully correct.
       Res_line[x] = (a + l + b * x) * Sup_Res_Adjustment; //Adjust the resistance by lowering it down to the standard deviation because my change to the indicator computation is not fully correct.
     }
   }
   
   LR_line[x]  = 0.0;
   Sup_line[x] = 0.0;
   Res_line[x] = 0.0;

   return(0);
}

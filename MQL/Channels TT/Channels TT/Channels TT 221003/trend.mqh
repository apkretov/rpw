#property strict
#ifndef TREND_MQH
#define TREND_MQH

#include "switch.mqh"

#ifdef REGRESSION

class trend {
	double cdblBarLengthAvr;
	double cdblBarLengthStdDev;
public:
	trend() : 
		cdblBarLengthAvr(0),
		cdblBarLengthStdDev(0)
	{}
	
	//Compute an average bar length within the trend and the standard deviation of trend bar lengths from their avarage one. The trend lasts from from RegressBegTime till mptrRegress.getTime2(). //Standard Deviation Formulas @ https://www.mathsisfun.com/data/standard-deviation-formulas.html
	//To calculate the standard deviation of those numbers:
	//1. Work out the Mean (the simple average of the numbers)
	//2. Then for each number: subtract the Mean and square the result
	//3. Then work out the mean of those squared differences.
	//4. Take the square root of that and we are done!
	void setBarLength(datetime dtmTime1, datetime dtmTime2) { 
		int intShift1 = iBarShift(NULL, PERIOD_CURRENT, dtmTime1);
		int intShift2 = iBarShift(NULL, PERIOD_CURRENT, dtmTime2);
		int intBars = intShift1 - intShift2 + 1;
		
		for (int i = intShift2; i <= intShift1; i++)
			cdblBarLengthAvr += MathAbs(Close[i] - Open[i]);
		cdblBarLengthAvr /= intBars;
		for (int i = intShift2; i <= intShift1; i++)
			cdblBarLengthStdDev += MathPow(((MathAbs(Close[i] - Open[i])) - cdblBarLengthAvr), 2);
		cdblBarLengthStdDev /= intBars;
		cdblBarLengthStdDev = MathSqrt(cdblBarLengthStdDev);
	}

	double getBarLengthAvr() const {
		return cdblBarLengthAvr;
	}

	double getBarLengthStdDev() const {
		return cdblBarLengthStdDev;
	}
};

#endif //REGRESSION

#endif //TREND_MQH
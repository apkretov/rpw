#include "alg.h"
//#include "functionsMT4.h"
using namespace mtqc;
#include "algEA.h"
using namespace mtqc::algEA;
//#include "constantsAlg.h"
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;

//extern const int gintIdx0; //constantsAlg
//extern const int MODE_GATORLIPS, MODE_GATORTEETH, MODE_GATORJAW;
//extern double Bid, Ask;

//double MathMax(double a, double b);
//double MathMin(double a, double b);
//double iAlligator(int intMode, int intShift);
//double iHigh(int intShift);
//double iLow(int intShift);
//double iClose(int intShift);
//datetime iTime(int intShift);
//int iBars();

//int distance_pts(double dblFrom, double dblTo, enmDirec intDirec); //functionsAlg
alg::alg(ENUM_TIMEFRAMES intTimeFrame, int intIdx) { initialise(intTimeFrame, intIdx); } //Get Alligator values, if the index is defined at the construction stage and get its location to the price. //+
/*inline*/ datetime alg::getSignalTime() const { return cdtmSignalTime; }
inline void alg::setSignalTime(const datetime& dtmSignalTime) { cdtmSignalTime = dtmSignalTime; }
inline double alg::getSignalPrice() const { return cdblSignalPrice; }
inline void alg::setSignalPrice(double dblSignalPrice) { cdblSignalPrice = dblSignalPrice; }

void alg::initialise(ENUM_TIMEFRAMES intTimeFrame, int intIdx) {
	cintTimeFrame = intTimeFrame;
	getSave(intIdx);
	getSetSaveDirec(intIdx);
}

enmDirec alg::setGetDirec(int intIdx) const { //the direction is defined based on where any bar prior to the specified one (intIdx) closes: above or below Alligator. //TO DO: Optimise the algorithm by keeping/uddating the pivot point only like in 1C. //+
	enmDirec intDirec = enmDirec::direc_up, intDirecUp = enmDirec::direc_up, intDirecDown = enmDirec::direc_down; //initialise with any direction just not to end up NULL in all of sudden
	int i = intIdx;
	while (i < iBars()) {
		if (distance_pts(high(i), iClose(i), intDirecUp) > 0) { //a bar closes above Alligator?
			intDirec = enmDirec::direc_up;
			break; //exit the loop as soon as a first closing outside Alligator occurs
		}
		else if (distance_pts(low(i), iClose(i), intDirecDown) > 0) { //a bar closes below Alligator? this solution didn't work out, I didn't check why
			intDirec = enmDirec::direc_down;
			break; //exit the loop as soon as a first closing outside Alligator occurs
		}
		i++;
	}
	return intDirec;
}

enmDirec alg::getSetSaveDirec(int intIdx) {
	cintDirec = setGetDirec(intIdx);
	return cintDirec;
}

inline double alg::lips_get( int intIdx) const { return iAlligator(MODE_GATORLIPS,  intIdx); }
inline double alg::teeth_get(int intIdx) const { return iAlligator(MODE_GATORTEETH, intIdx); }
inline double alg::jaws_get( int intIdx) const { return iAlligator(MODE_GATORJAW,   intIdx); }

double alg::getSave(int intIdx) { // TO DO: Rename intIdx to intShift here and in MT4. +
	cdblLips  = lips_get( intIdx); 
	cdblTeeth = teeth_get(intIdx); 
	cdblJaws  = jaws_get( intIdx); 
	return 0;
}

double alg::high() const { return MathMax(cdblLips, MathMax(cdblTeeth, cdblJaws)); } //the Alligator highest line value except dashed lips
double alg::high(int intIdx) const { return MathMax(lips_get(intIdx), MathMax(teeth_get(intIdx), jaws_get(intIdx))); } //the Alligator highest line value except dashed lips
double alg::low() const { return MathMin(cdblLips, MathMin(cdblTeeth, cdblJaws)); } //the Alligator lowest line value except dashed lips*/
double alg::low(int intIdx) const { return MathMin(lips_get(intIdx), MathMin(teeth_get(intIdx), jaws_get(intIdx))); } //the Alligator lowest line value except dashed lips

/*KTB
bool alg::time_frame_shift(ENUM_TIMEFRAMES intTimeFrame) {
	enmDirec intDirecPrior = cintDirec; //the prior direction
	deleteObjects(); //Delete all the objects created before.
	initialise(intTimeFrame, gintIdx0);
	signalGet();
	return cintDirec * intDirecPrior == 1; //the prior direction remained?
}*/

bool alg::signalGet() {
	int i = gintIdx0;
	do { i++; } while ((int)setGetDirec(i) * (int)cintDirec != -1); //an opposite direction from now on?
	do { i--; } while (setGetDirec(i) != cintDirec && i > gintIdx0); //cycle till the favourable direction begins but not beyond the current bar
	if (i == gintIdx0) {
		cdtmSignalTime = 0; //reset a signal time and price to flag no signal
		cdblSignalPrice = 0;
		return false; //the search has reached the current w/o a signal
	} else { //remember the signal
		cdtmSignalTime = iTime(i); //remember the signal bar
		cdblSignalPrice = cintDirec == enmDirec::direc_up ? iHigh(i) : iLow(i);
		return true;
}  }

/*inline*/ bool alg::signalOvercome() const { return distance_pts(cdblSignalPrice, Bid /*cobjCandlesByIndex->getClose(0)*/, cintDirec) > 0; } //Return true, if the signal has been overcome. //+

bool alg::signalTeethFarGetSave(int intSignalTeethFarness) { //Return true, if the signal is too far from the teeth. //TO DO: Split this opration into setting and getting. +
	if (distance_pts(cdblTeeth, Bid, cintDirec) > intSignalTeethFarness) cblnSignalTeethFar = true;
	return cblnSignalTeethFar;
}

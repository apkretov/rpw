#include "algEA.h"
#include <exception>
using std::exception;
#include "trend.h"
#include "alg.h"
#include "time.h"
#include "functions.h"
using namespace mtqc::functions;
using namespace mtqc;
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;
#include "messages.h"
#include "constants.h"
using namespace mtqc::constants;
#include "MT4QuikConnector.h"
using namespace mtqc::MT4QuikConnector;

//extern const int gintIdx0;
//extern double Bid;
//extern mtqc::time Time;
//extern const ENUM_TIMEFRAMES PERIOD_CURRENT;

//ENUM_POINTER_TYPE CheckPointer(const trend* const ptrTrend);
//void Alert(const string& strMessage);
//void keyPressedOperation(int intOperation);
//int BUYtoSELL(int intOperation);
//void message(const string& srtMessage);
//void messageException(const std::exception& objException);

namespace mtqc {
	//std::unique_ptr<trend> gobjTrend;
	namespace algEA {
		extern int SignalTeethFarness = 10; //MT4 version.
		extern int JawsReverseRange = 3; //MT4 version.
		extern int BreakEven = 20; //MT4 version.
		//extern double Lots = 0.1;
		//extern string TimeDelay = "2050.01.01 00:00";

		//const string mstrDelay = "Delay";
		//const string mstrDelayLong = "DelayLong";
		//const int gintIdx0 = 0;
		const ENUM_TIMEFRAMES mintPeriodCurrent = PERIOD_CURRENT;

		//enum enmAlgStates { alg_flat, alg_crossing, alg_moving_away, alg_ahead_of_dashed_lips };
		//enum enmFibo { fibo_1 = 1, fibo_3 = 3, fibo_5 = 5, fibo_8 = 8, fibo_13 = 13, fibo_21 = 21, fibo_34 = 34, fibo_55 = 55, fibo_89 = 89 };

		std::unique_ptr<trend> gobjTrend;

		//void message(const string& strMsg) {
		//	Print(strMsg);
		//	Comment(strMsg);
		//}

		//void message_v(string strMsg) {
		//	message(strMsg);
		//}

		//int round_to_pts(double dblValue) {
		//	return (int)MathRound(dblValue / Point);
		//}
		//int roundToPts(double dblValue);

		/*inline*/ double distance(double dblFrom, double dblTo, enmDirec intDirec) { return (dblTo - dblFrom) * (int)intDirec; }
		int distance_pts(double dblFrom, double dblTo, enmDirec intDirec) { return roundToPts((dblTo - dblFrom) * (int)intDirec); }

		void delay() { // It's kept for MT4 compatability. +
		}

		static bool delete_old_trend() { //delete the old trend, if a new signal appeared; return true, if deleted //TO DO: Rename it to something like newSignalAppeared etc. +
			static datetime dtmTimePrior; //avoid unnecessary computing at every tick, instead proceed once a bar on its opening
			datetime dtmTime = Time[gintIdx0];
			if (dtmTime > dtmTimePrior) { //has a new bar opened?
				dtmTimePrior = dtmTime; //remember the current bar openning time for the future
				alg objAlg(mintPeriodCurrent, gintIdx0); //monitore a start of an opposite direction
				if (objAlg.signalGet()) {
					if (objAlg.getSignalTime() > gobjTrend->alg_GetSignalTime()) {
						gobjTrend = nullptr; //A new signal appeared? Delete the old trend. //is it better to use shared_ptr.reset or operator =? @ http://stackoverflow.com/questions/14836691/is-it-better-to-use-shared-ptr-reset-or-operator
						return true;
					}
				}
			}
			return false; //not deleted.
		}

		#include "display.h"
		void OnTickAlg() {
			try {
				//MT4 version delay();
				if (CheckPointer(gobjTrend.get()) == ENUM_POINTER_TYPE::POINTER_INVALID) {
					messageMBFncNum(Bid);
					gobjTrend = std::make_unique<trend>(Bid); //a new trend began; create an object for it, unless available //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend //is it better to use shared_ptr.reset or operator =? @ http://stackoverflow.com/questions/14836691/is-it-better-to-use-shared-ptr-reset-or-operator
					messageMBFnc();
				}
				else {
					gobjTrend->alg_GetSave(gintIdx0); //otherwise refresh Alligator
				}
				
				switch (gobjTrend->getPhase()) {
				case enmPhases::phase_beginning:
					if (delete_old_trend()) OnTickAlg(); //the old trend has become obsolete; restart the procedure
					else { //trend exists
						if (gobjTrend->alg_SignalGet()) {
							if (!gobjTrend->alg_SignalTeethFarGetSave(SignalTeethFarness)) { //Isn't the signal too far from the teeth?
								/*SUSPENDED 2*/gobjTrend->setPhase(enmPhases::phase_signal_appeared); //develop: incapsulate flagging this phase into the trend class; currently this phase can be switched either insdie alg or outside trend
								//KTB Alert("Alligator signal_appeared!");
								gobjTrend->trade_open();
								keyPressedOperation(gobjTrend->tradeActive_GetType()); //ChannelsTT connection.
							}
						}
					}
					break; //no signal yet? //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend
				
				case enmPhases::phase_signal_appeared:
					if (delete_old_trend()) OnTickAlg(); //Has not the old trend become obsolete? Restart the procedure //develop: unite the three events (trend + signal + trade): create a trend object on the first trade within the trend
					gobjTrend->trade_open(); //isn't the signal too far from the teeth, when the signal has appeared?
					keyPressedOperation(gobjTrend->tradeActive_GetType()); //ChannelsTT connection.
					break;
				
				case enmPhases::phase_signal_triggered:
					if (!gobjTrend->tradeActive_GetBEReached()) gobjTrend->tradeActive_SetBEReached(roundToPts(gobjTrend->tradeActive_GetProfit()) >= BreakEven); //check for a break even, unless reached yet
					else if (gobjTrend->tradeActive_GetProfit() <= 0) {
						gobjTrend->trade_close(); //exit, if returned to zero after a break even
						keyPressedOperation(BUYtoSELL(gobjTrend->tradeActive_GetType())); //ChannelsTT connection.
						break; //skip the below steps
					}
					if (gobjTrend->direc_reversed()) { //Direction reversed? Close the position, unless shifted to the bigger time frame, or otherwise shift it.
						/*KTB if (!gobjTrend->time_frame_shift())*/ gobjTrend->trade_close(); //Shifting rejected? Close the trade.
						keyPressedOperation(BUYtoSELL(gobjTrend->tradeActive_GetType())); //ChannelsTT connection.
					}
					break;
				
				case enmPhases::phase_end: 
					delete_old_trend(); 
					break;
				}

				if (CheckPointer(gobjTrend.get()) == ENUM_POINTER_TYPE::POINTER_DYNAMIC) gobjTrend->update_peak(Bid); //update the peak for a later use, if a trend exists. //develop: why not placing it at the top below gobjTrend->cobjAlg.getSave(gintIdx0)?
			}
			
			catch (const exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__); 
			}
		}

		//void OnInitAlg(lua_State* L) { // Initialise the Alligator EA. +
		//		const long lngDelay = 0; //1000000;
		//		const long lngDelayLong = 0; //1000000000;
		//		GlobalVariableTemp(mstrDelay);
		//		GlobalVariableSet(mstrDelay, lngDelay);
		//		GlobalVariableTemp(mstrDelayLong);
		//		GlobalVariableSet(mstrDelayLong, lngDelayLong);
		//}

		//void OnDeinit(const int reason) { if (CheckPointer(gobjTrend.get()) == POINTER_DYNAMIC) gobjTrend.reset(); } //delete dynamically created objects
	}
}

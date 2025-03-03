#pragma once

#undef BLN_DISPLAY_MESSAGE_TO_QUIK

#undef BLN_ALG
#ifdef BLN_ALG
	#define BLN_ALG_SETTINGS_1
	#undef BLN_ALG_SETTINGS_2
#endif

#undef BLN_TRADE_IN_QUIK__FOR_QUIK_VS_MT4
#ifdef BLN_TRADE_IN_QUIK__FOR_QUIK_VS_MT4
	#define BLN_QUIK_SERVER //Initially: To test it for debugging: undefine it. //Currently: #define for Quik but #undef for MT4.
#endif 

#undef BLN_TEST_TRADE_SR_EVENING //To test it in the evening session.

//To test it for debugging in Quik when there are no quotes. 
//An error appeared in course of introducing namespaces at command:
//gobjTrend = std::make_unique<trend>(Bid) 
//in alligatorEA.cpp\OnTickAlg(). The error persists despite switching off the intorduced namespaces. 
//To debug it compare the current project with its version MTQC 170730 2000 - Before 3 projects to 2 - Full.
#undef BLN_TEST_NO_QUOTES_ERROR //CHECK: To debug it compare the current project with its version MTQC 170730 2000 - Before 3 projects to 2 - Full.

//#undef BLN_NO_TAPE // If the tape (таблица обезличенных сделок в Quik) is off the OnAllTrade function in MT4QuikConnector.cpp is not called. Therefore the stock price is not being set. Set it manually.

#undef BLN_TRADE_IN_SMARTX //Trade in SmartX.
#ifdef BLN_TRADE_IN_SMARTX
	#define SMARTX_VER_5_7_365 57365 //The SmartX versions.
	#define SMARTX_VER_5_7_637 57637
	#define SMARTX_ACTIVE_VER SMARTX_VER_5_7_365 //The active version.
	#define SMARTX_SBER_ABOVE //The position of SBER is above/below of SR in the Comparative Ticker list.
#endif

#define BLN_TRADE_IN_MT5
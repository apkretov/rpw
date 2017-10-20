#pragma once

#undef BLN_DISPLAY_MESSAGE_TO_QUIK

#undef BLN_ALG
#ifdef BLN_ALG
	#define BLN_ALG_SETTINGS_1
	#undef BLN_ALG_SETTINGS_2
#endif

#define BLN_QUIK_SERVER //To test it for debugging: undefine it.
#undef BLN_TRADE_SR //To test it in the evening session.
#undef BLN_TEST_NO_QUOTES_ERROR //To test it for debugging in Quik when there are no quotes. //An error appeared in course of intorducing namespaces at command gobjTrend = std::make_unique<trend>(Bid) in alligatorEA.cpp\OnTickAlg(). The error persists despite switching off the intorduced namespaces. To debug it compare the current project with its version MTQC 170730 2000 - Before 3 projects to 2 - Full.

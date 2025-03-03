#include "stdafx.h"
#include "switch.h"
#include <Windows.h>
#include "AutoItX3_DLL.h"
#include <stdio.h>
#include <exception>
#include <string>
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;
#include "functions.h"
using namespace mtqc::functions;
using std::wstring;
#include <bitset>

namespace mtqc {
	namespace mt4SmartXConnector {

		static constexpr LPCWSTR mchrOrderEntry = L"Order Entry";
		static constexpr LPCWSTR mchrUpUp = L"{UP}{UP}"; //Move upwords a list.
		static constexpr LPCWSTR mchrDownDown = L"{DOWN}{DOWN}"; //Move downwords a list.
		static constexpr int mintTitleSize = 256; //The size of the MT title.
		static wchar_t mchrMT4Title[mintTitleSize];

		static void messageException(const std::exception& objException, const char* chrFunction, long double lngLine) { // Dislplay an exception. 
			using std::string;
			string strMessage =
				"An exception in " + string(chrFunction)
				+ ", line " + std::to_string(long(lngLine))
				+ (string(":\n") + objException.what());
			MessageBox(NULL, strMessage.c_str(), STR_PROJECT_NAME, MB_ICONERROR);
		}

		static bool bitAND(unsigned intTested, unsigned intPattern) { //Performs a bitwise AND operation for AU3 because BitAND is missing in AutoItX. Returns the value of the parameters bitwise-AND'ed together. //BitAND @ https://www.autoitscript.com/autoit3/docs/functions/BitAND.htm
			const unsigned int32Bits = sizeof(unsigned) * CHAR_BIT; //32 bits.
			std::bitset<int32Bits> objBits(intTested); // we need 32 bits, start with bit the pattern tested. // 3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/ //sizeof operator @ http://en.cppreference.com/w/cpp/language/sizeof //C numeric limits interface @ http://en.cppreference.com/w/cpp/types/climits
			return objBits.test((unsigned)sqrt(intPattern)); //Returns whether the bit at position pos is set (i.e., whether it is one). //std::bitset::test @ http://www.cplusplus.com/reference/bitset/bitset/test/
		}

		static bool bitAND(int intTested, int intPattern) { //Performs a bitwise AND operation for AU3 because BitAND is missing in AutoItX. Returns the value of the parameters bitwise-AND'ed together. //BitAND @ https://www.autoitscript.com/autoit3/docs/functions/BitAND.htm
			const unsigned int32Bits = sizeof(int) * CHAR_BIT; //32 bits.
			std::bitset<int32Bits> objBits(intTested); // Start with bit the pattern tested. // 3.8a — Bit flags and bit masks @ http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/ //sizeof operator @ http://en.cppreference.com/w/cpp/language/sizeof //C numeric limits interface @ http://en.cppreference.com/w/cpp/types/climits
			return objBits.test((unsigned)sqrt(intPattern)); //Returns whether the bit at position pos is set (i.e., whether it is one). //std::bitset::test @ http://www.cplusplus.com/reference/bitset/bitset/test/
		}

		static bool activateSmartX()/*3*/ { // Activeate the SmartX window.
			try {
				#if SMARTX_ACTIVE_VER==SMARTX_VER_5_7_365 //The SmartX title version dependent. //#if, #else, #elif è #endif @ http://www.c-cpp.ru/books/if-else-elif-i-endif
					constexpr LPCWSTR chrSmartX = L"SmartX™";
				#elif SMARTX_ACTIVE_VER==SMARTX_VER_5_7_637
					constexpr LPCWSTR chrSmartX = L"SMARTx";
				#endif

				AU3_WinGetTitle(L"[ACTIVE]", L"", mchrMT4Title, mintTitleSize);/*4*/ //MetaTrader. Retrieve the window title of the active window. //WinGetTitle @ https://www.autoitscript.com/autoit3/docs/functions/WinGetTitle.htm
				if (mchrMT4Title == L"")
					return false;
				
				HWND hndSmartX = AU3_WinGetHandle(chrSmartX, L"");
				if (hndSmartX == 0)
					return false;
				if (AU3_WinActivateByHandle(hndSmartX) == 0) //Activate SmartX.
					return false;
				if (AU3_WinWaitActiveByHandle(hndSmartX, 0) == 0) //For more robustness, check if the window gets active.
					return false;
				return true; //Succeeded.
			}
			catch (const std::exception& objException) {
				messageException(objException, __FUNCTION__, __LINE__);
				return false;
			}
		}

		static bool presetOrderEntry(bool blnPresetOrderEntry) { //Preset the Order Entry form only by activating it (blnPresetOrderEntry = false; IMPORTANT: Order Entry MUST BE OPENED!!!) or also completely (blnPresetOrderEntry = true) entering its header fields down to the instrument that are common for placing and canceling orders.
			try {
				constexpr LPCWSTR chrPortfolio = L"[NAME:PortfolioComboBox]"; //Portfolio.
				constexpr LPCWSTR chrInstrument = L"[NAME:nInstrumentBox]"; //Instrument.
				constexpr LPCWSTR chrCtrlT = L"^t"; //Ctrl+T
				constexpr int WIN_STATE_EXISTS(1); //Window exists //WinGetState @ https://www.autoitscript.com/autoit3/docs/functions/WinGetState.htm

				AU3_WinGetTitle(L"[ACTIVE]", L"", mchrMT4Title, mintTitleSize); //MetaTrader. Retrieve the window title of the active window. //WinGetTitle @ https://www.autoitscript.com/autoit3/docs/functions/WinGetTitle.htm
				if (mchrMT4Title == L"")
					return false;
				
				if (!blnPresetOrderEntry) {
					bool blnOrderEntryActive{};
					HWND hndOrderEntry = AU3_WinGetHandle(mchrOrderEntry, L"");
					if (hndOrderEntry != 0) {
						if (AU3_WinActivateByHandle(hndOrderEntry) != 0) { //Activate Order Entry. //Failure: 0 if window is not found or cannot be activated. @ https://www.autoitscript.com/autoit3/docs/functions/WinActivate.htm
							if (AU3_WinWaitActiveByHandle(hndOrderEntry, 0) != 0) //Check if the window gets active. //AU3_WinWaitActiveByHandle does not work as it should according to the documentation. AU3_WinGetStateByHandle is added below. While redundant this line is kept for more robustness.
								blnOrderEntryActive = bitAND(AU3_WinGetStateByHandle(hndOrderEntry), WIN_STATE_EXISTS); //Retrieves the state of a given window. //WinGetState @ https://www.autoitscript.com/autoit3/docs/functions/WinGetState.htm
						}
					}
					if (!blnOrderEntryActive)
						MessageBox(NULL, (wstringToString(wstring(mchrOrderEntry)) + " is not opened!").c_str(), STR_PROJECT_NAME, MB_ICONERROR);
					return blnOrderEntryActive;
				}
				else {
					if (!activateSmartX()) // Activeate the SmartX window.
						return false;
					AU3_Send(chrCtrlT); //Ctrl+T
					if (AU3_WinWaitActive(mchrOrderEntry, L"") == 0) //Wait for the Order Entry window.
						return false;
					if (AU3_ControlFocus(mchrOrderEntry, L"", chrPortfolio) == 0) //Portfolio.
						return false;
					AU3_Send(mchrDownDown); //ÂÐ17336-ÌÎ-01.
					if (AU3_ControlFocus(mchrOrderEntry, L"", chrInstrument) == 0) //Instrument.
						return false;
					AU3_Send(mchrDownDown); //SR.
					return true; //Succeeded.
				}
			}
			catch (const std::exception& objException) {
				messageException(objException, __FUNCTION__, __LINE__);
				return false;
			}
		}

		static void conditionBuySellMkt(int intOperation, LPCWSTR& chrInDecrease, LPCWSTR& chrBUY_SELL_MKT) { //Choose a condition, buy/sell button.
			const LPCWSTR chrBUY_MKT = L"[NAME:btnIQBuyMarket]"; //BUY MKT.
			const LPCWSTR chrSELL_MKT = L"[NAME:btnIQSellMarket]"; //SELL MKT.

			switch (intOperation) { //Choose a condition, buy/sell button 
			case OP_BUYLIMIT:
				chrInDecrease = mchrUpUp;
				chrBUY_SELL_MKT = chrBUY_MKT;
				break;
			case OP_SELLLIMIT:
				chrInDecrease = mchrDownDown;
				chrBUY_SELL_MKT = chrSELL_MKT;
				break;
			case OP_BUYSTOP:
				chrInDecrease = mchrDownDown;
				chrBUY_SELL_MKT = chrBUY_MKT;
				break;
			case OP_SELLSTOP:
				chrInDecrease = mchrUpUp;
				chrBUY_SELL_MKT = chrSELL_MKT;
				break;
			}
		}

		/*KTB
		static bool setLots(int intLots) { //Set the required number of lots in the Qty text box by clicking the lots buttons. The function is needed because the text box's name is not constant.
			const LPCWSTR chrLots0 = L"[NAME:nButton0lots]"; // O lots.
			const LPCWSTR chrLots5 = L"[NAME:nButton5lots]"; // 5 lots.

			if (AU3_ControlClick(mchrOrderEntry, L"", chrLots0, L"", 1, 0, 0) == 0) //First annul the current number of lots.
				return false;
			for (int i = 0; i < intLots; i++) { //Click the 5 lots button as many times as how many lots are required. The button must be set to 1 lot instead of 5 by default. The buttons must add but not repalce the lots.
				if (AU3_ControlClick(mchrOrderEntry, L"", chrLots5, L"", 1, 0, 0) == 0)
					return false;
			}
			return true;
		}*/

		static bool enterTextBox(const POINT& sttTextBox, LPCWSTR chrText) { // Enter a text box.
			if (AU3_MouseClick(L"primary", sttTextBox.x, sttTextBox.y, 1, 0) == 0) //Click the mouse on the texbox. //MouseClick @ https://www.autoitscript.com/autoit3/docs/functions/MouseClick.htm
				return false;
			AU3_Send(L"^a"); //Select the entire text box by Ctrl+A to overtype the text being set.
			AU3_Send(chrText); //Overtype the text.
			return true;
		}

		static void hideOrderEntry() { //Hide the Entry Order by pressing Shift+Ecs.
			wchar_t chrTitle[mintTitleSize];
			AU3_WinGetTitle(L"[ACTIVE]", L"", chrTitle, mintTitleSize); //Retrieve the window title of the active window. //WinGetTitle @ https://www.autoitscript.com/autoit3/docs/functions/WinGetTitle.htm
			if (chrTitle != L"") //It must be Entry Order to be hidden below.
				AU3_Send(L"+{ESC}"); //Hide the Entry Order by pressing Shift+Ecs.		
		}
	}
}

using namespace mtqc::mt4SmartXConnector;

// Place an order in SmartX. 
// Hide the Entry Order by pressing Shift+Ecs. 
// Pre-set all the controls, if neceessary (blnPresetOrderEntry), usually the first time an order is sent. Then leave it open for a faster entry w/o the presetting.
// The position of SBER is above/below (blnSberAbove = true/false) of SR in the Comparative Ticker list. //TO DO: More than 4 parameters do not work. Combine blnPresetOrderEntry & blnSberAbove in a bitwise code.
MTQC_API bool __stdcall placeOrderSX(int intOperation, int intLots, double dblPrice, bool blnPresetOrderEntry/*KTB, bool blnSberAbove*/) {
	try {
		const int intCountTabs = 6; //The number of tabs on the Order Entry form.
		const POINT sttQty = { 58 + 72 / 2, 119 + 16 / 2 }; //The coordinates of Qty.
		const POINT sttOrdersTab{ 4 + 100, 196 + 25 / 2 }; //The coordinates of Orders tab.
		const LPCWSTR chrComparativeTicker = L"[NAME:cbxIQCondSymbol]"; //Comparative Ticker.
		const POINT sttActionPriceOfIQOrder{ 226 + 84 / 2, 274 + 16 / 2 }; //The coordinates of Action-Price of IQ-order.
		const LPCWSTR chrCondition = L"[NAME:cbxIQCond]"; //Condition.
		const LPCWSTR chrBUY_MKT = L"[NAME:btnIQBuyMarket]"; //BUY MKT.
		const LPCWSTR chrSELL_MKT = L"[NAME:btnIQSellMarket]"; //SELL MKT.
		#ifdef SMARTX_SBER_ABOVE
				const LPCWSTR chrSberPosition = mchrUpUp; //The position of SBER is above SR in the Comparative Ticker list.
		#else
				const LPCWSTR chrSberPosition = mchrDownDown; //The position of SBER is below SR in the Comparative Ticker list.
		#endif

		LPCWSTR chrInDecrease{}, chrBuySellMkt{};
		
		if (!presetOrderEntry(blnPresetOrderEntry))
			return false;

		POINT sttPointCurrent{}; //Retrieve the current position of the mouse cursor to restore it after clicking on Order Entry.
		AU3_AutoItSetOption(L"MouseCoordMode", 2); //Sets the way coords are used: 2 = relative coords to the client area of the active window @ https://www.autoitscript.com/autoit3/docs/functions/AutoItSetOption.htm#MouseCoordMode
		if (AU3_error() != 0) //Exit on an error above.
			return false;
		AU3_MouseGetPos(&sttPointCurrent); //MouseGetPos @ https://www.autoitscript.com/autoit3/docs/functions/MouseGetPos.htm
		if (AU3_error() != 0) //Exit on an error above. //AU3_error() - AutoitX Help @ https://www.autoitscript.com/forum/topic/90733-autoitx-help/
			return false;

		if (!enterTextBox(sttQty, numberToWchar_t(intLots))) //Enter Qty.
			return false;
		if (blnPresetOrderEntry) { //Pre-set all the controls, if neceessary
			if (AU3_MouseClick(L"primary", sttOrdersTab.x, sttOrdersTab.y, 1, 0) == 0) //Click Orders tab. //MouseClick @ https://www.autoitscript.com/autoit3/docs/functions/MouseClick.htm
				return false;
		}
		if (AU3_ControlFocus(mchrOrderEntry, L"", chrComparativeTicker) == 0) //Comparative Ticker.
			return false;
		AU3_Send(chrSberPosition); //Ñáåðáàíê.

		if (!enterTextBox(sttActionPriceOfIQOrder, numberToWchar_t(dblPrice))) //Enter Action-Price of IQ-order.
			return false;
		if (AU3_MouseMove(sttPointCurrent.x, sttPointCurrent.y, 0) == 0) //Restore the initial position of the mouse cursor before clicking Action-Price of IQ-order. 
			return false;

		conditionBuySellMkt(intOperation, chrInDecrease, chrBuySellMkt); //Choose a condition, buy/sell button.
		if (AU3_ControlFocus(mchrOrderEntry, L"", chrCondition) == 0) //Condition.
			return false;
		AU3_Send(chrInDecrease); //Increase/Decrease
		if (AU3_ControlClick(mchrOrderEntry, L"", chrBuySellMkt, L"", 1, 0, 0) == 0) //BUY/SELL MKT. //AutoIt Scripting Tutorial 10B Automating Installers & Programs Part 2 @ https://www.youtube.com/watch?v=Qm_s7HMQUnw&index=12&list=PL4Jcq5zn02jKpjX0nqI1_fS7mEEb5tw6z //Not able to click the button on File Download with JWinAuto @ https://stackoverflow.com/questions/5801760/not-able-to-click-the-button-on-file-download-with-jwinauto
			return false;

		hideOrderEntry(); //Hide the Entry Order by pressing Shift+Ecs.
		return AU3_WinActivate(mchrMT4Title, L"") != 0; //Return to MetaTrader. //Failure: 0 if window is not found or cannot be activated. @ https://www.autoitscript.com/autoit3/docs/functions/WinActivate.htm
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
		return false;
	}
}

MTQC_API bool __stdcall cancelOrdersSX(int intOperationsCanceled, bool blnPresetOrderEntry) { //Cancel orders in SmartX: all, buys, or sells. Pre-set all the controls, if neceessary (blnPresetOrderEntry), usually the first time an order is sent. Then leave it open for a faster entry w/o the presetting.
	try {
		const LPCWSTR chrAllOrders = L"[NAME:nButtonAll]"; //All Orders.
		const LPCWSTR chrBuyOrders = L"[NAME:nButtonBuys]"; //Buy Orders.
		const LPCWSTR chrSellOrders = L"[NAME:nButtonSells]"; //Sell Orders.
		const int intOperationAll = OP_SELLSTOP + 1; //All orders flag.
		LPCWSTR chrOrders{};

		if (!presetOrderEntry(blnPresetOrderEntry))
			return false;
		switch (intOperationsCanceled) { //All, buys or sells.
		case intOperationAll:
			chrOrders = chrAllOrders;
			break;
		case OP_BUY:
			chrOrders = chrBuyOrders;
			break;
		case OP_SELL:
			chrOrders = chrSellOrders;
			break;
		}
		if (AU3_ControlClick(mchrOrderEntry, L"", chrOrders, L"", 1, 0, 0) == 0) //Click all, buys or sells. //AutoIt Scripting Tutorial 10B Automating Installers & Programs Part 2 @ https://www.youtube.com/watch?v=Qm_s7HMQUnw&index=12&list=PL4Jcq5zn02jKpjX0nqI1_fS7mEEb5tw6z //Not able to click the button on File Download with JWinAuto @ https://stackoverflow.com/questions/5801760/not-able-to-click-the-button-on-file-download-with-jwinauto
			return false;
		
		hideOrderEntry(); //Hide the Entry Order by pressing Shift+Ecs.
		return AU3_WinActivate(mchrMT4Title, L"") != 0; //Return to MetaTrader. //Failure: 0 if window is not found or cannot be activated. @ https://www.autoitscript.com/autoit3/docs/functions/WinActivate.htm
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
		return false;
	}
}

/*KTB
MTQC_API bool __stdcall keyPressedOperationSX(int intOperation) { //Buy/sell in SmartX via the Entry Order. IMPORTANT: The Entry Order MUST be opened and the Orders tab ACTIVE.
	try {
		#if SMARTX_ACTIVE_VER==SMARTX_VER_5_7_365 //The Buy/Sell buttons version dependent. //#if, #else, #elif è #endif @ http://www.c-cpp.ru/books/if-else-elif-i-endif
			const LPCWSTR chrButtons[] = { L"[NAME:btnBuy]", L"[NAME:btnSell]" };
		#elif SMARTX_ACTIVE_VER==SMARTX_VER_5_7_637
			const LPCWSTR chrButtons[] = { L"[NAME:nMarketBuy]", L"[NAME:nMarketSell]" };
		#endif
		return AU3_ControlClick(mchrOrderEntry, L"", chrButtons[intOperation], L"", 1, 0, 0) == 1; //Press a Buy/Sell button. //AutoIt Scripting Tutorial 10B Automating Installers & Programs Part 2 @ https://www.youtube.com/watch?v=Qm_s7HMQUnw&index=12&list=PL4Jcq5zn02jKpjX0nqI1_fS7mEEb5tw6z //Not able to click the button on File Download with JWinAuto @ https://stackoverflow.com/questions/5801760/not-able-to-click-the-button-on-file-download-with-jwinauto
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
		return false;
	}
}
*/

MTQC_API bool __stdcall keyPressedOperationSX(int intOperation) { // Buy/sell in SmartX via hotkeys. IMPORTANT: The Buy/Sell ("b"/"s") hotkey MUST be preset in SmartX.
	try {
		const LPCWSTR chrHotKeys[] = { L"b", L"s" };
		if (!activateSmartX())/*2*/ // Activeate the SmartX window.
			return false;
		AU3_Send(chrHotKeys[intOperation]);
		return AU3_WinActivate(mchrMT4Title, L"") != 0; //Return to MetaTrader. //Failure: 0 if window is not found or cannot be activated. @ https://www.autoitscript.com/autoit3/docs/functions/WinActivate.htm
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
		return false;
	}
}

MTQC_API void __stdcall altDown(int _) { // Press and hold Alt.
	try {
		AU3_Send(L"{ALTDOWN}"); //Holds the ALT key down until {ALTUP} is sent @ https://www.autoitscript.com/autoit3/docs/functions/Send.htm
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
	}
}

MTQC_API void __stdcall altUp(int _) { // Release Alt.
	try {
		AU3_Send(L"{ALTUP}"); //Holds the ALT key down until {ALTUP} is sent @ https://www.autoitscript.com/autoit3/docs/functions/Send.htm
	}
	catch (const std::exception& objException) {
		messageException(objException, __FUNCTION__, __LINE__);
	}
}

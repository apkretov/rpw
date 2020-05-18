using std::string;
using std::wstring;
#include "resource.h"
#include "1\constantsXMLv.h"

typedef mtqc::constantsXMLv* (__cdecl *constantsXMLvFactory)(); // A factory of constantsXMLv-implementing objects looks thus //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/

//__declspec(dllimport) wchar_t* __stdcall messsagToMTQC(wchar_t* pWCBuffer);
MTQC_API wchar_t* __stdcall messsagToMTQC(wchar_t* pWCBuffer);

namespace mtqcWinAPI {
	static mtqc::constantsXMLv* mptrConstantsXMLv{}; //Introducing C++11 Brace-Initialization - int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519
	static HINSTANCE mhndDll{};
	static HWND mhndMain{}; //Introducing C++11 Brace-Initialization - int *p{}; //initialized to nullptr @ http://www.informit.com/articles/article.aspx?p=1852519

	inline wstring stringToWstring(const string& str) { return wstring(str.cbegin(), str.cend()); } 

	void messageException(const std::exception& objException, const char* chrFunction, long double lngLine) { // Dislplay an exception. 
		string strMessage = "An exception in " + string(chrFunction) + ", line " + std::to_string(long(lngLine)) + (string(":\n") + objException.what());
		MessageBox(NULL, (stringToWstring(strMessage)).c_str(),	TEXT(STR_PROJECT_NAME), MB_ICONERROR);
	} 

	static void setDlgItemFloat(HWND hwnMain, int intIDC, double dblNumber) { //Thread: SetDlgItemText, SetDlgItemInt but for float values @ http://forums.codeguru.com/showthread.php?54002-SetDlgItemText-SetDlgItemInt-but-for-float-values 
		const int intMaxDigits = DBL_MAX_10_EXP + 2;
		wchar_t chrNumber[intMaxDigits]; //What is the maximum length in chars needed to represent any double value? @ http://stackoverflow.com/questions/1701055/what-is-the-maximum-length-in-chars-needed-to-represent-any-double-value
		swprintf(chrNumber, intMaxDigits, L"%0.7f", dblNumber); //sprintf : double precision in C @ http://stackoverflow.com/questions/1786497/sprintf-double-precision-in-c // Microsoft _stprintf warning \ This should work @ http://stackoverflow.com/questions/1293889/microsoft-stprintf-warning
		SetDlgItemText(hwnMain, intIDC, chrNumber);
	}

	void fillInStockFutures() { //Fill in the stock/future controls depending stock/futures traded. 
		switch (mptrConstantsXMLv->getTradeSR()) { //Fill in the stock/future controls depending stock/futures traded.
		case false:
			SetDlgItemText(mhndMain, IDC_STATIC_STOCK_FUTURES, L"Trading stock");
			CheckRadioButton(mhndMain, IDC_RADIO_STOCK, IDC_RADIO_FUTURES, IDC_RADIO_STOCK); //CheckRadioButton function @ https://msdn.microsoft.com/en-us/library/windows/desktop/bb761877(v=vs.85).aspx
			setDlgItemFloat(mhndMain, IDC_EDIT_POINT, mptrConstantsXMLv->getStockPoint());
			SetDlgItemText(mhndMain, IDC_EDIT_TAG_PRICE, mptrConstantsXMLv->getStockTagPrice().c_str());
			SetDlgItemText(mhndMain, IDC_EDIT_TAG_ALG, mptrConstantsXMLv->getStockTagAlg().c_str());
			break;
		case true:
			SetDlgItemText(mhndMain, IDC_STATIC_STOCK_FUTURES, L"Trading futures");
			CheckRadioButton(mhndMain, IDC_RADIO_STOCK, IDC_RADIO_FUTURES, IDC_RADIO_FUTURES);
			SetDlgItemInt(mhndMain, IDC_EDIT_POINT, mptrConstantsXMLv->getFuturesPoint(), FALSE);
			SetDlgItemText(mhndMain, IDC_EDIT_TAG_PRICE, mptrConstantsXMLv->getFuturesTagPrice().c_str());
			SetDlgItemText(mhndMain, IDC_EDIT_TAG_ALG, mptrConstantsXMLv->getFuturesTagAlg().c_str());
			break;
	}	}

	static void fillInControls() { 
		try {
			SetDlgItemText(mhndMain, IDC_EDIT_CLASSCODE, mptrConstantsXMLv->getCLASSCODE().c_str()); //That's all it takes to change the text contained in the control (this can be used for pretty much any control that has a text value associated with it, STATICs, BUTTONs and so on). @ http://winprog.org/tutorial/controls.html
			SetDlgItemText(mhndMain, IDC_EDIT_STOCK, mptrConstantsXMLv->getStock().c_str());
			SetDlgItemText(mhndMain, IDC_EDIT_FUTURES, mptrConstantsXMLv->getFutures().c_str());

			fillInStockFutures();

			SetDlgItemInt(mhndMain, IDC_EDIT_LOTS_TRADED, mptrConstantsXMLv->getLotsTraded(), FALSE);
			SetDlgItemInt(mhndMain, IDC_EDIT_LOTS_MAX, mptrConstantsXMLv->getLotsMax(), FALSE);

			SendDlgItemMessage(mhndMain, IDC_CHECK_TRADE_DISABLED, BM_SETCHECK, mptrConstantsXMLv->getTradeDisabled() ? BST_CHECKED : BST_UNCHECKED, NULL); //An alternative is SendMessage(handle of the control, BM_GETCHECK, IDC_CHECK_TRADE_DISABLED, NULL); //BM_SETCHECK message @ https://msdn.microsoft.com/en-us/library/windows/desktop/bb775989(v=vs.85).aspx
			SendDlgItemMessage(mhndMain, IDC_CHECK_ALL_MESSAGES, BM_SETCHECK, mptrConstantsXMLv->getAllMessages() ? BST_CHECKED : BST_UNCHECKED, NULL);

			SetDlgItemInt(mhndMain, IDC_EDIT_RESUME_RANGE, mptrConstantsXMLv->getResumeRange(), FALSE);
		}
		catch (const std::exception& objException) { messageException(objException, __FUNCTION__, __LINE__); }
	}

	static int readInt(int intIDC) { // Read an integer control. 
 		BOOL blnSuccess = false;
		int intFuturesPoint = GetDlgItemInt(mhndMain, intIDC, &blnSuccess, FALSE); //GetDlgItemInt() works much like GetDlgItemText(), except that instead of copying the string to a buffer, it converts it internally into an integer and returns the value to you. The third parameter is optional, and takes a pointer to a BOOL. Since the function returns 0 on failure, there is no way to tell just from that whether or not the function failed or the user just entered 0. If you are fine with a value of 0 in the event of an error, then feel free to ignore this parameter. @ http://winprog.org/tutorial/controls.html
		if (blnSuccess) return intFuturesPoint;
		else return 0;
	}

	static wstring readText(int intIDC) { // Read a text control. 
		int intLength = GetWindowTextLength(GetDlgItem(mhndMain, intIDC));
		if (intLength == 0) return L"";
		else { // Now we allocate, and get the string into our buffer
			wchar_t* chrBuffer;
			chrBuffer = (wchar_t*)GlobalAlloc(GPTR, intLength + 1);
			GetDlgItemText(mhndMain, intIDC, chrBuffer, intLength + 1); //Finally we can call GetDlgItemText() to retrieve the contents of the control into the memory buffer that we've just allocated. This call expects the size of the buffer INCLUDING the null terminator. The return value, which we ignored here, is the number of characters copied, NOT including the null terminator.... fun eh? :) @ http://winprog.org/tutorial/controls.html
			wstring strText = wstring(chrBuffer);
			GlobalFree((HANDLE)chrBuffer); // Dont' forget to free the memory! //You may be or become aware of a second set of APIs named LocalAlloc(), LocalFree(), etc... which are legacy APIs from 16-bit windows. In Win32, the Local* and Global* memory functions are identical. @ http://winprog.org/tutorial/controls.html
			return strText;
	}	}

	static void readStock() { //Read the stock controls. 
		mptrConstantsXMLv->setStockPoint(readText(IDC_EDIT_POINT));
		mptrConstantsXMLv->setStockTagPrice(readText(IDC_EDIT_TAG_PRICE));
		mptrConstantsXMLv->setStockTagAlg(readText(IDC_EDIT_TAG_ALG));
	}

	static void readFutures() { //Read the futures controls. 
		mptrConstantsXMLv->setFuturesPoint(readInt(IDC_EDIT_POINT));
		mptrConstantsXMLv->setFuturesTagPrice(readText(IDC_EDIT_TAG_PRICE));
		mptrConstantsXMLv->setFuturesTagAlg(readText(IDC_EDIT_TAG_ALG));
	}

	static void readControls() { //Read all the controls to save them on closing the dialogue.
		try {
			mptrConstantsXMLv->setCLASSCODE(readText(IDC_EDIT_CLASSCODE));
			mptrConstantsXMLv->setStock(readText(IDC_EDIT_STOCK));
			mptrConstantsXMLv->setFutures(readText(IDC_EDIT_FUTURES));
	
			switch (mptrConstantsXMLv->getTradeSR()) { //Read either stock or futures. //A better alternative is to rely on the radio buttons via BM_GETCHECK message @ https://msdn.microsoft.com/en-us/library/windows/desktop/bb775986(v=vs.85).aspx
			case false: readStock(); break;
			case true: readFutures(); break;
			}

			mptrConstantsXMLv->setLotsTraded(readInt(IDC_EDIT_LOTS_TRADED));
			mptrConstantsXMLv->setLotsMax(readInt(IDC_EDIT_LOTS_MAX));
	
			mptrConstantsXMLv->setResumeRange(readInt(IDC_EDIT_RESUME_RANGE));

			mptrConstantsXMLv->setTradeDisabled( SendDlgItemMessage(mhndMain, IDC_CHECK_TRADE_DISABLED, BM_GETCHECK, NULL, NULL) == BST_CHECKED ); //BM_GETCHECK message @ https://msdn.microsoft.com/en-us/library/windows/desktop/bb775986(v=vs.85).aspx
			mptrConstantsXMLv->setAllMessages( SendDlgItemMessage(mhndMain, IDC_CHECK_ALL_MESSAGES, BM_GETCHECK, NULL, NULL) == BST_CHECKED ); //BM_GETCHECK message @ https://msdn.microsoft.com/en-us/library/windows/desktop/bb775986(v=vs.85).aspx
		}
		catch (const std::exception& objException) { messageException(objException, __FUNCTION__, __LINE__); }
	}

	void centerDialogue() { //Center the dialogue at the screen. //Using Dialog Boxes \ Initializing a Dialog Box @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms644996(v=vs.85).aspx
		HWND hwndOwner;
		RECT rc, rcDlg, rcOwner;
		if ((hwndOwner = GetParent(mhndMain)) == NULL) hwndOwner = GetDesktopWindow(); // Get the owner window and dialog box rectangles. //Because an application can create a dialog box that has no owner, the procedure checks the returned handle and uses the GetDesktopWindow function to retrieve the desktop window handle, if necessary. //Using Dialog Boxes \ Initializing a Dialog Box @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms644996(v=vs.85).aspx
		GetWindowRect(hwndOwner, &rcOwner);
		GetWindowRect(mhndMain, &rcDlg);
		CopyRect(&rc, &rcOwner);
		OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); // Offset the owner and dialog box rectangles so that right and bottom values represent the width and height, and then offset the owner again to discard space taken up by the dialog box.
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);
		SetWindowPos(mhndMain, HWND_TOP, rcOwner.left + (rc.right / 2), rcOwner.top + (rc.bottom / 2), 0, 0/*Ignores size arguments.*/, SWP_NOSIZE); // The new position is the sum of half the remaining space and the owner's original position. 
	}

	static bool initConstantsXML() { // Initialise mptrConstantsXMLv-> //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/ 
		try {
			const wstring strDllName = L"MTQC.dll";
			const string strCreateConstantsXML = "createConstantsXML";
			//const string strCreateConstantsXML = "mtqc::createConstantsXML";
			mhndDll = ::LoadLibrary(strDllName.c_str()); //Load the DLL. //How to link explicitly to a DLL  - Load the DLL and obtain a module handle. @ https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll
			if (!mhndDll) MessageBox(NULL, (stringToWstring("Unable to load ") + strDllName).c_str(), TEXT(STR_PROJECT_NAME), MB_ICONERROR);
			else {
				constantsXMLvFactory fncConstantsXMLvFactory = reinterpret_cast<constantsXMLvFactory>(::GetProcAddress(mhndDll, strCreateConstantsXML.c_str())); // Get the function from the DLL //How to link explicitly to a DLL - Obtain a function pointer to each exported function that the application calls. @ https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll
				if (!fncConstantsXMLvFactory) {
					MessageBox(NULL, ((stringToWstring(string("Unable to load ") + strCreateConstantsXML + string(" from ")) + strDllName + L"!")).c_str(), TEXT(STR_PROJECT_NAME), MB_ICONERROR);
					::FreeLibrary(mhndDll); //How to link explicitly to a DLL - Done with the DLL. @ https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll
				} else {
					mptrConstantsXMLv = fncConstantsXMLvFactory(); // Ask the factory for a new object implementing the constantsXMLv interface //TO DO: Think of a smart pointer.
					mptrConstantsXMLv->readXML();
					return true;
			}	}
			return false;
		}
		catch (const std::exception& objException) { 
			messageException(objException, __FUNCTION__, __LINE__);
			return false;
	}	}
}

using namespace mtqcWinAPI;

static BOOL CALLBACK DlgProc(HWND hndMain, UINT intMessage, WPARAM wParam, LPARAM lParam) { 
	try {
		mhndMain = hndMain;
		HICON hndIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_MTQC), IMAGE_ICON, 32, 32, 0); //Thread: Dialog Box Icon @ http://forums.codeguru.com/showthread.php?392013-Dialog-Box-Icon
		HICON hndIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_MTQC), IMAGE_ICON, 16, 16, 0);
		switch (intMessage) {
			case WM_INITDIALOG: { // This is where we set up the dialog box, and initialise any default values
				SendMessage(mhndMain, WM_SETICON, ICON_BIG, (LPARAM)hndIcon); //Thread: Dialog Box Icon @ http://forums.codeguru.com/showthread.php?392013-Dialog-Box-Icon
				SendMessage(mhndMain, WM_SETICON, ICON_SMALL, (LPARAM)hndIconSm);
				SetWindowText(mhndMain, TEXT(STR_PROJECT_NAME)); //How to change "Caption" of Dialog in run-time @ https://social.msdn.microsoft.com/Forums/vstudio/en-US/88618a9b-0ef2-4c6b-b674-7506c4fbae7d/how-to-change-caption-of-dialog-in-runtime?forum=vcgeneral
				if (initConstantsXML())	fillInControls(); //Fill in the controls, the constants object initialised.
				centerDialogue(); //Center the dialogue at the screen. 
				if (GetDlgCtrlID((HWND)wParam) != IDC_EDIT_CLASSCODE /*IDC_EDIT_RESUME_RANGE*/) { //Focus the first control in the window. //Using Dialog Boxes \ Initializing a Dialog Box @ https://msdn.microsoft.com/en-us/library/windows/desktop/ms644996(v=vs.85).aspx
					SetFocus(GetDlgItem(mhndMain, IDC_EDIT_CLASSCODE /*IDC_EDIT_RESUME_RANGE*/));
					return FALSE;
				}	
			} 
			break;
			case WM_COMMAND: //The WM_COMMAND message uses both, wParam contains two values, HIWORD(wParam) is the notification message (if applicable) and LOWORD(wParam) is the control or menu id that sent the message. @ http://winprog.org/tutorial/message_loop.html //As you may remember from our earlier discussion of the message loop, windows communicate using messages, you send them to get a control to do something, and when an event occurs on the control it will send you a notification message back. For the standard controls this notification will be a WM_COMMAND message as we've already seen with buttons and menus. For the Common Controls which I may get to later, it will be WM_NOTIFY. @ http://winprog.org/tutorial/controls.html
				switch (LOWORD(wParam)) {
					case IDC_RADIO_STOCK: //The stock settings selected to be displayed.
						if (mptrConstantsXMLv->getTradeSR()) { //Continue if the futures settings were displayed before.
							mptrConstantsXMLv->setTradeSR(false); //Remember all the futures settings.
							readFutures(); //Read the futures controls.
							fillInStockFutures(); //Fill in the stock/future controls depending stock/futures traded.
						}
						break;
					case IDC_RADIO_FUTURES:
						if (!mptrConstantsXMLv->getTradeSR())	{ //Continue if the stock settings were displayed before.
							mptrConstantsXMLv->setTradeSR(true); //Remember all the futures settings.
							readStock(); //Read the stock controls.
							fillInStockFutures(); //Fill in the stock/future controls depending stock/futures traded.
						}
						break;
					case IDOK: {
						//const wstring strRefreshConstants = L"C"; //The Refreshs Constants command.
						//const wstring strRefreshConstants = L"cmdRC"; //The Refreshs Constants command.
						//char* const chrRefreshConstants = "cmdRC"; //The Refreshs Constants command.
						wchar_t* const chrRefreshConstants = L"cmdRC"; //The Refreshs Constants command.
						readControls(); //Despite WM_CLOSE case seems a better choice leave this command here because the dialogue closes more stable this way.
						mptrConstantsXMLv->writeXML(); //Try a parallel thread. If it succeeds a flag will get true. Otherwise another thread will start. Maybe, a loop like below migtht be needed.
						//messsagToMTQC(const_cast<wchar_t*>(strRefreshConstants.c_str()));
						messsagToMTQC(chrRefreshConstants);
					} 
					case IDCANCEL: EndDialog(mhndMain, 0); break;
				} 
				break;
			case WM_CLOSE:	EndDialog(mhndMain, 0); break;
			case WM_DESTROY: 
				mptrConstantsXMLv->destroy(); // Destroy it explicitly
				::FreeLibrary(mhndDll); //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/ 
				mhndDll = nullptr;
				DestroyIcon(hndIcon); //Thread: Dialog Box Icon @ http://forums.codeguru.com/showthread.php?392013-Dialog-Box-Icon
				DestroyIcon(hndIconSm);
				break;
			default: return FALSE;
		}	
	}
	catch (const std::exception& objException) { messageException(objException, __FUNCTION__, __LINE__); }	
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { 
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DlgProc); 
}
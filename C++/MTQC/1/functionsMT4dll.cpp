#include "AutoItX3_DLL.h"

namespace mtqc {
	namespace functionsMT4dll {
		static std::string wchar_tToString(const wchar_t *s, char chrDefault = '?', const std::locale& loc = std::locale()) { // Convert from wchar_t to char. //"How do I convert wchar_t* to std::string?" @ http://stackoverflow.com/questions/4339960/how-do-i-convert-wchar-t-to-stdstring
			std::ostringstream stm;
			while (*s != L'\0') stm << std::use_facet<std::ctype<wchar_t>>(loc).narrow(*s++, chrDefault);
			return stm.str();
		}
	}
}

//CHECKED: 1) The input is non-const due to MT4. 2) Outside the mtqc namespace due to MT4. 
// Copy text to clipboard. @ http://www.cplusplus.com/forum/beginner/14349/ 
MTQC_API void __stdcall textToClipboard(wchar_t* chrText) { 
	const std::string &s = mtqc::functionsMT4dll::wchar_tToString(chrText);
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

/*KTB Before using the function make sure no memory leak happends due to the charToWchar_t function.
// Get Clipboard Text as String. The empty wchar_t* _ is needed just for MT4 to get connected. @ 
//http://cboard.cprogramming.com/windows-programming/103976-get-clipboard-text-string.html 
//http://www.codeproject.com/Articles/2242/Using-the-Clipboard-Part-I-Transferring-Simple-Tex
MT4_EXPFUNC wchar_t* __stdcall textFromClipboard(wchar_t* _) { 
	HANDLE h;
	wchar_t* strText = L""; //KTB wchar_t* strText = charToWchar_t(""); //Initialize it with an empty string.
	
	if (OpenClipboard(NULL)) {  // Test to see if we can open the clipboard first.
		h = GetClipboardData(CF_TEXT); // Retrieve the Clipboard data (specifying that we want ANSI text (via the CF_TEXT value).
		strText = charToWchar_t((char*)h); //retrieve a pointer to the data associated with the handle returned from GetClipboardData.
		
		// Finally, when finished I simply close the Clipboard which has the effect of unlocking it so that other applications can examine or modify its contents.
		CloseClipboard();  
	}
	return strText;
}
*/

#include "display.h"
MTQC_API void __stdcall saveSizePicture(wchar_t* chrPictureName) { //Save a picture and make its size actual in Windows Photo Viewer
	const LPCWSTR chrTitleSaveAs = L"Save As"; //The Save As dialogue box title.
	const LPCWSTR chrCmdSave = L"[CLASS:Button; INSTANCE:1]"; //The Save button in the Save As dialogue box.
	const LPCWSTR chrCmdSaveCaption = L"&Save"; //The caption of the Save button in the Save As dialogue box.
	const LPCWSTR chrTxtFileName = L"[CLASS:Edit; INSTANCE:1]"; //The File name text box.
	const LPCWSTR chrCmdActualSize = L"[CLASS:Photos_ButtonEx; INSTANCE:11]"; //The Actual size button in Windows Photo Viewer.
	const int intTimeOut = 3;

	if (AU3_WinWaitActive(chrTitleSaveAs, L"", intTimeOut) == 0) //Wait for the Save As dialogue box.
		return;
	if (AU3_ControlSetText(chrTitleSaveAs, L"", chrTxtFileName, chrPictureName) == 0) //ControlSetText @ https://www.autoitscript.com/autoit3/docs/functions/ControlSetText.htm
		return; 
	if (AU3_ControlClick(chrTitleSaveAs, chrCmdSaveCaption, chrCmdSave, L"", 1, 0, 0) == 0) //Click the Save button.
		return;
	
	if (AU3_WinWaitActive(chrPictureName, L"", intTimeOut) == 0) //Activate the Windows Photo Viewer whose title must begin with the picture file name. //WinActivate @ https://www.autoitscript.com/autoit3/docs/functions/WinActivate.htm
		return;
	AU3_ControlClick(chrPictureName, L"", chrCmdActualSize, L"", 1, 0, 0); //Click the Actual size button.
}
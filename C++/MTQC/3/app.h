#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "resource.h"       // main symbols

class app : public CWinApp {
	wchar_t* cchrFilter = L"JSON files (*.json)|*.json;";
public:
	app();
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
};

//extern app theApp;
namespace mtqcMFC { extern app theApp; }

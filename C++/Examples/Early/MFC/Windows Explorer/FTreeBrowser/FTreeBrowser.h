
// FTreeBrowser.h : main header file for the FTreeBrowser application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFTreeBrowserApp:
// See FTreeBrowser.cpp for the implementation of this class
//

class CFTreeBrowserApp : public CWinApp
{
public:
	CFTreeBrowserApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFTreeBrowserApp theApp;


// mtqcMfc.h : main header file for the mtqcMfc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// app:
// See mtqcMfc.cpp for the implementation of this class
//

class app : public CWinApp
{
public:
	app();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern app theApp;

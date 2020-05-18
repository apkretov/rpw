
// 35 Using ActiveX with Wizards.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// DiaApp:
// See 35 Using ActiveX with Wizards.cpp for the implementation of this class
//

class DiaApp : public CWinApp
{
public:
	DiaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern DiaApp theApp;

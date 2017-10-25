
// Pr4.h : main header file for the Pr4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPr4App:
// See Pr4.cpp for the implementation of this class
//

class CPr4App : public CWinAppEx
{
public:
	CPr4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPr4App theApp;

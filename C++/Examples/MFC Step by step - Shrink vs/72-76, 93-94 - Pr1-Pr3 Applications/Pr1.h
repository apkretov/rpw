#pragma once // Pr1.h : main header file for the Pr1 application

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "resource.h"       // main symbols

class CPr1App : public CWinAppEx {
public:
	CPr1App();
	virtual BOOL InitInstance(); // Overrides
	virtual int ExitInstance();
	afx_msg void OnAppAbout(); // Implementation
	DECLARE_MESSAGE_MAP()
};

//ORIG extern CPr1App theApp;

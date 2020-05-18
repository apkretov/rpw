
// 63 Multithreading.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy63MultithreadingApp:
// See 63 Multithreading.cpp for the implementation of this class
//

class CMy63MultithreadingApp : public CWinApp
{
public:
	CMy63MultithreadingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy63MultithreadingApp theApp;
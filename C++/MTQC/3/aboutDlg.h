#pragma once
#include "afxwinappex.h"
#include "afxdialogex.h"

class aboutDlg : public CDialogEx {
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	aboutDlg();
	#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_ABOUTBOX };
	#endif
};

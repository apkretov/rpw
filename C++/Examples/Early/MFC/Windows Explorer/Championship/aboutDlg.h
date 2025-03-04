#pragma once
#include "afxwinappex.h"
#include "afxdialogex.h"
// aboutDlg dialog used for App About

class aboutDlg : public CDialogEx
{
public:
	aboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

//BEGIN_MESSAGE_MAP(aboutDlg, CDialogEx)
//END_MESSAGE_MAP()

